#include "OpenGoogle.h"
#include <QWebView>

OpenGoogle::OpenGoogle(QWebView *view):
    CommandAbstract(view)
{

}

void OpenGoogle::run()
{
    connect(view(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));

    view()->load(QUrl("http://google.de/"));
    view()->show();
}

void OpenGoogle::onLoadFinished(bool ok)
{
    if(ok)
        emit loadFinished();
}

