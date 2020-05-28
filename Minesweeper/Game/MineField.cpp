#include <stdio.h>
#include "MineField.h"
#include "GolMath.h"
#include <random>
#include <functional>   // std::bind
///#include <algorithm>    //std::find
#include <chrono>

MineField::MineField(){
}

void MineField::createMatrix(int r, int c)
{
    printf("reached point \n");
    for (int i = 0; i<r+2; i++)
    {
        std::vector<int> row;
        for(int j = 0; j<c+2; j++)
            row.push_back(0);
        m_extendedMatrix.push_back(row);
    }
    printf("reached point \n");
    for (int i = 0; i<r; i++)
    {
        std::vector<int> row;
        for(int j = 0; j<c; j++)
            row.push_back(0);
        m_mineMatrix.push_back(row);
    }
}

void MineField::layMine(int numberOfMines, PosRC startPosXY)
{
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<int> distribution(0,7);
    ///int dice_roll = distribution(generator);
    auto dice = std::bind ( distribution, generator );

    std::vector<PosRC> testMines;
    PosRC mineLoc;
    bool found = false;
    for (int i = 0; i<numberOfMines; )
    {
        mineLoc[0] = dice();
        mineLoc[1] = dice();
        for (unsigned int j = 0;j<testMines.size();j++)
        {   if(testMines[j].r == mineLoc[0] and testMines[j].c == mineLoc[1])
            {
                found = true;
                break;
            }
        }

        if (not found)
        {
            testMines.push_back(mineLoc);
            i++;
        }
        else found = false;
    }

    for (unsigned int j = 0;j<testMines.size();j++)
    {
        m_minePos.push_back(testMines[j]);
    }
    ///mineLoc[0] = 2;
    ///mineLoc[1] = 2;
    ///testMines.push_back(mineLoc);

    for (unsigned int i = 0; i<testMines.size(); i++)
    {
        m_extendedMatrix[testMines[i].r+1][testMines[i].c+1] = 13;
        m_extendedMatrix[testMines[i].r+1][testMines[i].c] += 1;
        m_extendedMatrix[testMines[i].r][testMines[i].c] += 1;
        m_extendedMatrix[testMines[i].r][testMines[i].c+1] += 1;
        m_extendedMatrix[testMines[i].r][testMines[i].c+2] += 1;
        m_extendedMatrix[testMines[i].r+1][testMines[i].c+2] += 1;
        m_extendedMatrix[testMines[i].r+2][testMines[i].c+2] += 1;
        m_extendedMatrix[testMines[i].r+2][testMines[i].c+1] += 1;
        m_extendedMatrix[testMines[i].r+2][testMines[i].c] += 1;
    }
    /**
    //Just for display...
    for (int r = 0; r < m_extendedMatrix.size(); r++)
    {
        for (int c = 0; c < m_extendedMatrix[r].size(); c++)
            printf("%d  ", m_extendedMatrix[r][c]);
        printf("\n");
    }
    */

    //copy to other matrix.
    for (unsigned int r = 0; r < m_mineMatrix.size(); r++)
    {
        for (unsigned int c = 0; c < m_mineMatrix[r].size(); c++)
            m_mineMatrix[r][c] = m_extendedMatrix[r + 1][c + 1];
    }

    /**
    for (int r = 0; r < m_mineMatrix.size(); r++)
    {
        for (int c = 0; c < m_mineMatrix[r].size(); c++)
            printf("%d  ", m_mineMatrix[r][c]);
        printf("\n");
    }
    */
}

std::vector<PosRC> MineField::getMineLocs()
{
    return m_minePos;
}

int MineField::getValue(int r, int c)
{
    return m_mineMatrix[r][c];
}

bool MineField::checkGlitch()
{
    return false;
}

void MineField::clear()
{
    m_extendedMatrix.clear();
    m_mineMatrix.clear();
    m_maxR = m_maxC = 0;
}
