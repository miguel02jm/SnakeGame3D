#ifndef PR3B_IGVSNAKE_H
#define PR3B_IGVSNAKE_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

class igvSnake {

private:
    float coordX = 0;
    float coordY = 0;
    float coordZ = 0;

    float giro_vert = 0;
    float giro_hor = 0;

    bool animacion = false;
public:
    igvSnake() = default;
    /// Destructor
    ~igvSnake() = default;

    void CrearTorsoSerpiente();
    void CrearCabezaSerpiente();
    void CrearOjosSerpiente();
    void CrearLenguaSerpiente();
    void crearModelo();

    //Movimiento de la serpiente
    void setCoordX(float cX);
    void setCoordY(float cY);
    void setCoordZ(float cZ);
    float getCoordX();
    float getCoordY();
    float getCoordZ();

    void girarVert(float rot);
    void girarHor(float rot);
    float getGiroVert();
    float getGiroHor();

    void set_animacion(bool _animacion);
    bool get_animacion();
};


#endif //PR3B_IGVSNAKE_H
