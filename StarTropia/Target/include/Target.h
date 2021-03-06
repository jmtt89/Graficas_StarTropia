/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#ifndef TARGET_H
#define TARGET_H

#include <GL/gl.h>										
#include <GL/glu.h>		
#include "../../moveAgent/include/moveAgent.h"
#include "../../Resources/Libs/Materiales.h"
#include "../../Resources/Libs/Luces.h"

// Clase Taget usada para determinar los objetos que son blancos en el juego
class Target: public moveAgent{
	public:
	//Atributos
        GLMmodel* modelo;
        int ID;
		float radio;
		float TimeCT;
		float TimeT;
        int Light;
		c_luz *luz;
        c_material *material;
        GLuint lista;
	//Funciones	
        Target(int ID);	
		virtual ~Target();		
		void Assign(GLfloat x,GLfloat y,GLfloat z,GLfloat Angle,GLfloat Look);
		void Update(GLfloat Actualz,float Time);
		void Draw();
		void Draw_Shadow();		
		bool Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, int Light);
		bool Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
};

#endif
