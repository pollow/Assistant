#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <iostream>
#include <QFileDialog>
#include <QPushButton>
#include "dealer.h"
#include <QListWidget>
#include "search.h"

//namespace Ui {
//class MainWindow;
//}

struct cell
{
    int x,y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addClass_clicked();
    void addTable_clicked();
    void calc_clicked();

private:
    //Ui::MainWindow *ui;
    std::vector<courses> all;
    std::vector<courses> over;
    QListWidget preClass;
    QAction *addClass;
    QAction *addTable;
    QAction *calc;
    void createDock();
    //void creatCentral;
    void createAction();
    void createMenu();
    QMenu *opMenu;
    QListWidget *classes;
    QTableWidget *schedule;
    QStringList *cnamelist;
    search getans;

};

#endif // MAINWINDOW_H
