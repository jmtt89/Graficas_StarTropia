/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#include "../include/Anillo.h"

// Constructor de Anillo ( inicial )
Anillo::Anillo()
	:staticAgent()
	{
	
		glListBase(0);
    	lista = glGenLists(1);

        	
	    material = new c_material[2]; //2 Materiales
	    
        material[0].diffuse(0.9f,0.7f,0.1f); //Sin Chocar
        material[0].ambient(0.9f,0.7f,0.1f);
        material[0].specular(0.4f,0.4f,0.4f);
        material[0].emissive(0.0f,0.0f,0.0f);                        
        material[0].phongsize(128.0f);
        
        material[1].diffuse(0.0f,0.7f,0.1f); //Cuando Choca
        material[1].ambient(0.0f,0.7f,0.1f);
        material[1].specular(0.4f,0.4f,0.4f);
        material[1].emissive(0.0f,0.0f,0.0f);                        
        material[1].phongsize(128.0f);
        

	}

// Destructor de Anillo
Anillo::~Anillo(){
	std::cout << "Destructo de Anillo "<< std::endl;
}
	
// Asignador de los valores de Anillo
void Anillo::Assign(GLfloat x,GLfloat y,GLfloat z)
{
	staticAgent::Assign(x,y,z);
	
    glNewList( lista , GL_COMPILE );
        glPushMatrix();	
            glTranslatef(this->x,this->y,this->z);
            glutSolidTorus(0.05,0.4,20,50);
        glPopMatrix();
    glEndList();
	

}

// Actualiza las variables correspondientes al Anillo
void Anillo::Update(GLfloat Actualz){
    if(this->Alive){

        if(this->z > Actualz + 10 ){
            this->Alive = false; 
            glDeleteLists( lista,  1 );
	    }
    	staticAgent::Update();
	}
}

// Funcion para dibujar el Anillo en pantalla
void Anillo::Draw(){
    if(this->Alive){

        // Verifica una colision
        if(this->collide)
	        material[1].activa(); 
        else
	        material[0].activa();

        glCallList( lista );
            
        material[0].desactiva();
        material[1].desactiva();        

        /* //Verificar el cubo de colision
        glBegin(GL_LINES);

	        glColor3ub(0,255,0);
	        glVertex3f(this->minx,this->miny,this->minz);
	        glVertex3f(this->maxx,this->maxy,this->maxz);

        glEnd();
        */		

        staticAgent::Draw();
    }
}

// Funcion para dibujar el Anillo en pantalla
void Anillo::Draw_Shadow(){

	//Mientras esta vivo el Anillo
	if(this->Alive){
        material[0].desactiva();
        material[1].desactiva();  
        glCallList( lista );
	}
}

// Funcion para verificar la colision de ANillos con la Nave
bool Anillo::Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
	if(this-> Alive)
		return staticAgent::Collision(minX,  minY,  minZ,  maxX, maxY,  maxZ);
	
	return false;	
}

// Funcion para verificar la colision de ANillos con la Nave
bool Anillo::Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
	if(this-> Alive)
		return staticAgent::Collision2(minX,  minY,  minZ,  maxX, maxY,  maxZ);
	
	return false;	
}
