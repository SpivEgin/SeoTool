#ifndef OPENGOOGLE_H
#define OPENGOOGLE_H
#include "CommandAbstract.h"

class OpenGoogle : public CommandAbstract
{
    Q_OBJECT

public:
    OpenGoogle(QWebView *view);
    virtual void run();

protected slots:
    void onLoadFinished(bool ok);

signals:
    void loadFinished();
};

#endif // OPENGOOGLE_H
