//
// Created by miguel on 07/11/2023.
//

#include "igvBombs.h"

float igvBombs::getCoordXBomba(){
    return coordXBomba;
}

float igvBombs::getCoordYBomba(){
    return coordYBomba;
}

float igvBombs::getCoordZBomba(){
    return coordZBomba;
}

float igvBombs::generarAleatorioBombas(){
    return (-15 + rand() % 31) / 10.0;
}

void igvBombs::generarCoordsBombas() {
    coordXBomba = generarAleatorioBombas();
    coordYBomba = generarAleatorioBombas();
    coordZBomba = generarAleatorioBombas();
}

void igvBombs::crearBomba() {
    GLfloat color_bomba[] = { 0,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_bomba);

    glPushMatrix();
    glTranslatef(coordXBomba, coordYBomba, coordZBomba);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}
