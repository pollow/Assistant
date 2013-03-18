#include "mainwindow.h"
#include "dealer.h"
#include <QFile>

extern QMap<long long, cell> xxyy;
extern long long pt[50];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //List

    createAction();
    createMenu();
    createDock();
    setWindowTitle("helper");
}

void MainWindow::createDock()
{
    QDockWidget *dock1 = new QDockWidget;
    classes = new QListWidget(dock1);
    dock1->setWidget(classes);
    dock1->setAllowedAreas(Qt::RightDockWidgetArea);
    this->addDockWidget(Qt::RightDockWidgetArea,dock1);

    QDockWidget *dock2 = new QDockWidget;
    schedule = new QTableWidget(5,7,dock2);
    schedule->setItem(0,0,new QTableWidgetItem("Jan"));
    schedule->resizeColumnsToContents();
    schedule->resizeRowsToContents();
    dock2->setWidget(schedule);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock2);
}

void MainWindow::createAction()
{
    addClass = new QAction(tr("Add&Class"),this);
    connect(addClass,SIGNAL(triggered()),this,SLOT(addClass_clicked()));
    addTable = new QAction(tr("Add&Table"),this);
    connect(addTable,SIGNAL(triggered()),this,SLOT(addTable_clicked()));
    calc = new QAction(tr("&Calc"),this);
    connect(calc,SIGNAL(triggered()),this,SLOT(calc_clicked()));
}

void MainWindow::createMenu()
{
    opMenu = menuBar()->addMenu(tr("&Operate"));
    opMenu->addAction(addClass);
    opMenu->addAction(addTable);
    opMenu->addAction(calc);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::addClass_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),".",tr("All (*.*)"));
//    std::cerr << qPrintable(fileName) << std::endl;
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    dealer dd;
    QString tt;
    tt=dd.operate(&file,all);
    classes->addItem(tt);
}

void MainWindow::addTable_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),".",tr("All (*.*)"));
    //std::cerr << qPrintable(fileName) << std::endl;
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    dealer dd;
    dd.work(&file,over);
    std::vector<courses>::iterator p;
    for(p=over.begin();p!=over.end();p++)
    {
        QString tt='['+p->code+']'+p->cName;
        classes->addItem(tt);
    }
}

void MainWindow::calc_clicked()
{
//    std::vector<courses>::iterator p;
//    for(p=all.begin();p!=all.end();p++)
//        std::cerr << qPrintable(p->cName);
//    for(p=over.begin();p!=over.end();p++)
//        std::cerr << qPrintable(p->cName);
    getans.work(over,all);
//    qDebug() << "getans Finished! " << getans.ans.size() << endl;
    schedule->clear();
    for(std::vector<std::vector<courses>::iterator>::iterator i=getans.ans.begin();i!=getans.ans.end();i++)
    {
//        qDebug() << (*i)->cName << (*i)->tName << endl;
        long long tmp = (*i)->timeIndex;
        for(int j=0;j<36;j++)
        {
            if(tmp&pt[j])
            {
//                qDebug() << pt[j];
                cell tcell = xxyy.value(pt[j]);
//                QTableWidgetItem ttttt((*i)->cName+"</br>"+(*i)->location);
//                qDebug() << tcell.y << tcell.x << (*i)->cName+"\n"+(*i)->location;
                schedule->setItem(tcell.y-1,tcell.x,new QTableWidgetItem((*i)->cName+'\n'+(*i)->location));
                schedule->resizeColumnsToContents();
                schedule->resizeRowsToContents();
            }
        }
    }
}
