#include "mainwindow.h"
#include <QApplication>
#include <myqgraphicsview.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MyQGraphicsView *view = new MyQGraphicsView;
    w.setGeometry(100, 100, 800, 800);
    w.setCentralWidget(view);
    w.show();
    int ret = a.exec();
    delete view;
    return ret;
}
