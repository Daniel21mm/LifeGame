#include "paint.h"

#include <QDebug>

Paint::Paint(QWidget *parent)
    :QOpenGLWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(33);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start();

}

void Paint::initializeGL()
{
    glClearColor(1.0,1.0,1.0,1.0);
}

void Paint::resizeGL(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glOrtho(0,1,0,1,1,-1);
}

void Paint::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.0,1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);

    for(int i(0); i < map.size() ; i++ )
    {
        for(int j(0); j < map[i].size() ; j++ )
        {
            if(map[i][j])
            {
            float_t x = ( 0.5 / map.size() )    * i +0.52; // делим и получаем сколько одна клетка, умножаем - это наша
            float_t y = ( 0.5 / map[i].size() ) * j +0.52; // КОСТЫЛЬ - узнать у Игоря и исправить

            glVertex3f(x,y,0.0);

            }
        }
    }

    glEnd();
}


void Paint::setMap(QVector<QVector<bool> > _map)
{
    map.resize(_map.size());

    for(int i(0); i < map.size(); i++ )
    {
        map[i].resize(_map[i].size());
    }

    for( int i(0); i <map.size() ; i++)
    {
        for(int j(0); j < map[i].size() ; j++)
        {
            map[i][j] = _map[i][j];
        }
    }
}

Paint::~Paint()
{

}



