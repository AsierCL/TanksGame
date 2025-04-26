###############################################
# Makefile para ProyectoFinal (OpenGL Tanks)   
###############################################

# Compilador y flags
gCXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -IEngine -IUtils -IGame

# Librerías a enlazar
LIBS = -lglfw -lGL -ldl -lm

# Directorios
SRC_DIR := .
ENGINE_DIR := Engine
UTILS_DIR := Utils
GAME_DIR := Game

# Ficheros fuente
SRC := $(wildcard $(SRC_DIR)/main.cpp) \
       $(wildcard $(ENGINE_DIR)/*.cpp) \
       $(wildcard $(GAME_DIR)/*.cpp)

# Incluir glad.c manualmente
SRC += $(UTILS_DIR)/glad.c

# Objetos generados
OBJ := $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

# Nombre del ejecutable
target = ProyectoFinal

.PHONY: all clean run

all: $(target)

$(target): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Regla genérica para .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla genérica para .c -> .o (glad.c)
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(target)

clean:
	rm -f $(OBJ) $(target)
