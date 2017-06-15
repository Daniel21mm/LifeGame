#include "cell.h"

Cell::Cell()
    :_is_life(false),_next_status(false),_is_virus(false)
{

}

Cell::Cell(bool is_life)
    :_is_life(is_life),_next_status(false),_is_virus(false)
{

}

Cell::Cell(const Cell &cell)
    :_is_life(cell._is_life),_next_status(cell._next_status),_is_virus(cell._is_virus)
{

}

bool Cell::isLife()
{
    return _is_life;
}

bool Cell::isVirus()
{
    return _is_virus;
}

void Cell::setVirus(bool virus)
{
    _is_virus = virus;
}

bool Cell::isChangeStatus()
{
    return (_is_life != _next_status);
}

void Cell::activateNextStatus()
{
    _is_life = _next_status;

    if(!_next_status)
        _is_virus = false;

    _next_status = false;
}


void Cell::setNextStatus(bool status)
{
    _next_status = status;
}


Cell& Cell::operator=(const Cell &cell)
{
    if (this == &cell)
    {
        return *this;
    }
    _is_life = cell._is_life;
    _next_status = cell._next_status;
    _is_virus = cell._is_virus;
    return *this;

}

Cell::~Cell()
{

}

