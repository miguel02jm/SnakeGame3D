#include "igvSnake.h"

void igvSnake::CrearTorsoSerpiente() {
    GLfloat color_torso[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_torso);

    glPushMatrix();
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearCabezaSerpiente() {
    GLfloat color_cabeza[] = { 0.1,0.4,0.1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_cabeza);

    glPushMatrix();
    glTranslated(0, 0, 1);
    glScaled(1.25, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearOjosSerpiente() {
    GLfloat color_ojos[] = { 1,1,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_ojos);

    glPushMatrix();
    glTranslated(0.5, 0.55, 1);
    glScaled(0.25, 0.1, 0.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.5, 0.55, 1);
    glScaled(0.25, 0.1, 0.25);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::CrearLenguaSerpiente() {
    GLfloat color_lengua[] = { 1,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_lengua);

    glPushMatrix();
    glTranslated(0, 0, 1.75);
    glScaled(0.25, 0.1, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void igvSnake::crearModelo() {
    // Dibuja la cabeza de la serpiente en las coordenadas de la cabeza
    glPushMatrix();
    glTranslatef(coordX, 0.08, coordZ);
    glRotatef(giro_hor, 0, 1, 0);
    glRotatef(giro_vert, 1, 0, 0);
    glScalef(0.35, 0.35, 0.35);
    CrearCabezaSerpiente();
    CrearOjosSerpiente();
    CrearLenguaSerpiente();
    CrearTorsoSerpiente();
    glPopMatrix();

    // Dibuja los segmentos de la serpiente en las coordenadas correspondientes
    for (size_t i = 0; i < segmentos.size(); ++i) {
        const auto& segmento = segmentos[i];
        glPushMatrix();
        glTranslatef(segmento.first, 0.08, segmento.second);
        glRotatef(giro_hor, 0, 1, 0);
        glRotatef(giro_vert, 1, 0, 0);
        glScalef(0.35, 0.35, 0.35);
        CrearTorsoSerpiente();
        glPopMatrix();
    }
}



void igvSnake::girarHor(float rot) {
    giro_hor += rot;
    if (giro_hor > 270) {
        giro_hor = 0;
    }
    if (giro_hor < 0) {
        giro_hor = 270;
    }
}

float igvSnake::getGiroHor() {
    return giro_hor;
}

void igvSnake::set_animacion(bool _animacion) {
    animacion = true;
}

bool igvSnake::get_animacion() {
    return animacion;
}

void igvSnake::setCoordX(float col) {
    float tamCasillaX = 4.0 / columnas;
    coordX = -2 + col * tamCasillaX;
}

void igvSnake::setCoordZ(float fil) {
    float tamCasillaZ = 4.0 / filas;
    coordZ = -2 + fil * tamCasillaZ;
}

float igvSnake::getCoordX() {
    return coordX;
}

float igvSnake::getCoordZ() {
    return coordZ;
}

void igvSnake::setColumna(float col) {
    if(col>10){
        columna1=0;
    }else if(col<0){
        columna1=10;
    }else{
        columna1 = col;
    }
}

void igvSnake::setFila(float fil) {
    if(fil>10){
        fila1 = 0;
    }else if(fil<0){
        fila1 = 10;
    }else{
        fila1 = fil;
    }
}

float igvSnake::getColumna() {
    return columna1;
}

float igvSnake::getFila() {
    return fila1;
}

void igvSnake::crecer() {
    float newX, newZ;

    // Si hay al menos un segmento en la serpiente, toma las coordenadas del último segmento
    if (!segmentos.empty()) {
        newX = segmentos.back().first;
        newZ = segmentos.back().second;
    } else {
        // Si la serpiente está vacía, toma las coordenadas de la cabeza
        newX = coordX;
        newZ = coordZ;
    }

    // Agrega el nuevo segmento al vector
    segmentos.push_back(std::make_pair(newX, newZ));
}

bool igvSnake::hayColision() {
    for(int i = 0; i < segmentos.size(); i++){
        if((coordX == segmentos[i].first) &&
           (coordZ == segmentos[i].second)){
            return true;
        }
    }
    return false;
}


void igvSnake::moverSerpiente(float oldCoordX, float oldCoordZ) {
    for (int i = segmentos.size() - 1; i >= 0; --i) {
        if (i == 0) {
            segmentos[i].first = oldCoordX;
            segmentos[i].second = oldCoordZ;
        } else {
            segmentos[i].first = segmentos[i - 1].first;
            segmentos[i].second = segmentos[i - 1].second;
        }
    }
    if (hayColision()) {
        exit(1);
    }
}

std::vector<std::pair<float, float>> igvSnake::getSegmentos(){
    return segmentos;
}