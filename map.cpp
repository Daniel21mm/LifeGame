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

void Map::setMap(QVector<QVector<Cell> > map)
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
            _map[i][j].setNextStatus( map[i][j].isLife() );
            _map[i][j].setVirus(map[i][j].isVirus());
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

QVector<QVector<Cell> > Map::getMapForPrint()
{

    return _map;
}

void Map::buildNextStatus()
{
    for( int i(0); i <_map.size() ; i++)
    {
        for(int j(0); j < _map[i].size() ; j++)
        {
            _buildNextStatus(i, j);
            if(_map[i][j].isVirus() && _map[i][j].isLife())
                spreadDisease(i, j);
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

void Map::_spreadDisease(int x, int y)
{
    if( ( x > -1 ) && (x < _map.size()) && (y > -1 ) && ( y < _map[x].size()) )
    {
        //if(_map[x][y].isLife())
            _map[x][y].setVirus(true);
    }
}

void Map::spreadDisease(int x, int y)
{
    _spreadDisease( x - 1 , y - 1 );
    _spreadDisease( x - 1 , y     );
    _spreadDisease( x - 1 , y + 1 );
    _spreadDisease( x     , y + 1 );
    _spreadDisease( x + 1 , y + 1 );
    _spreadDisease( x + 1 , y     );
    _spreadDisease( x + 1 , y - 1 );
    _spreadDisease( x     , y - 1 );
}



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



