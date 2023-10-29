#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{  private:
      // Atributos
      bool ejes = true;   ///< Indica si hay que dibujar los _ejes coordenados o no
      float ejeX = 0;
      float ejeY = 0;
      float giro_vert = 0;
      float giro_hor = 0;

      bool animacion = false;

      float coordX = 0;
      float coordY = 0;
      float coordZ = 0;

      float coordXManzana = 0;
      float coordYManzana = 0;
      float coordZManzana = 0;

      float coordXBomba = 0;
      float coordYBomba = 0;
      float coordZBomba = 0;

      bool Primera_Generacion = true;
      float num1 = 0;
      float num2 = 0;
      float num3 = 0;
      float num4 = 0;
      float num5 = 0;
      float num6 = 0;

      int contador = 0;

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
      void CrearManzanayBombas();
      void CrearTorsoSerpiente();
      void CrearCabezaSerpiente();
      void CrearOjosSerpiente();
      void CrearLenguaSerpiente();

      void crearModelo();

      void setEjeX(float rotacion);
      void setEjeY(float rotacion);

      float getEjeX();
      float getEjeY();

    //Movimiento de la serpiente
    void girarVert(float rot);
    void girarHor(float rot);
    float getGiroVert();
    float getGiroHor();

    void set_animacion(bool _animacion);
    bool get_animacion();

    void set_coordX(float cX);
    void set_coordY(float cY);
    void set_coordZ(float cZ);

    float get_coordX();
    float get_coordY();
    float get_coordZ();

    //Metodos para modificar y obtener la posicion de las manzanas
    void set_coordXManzana(float cX);
    void set_coordYManzana(float cY);
    void set_coordZManzana(float cZ);

    float get_coordXManzana();
    float get_coordYManzana();
    float get_coordZManzana();


    //Metodos para modificar y obtener la posicion de las bombas
    void set_coordXBomba(float cX);
    void set_coordYBomba(float cY);
    void set_coordZBomba(float cZ);

    float get_coordXBomba();
    float get_coordYBomba();
    float get_coordZBomba();

private:

    void pintar_ejes();
};

#endif   // __IGVESCENA3D
