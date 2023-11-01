//
// Created by Jaime on 01/11/2023.
//

#ifndef PR3B_BOARD_H
#define PR3B_BOARD_H

#include <vector>
#include <array>

#define BOARD_SIDE_SIZEX 10
#define BOARD_SIDE_SIZEY 10
#define BOARD_SIDE_SIZEZ 10

#define FIELD_SIZE_X 1
#define FIELD_SIZE_Y 1
#define FIELD_SIZE_Z 1

#define FLOOR_FIELDS BOARD_SIDE_SIZEX*BOARD_SIDE_SIZEZ
#define BOARD_FIELDS BOARD_SIDE_SIZEX*BOARD_SIDE_SIZEY*BOARD_SIDE_SIZEZ

using namespace std;

enum Field{
    empty = 0,
    snake = 1,
    food = 2,
    wall = 3,
};

class Board {
private:
    vector<char> boardValues;
    array<float, 3> boardPositionInWorld;

public:
    Board();

    Field getFieldState(int x, int y, int z) const;
    Field getFieldState(array<float, 3> pos) const;
    array<float, 3> calculateOffset(int x, int y, int z) const;

    void setFieldState(int x, int y, int z, Field state);
    void setFieldState(array<int, 3>, Field state);
    void setBoardInWorldPosition(array<float, 3> boardPositionInWorld);
    array<float, 3> getBoardPositionInWorld();



};


#endif //PR3B_BOARD_H
