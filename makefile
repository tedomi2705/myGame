SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR := obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEPENDS := $(patsubst %.o,%.d,$(OBJ_FILES))

CC = g++
OUT_DIR = bin\debug

OBJ_NAME = loldodge

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
COMPILER_FLAGS = -g -MMD
INCLUDE_PATHS = -IC:\SDL2-2.0.20\x86_64-w64-mingw32\include\SDL2
LIBRARY_PATHS = -LC:\SDL2-2.0.20\x86_64-w64-mingw32\lib

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@echo Compiling $<
	@$(CC) $< $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c -o $@


$(OUT_DIR)/loldodge.exe : $(OBJ_FILES)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR)
	@echo Building debug
	@$(CC) $(OBJ_FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT_DIR)/loldodge.exe
	@echo Done

release : COMPILER_FLAGS = -w -Wl,-subsystem,windows -static-libstdc++ -static-libgcc -MMD 
release : OUT_DIR = bin\release
release : $(OBJ_FILES)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR)
	@echo Building release
	@$(CC) $(OBJ_FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT_DIR)/loldodge.exe
	@echo Done
-include $(DEPENDS)
