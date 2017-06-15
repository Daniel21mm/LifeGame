#include "mainwindow.h"


#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800,600);
    startGame();
}

void MainWindow::startGame()
{
    mainLayout = new QGridLayout(this);

    timeKey = new QLabel;
    timeKey->setText("Интервал обновления (мил-сек)");
    mainLayout->addWidget(timeKey,1,0);

    timeValue = new QLineEdit;
    timeValue->setText("1"); // delet
    mainLayout->addWidget(timeValue,1,1);

    setValue = new QPushButton;
    setValue->setText("Создать");
    connect(setValue,SIGNAL(clicked(bool)),this,SLOT(validityChecking()));
    mainLayout->addWidget(setValue,2,0,1,2);
}

void MainWindow::validityChecking()
{
    bool isOk(false);

    int _time  ( timeValue->text().toInt(&isOk));

    if( isOk && _time > 0 )
    {

        setValue->close();
        timeKey->close();
        timeValue->close();

        int _length_value = 40;
        int _width_value = 30;

        creater(_length_value, _width_value, _time );

    }
    else
    {
        if(!isOk || _time < 1 );
            timeValue->setText("Не корректно");
    }

}

void MainWindow::nextStatus()
{
    map->setMap(paint->getMap());

    map->buildNextStatus();

    if(map->isNotEnd())
    {
        map->activateNextStatusMap();
        paint->setMap(map->getMapForPrint());
    }
    else
    {
        paint->close();
        next->close();
        startTimer->close();
        stopTimer->close();
        draw->close();
        gameOver();
    }

}

void MainWindow::gameOver()
{
    gameEnd = new QLabel;
    gameEnd->setText("Игра закончена");
    QFont font = gameEnd->font();
    font.setPointSize(50);
    gameEnd->setFont(font);
    mainLayout->addWidget(gameEnd,0,0,1,2);

//    restart = new QPushButton;
//    restart->setText("Перезапуск в разработке");
////    connect(restart,SIGNAL(clicked(bool)),this,SLOT(startGame()));
////    connect(restart,SIGNAL(clicked(bool)),gameEnd,SLOT(close()));
////    connect(restart,SIGNAL(clicked(bool)),restart,SLOT(close()));
//    mainLayout->addWidget(restart,1,0);

}

void MainWindow::drawStatus(bool status)
{
    paint->setStatusDraw(status);
}


void MainWindow::creater(int _length_value ,int _width_value, int _time  )
{

    QVector < QVector < Cell > > _map(0);
    for(int i(0); i < _length_value ; i++ )
    {
        _map.push_back(QVector<Cell>(_width_value));
    }
    timer = new QTimer(this);
    timer->setInterval( _time );
    connect(timer,SIGNAL(timeout()),this,SLOT(nextStatus()));




    paint = new Paint;
    paint->setMap(_map);
    mainLayout->addWidget(paint,0,0,1,4);

    map = new Map;


    next = new QPushButton;
    next->setText("NEXT");
    connect(next, SIGNAL(clicked(bool)),this,SLOT(nextStatus()));
    mainLayout->addWidget(next,1,0);

    startTimer = new QPushButton;
    startTimer->setText("START");
    connect(startTimer,SIGNAL(clicked(bool)),timer,SLOT(start()));
    mainLayout->addWidget(startTimer,1,1);

    stopTimer = new QPushButton;
    stopTimer->setText("STOP");
    connect(stopTimer,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    mainLayout->addWidget(stopTimer,1,2);



    draw = new QRadioButton;
    draw->setText("DRAW");
    connect(draw,SIGNAL(toggled(bool)),this,SLOT(drawStatus(bool)));
    mainLayout->addWidget(draw,1,3);

}


MainWindow::~MainWindow()
{
    delete      map;

    //стартовое окно
    delete      timeKey;
    delete      timeValue;
    delete      setValue;

    //главное окно
    delete      paint;
    delete      next;
    delete      timer;
    delete      startTimer;
    delete      stopTimer;
    delete      draw;
    delete      mainLayout;


    //конец игры
    delete      gameEnd;
    //delete      restart;

}

