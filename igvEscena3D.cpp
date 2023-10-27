#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// M�todos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D ()
{  // TODO: Apartado C: inicializar los atributos para el control de los grados de libertad del modelo
}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D ()
{
}

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{	GLfloat rojo[] = { 1,0,0,1.0 };
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
    glScaled(5, 5, 5);
    glutWireCube(1);
    glPopMatrix();
}

// M�todos p�blicos

// TODO: Apartado B: M�todos para visualizar cada parte del modelo

// TODO: Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo


/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar ()
{  // crear luces
   GLfloat luz0[4] = { 5.0, 5.0, 5.0, 1 }; // luz puntual
   glLightfv ( GL_LIGHT0, GL_POSITION, luz0 ); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
   glEnable ( GL_LIGHT0 );

   // crear el modelo
   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   { pintar_ejes (); }

   CrearEscenario();

   //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).



   // TODO: Apartado B: aqu� hay que a�adir la visualizaci�n del �rbol del modelo utilizando la pila de matrices de OpenGL
   //       se recomienda crear una m�todo auxiliar que encapsule el c�digo para la visualizaci�n
   //       del modelo, dejando aqu� s�lo la llamada a ese m�todo, as� como distintas funciones una para cada
   //       parte del modelo.



   glPopMatrix (); // restaura la matriz de modelado
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
 * M�todo para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}




