# Para usar este archivo, hacer:
#
#        make inicio
#
# ALfredo Gallardo 0639563
# Jesus Torres 0640386


CC = g++
LDLIBS = -lglut -lGL -lGLU -lSDL -lSDL_image -lopenal -lalut -fpermissive
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

inicio:
	$(CC) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LDLIBS) glm.h glm.c Resources/Libs/Mirror.h Resources/Libs/Mirror.cpp Resources/Libs/Texturas_2D.h Resources/Libs/Texturas_2D.cpp Resources/Libs/Cargador_Obj.h Resources/Libs/Cargador_Obj.cpp Resources/Libs/Luces.h Resources/Libs/Luces.cpp Resources/Libs/Sombras.h Resources/Libs/Sombras.cpp Resources/Libs/Entorno.h Resources/Libs/Entorno.cpp Resources/Libs/Materiales.h Resources/Libs/Materiales.cpp moveAgent/include/moveAgent.h moveAgent/src/moveAgent.cpp staticAgent/src/staticAgent.cpp staticAgent/include/staticAgent.h Target/src/Target.cpp Target/include/Target.h Jugador/Disparo/include/Disparo.h Jugador/Disparo/src/Disparo.cpp Jugador/include/Jugador.h Jugador/src/Jugador.cpp Edificio/include/Edificio.h Edificio/src/Edificio.cpp Anillo/include/Anillo.h Anillo/src/Anillo.cpp Mundo/Camara/include/Camara.h Mundo/Camara/src/Camara.cpp Mundo/include/Mundo.h Mundo/src/Mundo.cpp -g main.cpp -o main

clean:
	rm *.o
