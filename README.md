# 🕹️ Juego de Tanques 3D para 2 Jugadores

Proyecto desarrollado como parte de la asignatura de Computación Gráfica. Se trata de un juego de tanques en 3D para dos jugadores, con soporte de texturas, iluminación, sonido, colisiones y múltiples técnicas gráficas, todo implementado en C++ con OpenGL (GLFW + GLAD).

## 📁 Estructura del Proyecto
```
ProyectoFinal/
├── assets/
│ ├── audio/ # Efectos de sonido y música de fondo (WAV)
│ └── textures/ # Texturas de tanques, suelo, muros, etc. (PNG)
├── include/
│ ├── Engine/ # Cabeceras del motor gráfico: cámara, audio, shaders, etc.
│ └── Utils/ # Geometrías, constantes, stb_image.h
├── src/
│ ├── Engine/ # Código fuente del motor
│ └── Utils/ # glad.c y utilidades generales
├── shaders/ # Shaders GLSL: vertex y fragment
├── main.cpp # Punto de entrada, bucle principal
└── Makefile # Para compilar y ejecutar el proyecto
```

## 🎮 Controles

**Jugador 1**  
- Movimiento: `W`, `A`, `S`, `D`  
- Disparo: `X`  
- Rotar torreta: `Q`, `E`  

**Jugador 2**  
- Movimiento: `I`, `J`, `K`, `L`  
- Disparo: `M`  
- Rotar torreta: `U`, `O`  

**Cámara**  
- Mover cámara: Flechas  
- Subir/Bajar: `V` / `B`

## ✨ Características Técnicas

- **Renderizado OpenGL** con shaders personalizados.
- **Iluminación Phong** (ambiente, difusa, especular).
- **Texturizado** con PNG usando `stb_image.h`.
- **Audio** con SDL_mixer (música de fondo y efectos).
- **Detección de colisiones** entre proyectiles, muros y tanques.
- **Cámara en 3ª persona** controlable por el usuario.
- **Muros aleatorios** generados dinámicamente en el escenario.
- **Animaciones simples** y árboles con transparencias.

## 🛠️ Compilación y Ejecución

Este proyecto utiliza `Makefile` para compilar, limpiar y ejecutar.

### Requisitos previos

- C++ (C++17 o superior recomendado)
- OpenGL
- GLFW
- GLAD
- SDL2 + SDL2_mixer

### Comandos disponibles

```bash
make         # Compila el proyecto
make run     # Compila (si es necesario) y ejecuta el juego
make clean   # Elimina los binarios y archivos temporales

Ejemplo de uso

make         # Compila el proyecto
make run     # Ejecuta el binario generado
```

🎓 Proyecto desarrollado en el contexto de la asignatura de Computación Gráfica (USC).