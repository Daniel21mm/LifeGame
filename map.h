#ifndef MAP_H
#define MAP_H

#include "cell.h"

#include <QVector>
class Map
{
public:
    Map();
    Map(size_t height , size_t length);

    void                            setMap(QVector < QVector < bool > > map );
    void                            activateNextStatusMap();
    QVector < QVector < bool > >    getMapForPrint();
    void                            buildNextStatus();
    bool                            isNotEnd();

private:
    typedef QVector < QVector <Cell > > _Map;
    _Map                            _map;

    void                            _buildNextStatus(int x, int y);
    int                             _checkingForLife(int x, int y);
    int                             _sumLife(int x, int y);

};

#endif // MAP_H
