#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell();
    Cell(bool is_life);
    Cell(const Cell& cell );
    ~Cell();

    bool            isLife();
    bool            isVirus();
    void            setVirus(bool);
    bool            isChangeStatus();
    void            setNextStatus(bool status);
    void            activateNextStatus();

   Cell&            operator =(const Cell& cell);

private:

    bool            _is_life;
    bool            _next_status;
    bool            _is_virus;
};

#endif // CELL_H
