#ifndef INCLUDED_BOARD
#define INCLUDED_BOARD

#include <vector>
#include "GolMath.h"
class MineField
{
    int m_maxR = 0;
    int m_maxC = 0;
public:
    MineField();
    std::vector<std::vector<int>> m_extendedMatrix;
    std::vector<std::vector<int>> m_mineMatrix;
    std::vector<PosRC> m_minePos;

    void clear();
    void createMatrix(int r, int c);

    int getValue(int r, int c);
    void layMine(int numberOfMines, PosRC startPosXY);
    std::vector<PosRC> getMineLocs();
    bool checkGlitch();

};





#endif // INCLUDED_BOARD
