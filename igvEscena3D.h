#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>
#include <vector>
#include "igvSnake.h"
#include "igvApples.h"
#include "igvBombs.h"

#endif   // defined(__APPLE__) && defined(__MACH__)

struct Segmento {
    float x, y, z;
};

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{  private:
      // Atributos
      bool ejes = true;   ///< Indica si hay que dibujar los _ejes coordenados o no
      float ejeX = 0;
      float ejeY = 0;

      bool Primera_Generacion = true;

      igvSnake snake;
      igvApples apples;
      igvBombs bombs;

    static const int filas = 10;
    static const int columnas = 10;
    int matrizEscenario[filas][columnas];

   public:
      // Constructores por defecto y destructor
      /// Constructor por defecto
      igvEscena3D () = default;
      /// Destructor
      ~igvEscena3D () = default;

      // Métodos
      // método con las llamadas OpenGL para visualizar la escena
      void visualizar ();

      bool get_ejes ();

      void set_ejes ( bool _ejes );

      void CrearEscenario();

      void verificarColision();

      void setEjeX(float rotacion);
      void setEjeY(float rotacion);

      igvSnake* getSnake();

      void pintar_ejes();
};

#endif   // __IGVESCENA3D
