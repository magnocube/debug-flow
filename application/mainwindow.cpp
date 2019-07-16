#include "mainwindow.h"

#include <visualcontextfilter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    itemList = new ItemList(m_ui->resourceList);
    initActionsConnections();

    serialNode = new SerialNode();
    m_ui->mdiArea->setViewMode(QMdiArea::TabbedView);

    WindowBase* window = new MdiWindow(m_ui->mdiArea);
    FilteredConsole* console = new FilteredConsole(window);
    console->addSubscription(serialNode);

    WindowBase* window2 = new MdiWindow(m_ui->mdiArea);
    FilteredConsole* console2 = new FilteredConsole(window2);
    console2->addSubscription(serialNode);

    m_ui->actionConnect->setEnabled(true);


    nodeScene = new NodeScene();
    m_ui->nodesScene->setScene(nodeScene);

    VisualSerialNode *node = new VisualSerialNode();
    nodeScene->addItem(node);

    VisualSerialNode *node2 = new VisualSerialNode();
    nodeScene->addItem(node2);

    VisualContextFilter* node3 = new VisualContextFilter();
    nodeScene->addItem(node3);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
    UiUpdatetimer->start(30);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete UiUpdatetimer;
}
void MainWindow::updateUI()
{
    //m_ui->nodesScene->fitInView(0, 0, 1000, 300, Qt::KeepAspectRatio);
    m_ui->nodesScene->setSceneRect(0, 0, 1000, 300);
    nodeScene->update();
}
void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, serialNode, &SerialNode::openSerialPort);
}

