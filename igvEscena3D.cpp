#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Métodos constructores

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
 * Método para pintar los ejes coordenados llamando a funciones de OpenGL
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

// Métodos públicos

// TODO: Apartado B: Métodos para visualizar cada parte del modelo

// TODO: Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo


/**
 * Método con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar ()
{  // crear luces
   GLfloat luz0[4] = { 5.0, 5.0, 5.0, 1 }; // luz puntual
   glLightfv ( GL_LIGHT0, GL_POSITION, luz0 ); // la luz se coloca aquí si permanece fija y no se mueve con la escena
   glEnable ( GL_LIGHT0 );

   // crear el modelo
   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   { pintar_ejes (); }

   CrearEscenario();

   //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena (también habría que desactivar la de arriba).



   // TODO: Apartado B: aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
   //       se recomienda crear una método auxiliar que encapsule el código para la visualización
   //       del modelo, dejando aquí sólo la llamada a ese método, así como distintas funciones una para cada
   //       parte del modelo.



   glPopMatrix (); // restaura la matriz de modelado
}

/**
 * Método para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * Método para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como parámetro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}




