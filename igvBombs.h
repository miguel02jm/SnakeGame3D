#ifndef PR3B_IGVBOMBS_H
#define PR3B_IGVBOMBS_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

class igvBombs {

private:
    float coordXBomba = 0;
    float coordYBomba = 0;
    float coordZBomba = 0;

public:
    float getCoordXBomba();
    float getCoordYBomba();
    float getCoordZBomba();

    float generarAleatorioBombas();

    void generarCoordsBombas();

    void crearBomba();
};


#endif //PR3B_IGVBOMBS_H
