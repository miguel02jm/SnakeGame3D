#include <cstdlib>
#include <stdio.h>
#include "igvInterfaz.h"

// Aplicaci�n del patr�n Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * dise�o Singleton
 * @return Una referencia al objeto �nico de la clase
 */
igvInterfaz& igvInterfaz::getInstancia ()
{  if ( !_instancia )
   {  _instancia = new igvInterfaz;
   }

   return *_instancia;
}

/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo ()
{  // r tiene valor por defecto (0,0,0)
   // crear c�maras
   p0 = igvPunto3D ( 3.0, 2.0, 4 );
   r = igvPunto3D ( 0, 0, 0 );
   V = igvPunto3D ( 0, 1.0, 0 );

   _instancia->camara.set ( IGV_PARALELA, p0, r, V, -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200 );

   // Las c�maras se han creado con valores por defecto de 60 grados de apertura
   // y ratio de aspecto 1
}

/**
 * Inicializa todos los par�metros para crear una ventana de visualizaci�n
 * @param argc N�mero de par�metros por l�nea de comandos al ejecutar la
 *             aplicaci�n
 * @param argv Par�metros por l�nea de comandos al ejecutar la aplicaci�n
 * @param _ancho_ventana Ancho inicial de la ventana de visualizaci�n
 * @param _alto_ventana Alto inicial de la ventana de visualizaci�n
 * @param _pos_X Coordenada X de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _pos_Y Coordenada Y de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _titulo T�tulo de la ventana de visualizaci�n
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void igvInterfaz::configura_entorno ( int argc, char **argv, int _ancho_ventana
                                      , int _alto_ventana, int _pos_X, int _pos_Y
                                      , std::string _titulo )
{  // inicializaci�n de los atributos de la interfaz
   ancho_ventana = _ancho_ventana;
   alto_ventana = _alto_ventana;

   // inicializaci�n de la ventana de visualizaci�n
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize ( _ancho_ventana, _alto_ventana );
   glutInitWindowPosition ( _pos_X, _pos_Y );
   glutCreateWindow ( _titulo.c_str () );

   glEnable ( GL_DEPTH_TEST ); // activa el ocultamiento de superficies por z-buffer
   glClearColor ( 1.0, 1.0, 1.0, 0.0 ); // establece el color de fondo de la ventana

   glEnable ( GL_LIGHTING ); // activa la iluminacion de la escena
   glEnable ( GL_NORMALIZE ); // normaliza los vectores normales para calculo iluminacion

   crear_mundo (); // crea el mundo a visualizar en la ventana
}

/**
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion ()
{  glutMainLoop (); // inicia el bucle de visualizaci�n de GLUT
}


void igvInterfaz::SpecialFunc(int key, int x, int y) {
    //manejo de las teclas especiales del teclado para mover la posici?n del foco

    if (key == GLUT_KEY_UP) {
        _instancia->escena.setEjeX(-5); //rota el eje X
    }
    else if (key == GLUT_KEY_DOWN) {
        _instancia->escena.setEjeX(5); //rota el eje X
    }
    else if (key == GLUT_KEY_RIGHT) {
        _instancia->escena.setEjeY(5); //rota el eje Y
    }
    else if (key == GLUT_KEY_LEFT) {
        _instancia->escena.setEjeY(-5); //rota el eje Y
    }
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

/**
 * M�todo para control de eventos del teclado
 * @param key C�digo de la tecla pulsada
 * @param x Coordenada X de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc ( unsigned char key, int x, int y )
{  /* IMPORTANTE: en la implementaci�n de este m�todo hay que cambiar convenientemente el estado
      de los objetos de la aplicaci�n, pero no hacer llamadas directas a funciones de OpenGL */

   switch ( key ) {
       case 'p':
       case 'P':
           if (_instancia->camara.tipo == IGV_PARALELA) {
               _instancia->camara.tipo = IGV_PERSPECTIVA;
               _instancia->camara.aplicar();
           } else {
               _instancia->camara.tipo = IGV_PARALELA;
               _instancia->camara.aplicar();
           }
           break;
       case 'v':
       case 'V':
           _instancia->camara.cambiar_vista();
           _instancia->camara.aplicar();
           break;
       case '+':
           _instancia->camara.zoom(-0.05);
           _instancia->camara.aplicar();
           break;
       case '-':
           _instancia->camara.zoom(0.05);
           _instancia->camara.aplicar();
           break;
       case 'a':
           _instancia->escena.getSnake()->girarHor(90); //giro hacia la derecha de la serpiente
           break;
       case 'd':
           _instancia->escena.getSnake()->girarHor(-90); //giro hacia la izquierda de la serpiente
           break;
       case 'i':
           _instancia->escena.getSnake()->set_animacion(!_instancia->escena.getSnake()->get_animacion());
           break;
       case 'n':
           _instancia->camara.znear = _instancia->camara.znear + 0.2;
           _instancia->camara.zfar = _instancia->camara.zfar + 0.2;
           _instancia->camara.aplicar();
           break;
       case 'N':
           _instancia->camara.znear = _instancia->camara.znear - 0.2;
           _instancia->camara.zfar = _instancia->camara.zfar - 0.2;
           _instancia->camara.aplicar();
           break;
       case 'e': // activa/desactiva la visualizaci�n de los ejes
           _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
           break;
       case 27: // tecla de escape para SALIR
         exit ( 1 );
         break;
   }
   glutPostRedisplay (); // renueva el contenido de la ventana de vision y redibuja la escena
}

/**
 * M�todo que define la c�mara de visi�n y el viewport. Se llama autom�ticamente
 * cuando se cambia el tama�o de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 */
void igvInterfaz::reshapeFunc ( int w, int h )
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
   // guardamos valores nuevos de la ventana de visualizacion
   _instancia->set_ancho_ventana ( w );
   _instancia->set_alto_ventana ( h );

   // establece los par�metros de la c�mara y de la proyecci�n
   _instancia->camara.aplicar ();
}

/**
 * M�todo para visualizar la escena
 */
/*void igvInterfaz::displayFunc ()
{  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // borra la ventana y el Z-buffer

    // se establece el viewport
    if (_instancia->booleano) {
        glViewport(250, 250, _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->camara.P0 = _instancia->vistas[_instancia->indice_vistas];
        _instancia->escena.visualizar();
        _instancia->camara.aplicar();
        glViewport(0, 250, _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->camara.P0 = _instancia->vistas[_instancia->indice_vistas+1];
        _instancia->escena.visualizar();
        _instancia->camara.aplicar();
        glViewport(250, 0, _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->camara.P0 = _instancia->vistas[_instancia->indice_vistas+2];
        _instancia->escena.visualizar();
        _instancia->camara.aplicar();
        glViewport(0, 0, _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->camara.P0 = _instancia->vistas[_instancia->indice_vistas+3];
        _instancia->escena.visualizar();
        _instancia->camara.aplicar();
    } else {
        //visualiza la escena
        glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());
        _instancia->escena.visualizar();
    }

    // refresca la ventana
    glutSwapBuffers (); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}*/

void igvInterfaz::displayFunc ()
{  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // borra la ventana y el Z-buffer

    // se establece el viewport
    glViewport ( 0, 0, _instancia->get_ancho_ventana (), _instancia->get_alto_ventana () );

    //visualiza la escena
    _instancia->escena.visualizar ();

    // refresca la ventana
    glutSwapBuffers (); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::IdleFunc() {
    if(_instancia->escena.getSnake()->get_animacion()){
        float oldCoordX = _instancia->escena.getSnake()->getCoordX();
        float oldCoordZ = _instancia->escena.getSnake()->getCoordZ();

        float fila = _instancia->escena.getSnake()->getFila();
        float columna = _instancia->escena.getSnake()->getColumna();

        if (_instancia->escena.getSnake()->getGiroHor() == 0) {
            _instancia->escena.getSnake()->setFila(fila += 1);
            _instancia->escena.getSnake()->setCoordZ(_instancia->escena.getSnake()->getFila());
        } else if (_instancia->escena.getSnake()->getGiroHor() == 90) {
            _instancia->escena.getSnake()->setColumna(columna += 1);
            _instancia->escena.getSnake()->setCoordX(_instancia->escena.getSnake()->getColumna());
        } else if (_instancia->escena.getSnake()->getGiroHor() == 180) {
            _instancia->escena.getSnake()->setFila(fila -= 1);
            _instancia->escena.getSnake()->setCoordZ(_instancia->escena.getSnake()->getFila());
        } else if (_instancia->escena.getSnake()->getGiroHor() == 270) {
            _instancia->escena.getSnake()->setColumna(columna -= 1);
            _instancia->escena.getSnake()->setCoordX(_instancia->escena.getSnake()->getColumna());
        }
        _instancia->escena.getSnake()->moverSerpiente(oldCoordX, oldCoordZ);
    }

    _instancia->escena.getClouds()->setCoordX(0.5);

    glutPostRedisplay();
}

void igvInterfaz::TimerFunc(int value) {
    glutTimerFunc(500, TimerFunc, 0);
    IdleFunc();
}

/**
 * M�todo para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks () {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(SpecialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutTimerFunc(0, TimerFunc, 0);
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}

