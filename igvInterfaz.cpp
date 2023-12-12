#include <cstdlib>
#include <stdio.h>
#include "igvInterfaz.h"

// Aplicación del patrón Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// Métodos públicos ----------------------------------------

/**
 * Método para acceder al objeto único de la clase, en aplicación del patrón de
 * diseño Singleton
 * @return Una referencia al objeto único de la clase
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
    // crear cámaras
    p0 = igvPunto3D ( 3.0, 2.0, 4 );
    r = igvPunto3D ( 0, 0, 0 );
    V = igvPunto3D ( 0, 1.0, 0 );

    _instancia->camara.set ( IGV_PARALELA, p0, r, V, -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200 );

    // Las cámaras se han creado con valores por defecto de 60 grados de apertura
    // y ratio de aspecto 1
}

/**
 * Inicializa todos los parámetros para crear una ventana de visualización
 * @param argc Número de parámetros por línea de comandos al ejecutar la
 *             aplicación
 * @param argv Parámetros por línea de comandos al ejecutar la aplicación
 * @param _ancho_ventana Ancho inicial de la ventana de visualización
 * @param _alto_ventana Alto inicial de la ventana de visualización
 * @param _pos_X Coordenada X de la posición inicial de la ventana de
 *               visualización
 * @param _pos_Y Coordenada Y de la posición inicial de la ventana de
 *               visualización
 * @param _titulo Título de la ventana de visualización
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void igvInterfaz::configura_entorno ( int argc, char **argv, int _ancho_ventana
        , int _alto_ventana, int _pos_X, int _pos_Y
        , std::string _titulo )
{  // inicialización de los atributos de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicialización de la ventana de visualización
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
 * Método para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion ()
{  glutMainLoop (); // inicia el bucle de visualización de GLUT
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
 * Método para control de eventos del teclado
 * @param key Código de la tecla pulsada
 * @param x Coordenada X de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc ( unsigned char key, int x, int y )
{  /* IMPORTANTE: en la implementación de este método hay que cambiar convenientemente el estado
      de los objetos de la aplicación, pero no hacer llamadas directas a funciones de OpenGL */

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
            _instancia->jugando=true;
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
        case 'e': // activa/desactiva la visualización de los ejes
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 27: // tecla de escape para SALIR
            if(_instancia->jugando == false && _instancia->currentState == PLAYING){
                _instancia->unaVezVistaNorm=false;
                _instancia->currentState = MAIN_MENU;
            }
            break;
    }
    glutPostRedisplay (); // renueva el contenido de la ventana de vision y redibuja la escena
}

/**
 * Método que define la cámara de visión y el viewport. Se llama automáticamente
 * cuando se cambia el tamaño de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los parámetros tienen valores válidos
 */
void igvInterfaz::reshapeFunc ( int w, int h )
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
    // guardamos valores nuevos de la ventana de visualizacion
    _instancia->set_ancho_ventana ( w );
    _instancia->set_alto_ventana ( h );

    // establece los parámetros de la cámara y de la proyección
    _instancia->camara.aplicar ();
}

/**
 * Método para visualizar la escena
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

void igvInterfaz::displayFunc (){
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // borra la ventana y el Z-bufferç
    glViewport ( 0, 0, _instancia->get_ancho_ventana (), _instancia->get_alto_ventana () );
    if(_instancia->currentState == MAIN_MENU){
        _instancia->camara.setVistaPerfil();
        _instancia->camara.aplicar();
        _instancia->escena.visualizarMenu();
    }
    if (_instancia->currentState == PLAYING) {
        _instancia->unaVezVistaNormal();
        _instancia->escena.visualizar();
    }
    if(_instancia->currentState == CHANGE_SKIN){
        _instancia->escena.visualizarSkin();
    }

    glutSwapBuffers ();
}

void igvInterfaz::unaVezVistaNormal(){
    if(unaVezVistaNorm == false){
        _instancia->camara.setVistaNormal();
        _instancia->camara.aplicar();
        unaVezVistaNorm = true;
    }
}

void igvInterfaz::mouseFunc ( GLint boton, GLint estado, GLint x, GLint y )
{
    if(_instancia->currentState == MAIN_MENU){
        if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
            printf("x = %d, y = %d\n", x, y);
            if (x >= 82 && x <= 405 &&
                y >= 126 && y <= 187) {
                _instancia->currentState = PLAYING;
            } else if (x >= 82 && x <= 405 &&
                       y >= 251 && y <= 312) {
                _instancia->currentState = CHANGE_SKIN;
            } else if (x >= 82 && x <= 405 &&
                       y >= 375 && y <= 437) {
                exit ( 1 );
            }
            glutPostRedisplay();
        }
    }
    if(_instancia->currentState == CHANGE_SKIN){
        if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
            printf("x = %d, y = %d\n", x, y);
            if (x >= 180 && x <= 319 &&
                y >= 108 && y <= 141 && _instancia->escena.getVisualizandose()==true) {
                _instancia->escena.setSkin1();
                _instancia->currentState = MAIN_MENU;
            } else if (x >= 180 && x <= 319 &&
                       y >= 258 && y <= 291 && _instancia->escena.getVisualizandose()==true) {
                _instancia->escena.setSkin2();
                _instancia->currentState = MAIN_MENU;
            } else if (x >= 180 && x <= 319 &&
                       y >= 413 && y <= 445 && _instancia->escena.getVisualizandose()==true) {
                _instancia->escena.setSkin3();
                _instancia->currentState = MAIN_MENU;
            }
            glutPostRedisplay();
        }
    }
}

void igvInterfaz::IdleFunc() {
    //Codigo para que la serpiente avance automaticamente
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
    glutPostRedisplay();
}

void igvInterfaz::TimerFunc(int value) {
    // Configura el temporizador para la próxima llamada
    glutTimerFunc(500, TimerFunc, 0);

    // Llama a IdleFunc para que la serpiente avance
    IdleFunc();
}

/**
 * Método para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks ()
{  glutKeyboardFunc ( keyboardFunc );
    glutSpecialFunc(SpecialFunc);
    glutReshapeFunc ( reshapeFunc );
    glutDisplayFunc ( displayFunc );
    glutMouseFunc ( mouseFunc );
    glutTimerFunc(0, TimerFunc, 0);
}

/**
 * Método para consultar el ancho de la ventana de visualización
 * @return El valor almacenado como ancho de la ventana de visualización
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * Método para consultar el alto de la ventana de visualización
 * @return El valor almacenado como alto de la ventana de visualización
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

/**
 * Método para cambiar el ancho de la ventana de visualización
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El ancho de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * Método para cambiar el alto de la ventana de visualización
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El alto de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}




