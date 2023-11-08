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


void igvEscena3D::verificarColision() {

    if (Primera_Generacion == true) {
        srand(time(NULL));

        apples.generarCoordsManzanas();
        bombs.generarCoordsBombas();

        Primera_Generacion = false;
    }else if ((snake.getCoordX() >= apples.getCoordXManzana() - 0.25 && snake.getCoordX() <= apples.getCoordXManzana() + 0.25) &&
        (snake.getCoordY() >= apples.getCoordYManzana() - 0.25 && snake.getCoordY() <= apples.getCoordYManzana() + 0.25) &&
        (snake.getCoordZ() >= apples.getCoordZManzana() - 0.25 && snake.getCoordZ() <= apples.getCoordZManzana() + 0.25)) {

        apples.generarCoordsManzanas();
        bombs.generarCoordsBombas();

    }else if((snake.getCoordX() >= bombs.getCoordXBomba() - 0.25 && snake.getCoordX() <= bombs.getCoordXBomba() + 0.25) &&
             (snake.getCoordY() >= bombs.getCoordYBomba() - 0.25 && snake.getCoordY() <= bombs.getCoordYBomba() + 0.25) &&
             (snake.getCoordZ() >= bombs.getCoordZBomba() - 0.25 && snake.getCoordZ() <= bombs.getCoordZBomba() + 0.25)){
                exit(1);
    }
}

void igvEscena3D::setEjeX(float rotacion) {
    ejeX += rotacion;
}

void igvEscena3D::setEjeY(float rotacion) {
    ejeY += rotacion;
}

igvSnake* igvEscena3D::getSnake(){
    return &snake;
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

    glRotated(ejeX, 1, 0, 0);
    glRotated(ejeY, 0, 1, 0);
    CrearEscenario();
    verificarColision();
    apples.crearManzana();
    bombs.crearBomba();
    snake.crearModelo();

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