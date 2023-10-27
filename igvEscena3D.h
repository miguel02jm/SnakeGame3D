#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

/**
 * Partes del modelo
 */
enum parte
{	basex   ///< Identifica la base del modelo
   , cuerpoinferior   ///< Identifica el cuerpo inferior del modelo
   , cuerposuperior   ///< Identifica el cuerpo superior del modelo
   , brazo   ///< Identifica el brazo del modelo
};

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{  private:
      // Atributos
	   // TODO: Apartado C: añadir quí los atributos para el control de los grados de libertad del modelo

	   // Otros atributos
      bool ejes = true;   ///< Indica si hay que dibujar los ejes coordenados o no

   public:

      // Constructores por defecto y destructor
      igvEscena3D();
      ~igvEscena3D();

      // método con las llamadas OpenGL para visualizar la escena
      void visualizar();

      // TODO: Apartado B: Métodos para visualizar cada parte del modelo


      // TODO: Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo


      bool get_ejes ();
      void set_ejes ( bool _ejes );

   private:
      void pintar_ejes ();
      void CrearEscenario();

};

#endif   // __IGVESCENA3D
