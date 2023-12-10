#include <math.h>

#include "igvCamara.h"

// M�todos constructores

/**
 * Constructor parametrizado
 * @param _tipo Tipo de c�mara (IGV_PARALELA, IGV_FRUSTUM o IGV_PERSPECTIVA)
 * @param _P0 Posici�n de la c�mara (punto de visi�n)
 * @param _r Punto al que mira la c�mara (punto de referencia)
 * @param _V Vector que indica la vertical
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la nueva c�mara ser�n iguales a los par�metros que se
 *       le pasan
 */
igvCamara::igvCamara ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
        , igvPunto3D _V ): P0 ( _P0 ), r ( _r ), V ( _V )
        , tipo ( _tipo )
{ }

// M�todos p�blicos
/**
 * Define la posici�n de la c�mara
 * @param _P0 Posici�n de la c�mara (punto de visi�n)
 * @param _r Punto al que mira la c�mara (punto de referencia)
 * @param _V Vector que indica la vertical
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores pasados como par�metro
 */
void igvCamara::set ( igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V )
{  P0 = _P0;
    r  = _r;
    V  = _V;
}

/**
 * Define una c�mara de tipo paralela o frustum
 * @param _tipo Tipo de la c�mara (IGV_PARALELA o IGV_FRUSTUM)
 * @param _P0 Posici�n de la c�mara
 * @param _r Punto al que mira la c�mara
 * @param _V Vector que indica la vertical
 * @param _xwmin Coordenada X m�nima del frustum
 * @param _xwmax Coordenada X m�xima del frustum
 * @param _ywmin Coordenada Y m�nima del frustum
 * @param _ywmax Coordenada Y m�xima del frustum
 * @param _znear Distancia de la c�mara al plano Z near
 * @param _zfar Distancia de la c�mara al plano Z far
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores pasados como par�metro
 */
void igvCamara::set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
        , igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin
        , double _ywmax, double _znear, double _zfar )
{  tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    xwmin = _xwmin;
    xwmax = _xwmax;
    ywmin = _ywmin;
    ywmax = _ywmax;
    znear = _znear;
    zfar = _zfar;
}

/**
 * Define una c�mara de tipo perspectiva
 * @param _tipo Tipo de la c�mara (IGV_PERSPECTIVA)
 * @param _P0 Posici�n de la c�mara
 * @param _r Punto al que mira la c�mara
 * @param _V Vector que indica la vertical
 * @param _angulo �ngulo de apertura
 * @param _raspecto Raz�n de aspecto
 * @param _znear Distancia de la c�mara al plano Z near
 * @param _zfar Distancia de la c�mara al plano Z far
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores que se pasan como
 *       par�metros
 */
void igvCamara::set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
        , igvPunto3D _V, double _angulo, double _raspecto
        , double _znear, double _zfar )
{  tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    angulo = _angulo;
    raspecto = _raspecto;
    znear = _znear;
    zfar = _zfar;
}

/**
 * Aplica a los objetos de la escena la transformaci�n de visi�n y la
 * transformaci�n de proyecci�n asociadas a los par�metros de la c�mara
 */
void igvCamara::aplicar ()
{  glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ();

    if ( tipo == IGV_PARALELA )
    {
        glOrtho ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
    }
    if ( tipo == IGV_FRUSTUM )
    {
        glFrustum ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
    }
    if ( tipo == IGV_PERSPECTIVA )
    {
        gluPerspective ( angulo, raspecto, znear, zfar );
    }

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity ();
    gluLookAt ( P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z] );
}

/**
 * Realiza un zoom sobre la c�mara
 * @param factor Factor (en tanto por 100) que se aplica al zoom. Si el valor es
 *        positivo, se aumenta el zoom. Si es negativo, se reduce.
 * @pre Se asume que el par�metro tiene un valor v�lido
 */
void igvCamara::zoom ( double factor )
{
    xwmin = xwmin + (xwmin * factor);
    xwmax = xwmax + (xwmax * factor);
    ywmin = ywmin + (ywmin * factor);
    ywmax = ywmax + (ywmax * factor);
    angulo = angulo + (angulo * factor);
}

void igvCamara::cambiar_vista() {
    if (def == 1) {
        setVistaPerfil();
    }
    else if (perf == 1) {
        setVistaPlanta();
    }
    else if (plant == 1) {
        setVistaAlzado();
    }
    else if (alz == 1) {
        setVistaNormal();
    }
}

void igvCamara::setVistaPerfil() {
    plant=0;
    alz=0;
    def=0;
    perf=1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.9, 0.0, 0.0);

    gluLookAt(0.0, 0.0, 4.0,
              1.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

void igvCamara::setVistaNormal() {
    plant=0;
    alz=0;
    def=1;
    perf=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.9, 0.0, 0.0);

    gluLookAt(3.0, 2.0, 4.0,
              1.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

void igvCamara::setVistaAlzado(){
    plant=0;
    alz=1;
    def=0;
    perf=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.9, 0.0, 0.0);

    gluLookAt(3.0, 0.0, 0.0,
              1.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

void igvCamara::setVistaPlanta() {
    plant=1;
    alz=0;
    def=0;
    perf=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.9, 0.0, 0.0);

    gluLookAt(0.001, 5.0, 0.0,
              1.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}