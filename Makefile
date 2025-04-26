###############################################
# Makefile para ProyectoFinal (OpenGL Tanks)   
###############################################

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iinclude/Engine -Iinclude/Engine/Objects -Iinclude/Utils

# Librerías a enlazar
LIBS = -lglfw -lGL -ldl -lm

# Ficheros fuente
SRC = \
    main.cpp \
    src/Engine/Camera.cpp \
    src/Engine/Shaders.cpp \
    src/Engine/Objects/Bullet.cpp \
    src/Engine/Objects/GameObject.cpp \
    src/Engine/Objects/Tank.cpp \
    src/Engine/Objects/Wall.cpp \
    src/Utils/glad.c

# Archivos objeto generados
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

# Nombre del ejecutable
target = ProyectoFinal

.PHONY: all clean run

all: $(target)

$(target): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Reglas genéricas
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(target)

clean:
	rm -f $(OBJ) $(target)
