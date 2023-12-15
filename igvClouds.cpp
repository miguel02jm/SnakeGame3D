#include "igvClouds.h"

void igvClouds::crearModelo() {
    GLfloat color_nube[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_nube);
        glPushMatrix();
        glutSolidCube(1);
        glPopMatrix();
}

void igvClouds::GenerarNubes() {
    glPushMatrix();
    glTranslatef(coordX, 2.5, -1);
    glScalef(2,0.25,1);
    crearModelo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-coordX, 2.5, 1);
    glScalef(2,0.25,1);
    crearModelo();
    glPopMatrix();
}

void igvClouds::setCoordX(float velNube){
    if(coordX < -5){
       coordX = 5;
    }
    coordX -= velNube;
}
