#include "myqgraphicsview.h"
#include <QPointF>
#include <iostream>
#include <QDebug>
MyQGraphicsView::MyQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
}

MyQGraphicsView::~MyQGraphicsView()
{
    delete scene;
    delete arrow;
}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    double rad = 1;
    pt = mapToScene(event->pos());
    QGraphicsItem *item = itemAt(event->pos());
    if (!item){
        MyPoint *point = new MyPoint(pt.x(), pt.y(), rad*5.0, rad*5.0);
        pointlist.append(point);
        scene->addItem(point);
        arrow = scene->addLine(pt.x() + rad , pt.y() + rad, pt.x() , pt.y());
    }
    else {
        //добавить функционал перерисовки касательной
    }
}
void MyQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (arrow == NULL)
        return;
    else {
        QPointF currentpt = mapToScene(event->pos());
        scene->removeItem(arrow);
        arrow = scene->addLine(pt.x(), pt.y(), currentpt.x() , currentpt.y());
        MyPoint *point = pointlist.last();
        if(!point) {
            return;
        }
        else{
            qreal derivative;
            if (currentpt.x() - pt.x() == 0) derivative = 100;
            else derivative = (currentpt.y() - pt.y())/(currentpt.x() - pt.x());
            point->setDerivative(derivative);
        }
     }
}

void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(arrow == NULL)
        return;
    else{
       scene->removeItem(arrow);
       qDebug() << pointlist.last()->x() << pointlist.last()->y();
    }
}


MyPoint::MyPoint(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) :
    QGraphicsEllipseItem(0,0,width, height, parent)
{
    setPos(x, y);
    derivative = 0;
    setBrush(Qt::blue);
}
void MyPoint::setDerivative(qreal number)
{
    derivative = number;
}
void MyPoint::getDerivative()
{
    std::cout << derivative;
}

