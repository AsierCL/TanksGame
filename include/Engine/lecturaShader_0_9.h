//
//  lectura_shader.h
//  Transformaciones3D
//
//
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


GLuint vertexShader, fragmentShader;
GLuint  progShader;                 

char *textFileRead(const char *fn) {
    FILE *fichero;
    char *contenido = NULL;
    int count = 0;
    
    if (fn != NULL) {
        fichero = fopen(fn, "rt");
        if (fichero != NULL) {
            fseek(fichero, 0, SEEK_END);
            count = ftell(fichero);
            rewind(fichero);
            if (count > 0) {
                contenido = (char *)malloc(sizeof(char) * (count + 1));
                count = fread(contenido, sizeof(char), count, fichero);
                contenido[count] = '\0';
            }
            fclose(fichero);
        }
        else {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return NULL;
        }
    }
    return contenido;
}

void printShaderInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0){
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0) {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}


GLuint setShaders(const char *nVertx, const char *nFrag) {
    char *ficherovs = NULL;
    char *ficherofs = NULL;
    const char * codigovs = NULL;
    const char * codigofs = NULL;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    ficherovs = textFileRead(nVertx);
        if (ficherovs == NULL) return 0;
    ficherofs = textFileRead(nFrag);
        if (ficherofs == NULL) return 0;

    codigovs = ficherovs;
    codigofs = ficherofs;
    glShaderSource(vertexShader, 1, &codigovs,NULL);
    glShaderSource(fragmentShader, 1, &codigofs,NULL);

    free(ficherovs);free(ficherofs);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    printShaderInfoLog(vertexShader);
    printShaderInfoLog(fragmentShader);

    progShader = glCreateProgram();

    glAttachShader(progShader,vertexShader);
    glAttachShader(progShader,fragmentShader);

    glLinkProgram(progShader);
    printProgramInfoLog(progShader);

    return (progShader);
}


