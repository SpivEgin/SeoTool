#ifndef COMMANDABSTRACT_H
#define COMMANDABSTRACT_H
#include <QObject>

class QWebView;
class CommandAbstract : public QObject
{
public:
    CommandAbstract(QWebView *view);

    QWebView *view() const;
    void setView(QWebView *view);

    virtual void run() = 0;

private:
    QWebView *m_view;
};

#endif // COMMANDABSTRACT_H
