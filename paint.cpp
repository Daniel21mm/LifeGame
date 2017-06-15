#include "paint.h"

#include <math.h>
#include <QDebug>

Paint::Paint(QWidget *parent)
    :QOpenGLWidget(parent), isDraw(false)
{
    timer = new QTimer(this);
    timer->setInterval(33);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start();

}

void Paint::initializeGL()
{
    glClearColor(0.0,0.0,0.0,1.0);
}

void Paint::resizeGL(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glOrtho(0,1,0,1,1,-1);
}

void Paint::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    double sizePoint = 15.0;
    glPointSize(sizePoint);
    glBegin(GL_POINTS);

    for(int i(0); i < sizeOx ; i++ )
    {
        for(int j(0); j < sizeOy ; j++ )
        {
            if(map[i][j].isLife())
            {
                float_t x = ( 0.5 / sizeOx )    * i +0.505; // делим и получаем сколько одна клетка, умножаем - это наша
                float_t y = ( 0.5 / sizeOy ) * j +0.505; // КОСТЫЛЬ - узнать у Игоря и исправить

                if(map[i][j].isVirus())
                    glColor3f(0.0,1.0,0.0);
                else
                    glColor3f(1.0,0.0,0.0);

                glVertex3f(x,y,0.0);

            }
        }
    }

    glEnd();
}

void Paint::mousePressEvent(QMouseEvent *me)
{
    if(isDraw)
    {
        if(me->button() == Qt::LeftButton)
        {
            double x = me->x()/( 770/sizeOx );
            if(x > sizeOx-1) x = sizeOx-1;

            double y = abs(( me->y()/( 540/sizeOy ) ) - sizeOy);
            if(y > sizeOy-1) y = sizeOy-1;

            qDebug()  << "x = " << x << " y = " << y << " Левая!";
            map[x][y].setNextStatus( !map[x][y].isLife());
            map[x][y].activateNextStatus();


        }

        //Для правой
        if(me->button() == Qt::RightButton)
        {
            double x = me->x()/( 777/sizeOx );
            if(x > sizeOx-1) x = sizeOx-1;

            double y = abs(( me->y()/( 545/sizeOy ) ) - sizeOy);
            if(y > sizeOy-1) y = sizeOy-1;
            qDebug()  << "x = " << x << " y = " << y << " Правая!";

            if(!map[x][y].isLife())
            {
                map[x][y].setNextStatus( !map[x][y].isLife());
                map[x][y].activateNextStatus();
            }
            map[x][y].setVirus(!map[x][y].isVirus());
        }
    }
}


void Paint::setMap(QVector<QVector<Cell> > _map)
{
    sizeOx = _map.size();
    sizeOy = _map[0].size();

    map.resize(sizeOx);

    for(int i(0); i < sizeOx; i++ )
    {
        map[i].resize(sizeOy);
    }

    for( int i(0); i <sizeOx ; i++)
    {
        for(int j(0); j < sizeOy ; j++)
        {
            map[i][j] = _map[i][j];
        }
    }
}

QVector<QVector<Cell> > Paint::getMap()
{
    return map;
}

void Paint::setStatusDraw(bool _isDraw)
{
    isDraw = _isDraw;
}

Paint::~Paint()
{

}



