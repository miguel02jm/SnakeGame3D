#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "igvPunto3D.h"

/**
 * Etiquetas para los diferentes tipos de cámara
 */
enum tipoCamara
{  IGV_PARALELA   ///< Proyección paralela
    , IGV_FRUSTUM   ///< Proyección en perspectiva usando OpenGL
    , IGV_PERSPECTIVA   ///< Proyección en perspectiva usando GLU
};

/**
 * Los objetos de esta clase representan cámaras de visualización en la aplicación
 */
class igvCamara
{  public:
    // atributos
    tipoCamara tipo = IGV_PARALELA;  ///< Tipo de la cámara

    // ventana de visión: parámetros proyección paralela y frustum
    GLdouble xwmin = -3    ///< Coordenada X mínima del frustum/proyección paralela
    , xwmax = 3   ///< Coordenada X máxima del frustum/proyección paralela
    , ywmin = -3   ///< Coordenada Y mínima del frustum/proyección paralela
    , ywmax = 3   ///< Coordenada Y máxima del frustum/proyección paralela
    ;

    // ventana de visión: parámetros proyección perspectiva
    GLdouble angulo = 60   ///< Ángulo de apertura (proyección perspectiva)
    , raspecto = 1   ///< Razón de aspecto (proyección perspectiva)
    ;

    // distancias de planos cercano y lejano
    GLdouble znear = 1    ///< Distancia de la cámara al plano Z near
    , zfar = 200 ///< Distancia de la cámara al plano Z far
    ;

    // punto de visión
    igvPunto3D P0 = { 0, 2, 4 };   ///< Posición de la cámara

    // punto de referencia de visión
    igvPunto3D r = { 0, 0, 0 };   ///< Punto al que mira la cámara

    // vector arriba
    igvPunto3D V = { 0, 1, 0 };   ///< Vector que indica la vertical

    //vistas
    igvPunto3D Default = igvPunto3D(3.0, 2.0, 4.0);
    igvPunto3D Planta = igvPunto3D(0.001, 5.0, 0.0);
    igvPunto3D Alzado = igvPunto3D(0.0, 0.0, 4.0);
    igvPunto3D Perfil = igvPunto3D(3.0, 0.0, 0.0);

    // Métodos
    void cambiar_vista();
public:
    // Constructores por defecto y destructor
    /// Constructor por defecto
    igvCamara () = default;

    /// Destructor
    ~igvCamara () = default;

    void setVistaPerfil();
    void setVistaNormal();

    // Otros constructores
    igvCamara ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V );

    // Métodos
    // define la posición de la cámara
    void set ( igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V );

    // define una cámara de tipo paralela o frustum
    void set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V
            , double _xwmin, double _xwmax, double _ywmin
            , double _ywmax, double _znear, double _zfar );

    // define una cámara de tipo perspectiva
    void set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V
            , double _angulo, double _raspecto, double _znear, double _zfar );

    void aplicar ( void ); // aplica a los objetos de la escena la transformación
    // de visión y la transformación de proyección
    // asociadas a los parámetros de la cámara
    void zoom ( double factor ); // realiza un zoom sobre la cámara
};

#endif   // __IGVCAMARA

