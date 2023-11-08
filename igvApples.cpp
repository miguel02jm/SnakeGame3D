//
// Created by miguel on 07/11/2023.
//

#include "igvApples.h"
#include <time.h>

float igvApples::getCoordXManzana() {
    return coordXManzana;
}

float igvApples::getCoordYManzana() {
    return coordYManzana;
}

float igvApples::getCoordZManzana() {
    return coordZManzana;
}

float igvApples::generarAleatorioManzanas() {
    srand(time(NULL));
    return (-15 + rand() % 31) / 10.0;
}

void igvApples::generarCoordsManzanas() {
    coordXManzana = generarAleatorioManzanas();
    coordYManzana = generarAleatorioManzanas();
    coordZManzana = generarAleatorioManzanas();
}

void igvApples::crearManzana() {
    GLfloat color_manzana[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_manzana);

    glPushMatrix();
    glTranslatef(coordXManzana, coordYManzana, coordZManzana);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}