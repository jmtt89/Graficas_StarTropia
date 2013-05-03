/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#ifndef MOVEAGENT_H
#define MOVEAGENT_H

#include <iostream>
#include <sstream>
#include <GL/glut.h>
#include "../../glm.h"

// Clase moveAgent usada para objetos que se mueven en la escena.
class moveAgent{
	public:
        //Atributos
		GLfloat x,y,z;
		GLfloat Angle;
		GLfloat Look;
		bool Alive;
		float minx,miny,minz;
		float maxx,maxy,maxz;
		float dminx,dminy,dminz;
		float dmaxx,dmaxy,dmaxz;

		bool collide;
        //Funciones
        	moveAgent();
		virtual ~moveAgent();		
		void Assign(GLfloat x,GLfloat y,GLfloat z,GLfloat Angle,GLfloat Look);
		void Update();
		void Draw();
		bool Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		bool Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	private:

		
};

#endif
