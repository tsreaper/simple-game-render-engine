LINKS := -lglfw3dll -lopengl32 -lglew32

main: tmp/main.o tmp/displayManager.o tmp/loader.o tmp/renderer.o tmp/shaderProgram.o tmp/staticShader.o tmp/rawModel.o tmp/texturedModel.o tmp/modelTexture.o tmp/lodepng.o
	g++ tmp/main.o tmp/displayManager.o tmp/loader.o tmp/renderer.o tmp/shaderProgram.o tmp/staticShader.o tmp/rawModel.o tmp/texturedModel.o tmp/modelTexture.o tmp/lodepng.o -o main $(LINKS)

tmp/main.o: src/main.cpp
	g++ -c src/main.cpp -o tmp/main.o $(LINKS)

tmp/displayManager.o: src/renderEngine/displayManager.cpp
	g++ -c src/renderEngine/displayManager.cpp -o tmp/displayManager.o $(LINKS)

tmp/loader.o: src/renderEngine/loader.cpp
	g++ -c src/renderEngine/loader.cpp -o tmp/loader.o $(LINKS)

tmp/renderer.o: src/renderEngine/renderer.cpp
	g++ -c src/renderEngine/renderer.cpp -o tmp/renderer.o $(LINKS)

tmp/shaderProgram.o: src/shaders/shaderProgram.cpp
	g++ -c src/shaders/shaderProgram.cpp -o tmp/shaderProgram.o $(LINKS)

tmp/staticShader.o: src/shaders/staticShader.cpp
	g++ -c src/shaders/staticShader.cpp -o tmp/staticShader.o $(LINKS)

tmp/rawModel.o: src/models/rawModel.cpp
	g++ -c src/models/rawModel.cpp -o tmp/rawModel.o $(LINKS)

tmp/texturedModel.o: src/models/texturedModel.cpp
	g++ -c src/models/texturedModel.cpp -o tmp/texturedModel.o $(LINKS)

tmp/modelTexture.o: src/textures/modelTexture.cpp
	g++ -c src/textures/modelTexture.cpp -o tmp/modelTexture.o $(LINKS)

tmp/lodepng.o: src/thirdparty/lodepng.cpp
	g++ -c src/thirdparty/lodepng.cpp -o tmp/lodepng.o $(LINKS)

clean:
	del /q tmp\*.*
