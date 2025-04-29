#ifndef DRAW_H
#define DRAW_H
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Objects/Object.h"

extern unsigned int gVAO_Ejes, gVAO_Cuadrado, gVAO_Cubo, gVAO_Esfera, gVAO_Arbol;
extern objeto suelo, arbol1, arbol2, arbol3, arbol4;

void inicializarVAOs();
void dibujarSuelo();
void dibujarCubo();
void dibujarEsfera();
void dibujarArbusto();
void dibujarObjeto(glm::mat4& stack, unsigned int transformLoc, unsigned int colorLoc, objeto obj, bool dibujarRueda);
void dibujarSinRef(unsigned int transformLoc, unsigned int colorLoc, objeto obj, int textura);

#endif // DRAW_H