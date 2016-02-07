#ifndef SEARCHCMD_H
#define SEARCHCMD_H
#include "CommandAbstract.h"
#include <memory>

class DomainObject;
class KeywordObject;

class SearchSiteCmd : public CommandAbstract
{
    Q_OBJECT

public:
    enum ActiveMode
    {
        SearchInPage,
        StartSearch
    };

    SearchSiteCmd(QWebView *view, int domainID);
    virtual void run();

protected:
    void searchKeywordInPage();

protected slots:
    void startSearchSlot();
    void startSearch();
    void onLoadFinished(bool ok);
    void nextPage();
    void nextKeyword();

signals:
    void finished();

private:
    int m_pageNr = 1;
    std::shared_ptr<DomainObject> m_domainObject;
    QList<std::shared_ptr<KeywordObject> > m_keywords;
    int m_pageMax = 10;
    ActiveMode m_mode = StartSearch;

};

#endif // SEARCHCMD_H
