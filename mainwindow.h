#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QFileInfo>
#include <QDir>
#include <QModelIndex>

using std::shared_ptr;
class QWebView;

namespace Ui {
class MainWindow;
}

class CommandAbstract;
class QSqlQueryModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void runCommand(std::shared_ptr<CommandAbstract> command);

    QFileInfo dbFile();
protected slots:
    void onPageLoaded();
    void onDomainIndexChanged(QModelIndex curr, QModelIndex prev);
    void onSearchFinished();
    void startSearch();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<CommandAbstract> m_command;
    QWebView *m_view;
    std::shared_ptr<QSqlQueryModel> m_domainsModel;
    std::shared_ptr<QSqlQueryModel> m_keywordsModel;
    int m_currDomainID = -1;
};

#endif // MAINWINDOW_H
