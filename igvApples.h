#ifndef PR3B_IGVAPPLES_H
#define PR3B_IGVAPPLES_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)


class igvApples {

private:
    float coordXManzana = 0;
    float coordZManzana = 0;

    int filas = 10;
    int columnas = 10;

public:
    float getCoordXManzana();
    float getCoordZManzana();

    float generarAleatorioCoordXManzanas();
    float generarAleatorioCoordZManzanas();

    void generarCoordsManzanas();

    void crearManzana();
};


#endif //PR3B_IGVAPPLES_H
