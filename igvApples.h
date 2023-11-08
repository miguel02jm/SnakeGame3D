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
    float coordYManzana = 0;
    float coordZManzana = 0;

public:
    float getCoordXManzana();
    float getCoordYManzana();
    float getCoordZManzana();

    float generarAleatorioManzanas();

    void generarCoordsManzanas();

    void crearManzana();
};


#endif //PR3B_IGVAPPLES_H
