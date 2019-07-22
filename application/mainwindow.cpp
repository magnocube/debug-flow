#include "mainwindow.h"

#include <visualcontextfilter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    initActionsConnections();

    serialNode = new SerialNode();
    m_ui->mdiArea->setViewMode(QMdiArea::TabbedView);

    WindowBase* window = new MdiWindow(m_ui->mdiArea);
    FilteredConsole* console = new FilteredConsole(window);
    console->addSubscription(serialNode);

    m_ui->actionConnect->setEnabled(true);

    nodeScene = new NodeScene();
    m_ui->nodesScene->setScene(nodeScene);

    itemsList = new ItemList(m_ui->resourceList,nodeScene);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
    UiUpdatetimer->start(30);
    m_ui->nodesScene->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);

}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete UiUpdatetimer;
}
void MainWindow::updateUI()
{
    nodeScene->update();
}
void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, serialNode, &SerialNode::openSerialPort);
}

