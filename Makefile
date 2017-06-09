SRC := $(subst $(shell cd)\,,$(shell for /r . %%s in (*.cpp) do @echo %%s))
OBJ := $(patsubst src%.cpp,obj%.o,$(SRC))
LIB := -lglfw3dll -lopengl32 -lglew32
FLAGS := -Wall -std=c++11 -O2 -I src

main: $(OBJ)
	@echo Linking object files...
	@g++ $(OBJ) $(FLAGS) -o main $(LIB)

$(OBJ): obj\\%.o: src\\%.cpp
	@echo Compiling $^
	@if not exist $(dir $@) mkdir $(dir $@)
	@g++ -c $^ $(FLAGS) -o $@ $(LIB)

clean:
	@echo Cleaning object files...
	@rd /s /q obj
