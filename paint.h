#ifndef PAINT_H
#define PAINT_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QVector>

class Paint : public QOpenGLWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = 0);
    ~Paint();

    void        setMap(QVector< QVector < bool > > _map);

protected:
    void        initializeGL() override;
    void        resizeGL(int w, int h) override;
    void        paintGL() override;

private:
    QTimer* timer;
    QVector< QVector < bool > > map;

};


#endif // PAINT_H
