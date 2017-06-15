#ifndef MAP_H
#define MAP_H

#include "cell.h"

#include <QVector>
class Map
{
public:
    Map();
    Map(size_t height , size_t length);

    void                            setMap(QVector < QVector < Cell > > map );
    void                            activateNextStatusMap();
    QVector < QVector < Cell > >    getMapForPrint();
    void                            buildNextStatus();
    bool                            isNotEnd();


private:
    typedef QVector < QVector <Cell > > _Map;
    _Map                            _map;

    void                            spreadDisease(int x, int y);
    void                            _spreadDisease(int x, int y);

    void                            _buildNextStatus(int x, int y);
    int                             _checkingForLife(int x, int y);
    int                             _sumLife(int x, int y);

};

#endif // MAP_H
