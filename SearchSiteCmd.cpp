#include "SearchSiteCmd.h"
#include <QWebPage>
#include <QWebView>
#include <QWebFrame>
#include <QWebElement>
#include <QTimer>
#include <QDebug>
#include "DomainObject.h"
#include "KeywordObject.h"
#include <stdlib.h>
#include <time.h>

SearchSiteCmd::SearchSiteCmd(QWebView *v, int domainID):
    CommandAbstract(v)
{
    m_domainObject = std::shared_ptr<DomainObject>(new DomainObject(domainID));
    m_domainObject->loadKeywords();
    m_keywords = m_domainObject->keywords();

    connect(view(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    view()->show();
}

void SearchSiteCmd::run()
{
    nextKeyword();
}

void SearchSiteCmd::nextPage()
{
    m_pageNr++;

    QWebElementCollection collection = view()->page()->mainFrame()->findAllElements("a[class=fl]");
    foreach (QWebElement paraElement, collection)
    {
        if(paraElement.toPlainText().toInt() == m_pageNr)
        {
//            paraElement.evaluateJavaScript("var evObj = document.createEvent('MouseEvents');evObj.initEvent( 'click', true, true );this.dispatchEvent(evObj);");
            paraElement.evaluateJavaScript("this.click()");
            m_mode = SearchInPage;
            break;
        }
    }
}

void SearchSiteCmd::nextKeyword()
{
    if(!m_keywords.isEmpty())
    {
        view()->load(QUrl(m_domainObject->googleDomain()));
        m_mode = StartSearch;
    }
    else
    {
        m_domainObject->updateKeywords();
        emit finished();
    }
}

void SearchSiteCmd::startSearchSlot()
{
    QTimer::singleShot(5000, this, SLOT(startSearch()));
}

void SearchSiteCmd::startSearch()
{
    if(!m_keywords.isEmpty())
    {
        view()->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
        m_pageNr = 1;
        QWebElement inputElement = view()->page()->mainFrame()->findFirstElement("input[name=q]");
        inputElement.setAttribute("value", m_keywords.last()->name());
        QWebElement buttonElement = view()->page()->mainFrame()->findFirstElement("input[name=btnG]");
        if(buttonElement.isNull())
            qDebug()<<"SearchSiteCmd::startSearch: kein Element mit: input[name=btnG]";
        else
        {
            view()->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
            buttonElement.evaluateJavaScript("this.click()");
            m_mode = SearchInPage;
        }
    }
}

void SearchSiteCmd::onLoadFinished(bool ok)
{
    if(ok)
    {
        switch(m_mode)
        {
        case SearchInPage:
            searchKeywordInPage();
            break;
        case StartSearch:
            startSearchSlot();
            break;
        }
    }
}

void SearchSiteCmd::searchKeywordInPage()
{
    QWebElementCollection collection = view()->page()->mainFrame()->findAllElements("h3[class=r]");
    if(collection.count()<1)
        return;

    int i =1;
    foreach (QWebElement paraElement, collection)
    {
        if(!paraElement.findFirst("a").isNull())
        {
            if(paraElement.findFirst("a").attribute("href").contains(m_domainObject->name()))
            {
                if(!m_keywords.isEmpty())
                {
                    m_keywords.last()->setNewPosition((m_pageNr-1)*10 + i);
                    m_keywords.removeLast();
                }
                nextKeyword();
            }
        }
        else
            qDebug()<< "SearchSiteCmd::onLoadFinished: kein <a> Element gefunden";
        i++;
    }
    if(m_pageMax == m_pageNr)
    {
        if(!m_keywords.isEmpty())
        {
            m_keywords.last()->setNewPosition(-1);
            m_keywords.removeLast();
        }
        nextKeyword();
    }
    else
    {
        int number;
        srand (time(NULL));
        number = rand() % 3000 + 2000;
        qDebug() << "SearchSiteCmd::searchKeywordInPage: random = " <<number;
        QTimer::singleShot(number, this, SLOT(nextPage()));
    }
}
