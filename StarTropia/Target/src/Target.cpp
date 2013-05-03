#include "../include/Target.h"

// Constructor de Target ( inicial )
Target::Target(int Ident)
	:moveAgent()
	{
	// Se carga el modelo 
	    this->modelo = glmReadOBJ("Modelos/meteoro.obj");

	    // Inicializacion de los valores del Target
	    this->ID = Ident; 
        this->radio =0.0f;
        this->TimeCT = 0.0f;
        this->TimeT = 0.0f;
        
		glListBase(0);
    	lista = glGenLists(1);

        	
	    material = new c_material[1]; //1 Materiales
	    
        material[0].diffuse(0.9f,0.9f,0.9f); 
        material[0].ambient(0.9f,0.9f,0.9f);
        material[0].specular(0.1f,0.1f,0.1f);
        material[0].emissive(0.0f,0.0f,0.0f);                        
        material[0].phongsize(0.9f * 128.0f);
        
        
	}

// Destructor de Target
Target::~Target(){
	
}

// Asignador de los valores de Target	
void Target::Assign(GLfloat x,GLfloat y,GLfloat z,GLfloat Angle,GLfloat Look)
{

	moveAgent::Assign(x,y,z,Angle,Look);
	
    glNewList( lista , GL_COMPILE );
		glPushMatrix();
            glTranslatef(this->x,this->y,this->z);
			glRotatef(180,0,0,1);
			glRotatef(80,1,0,0);
			glScalef(0.01,0.01,0.01);
			glmDraw(this->modelo, GLM_SMOOTH );
		glPopMatrix();
    glEndList();


}

// Actualiza las variables correspondientes al Target
void Target::Update(GLfloat Actualz,float Time){
    if(this->Alive){
        if(this->z > Actualz + 10 ){
            this->Alive = false;
            glDeleteLists( lista,  1 );
        }
        
        if(this->collide){
            TimeCT += Time - TimeT;
	        TimeT = Time;
        }

	    moveAgent::Update();
	}
}

// Funcion para dibujar el Target en pantalla
void Target::Draw(){

	//Mientras esta vivo el blanco
	if(this->Alive){

        material[0].activa();
		//Carga un identificador para el clicking
		glLoadName(this->ID);
		
		glCallList( lista );
		
        material[0].desactiva();
	}

	//Si el objeto colisiona con un proyectil se genera la animacion y la iluminacion
    if(this->collide){
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(0.9 + radio, 0.7, 0.7, 0.0);

        float position[] = {this->x,this->y,this->z,1};
        float diffuse[] = {0.75, 0.5, 0.5, 1.0};
        glLightfv(GL_LIGHT2, GL_POSITION, position);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);

        glEnable(GL_LIGHT2);

        glPushMatrix();

        if( radio < 1.5 ){ 
            if ( TimeCT < 0.5 ) {
                glTranslatef(this->x,this->y,this->z);
                glutSolidSphere(radio,20,60);
                radio += 0.05f;
            }else{
                TimeCT=0;
                }
        }else{
            this->collide = false;
            radio = 0.0f;
            glDisable(GL_LIGHT2);
        }
        glPopMatrix();

    }
    

    moveAgent::Draw();

}

// Funcion para dibujar el Target en pantalla
void Target::Draw_Shadow(){

	//Mientras esta vivo el blanco
	if(this->Alive){
        material[0].desactiva();
		glCallList( lista );
	}
}


//Verifica la colision del Target con algun proyectil.
bool Target::Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,int Light){
    bool Tmp = false;    
    if(this->Alive){	
        
        Tmp = moveAgent::Collision(minX, minY, minZ,  maxX,  maxY,  maxZ);

        if(Tmp){
            this->Alive = false;
        }

    }
    return Tmp;
}

//Verifica la colision del Target con algun proyectil.
bool Target::Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
    if(this-> Alive)
        return moveAgent::Collision2(minX, minY, minZ,  maxX,  maxY,  maxZ);

    return false;
}
