#include "mainwindow.h"
#include <QApplication>

//Решить проблему с выводом ( спросить у Игоря)
//Сделать ввод пользователя
//Докрутить интерфейс
//Добавить свои правила и сделать выбор режима в начале


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
