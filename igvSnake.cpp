#include "igvSnake.h"

void igvSnake::CrearTorsoSerpiente() {
    GLfloat color_torso[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_torso);

    glPushMatrix();
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearCabezaSerpiente() {
    GLfloat color_cabeza[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_cabeza);

    glPushMatrix();
    glTranslated(0, 0, 1);
    glScaled(1.25, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearOjosSerpiente() {
    GLfloat color_ojos[] = { 1,1,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_ojos);

    glPushMatrix();
    glTranslated(0.5, 0.55, 1);
    glScaled(0.25, 0.1, 0.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.5, 0.55, 1);
    glScaled(0.25, 0.1, 0.25);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearLenguaSerpiente() {
    GLfloat color_lengua[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_lengua);

    glPushMatrix();
    glTranslated(0, 0, 1.75);
    glScaled(0.25, 0.1, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::crearModelo() {
    glTranslatef(coordX, coordY, coordZ);
    glRotatef(giro_hor,0,1,0);
    glRotatef(giro_vert,1, 0, 0);
    glScalef(0.25, 0.25, 0.25);
    CrearCabezaSerpiente();
    CrearOjosSerpiente();
    CrearLenguaSerpiente();
    CrearTorsoSerpiente();
}

void igvSnake::girarVert(float rot) {
    giro_vert += rot;
    if (giro_vert == -270) {
        giro_vert = 90;
    }
    if (giro_vert >= 270) {
        giro_vert = -90;
    }
}

void igvSnake::girarHor(float rot) {
    giro_hor += rot;
    if (giro_hor == -270) {
        giro_hor = 90;
    }
    if (giro_hor == 270) {
        giro_hor = -90;
    }
}

float igvSnake::getGiroVert() {
    return giro_vert;
}

float igvSnake::getGiroHor() {
    return giro_hor;
}

void igvSnake::set_animacion(bool _animacion) {
    if (_animacion == true)
        animacion = false;
    animacion = true;
}

bool igvSnake::get_animacion() {
    return animacion;
}

void igvSnake::setCoordX(float cX) {
    if (coordX > 1.35 || coordX < -1.35)
        coordX = -coordX;
    coordX += cX;
}

void igvSnake::setCoordY(float cY) {
    if (coordY > 1.35 || coordY < -1.35)
        coordY = -coordY;
    coordY += cY;
}

void igvSnake::setCoordZ(float cZ) {
    if (coordZ > 1.35 || coordZ < -1.35)
        coordZ = -coordZ;
    coordZ += cZ;
}

float igvSnake::getCoordX() {
    return coordX;
}

float igvSnake::getCoordY() {
    return coordY;
}

float igvSnake::getCoordZ() {
    return coordZ;
}
