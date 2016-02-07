#include "DomainObject.h"
#include <QSqlQuery>
#include "KeywordObject.h"
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

DomainObject::DomainObject()
{

}

DomainObject::DomainObject(int id):
    m_ID(id)
{
    QSqlQuery query(QString("SELECT * FROM Domains WHERE ID=%1").arg(m_ID));
    if(query.next())
    {
        m_name = query.value("Name").toString();
        m_googleDomain = query.value("GoogleDomain").toString();
    }
}

void DomainObject::loadKeywords()
{
    QSqlQuery query(QString("SELECT * FROM Keywords WHERE DomainID='%1'").arg(m_ID));
    while (query.next()) 
    {
        QSqlRecord rec = query.record();
        std::shared_ptr<KeywordObject> keyword(new KeywordObject());
        keyword->setName(rec.value("Keyword").toString());
        keyword->setPosition(rec.value("Position").toInt());
        keyword->setTime(rec.value("Time").toDateTime());
        keyword->setBestPosition(rec.value("BestPosition").toInt());
        keyword->setBestPosTime(rec.value("BestPosTime").toDateTime());
        keyword->setPositionDiff(rec.value("PositionDiff").toInt());
        keyword->setDomainID(m_ID);

        m_keywords << keyword;
    }
}

void DomainObject::updateKeywords()
{
    QListIterator<std::shared_ptr<KeywordObject>>it(m_keywords);
    while(it.hasNext())
    {
        std::shared_ptr<KeywordObject> keyword = it.next();

        QSqlQuery updateQuery;
        updateQuery.prepare("INSERT OR REPLACE INTO Keywords (Keyword, Position, Time, BestPosition, BestPosTime, PositionDiff, DomainID)"
                         "VALUES (:Keyword, :Position, :Time, :BestPosition, :BestPosTime, :PositionDiff, :DomainID)");
        updateQuery.bindValue(":Keyword", keyword->name());
        updateQuery.bindValue(":Position", keyword->newPosition());
        updateQuery.bindValue(":Time", keyword->time().toString("dd.MM.yyyy - HH:mm"));
        updateQuery.bindValue(":BestPosition", keyword->bestPosition());
        updateQuery.bindValue(":BestPosTime", keyword->bestPosTime().toString("dd.MM.yyyy - HH:mm"));
        updateQuery.bindValue(":PositionDiff", keyword->positionDiff());
        updateQuery.bindValue(":DomainID", keyword->domainID());

        bool status = updateQuery.exec();

        if (!status) {
            qDebug() << "DomainObject::updateKeywords: Fehler bei DatabseUpdate";
        }
    }
}

void DomainObject::addKeyword(std::shared_ptr<KeywordObject> keyword)
{
    QListIterator<std::shared_ptr<KeywordObject>>it(m_keywords);
    while(it.hasNext())
    {
        if(it.next()->name() == keyword->name())
            return;
    }
    m_keywords << keyword;
}

QList<std::shared_ptr<KeywordObject> > DomainObject::keywords() const
{
    return m_keywords;
}

QString DomainObject::name() const
{
    return m_name;
}

QString DomainObject::googleDomain() const
{
    return m_googleDomain;
}
