CCX=g++


GAME2.o: someModule.o RenderSystem.o main.o 
	$(CCX) -o game02.exe someModule.o RenderSystem.o main.o

someModule.o: someModule.cpp
	$(CCX) -o someModule.o -c someModule.cpp

RenderSystem.o: RenderSystem.cpp
	$(CCX) -o RenderSystem.o -c RenderSystem.cpp

main.o: main.cpp
	$(CCX) -o main.o -c main.cpp