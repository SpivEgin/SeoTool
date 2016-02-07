#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebFrame>
#include <QWebElement>
#include <QTimer>
#include "CommandAbstract.h"
#include "OpenGoogle.h"
#include "SearchSiteCmd.h"
#include "DatabaseConnector.h"
#include <QFileInfo>
#include <QSqlQueryModel>
#include <QWebView>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, SIGNAL(clicked(bool)), this, SLOT(startSearch()));

    m_view = new QWebView;
    DatabaseConnector databaseConnector("localhost", dbFile().absoluteFilePath(), "admin", "admin");
    databaseConnector.connect();


    m_domainsModel = std::shared_ptr<QSqlQueryModel>(new QSqlQueryModel);
    m_domainsModel->setQuery("SELECT * FROM Domains");
    m_domainsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_domainsModel->setHeaderData(1, Qt::Horizontal, tr("Domain"));

    ui->domainsView->setModel(m_domainsModel.get());
    ui->domainsView->resizeColumnsToContents();

    m_keywordsModel = std::shared_ptr<QSqlQueryModel>(new QSqlQueryModel);
    ui->keywordsView->setModel(m_keywordsModel.get());
    connect(ui->domainsView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onDomainIndexChanged(QModelIndex,QModelIndex)));
    std::shared_ptr<OpenGoogle>command(new OpenGoogle(m_view));
    connect(command.get(), SIGNAL(loadFinished()), this, SLOT(onPageLoaded()));
    runCommand(command);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runCommand(std::shared_ptr<CommandAbstract> command)
{
    m_command = command;
    m_command->run();
}

void MainWindow::onPageLoaded()
{

}

void MainWindow::startSearch()
{
    if(m_currDomainID <= 0)
        return;

    QSqlQuery query(QString("SELECT * FROM Domains WHERE ID= '%1'").arg(m_currDomainID));
    if(query.next())
    {
        std::shared_ptr<SearchSiteCmd>command(new SearchSiteCmd(m_view, m_currDomainID));
        connect(command.get(), SIGNAL(finished()), this, SLOT(onSearchFinished()));
        runCommand(command);
    }
}

void MainWindow::onDomainIndexChanged(QModelIndex curr, QModelIndex prev)
{
    QModelIndex index  = m_domainsModel->index(curr.row(), 0);
    m_currDomainID = index.data().toInt();
    m_keywordsModel->setQuery(QString("SELECT * FROM Keywords WHERE DomainID = '%1' ORDER BY Position DESC").arg(m_currDomainID));
    ui->keywordsView->resizeColumnsToContents();
}

void MainWindow::onSearchFinished()
{
    m_domainsModel->setQuery("SELECT * FROM Domains");
}

QFileInfo MainWindow::dbFile()
{
    QDir dbDir(qApp->applicationDirPath());

    #if defined(Q_OS_WIN)

    #elif defined(Q_OS_MAC)
        if (dbDir.dirName() == "MacOS") {
            dbDir.cdUp();
        }
        else{
            dbDir.cd(qApp->applicationName()+".app");
            dbDir.cd("Contents");
        }
    #endif
        if(!dbDir.cd("tools"))
            dbDir.mkdir("tools");
        dbDir.cd("tools");

        return QFileInfo (dbDir, "Database.db");
}
