//
// Created by Jaime on 01/11/2023.
//

#include "board.h"

Board::Board() : boardValues(BOARD_FIELDS , 0){
    boardPositionInWorld = {0.0f, 0.0f, 0.0f};
}

Field Board::getFieldState(int x, int y, int z) const{
    return static_cast<Field>(boardValues.at(y * FLOOR_FIELDS + z * BOARD_SIDE_SIZEX + x));
}

Field Board::getFieldState(array<float, 3> pos) const
{
    return static_cast<Field>(boardValues.at(pos[1] * FLOOR_FIELDS + pos[2] * BOARD_SIDE_SIZEX + pos[0]));
}

array<float, 3> Board::calculateOffset(int x, int y, int z) const
{
    std::array<float, 3> offset;
    offset[0] = x * FIELD_SIZE_X;
    offset[1] = y * FIELD_SIZE_Y;
    offset[2] = z * FIELD_SIZE_Z;
    return offset;
}

void Board::setFieldState(int x, int y, int z, Field state)
{
    boardValues.at(y * FLOOR_FIELDS + z * BOARD_SIDE_SIZEX + x) = state;
}

void Board::setFieldState(std::array<int, 3> pos, Field state)
{
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];
    boardValues.at(y * FLOOR_FIELDS + z * BOARD_SIDE_SIZEX + x) = state;
}

void Board::setBoardInWorldPosition(array<float, 3> boardPositionInWorld)
{
    this->boardPositionInWorld = boardPositionInWorld;
}

array<float, 3> Board::getBoardPositionInWorld()
{
    return boardPositionInWorld;
}