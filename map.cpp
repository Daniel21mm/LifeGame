#include "map.h"

Map::Map()
{

}

Map::Map(size_t height, size_t length)
{
    _map.resize(height);

    for(int i(0); i < _map.size(); i++ )
    {
        _map[i].resize(length);
    }

}

void Map::setMap(QVector<QVector<bool> > map)
{
    _map.resize(map.size());

    for(int i(0); i < _map.size(); i++ )
    {
        _map[i].resize(map[i].size());
    }

    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            _map[i][j].setNextStatus( map[i][j] );
            _map[i][j].activateNextStatus();
        }
    }
}

void Map::activateNextStatusMap()
{
    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            _map[i][j].activateNextStatus();
        }
    }
}

QVector<QVector < bool> > Map::getMapForPrint()
{
    QVector < QVector < bool > > map(_map.size());
    for(int i(0); i < map.size() ; i++ )
    {
        map[i].push_back(false);
        for(int j(1); j < _map[i].size(); j++ )
            map[i].push_back(false);
    }

    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            map[i][j] = _map[i][j].isLife();
        }
    }

    return map;
}

void Map::buildNextStatus()
{
    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            _buildNextStatus(i, j);
        }
    }
}

bool Map::isNotEnd()
{
    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            if( _map[i][j].isLife())
                return true;
            if(_map[i][j].isChangeStatus())
                return true;
        }
    }
    return false;
}


//
//---------------приватные методы----------
//


int Map::_checkingForLife(int x, int y)
{
    if( ( x > -1 ) && (x < _map.size()) && (y > -1 ) && ( y < _map[x].size()) )
    {
        if(_map[x][y].isLife())
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int Map::_sumLife(int x, int y)
{
    int sum_life(0);

    sum_life += _checkingForLife( x - 1 , y - 1 );
    sum_life += _checkingForLife( x - 1 , y     );
    sum_life += _checkingForLife( x - 1 , y + 1 );
    sum_life += _checkingForLife( x     , y + 1 );
    sum_life += _checkingForLife( x + 1 , y + 1 );
    sum_life += _checkingForLife( x + 1 , y     );
    sum_life += _checkingForLife( x + 1 , y - 1 );
    sum_life += _checkingForLife( x     , y - 1 );

    return sum_life;


}


void Map::_buildNextStatus(int x, int y)
{
    const int sum_life(_sumLife(x,y));

    if(_map[x][y].isLife())
    {
        if( ( sum_life == 2 ) || ( sum_life == 3 ) )
            _map[x][y].setNextStatus(true);
        else
            _map[x][y].setNextStatus(false);
    }
    else
    {
        if( sum_life == 3  )
            _map[x][y].setNextStatus(true);
        else
            _map[x][y].setNextStatus(false);
    }
}



