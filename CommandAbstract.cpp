#include "CommandAbstract.h"

CommandAbstract::CommandAbstract(QWebView *view):
    m_view(view)
{

}

QWebView *CommandAbstract::view() const
{
    return m_view;
}

void CommandAbstract::setView(QWebView *view)
{
    m_view = view;
}
