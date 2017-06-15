#ifndef PAINT_H
#define PAINT_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QVector>
#include <QMouseEvent>
#include <QPoint>

#include <cell.h>

class Paint : public QOpenGLWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = 0);
    ~Paint();

    void                          setMap(QVector< QVector < Cell > > _map);
    QVector<QVector<Cell>>        getMap();
    void                          setStatusDraw(bool);

protected:
    void                          initializeGL() override;
    void                          resizeGL(int w, int h) override;
    void                          paintGL() override;


    void                          mousePressEvent(QMouseEvent* me);   //Нажатие клавиши мыши


private:
    QTimer*                       timer;
    QVector<QVector<Cell>>        map;
    int                           sizeOx;
    int                           sizeOy;
    bool                          isDraw;


};


#endif // PAINT_H
