#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QList>

class MyPoint : public QGraphicsEllipseItem
{
public:
        explicit MyPoint(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = 0);
        void setDerivative(qreal number);
        void getDerivative();
private:
    qreal derivative;
};


class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    virtual ~MyQGraphicsView();
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    QGraphicsScene *scene;
    QGraphicsLineItem *arrow; //tangent line used for derivative calculation
    QPointF pt;
    QList<MyPoint*> pointlist;

};



#endif // MYQGRAPHICSVIEW_H
