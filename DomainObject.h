#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H
#include <QString>
#include <memory>
#include <QList>

class KeywordObject;

class DomainObject
{
public:
    DomainObject();
    DomainObject(int id);
    void loadKeywords();
    void updateKeywords();
    void addKeyword(std::shared_ptr<KeywordObject> keyword);

    QList<std::shared_ptr<KeywordObject> > keywords() const;
    QString name() const;
    QString googleDomain() const;

private:
    int m_ID = -1;
    QString m_name;
    QString m_googleDomain = "https://www.google.de";
    QList<std::shared_ptr<KeywordObject> > m_keywords;
};

#endif // DOMAINOBJECT_H
