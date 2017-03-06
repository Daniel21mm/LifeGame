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

    lengthKey = new QLabel;
    lengthKey->setText("Выстота ");
    mainLayout->addWidget(lengthKey,0,0);

    lengthValue = new QLineEdit;
    mainLayout->addWidget(lengthValue,0,1);

    widthKey = new QLabel;
    widthKey->setText("Ширина ");
    mainLayout->addWidget(widthKey,1,0);

    widthValue = new QLineEdit;
    mainLayout->addWidget(widthValue,1,1);

    timeKey = new QLabel;
    timeKey->setText("Интервал обновления (сек)");
    mainLayout->addWidget(timeKey,2,0);

    timeValue = new QLineEdit;
    mainLayout->addWidget(timeValue,2,1);

    setValue = new QPushButton;
    setValue->setText("Создать");
    connect(setValue,SIGNAL(clicked(bool)),this,SLOT(validityChecking()));
    mainLayout->addWidget(setValue,3,0,1,2);
}

void MainWindow::validityChecking()
{
    bool isOk1(false),isOk2(false),isOk3(false);

    int _length_value ( lengthValue->text().toInt(&isOk1));
    int _width_value (  widthValue->text().toInt(&isOk2) );
    int _time   ( timeValue->text().toInt(&isOk3));

    if( (isOk1 && isOk2 && isOk3) && (_length_value > 0 && _width_value > 0 && _time > 0) )
    {
        lengthKey->close();
        lengthValue->close();
        widthKey->close();
        widthValue->close();
        setValue->close();
        timeKey->close();
        timeValue->close();
        creater(_length_value, _width_value, _time );

    }
    else
    {
        if(!isOk1 || _length_value < 1)
            lengthValue->setText("Не корректно");
        if(!isOk2 || _width_value < 1)
            widthValue->setText("Не корректнно");
        if(!isOk3 || _time < 1 );
            timeValue->setText("Не корректно");
    }

}

void MainWindow::nextStatus()
{
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


void MainWindow::creater(int _length_value ,int _width_value, int _time  )
{


    // убрать после
    srand(time(NULL));
    QVector < QVector < bool > > _map(0);
    for(int i(0); i < _length_value ; i++ )
    {
        _map.push_back(QVector<bool>(_width_value));
    }

    for(int i(0); i < _map.size(); i++)
    {
        for(int j(0); j < _map[i].size(); j++ )
        {
            int tmp = rand()%10;
            if( tmp > 6 )
                _map[i][j]=true;
            else
                _map[i][j]=false;
        }
    }


    timer = new QTimer(this);
    timer->setInterval( _time * 1000 );
    connect(timer,SIGNAL(timeout()),this,SLOT(nextStatus()));


    map = new Map;
    map->setMap(_map);

    paint = new Paint;
    paint->setMap(_map);
    mainLayout->addWidget(paint,0,0,1,3);

    next = new QPushButton;
    next->setText("NEXT");
    connect(next, SIGNAL(clicked(bool)),this,SLOT(nextStatus()));

    startTimer = new QPushButton;
    startTimer->setText("START");
    connect(startTimer,SIGNAL(clicked(bool)),timer,SLOT(start()));
    mainLayout->addWidget(startTimer,1,1);

    stopTimer = new QPushButton;
    stopTimer->setText("STOP");
    connect(stopTimer,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    mainLayout->addWidget(stopTimer,1,2);

    mainLayout->addWidget(next,1,0);

}


MainWindow::~MainWindow()
{
    delete      map;

    //стартовое окно
    delete      lengthKey;
    delete      lengthValue;
    delete      widthKey;
    delete      widthValue;
    delete      timeKey;
    delete      timeValue;
    delete      setValue;

    //главное окно
    delete      paint;
    delete      next;
    delete      timer;
    delete      startTimer;
    delete      stopTimer;
    delete      mainLayout;


    //конец игры
    delete      gameEnd;
    //delete      restart;

}

