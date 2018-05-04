#include "myqgraphicsview.h"
#include <QPointF>
#include <iostream>
#include <QDebug>
//Вспомогательные функции для отрисовки полинома
qreal h1(qreal t)
{
    return 2*t*t*t - 3*t*t + 1;
}
qreal h3(qreal t)
{
    return t*t*t -2*t*t + t;
}
qreal h2(qreal t)
{
    return -2*t*t*t + 3*t*t;
}
qreal h4(qreal t)
{
    return t*t*t - t*t;
}

QPointF polynom(MyPoint* point1, MyPoint* point2, qreal t)
{
    QPointF first(point1->pos().x(), point1->pos().y());
    QPointF second(point2->pos().x(), point2->pos().y());
    return h1(t)*first + h3(t)*point1->getDerivative() + h2(t)*second + h4(t)*point2->getDerivative();
}

void MyQGraphicsView::drawSpline()
{
    if (pointlist.size() > 1){
        while(!linelist.isEmpty())
        {
            scene->removeItem(linelist.first());
            delete linelist.takeFirst();
        }
        QPointF bufpoint1(pointlist.first()->x(),pointlist.first()->y()), bufpoint2;
        for (int i = 0; i < pointlist.size() - 1; ++i){//цикл по парам точек
            for(qreal t = 0; t < 1; t += 0.02){//строим сплайн на каждом отрезке
                bufpoint2 = polynom(pointlist.at(i), pointlist.at(i+1), t);
                QGraphicsLineItem* line = scene->addLine(bufpoint1.x(), bufpoint1.y(), bufpoint2.x(), bufpoint2.y());
                linelist.append(line);
                bufpoint1 = bufpoint2;
            }
        }
    }
}

MyQGraphicsView::MyQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
}

MyQGraphicsView::~MyQGraphicsView()
{}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{//эта функция отвечает за добавление точек
    double rad = 1;
    pt = mapToScene(event->pos());
    if (!itemAt(event->pos())){
        MyPoint *point = new MyPoint(pt.x(), pt.y(), rad*12.0, rad*12.0);
        pointlist.append(point);
        lastpoint = point;
        scene->addItem(point);
    }
    else {
        for (int i = 0; i < pointlist.size(); ++i){
            QPointF distance(pointlist.at(i)->pos() - pt);
            if (distance.x()*distance.x() + distance.y()*distance.y() < 144){
                lastpoint = pointlist.at(i);
                if (event->button() == Qt::RightButton){
                    scene->removeItem(pointlist.at(i));
                    delete pointlist.takeAt(i);
                    drawSpline();
                    return;
                }
            }
        }

    }
    arrow = scene->addLine(pt.x() + rad , pt.y() + rad, pt.x() , pt.y()); //отрисовываем касательную
}
void MyQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{//эта функция отвечает за добавление касательных к точкам из списка и за отрисовку полинома с помощью linelist
    if (arrow == NULL)
        return;
    else {
        QPointF currentpt = mapToScene(event->pos());
        scene->removeItem(arrow);
        arrow = scene->addLine(pt.x(), pt.y(), currentpt.x() , currentpt.y());
        if(!lastpoint) {
            return;
        }
        else{
            QPointF derivative;
            if (currentpt.x() - pt.x() == 0) derivative = QPointF(0,1);
            else derivative = QPointF(currentpt.x() - pt.x(), currentpt.y() - pt.y());
            lastpoint->setDerivative(derivative);
        }
     }
    drawSpline();
}

void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(arrow == NULL)
        return;
    else{
       scene->removeItem(arrow);
    }
}


MyPoint::MyPoint(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) :
    QGraphicsEllipseItem(-5,-5,width, height, parent)
{
    setPos(x, y);
    derivative = QPointF(0,0);
    setBrush(Qt::green);
}
void MyPoint::setDerivative(QPointF number)
{
    derivative = number;
}
QPointF MyPoint::getDerivative()
{
    return derivative;
}

