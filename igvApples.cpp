//
// Created by miguel on 07/11/2023.
//

#include "igvApples.h"

float igvApples::getCoordXManzana() {
    return coordXManzana;
}

float igvApples::getCoordZManzana() {
    return coordZManzana;
}

float igvApples::generarAleatorioCoordXManzanas() {
    int columna = rand() % columnas;

    float tamCasillaX = 4.0 / columnas;

    return coordXManzana = -2 + columna * tamCasillaX;
}

float igvApples::generarAleatorioCoordZManzanas() {
    int fila = rand() % filas;

    float tamCasillaZ = 4.0 / filas;

    return coordZManzana = -2 + fila * tamCasillaZ;
}

void igvApples::generarCoordsManzanas() {
    coordXManzana = generarAleatorioCoordXManzanas();
    coordZManzana = generarAleatorioCoordZManzanas();
}

void igvApples::crearManzana() {
    GLfloat color_manzana[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_manzana);

    glPushMatrix();
    glTranslatef(coordXManzana, 0, coordZManzana);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}