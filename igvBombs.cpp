#include "igvBombs.h"

float igvBombs::getCoordXBomba(){
    return coordXBomba;
}

float igvBombs::getCoordZBomba(){
    return coordZBomba;
}

float igvBombs::generarAleatorioCoordXBombas() {
    int columna = rand() % columnas;

    float tamCasillaX = 4.0 / columnas;

    return coordXBomba = -2 + columna * tamCasillaX;
}

float igvBombs::generarAleatorioCoordZBombas() {
    int fila = rand() % filas;

    float tamCasillaZ = 4.0 / filas;

    return coordZBomba = -2 + fila * tamCasillaZ;
}

void igvBombs::generarCoordsBombas() {
    coordXBomba = generarAleatorioCoordXBombas();
    coordZBomba = generarAleatorioCoordZBombas();
}

void igvBombs::crearBomba() {
    GLfloat color_bomba[] = { 0,0,0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color_bomba);

    glPushMatrix();
    glTranslatef(coordXBomba, 0, coordZBomba);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}
