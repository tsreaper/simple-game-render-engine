SRC := $(shell for /r . %%s in (*.cpp) do @echo %%s)
LIB := -lglfw3dll -lopengl32 -lglew32

main: $(SRC)
	@g++ $(SRC) -O2 -o main $(LIB)

clean:
	@del main.exe
