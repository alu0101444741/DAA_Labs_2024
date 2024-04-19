CXX = g++
CXXFLAGS = -std=c++14 -Wall
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
# SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES := $(wildcard $(SRC_DIR)/*.cpp) # Obtener la lista de todos los archivos en el directorio src
#IGNORE_CPP := $(wildcard src/binarysearch*.cpp) $(wildcard src/binarysearch*.h) # Lista de archivos que se deben ignorar
#SOURCES := $(filter-out $(IGNORE_CPP), $(SOURCES)) # Filtrar los archivos ignorados

HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/dnc_framework

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
