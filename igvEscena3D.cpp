#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "igvEscena3D.h"

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{  GLfloat rojo[] = { 1, 0, 0, 1.0 };
   GLfloat verde[] = { 0, 1, 0, 1.0 };
   GLfloat azul[] = { 0, 0, 1, 1.0 };

   glMaterialfv ( GL_FRONT, GL_EMISSION, rojo );
   glBegin ( GL_LINES );
   glVertex3f ( 1000, 0, 0 );
   glVertex3f ( -1000, 0, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, verde );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 1000, 0 );
   glVertex3f ( 0, -1000, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, azul );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 0, 1000 );
   glVertex3f ( 0, 0, -1000 );
   glEnd ();
}


void igvEscena3D::CrearEscenario() {
    glPushMatrix();
    glScaled(3, 3, 3);
    glutWireCube(1);
    glPopMatrix();
}

void igvEscena3D::CrearManzanayBombas() {

    if (Primera_Generacion == true) {
        srand(time(NULL));

        num1 = (-14 + rand() % (15 + 14));
        num2 = (-14 + rand() % (15 + 14));
        num3 = (-14 + rand() % (15 + 14));
        num4 = (-14 + rand() % (15 + 14));
        num5 = (-14 + rand() % (15 + 14));
        num6 = (-14 + rand() % (15 + 14));
        num1 = num1 / 10;
        num2 = num2 / 10;
        num3 = num3 / 10;
        num4 = num4 / 10;
        num5 = num5 / 10;
        num6 = num6 / 10;

        set_coordXManzana(num1);
        set_coordYManzana(num2);
        set_coordZManzana(num3);
        set_coordXBomba(num4);
        set_coordYBomba(num5);
        set_coordZBomba(num6);

        Primera_Generacion = false;
    }

    if ((get_coordX() >= get_coordXManzana()-0.15 && get_coordX() <= get_coordXManzana() + 0.15) && (get_coordY() >= get_coordYManzana() - 0.15 && get_coordY() <= get_coordYManzana() + 0.15) && (get_coordZ() >= get_coordZManzana() - 0.15 && get_coordZ() <= get_coordZManzana() + 0.15)) {

        contador++;

        srand(time(NULL));

        num1 = (-15 + rand() % (16 + 15));
        num2 = (-15 + rand() % (16 + 15));
        num3 = (-15 + rand() % (16 + 15));
        num4 = (-15 + rand() % (16 + 15));
        num5 = (-15 + rand() % (16 + 15));
        num6 = (-15 + rand() % (16 + 15));
        num1 = num1 / 10;
        num2 = num2 / 10;
        num3 = num3 / 10;
        num4 = num4 / 10;
        num5 = num5 / 10;
        num6 = num6 / 10;

        set_coordXManzana(num1);
        set_coordYManzana(num2);
        set_coordZManzana(num3);
        set_coordXBomba(num4);
        set_coordYBomba(num5);
        set_coordZBomba(num6);

    }

    if ((get_coordX() >= get_coordXBomba()-0.15 && get_coordX() <= get_coordXBomba() + 0.15) && (get_coordY() >= get_coordYBomba() - 0.15 && get_coordY() <= get_coordYBomba() + 0.15) && (get_coordZ() >= get_coordZBomba() - 0.15 && get_coordZ() <= get_coordZBomba() + 0.15)) {
        exit(1);
    }

    GLfloat color_manzana[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_manzana);

    glPushMatrix();
    glTranslatef(get_coordXManzana(), get_coordYManzana(), get_coordZManzana());
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();

    GLfloat color_bomba[] = { 0,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_bomba);

    glPushMatrix();
    glTranslatef(get_coordXBomba(), get_coordYBomba(), get_coordZBomba());
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}

void igvEscena3D::CrearTorsoSerpiente() {
    GLfloat color_torso[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_torso);

    glPushMatrix();
    glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::CrearCabezaSerpiente() {
    GLfloat color_cabeza[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_cabeza);

    glPushMatrix();
    glTranslated(0, 0, 1);
    glScaled(1.25, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::CrearOjosSerpiente() {
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

void igvEscena3D::CrearLenguaSerpiente() {
    GLfloat color_lengua[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_lengua);

    glPushMatrix();
    glTranslated(0, 0, 1.75);
    glScaled(0.25, 0.1, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::crearModelo() {
    glTranslatef(get_coordX(), get_coordY(), get_coordZ());
    glRotatef(getGiroHor(),0,1,0);
    glRotatef(-getGiroVert(),1, 0, 0);
    glScalef(0.25, 0.25, 0.25);
    CrearCabezaSerpiente();
    glPushMatrix();
    CrearOjosSerpiente();
    glPopMatrix();
    CrearLenguaSerpiente();
    CrearTorsoSerpiente();
}

void igvEscena3D::setEjeX(float rotacion) {
    ejeX += rotacion;
}

void igvEscena3D::setEjeY(float rotacion) {
    ejeY += rotacion;
}

float igvEscena3D::getEjeX() {
    return ejeX;
}

float igvEscena3D::getEjeY() {
    return ejeY;
}

void igvEscena3D::girarVert(float rot) {
    giro_vert += rot;
    if (giro_vert == -270) {
        giro_vert = 90;
    }
    if (giro_vert >= 270) {
        giro_vert = -90;
    }
}

void igvEscena3D::girarHor(float rot) {
    giro_hor += rot;
    if (giro_hor == -270) {
        giro_hor = 90;
    }
    if (giro_hor == 270) {
        giro_hor = -90;
    }
}

float igvEscena3D::getGiroVert() {
    return giro_vert;
}

float igvEscena3D::getGiroHor() {
    return giro_hor;
}

void igvEscena3D::set_animacion(bool _animacion) {
    if (_animacion == true)
        animacion = false;
    animacion = true;
}

bool igvEscena3D::get_animacion() {
    return animacion;
}

void igvEscena3D::set_coordX(float cX) {
    if (coordX > 1.35 || coordX < -1.35)
        coordX = -coordX;
    coordX += cX;
}

void igvEscena3D::set_coordY(float cY) {
    if (coordY > 1.35 || coordY < -1.35)
        coordY = -coordY;
    coordY += cY;
}

void igvEscena3D::set_coordZ(float cZ) {
    if (coordZ > 1.35 || coordZ < -1.35)
        coordZ = -coordZ;
    coordZ += cZ;
}

float igvEscena3D::get_coordX() {
    return coordX;
}

float igvEscena3D::get_coordY() {
    return coordY;
}

float igvEscena3D::get_coordZ() {
    return coordZ;
}

void igvEscena3D::set_coordXManzana(float cX) {
    coordXManzana = cX;
}

void igvEscena3D::set_coordYManzana(float cY) {
    coordYManzana = cY;
}

void igvEscena3D::set_coordZManzana(float cZ) {
    coordZManzana = cZ;
}

float igvEscena3D::get_coordXManzana() {
    return coordXManzana;
}

float igvEscena3D::get_coordYManzana() {
    return coordYManzana;
}

float igvEscena3D::get_coordZManzana() {
    return coordZManzana;
}


void igvEscena3D::set_coordXBomba(float cX) {
    coordXBomba = cX;
}

void igvEscena3D::set_coordYBomba(float cY) {
    coordYBomba = cY;
}

void igvEscena3D::set_coordZBomba(float cZ) {
    coordZBomba = cZ;
}

float igvEscena3D::get_coordXBomba() {
    return coordXBomba;
}

float igvEscena3D::get_coordYBomba() {
    return coordYBomba;
}

float igvEscena3D::get_coordZBomba() {
    return coordZBomba;
}

void igvEscena3D::visualizar(void)
{  // crear luces
   GLfloat luz0[] = { 10, 8, 9, 1 }; // luz puntual
   glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
   glEnable ( GL_LIGHT0 );

   // crear el modelo
   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   { pintar_ejes (); }

    // Creacion del escenario
    glPushMatrix();
    glRotated(getEjeX(), 1, 0, 0);
    glRotated(getEjeY(), 0, 1, 0);
    CrearEscenario();
    glPopMatrix();

    // Creacion de las manzanas y las bombas
    glPushMatrix();
    glRotated(getEjeX(), 1, 0, 0);
    glRotated(getEjeY(), 0, 1, 0);
    CrearManzanayBombas();
    glPopMatrix();

    // Creacion del modelo de la serpiente
    glPushMatrix();
    glRotated(getEjeX(), 1, 0, 0);
    glRotated(getEjeY(), 0, 1, 0);
    crearModelo();
    glPopMatrix();

   glPopMatrix();
}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}