#ifndef PR3B_IGVCLOUDS_H
#define PR3B_IGVCLOUDS_H

#if defined(APPLE) && defined(MACH)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(APPLE) && defined(MACH)

class igvClouds {
    float coordX = 5;
public:
    void crearModelo();
    void GenerarNubes();

    void setCoordX(float velNube);
};


#endif //PR3B_IGVCLOUDS_H
