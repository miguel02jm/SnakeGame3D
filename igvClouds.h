#ifndef PR3B_IGVCLOUDS_H
#define PR3B_IGVCLOUDS_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

class igvClouds {
    float coordX = 5;
public:
    void crearModelo();
    void GenerarNubes();

    void setCoordX(float velNube);
};


#endif //PR3B_IGVCLOUDS_H
