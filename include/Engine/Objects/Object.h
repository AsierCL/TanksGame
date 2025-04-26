#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
    float px, py, pz;       // initial position
    float angulo_trans;     // rotation angle (degrees)
    float angulo_rot;       // rotation angle (degrees)
    float velocidad;	
    float sx, sy, sz;       // scale factors
    float colores[3];
    int num_vertices;       // number of vertices
    unsigned int VAO;       // associated VAO handle
    int textura;
} objeto;

#endif // OBJECT_H