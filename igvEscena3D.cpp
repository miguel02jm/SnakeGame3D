#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "igvEscena3D.h"

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{  GLfloat rojo[] = { 1, 0, 0, 1.0 };
    GLfloat verde[] = { 0, 1, 0, 1.0 };
    GLfloat azul[] = { 0, 0, 1, 1.0 };

    glMaterialfv ( GL_FRONT, GL_DIFFUSE, rojo );
    glBegin ( GL_LINES );
    glVertex3f ( 1000, 0, 0 );
    glVertex3f ( -1000, 0, 0 );
    glEnd ();

    glMaterialfv ( GL_FRONT, GL_DIFFUSE, verde );
    glBegin ( GL_LINES );
    glVertex3f ( 0, 1000, 0 );
    glVertex3f ( 0, -1000, 0 );
    glEnd ();

    glMaterialfv ( GL_FRONT, GL_DIFFUSE, azul );
    glBegin ( GL_LINES );
    glVertex3f ( 0, 0, 1000 );
    glVertex3f ( 0, 0, -1000 );
    glEnd ();
}

void igvEscena3D::CrearEscenario() {
    float tamCasillaX = 4.0 / filas;
    float tamCasillaZ = 4.0 / columnas;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Determinar el color de la casilla (verde claro o verde oscuro)
            GLfloat* color;
            if ((i + j) % 2 == 0) {
                GLfloat blanco[] = { 1, 1, 1, 1.0 };  // Cambia este color si es necesario
                color = blanco;
            } else {
                GLfloat verde[] = { 0, 1, 0, 1.0 };  // Cambia este color si es necesario
                color = verde;
            }

            // Establecer el color de la casilla
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

            // Dibujar el cubo con una escala menos en el eje y
            glPushMatrix();
            glTranslated(-2 + j * tamCasillaX + tamCasillaX / 2, -0.35, 2 - i * tamCasillaZ - tamCasillaZ / 2);
            glScaled(tamCasillaX, 0.5, tamCasillaZ);
            glutSolidCube(1);
            glPopMatrix();
        }
    }
}

void igvEscena3D::verificarColision() {
    if (Primera_Generacion == true) {
        srand(time(NULL));

        apples.generarCoordsManzanas();
        bombs.generarCoordsBombas();

        Primera_Generacion = false;
    }else if ((snake.getCoordX() == apples.getCoordXManzana()) &&
              (snake.getCoordZ() == apples.getCoordZManzana())) {

        while (true) {

            apples.generarCoordsManzanas();
            bombs.generarCoordsBombas();

            bool colisionConSerpiente = false;

            if((snake.getCoordX() == apples.getCoordXManzana()) && (snake.getCoordZ() == apples.getCoordZManzana())
               || ((snake.getCoordX() == bombs.getCoordXBomba()) && (snake.getCoordZ() == bombs.getCoordZBomba()))){
                colisionConSerpiente = true;
                break;
            }

            if((bombs.getCoordXBomba() == apples.getCoordXManzana()) && (bombs.getCoordZBomba() == apples.getCoordZManzana())){
                colisionConSerpiente = true;
                break;
            }

            for (const auto& segmento : snake.getSegmentos()) {
                if (segmento.first == apples.getCoordXManzana() && segmento.second == apples.getCoordZManzana()) {
                    colisionConSerpiente = true;
                    break;
                }
                if (segmento.first == bombs.getCoordXBomba() && segmento.second == bombs.getCoordZBomba()) {
                    colisionConSerpiente = true;
                    break;
                }
            }

            // Si no hay colisión, sal del bucle
            if (!colisionConSerpiente) {
                break;
            }
        }

        cont+=100;
        snake.crecer();

    }else if((snake.getCoordX() == bombs.getCoordXBomba()) &&
             (snake.getCoordZ() == bombs.getCoordZBomba())){
        bomba = true;
    }
}

void igvEscena3D::setEjeX(float rotacion) {
    ejeX += rotacion;
}

void igvEscena3D::setEjeY(float rotacion) {
    ejeY += rotacion;
}

igvSnake* igvEscena3D::getSnake(){
    return &snake;
}

igvBombs* igvEscena3D::getBombs() {
    return &bombs;
}

igvApples* igvEscena3D::getApples() {
    return &apples;
}

void igvEscena3D::visualizar(igvPunto3D camara)
{
    GLfloat negro[] = { 0, 0, 0, 1.0 };

    visualizandose = false;
    visualizandoPausa = false;

    GLfloat luz0[] = { 10, 8, 9, 1 };
    glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
    glEnable ( GL_LIGHT0 );

// Dentro de la función de dibujo (display callback):
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

// Crear una cadena que combine "Puntuacion:" y el valor de cont
    std::string text4 = "Puntuacion: " + std::to_string(cont);

    if(camara==igvPunto3D(Default)){
        glRasterPos3f(0.93, -2.57, 0);
    }
    if(camara==igvPunto3D(Planta)){
        glRasterPos3f(2.6, -2.5, -0.75);
    }
    if(camara==igvPunto3D(Alzado)){
        glRasterPos3f(0.75, -2.6, 0);
    }
    if(camara==igvPunto3D(Perfil)){
        glRasterPos3f(1.5, -2.6, -0.75);
    }


// Mostrar cada carácter de la cadena combinada
    for (size_t i = 0; i < text4.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
    }

    glPopMatrix();

    // crear el modelo
    glPushMatrix (); // guarda la matriz de modelado

    glRotated(ejeX, 1, 0, 0);
    glRotated(ejeY, 0, 1, 0);
    CrearEscenario();
    verificarColision();
    apples.crearManzana();
    bombs.crearBomba();
    snake.crearModelo(skin);

    if(camara!=igvPunto3D(Planta)){
        clouds.GenerarNubes();
    }

    glPopMatrix();
}

void igvEscena3D::visualizarMenu(void) {
    visualizandose = false;

    GLfloat luz0[] = { 10, 8, 9, 1 };
    glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
    glEnable ( GL_LIGHT0 );

    glPushMatrix ();

    GLfloat negro[] = { 0, 0, 0, 1 };
    GLfloat verde[] = { 0.5, 1.0, 0.5, 1.0 };

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);
    glRasterPos3f(button1X + 1.25, button1Y + buttonHeight / 2 + 1, 0.1);
    const char* text4 = "Snake Game 3D";
    for (int i = 0; text4[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
    }
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button1X, button1Y);
    glVertex2f(button1X + buttonWidth, button1Y);
    glVertex2f(button1X, button1Y + buttonHeight);

    glVertex2f(button1X + buttonWidth, button1Y);
    glVertex2f(button1X + buttonWidth, button1Y + buttonHeight);
    glVertex2f(button1X, button1Y + buttonHeight);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    glRasterPos3f(button1X + 1.75, button1Y + buttonHeight / 2 - 0.1, 0.1);

    const char* text = "Jugar";
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button2X, button2Y);
    glVertex2f(button2X + buttonWidth, button2Y);
    glVertex2f(button2X, button2Y + buttonHeight);

    glVertex2f(button2X + buttonWidth, button2Y);
    glVertex2f(button2X + buttonWidth, button2Y + buttonHeight);
    glVertex2f(button2X, button2Y + buttonHeight);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button2X + 1.3, button2Y + buttonHeight / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text2 = "Cambiar skin";
    for (int i = 0; text2[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button3X, button3Y);
    glVertex2f(button3X + buttonWidth, button3Y);
    glVertex2f(button3X, button3Y + buttonHeight);

    glVertex2f(button3X + buttonWidth, button3Y);
    glVertex2f(button3X + buttonWidth, button3Y + buttonHeight);
    glVertex2f(button3X, button3Y + buttonHeight);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button3X + 1.75, button3Y + buttonHeight / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text3 = "Salir";
    for (int i = 0; text3[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }

    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,1,0);
    glRotatef(17,1,0,0);
    glTranslatef(1.5,-2.15,1);
    glScalef(1.5,1.5,1.5);
    snake.crearModelo2(skin);
    glPopMatrix();
}

void igvEscena3D::visualizarSkin(void) {
    GLfloat luz0[] = { 10, 8, 9, 1 };
    glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
    glEnable ( GL_LIGHT0 );

    glPushMatrix ();

    GLfloat verde[] = { 0.5, 1.0, 0.5, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button4X, button4Y);
    glVertex2f(button4X + button2Width, button4Y);
    glVertex2f(button4X, button4Y + button2Height);

    glVertex2f(button4X + button2Width, button4Y);
    glVertex2f(button4X + button2Width, button4Y + button2Height);
    glVertex2f(button4X, button4Y + button2Height);
    glEnd();

    GLfloat negro[] = { 0, 0, 0, 1 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    glRasterPos3f(button4X + 0.25, button4Y + button2Height / 2 - 0.1, 0.1);

    const char* text = "Seleccionar";
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    glRotatef(-30,0,1,0);
    glRotatef(17,1,0,0);
    glTranslatef(0.25,2.3,0);
    snake.crearModelo2(skin1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,1,0);
    glRotatef(17,1,0,0);
    glTranslatef(0,0.43,0);
    snake.crearModelo2(skin2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,1,0);
    glRotatef(17,1,0,0);
    glTranslatef(-0.4,-1.5,0);
    snake.crearModelo2(skin3);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button5X, button5Y);
    glVertex2f(button5X + button2Width, button5Y);
    glVertex2f(button5X, button5Y + button2Height);

    glVertex2f(button5X + button2Width, button5Y);
    glVertex2f(button5X + button2Width, button5Y + button2Height);
    glVertex2f(button5X, button5Y + button2Height);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    glRasterPos3f(button5X + 0.25, button5Y + button2Height / 2 - 0.1, 0.1);

    const char* text2 = "Seleccionar";
    for (int i = 0; text2[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button6X, button6Y);
    glVertex2f(button6X + button2Width, button6Y);
    glVertex2f(button6X, button6Y + button2Height);

    glVertex2f(button6X + button2Width, button6Y);
    glVertex2f(button6X + button2Width, button6Y + button2Height);
    glVertex2f(button6X, button6Y + button2Height);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    glRasterPos3f(button6X + 0.25, button6Y + button2Height / 2 - 0.1, 0.1);

    const char* text3 = "Seleccionar";
    for (int i = 0; text3[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text3[i]);
    }

    glPopMatrix();

    visualizandose = true;
}

void igvEscena3D::visualizarPausa() {
    GLfloat luz0[] = { 10, 8, 9, 1 };
    glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
    glEnable ( GL_LIGHT0 );

    glPushMatrix ();

    GLfloat negro[] = { 0, 0, 0, 1 };
    GLfloat verde[] = { 0.5, 1.0, 0.5, 1.0 };

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);
    glRasterPos3f(button1X + 1.65, button1Y + buttonHeight / 2 + 1, 0.1);
    const char* text4 = "Pausa";
    for (int i = 0; text4[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
    }
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);
    glRasterPos3f(button1X + 1.15, button1Y + buttonHeight / 2, 0.1);
    std::string text5 = "Puntuacion: " + std::to_string(cont);
    for (int i = 0; text5[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text5[i]);
    }
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button2X, button2Y);
    glVertex2f(button2X + buttonWidth, button2Y);
    glVertex2f(button2X, button2Y + buttonHeight);

    glVertex2f(button2X + buttonWidth, button2Y);
    glVertex2f(button2X + buttonWidth, button2Y + buttonHeight);
    glVertex2f(button2X, button2Y + buttonHeight);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button2X + 1.5, button2Y + buttonHeight / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text2 = "Reanudar";
    for (int i = 0; text2[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button3X, button3Y);
    glVertex2f(button3X + buttonWidth, button3Y);
    glVertex2f(button3X, button3Y + buttonHeight);

    glVertex2f(button3X + buttonWidth, button3Y);
    glVertex2f(button3X + buttonWidth, button3Y + buttonHeight);
    glVertex2f(button3X, button3Y + buttonHeight);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button3X + 1.15, button3Y + buttonHeight / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text3 = "Finalizar partida";
    for (int i = 0; text3[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }

    glPopMatrix();

    visualizandoPausa = true;
}

void igvEscena3D::visualizarFinal() {
    visualizandoPausa = false;

    GLfloat luz0[] = { 10, 8, 9, 1 };
    glLightfv ( GL_LIGHT0, GL_POSITION, luz0 );
    glEnable ( GL_LIGHT0 );

    glPushMatrix ();

    GLfloat negro[] = { 0, 0, 0, 1 };
    GLfloat verde[] = { 0.5, 1.0, 0.5, 1.0 };

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);
    glRasterPos3f(button1X + 1, button1Y + buttonHeight / 2 + 1, 0.1);
    const char* text4 = "Final de la partida";
    for (int i = 0; text4[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
    }
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);
    glRasterPos3f(button1X + 0.8, button1Y + buttonHeight / 2, 0.1);
    std::string text5 = "Puntuacion final: " + std::to_string(cont);
    for (int i = 0; text5[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text5[i]);
    }
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button7X, button7Y);
    glVertex2f(button7X + button3Width, button7Y);
    glVertex2f(button7X, button7Y + button3Height);

    glVertex2f(button7X + button3Width, button7Y);
    glVertex2f(button7X + button3Width, button7Y + button3Height);
    glVertex2f(button7X, button7Y + button3Height);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button7X + 1.8, button7Y + button3Height / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text2 = "Salir";
    for (int i = 0; text2[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, verde);
    glBegin(GL_TRIANGLES);
    glVertex2f(button8X, button8Y);
    glVertex2f(button8X + button3Width, button8Y);
    glVertex2f(button8X, button8Y + button3Height);

    glVertex2f(button8X + button3Width, button8Y);
    glVertex2f(button8X + button3Width, button8Y + button3Height);
    glVertex2f(button8X, button8Y + button3Height);
    glEnd();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, negro);

    // Establece la posición del raster para el texto
    glRasterPos3f(button8X + 1, button8Y + button3Height / 2 - 0.1, 0.1);

    // Renderiza el texto "Jugar"
    const char* text3 = "Ir al menu principal";
    for (int i = 0; text3[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }

    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,1,0);
    glRotatef(17,1,0,0);
    glTranslatef(1.5,-2.15,1);
    glScalef(1.5,1.5,1.5);
    snake.crearModelo2(skin);
    glPopMatrix();
}

bool igvEscena3D::getVisualizandose() {
    return visualizandose;
}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}

void igvEscena3D::setSkin1() {
    memcpy(skin, skin1, sizeof(skin));
}

void igvEscena3D::setSkin2() {
    memcpy(skin, skin2, sizeof(skin));
}

void igvEscena3D::setSkin3() {
    memcpy(skin, skin3, sizeof(skin));
}

bool igvEscena3D::getVisualizandoPausa() {
    return visualizandoPausa;
}

bool igvEscena3D::getBomba(){
    return bomba;
}

void igvEscena3D::setBomba(bool _bomba){
    bomba = _bomba;
}

igvClouds* igvEscena3D::getClouds(){
    return &clouds;
}