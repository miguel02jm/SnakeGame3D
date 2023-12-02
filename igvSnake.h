#ifndef PR3B_IGVSNAKE_H
#define PR3B_IGVSNAKE_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>
#include <vector>

#endif   // defined(__APPLE__) && defined(__MACH__)

class igvSnake {

private:
    float coordX = 0;
    float coordZ = 0;

    float giro_vert = 0;
    float giro_hor = 0;

    bool animacion = false;

    std::vector<std::pair<float, float>> segmentos;

    int fila = 10;
    int columna = 10;

    int fila1 = 5;
    int columna1 = 5;
public:
    void CrearTorsoSerpiente();
    void CrearCabezaSerpiente();
    void CrearOjosSerpiente();
    void CrearLenguaSerpiente();
    void crearModelo();

    //Movimiento de la serpiente
    void setCoordX(float columna);
    void setCoordZ(float fila);
    float getCoordX();
    float getCoordZ();

    void setColumna(float col);
    void setFila(float fil);
    float getColumna();
    float getFila();

    void girarHor(float rot);
    float getGiroHor();

    void set_animacion(bool _animacion);
    bool get_animacion();

    void crecer();

    void moverSerpiente(float oldCoordX, float oldCoordZ);
};


#endif //PR3B_IGVSNAKE_H
