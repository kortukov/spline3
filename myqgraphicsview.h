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
        void setDerivative(QPointF number);
        QPointF getDerivative();
private:
    QPointF derivative; //вектор производной
};


class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    virtual ~MyQGraphicsView();
    void drawSpline();
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    QGraphicsScene *scene;
    QGraphicsLineItem *arrow; //касательная, используется для ввода производной в точке
    QPointF pt; //точка на сцене в которой мы создаём базовую точку сплайна
    QList<MyPoint*> pointlist;
    MyPoint* lastpoint; //указатель на точку, для которой мы считаем касательную
    QList<QGraphicsLineItem*> linelist;
};



#endif // MYQGRAPHICSVIEW_H
