#ifndef MUNDO_H
#define MUNDO_H

#include <stdio.h>
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alut.h>

#include "../Camara/include/Camara.h"
#include "../../Jugador/include/Jugador.h"
#include "../../Edificio/include/Edificio.h"
#include "../../Anillo/include/Anillo.h"
#include "../../Target/include/Target.h"
#include "../../Resources/Libs/Entorno.h"
#include "../../Resources/Libs/Materiales.h"
#include "../../Resources/Libs/Luces.h"
#include "../../Resources/Libs/Sombras.h"

#define NUM_SOURCES 3
#define NUM_BUFFERS 3

class Mundo{
	public:
		//Atributos
		float TimeG;
		float Time_A;
		float TimeB;
		float TimeAC;
		float TimeBC ;
		float Time_Mete;
		float TimeCC;		
		float Time_C;

		float TiempoContador;
		bool Inicio;
		bool in_Menu;
		
        c_entorno *entorno;
		c_luz *luz;
        c_material *material;
		//Funciones
		Mundo();
		virtual ~Mundo();
	
		void Keyboard(unsigned char k);//Captura por teclado
    	void Reshape(int W, int H);
        
		void Update(float Time);
		void Draw();
		void renderString(float x, float y, float z, void *font, char *string);
		char buffer [33];
		char buffer1 [33];
		char buffer2 [33];		


        GLuint lista;
		void mouse(int x,int y);
		void gl_select(int x, int y);
		void list_hits(GLint hits, GLuint *names);

		ALsizei size,freq;
		ALenum 	format;
		ALvoid 	*data;
		
	private:
	//Atributos
		static const int Max_Target = 6;
		Target *Targets[Max_Target];
		
		static const int Max_Anillo = 20;
		Anillo *Anillos[Max_Anillo];
		
		static const int Max_Edificio = 10;
        Edificio *Edificios[Max_Edificio];	
        GLfloat Plano[4];

		Jugador* Nave;
		Camara *Cam;

		ALuint	bufferS[NUM_BUFFERS];
		ALuint	source[NUM_SOURCES];
		
        //Funciones
		void Menu();
		void Run(float Time);
		void Draw_Menu();
		void Draw_Game();
		void ReSpam();
		void CrearAnillo();
		void CrearMeteorito();
		void CrearEdificio();
		int MeteoritosMundo(int i);
		int AnillosMundo(int i);
		int EdificiosMundo(int i);
		void Init();
		
};

#endif
