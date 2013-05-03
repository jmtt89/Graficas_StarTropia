/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#include "../include/moveAgent.h"

// Constructor de moveAgent ( inicial )
moveAgent::moveAgent(){

	// Pos del objeto.
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->Angle = 0.0f;
	this->Look = 0.0f;
	this->Alive = false;
	
	// Pos de la caja de colisiones.
	this->minx = 0.0f;
	this->miny = 0.0f;
	this->minz = 0.0f;
	this->maxx = 0.0f;
	this->maxy = 0.0f;
	this->maxz = 0.0f;

	this->dminx = 0.3f;
	this->dminy = 0.3f;
	this->dminz = 0.3f;
	this->dmaxx = 0.3f;
	this->dmaxy = 0.3f;
	this->dmaxz = 0.3f;

	this->collide = true;

}

//  Destructor de Move Agent
moveAgent::~moveAgent()
{	
	
}

// Asignador de valores de static Agent
void moveAgent::Assign(GLfloat x,GLfloat y,GLfloat z,GLfloat Angle,GLfloat Look){
	// Variables para indicar la pos del objeto.
	this->x = x;
	this->y = y;
	this->z = z;
	this->Angle = Angle;
	this->Look = Look;

	// determina si un objeto esta vivo.
	this->Alive = true;

	// determina si un objeto ha colisionado.
	this->collide = false;

	// Posiciones de los puntos maximos y minimos de la caja de colision.
	this->minx = x - this->dminx;
	this->miny = y - this->dminy;
	this->minz = z + this->dminz;	
	this->maxx = x + this->dmaxx;
	this->maxy = y + this->dmaxy;
	this->maxz = z - this->dmaxz;

}

void moveAgent::Update()
{

}

void moveAgent::Draw()
{

}

// Funcion para verificar la colision del objeto actual con los puntos
// maximos y minimos de otro objeto.
bool moveAgent::Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    if(!this->collide){
        this->collide =this->Alive && 
                       (this->maxx > minX && 
                        this->minx < maxX &&
                        this->maxy > minY &&
                        this->miny < maxY &&
                        this->maxz < minZ &&
                        this->minz > maxZ);

        return this->collide;
    }

    return false;

}

// Funcion para verificar la colision del objeto actual con los puntos
// maximos y minimos de otro objeto.
bool moveAgent::Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    return this->Alive && 
                       (this->maxx > minX && 
                        this->minx < maxX &&
                        this->maxy > minY &&
                        this->miny < maxY &&
                        this->maxz < minZ &&
                        this->minz > maxZ);

}


