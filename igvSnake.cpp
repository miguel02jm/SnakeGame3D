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
    glTranslatef(coordX, 0, coordZ);
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
        glTranslatef(segmento.first, 0, segmento.second);
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
    if (_animacion == true)
        animacion = false;
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

int igvSnake::obtenerFilaDesdeCoordZ(float coordZ) {
    // Asumiendo que coordZ está en el rango [-2, 2] y hay 10 filas en total
    int filas = 10;
    float tamCasillaZ = 4.0 / filas;
    int fila = static_cast<int>((coordZ + 2.0) / tamCasillaZ);

    // Asegúrate de que la fila esté en el rango correcto
    fila = std::max(0, std::min(filas - 1, fila));

    return fila;
}

int igvSnake::obtenerColumnaDesdeCoordX(float coordX) {
    // Asumiendo que coordX está en el rango [-2, 2] y hay 10 columnas en total
    int columnas = 10;
    float tamCasillaX = 4.0 / columnas;
    int columna = static_cast<int>((coordX + 2.0) / tamCasillaX);

    // Asegúrate de que la columna esté en el rango correcto
    columna = std::max(0, std::min(columnas - 1, columna));

    return columna;
}

bool igvSnake::hayColision() {
    for(int i = 0; i < segmentos.size(); i++){
        if((coordX >= segmentos[i].first - 0.15 && coordX <= segmentos[i].first + 0.15) &&
           (coordZ >= segmentos[i].second - 0.15 && coordZ <= segmentos[i].second + 0.15)){
            return true;
        }
    }
    return false;
}


void igvSnake::moverSerpiente(float oldCoordX, float oldCoordZ) {
    // Inicializar todas las casillas de la matriz como vacías (0)
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrizEscenario[i][j] = 0;
        }
    }

    // Actualiza las coordenadas de los segmentos y la matriz del escenario
    for (int i = segmentos.size() - 1; i >= 0; --i) {
        if (i == 0) {
            // Primer elemento sigue a la cabeza
            segmentos[i].first = oldCoordX;
            segmentos[i].second = oldCoordZ;
        } else {
            // Elementos siguientes siguen al anterior
            segmentos[i].first = segmentos[i - 1].first;
            segmentos[i].second = segmentos[i - 1].second;
        }

        // Actualiza la matriz del escenario
        int fila = obtenerFilaDesdeCoordZ(segmentos[i].second);
        int columna = obtenerColumnaDesdeCoordX(segmentos[i].first);
        matrizEscenario[fila][columna] = 1; // Marca la posición de la serpiente
    }

    if (hayColision()) {
        exit(1);
    }
}


