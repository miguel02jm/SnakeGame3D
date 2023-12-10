#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>
#include <vector>
#include <cstring>
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

    float button1X = -2, button1Y = 0.75, buttonWidth = 4, buttonHeight = 0.75;
    float button2X = -2, button2Y = -0.75;
    float button3X = -2, button3Y = -2.25;

    float button4X = -0.8, button4Y = 1.3, button2Width = 1.75, button2Height = 0.4;
    float button5X = -0.8, button5Y = -0.5;
    float button6X = -0.8, button6Y = -2.35;

    GLfloat skin1[3] = { 0.1,0.4,0.1 };
    GLfloat skin2[3] = {1.0, 0.5, 0.5};
    GLfloat skin3[3] = {0.5, 0.5, 1.0};
    GLfloat skin[3] = { 0.1,0.4,0.1 };

    bool visualizandose=false;
public:
    // Constructores por defecto y destructor
    /// Constructor por defecto
    igvEscena3D () = default;
    /// Destructor
    ~igvEscena3D () = default;

    void visualizar();
    void visualizarMenu();
    void visualizarSkin();

    bool get_ejes ();

    void set_ejes ( bool _ejes );

    void CrearEscenario();

    void verificarColision();

    void setEjeX(float rotacion);
    void setEjeY(float rotacion);

    igvSnake* getSnake();

    void pintar_ejes();

    void setSkin1();
    void setSkin2();
    void setSkin3();

    bool getVisualizandose();
};

#endif   // __IGVESCENA3D
