#ifndef KEYWORDOBJECT_H
#define KEYWORDOBJECT_H
#include <QString>
#include <QDate>

class KeywordObject
{
public:
    KeywordObject();

    QString name() const;
    void setName(const QString &name);

    int position() const;
    void setPosition(int position);

    int bestPosition() const;
    void setBestPosition(int value);

    int newPosition() const;
    void setNewPosition(int newPosition);

    QDateTime time() const;
    void setTime(const QDateTime &time);

    QDateTime bestPosTime() const;
    void setBestPosTime(const QDateTime &bestPosTime);

    int positionDiff() const;
    void setPositionDiff(int positionDiff);

    int domainID() const;
    void setDomainID(int domainID);

private:
    QString m_name;
    int m_position = -1;
    int m_bestPosition = -1;
    int m_newPosition = -1;
    QDateTime m_time;
    QDateTime m_bestPosTime;
    int m_positionDiff = 0;
    int m_domainID = -1;
};

#endif // KEYWORDOBJECT_H
