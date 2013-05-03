/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#include "../include/Edificio.h"

void Edificio::LoadTexture(const char *direccion){
    char _nombres[6][60];
    SDL_Surface *imagen[6];
        
    strcpy( &_nombres[0][0], direccion );
    strcpy( &_nombres[1][0], direccion );
    strcpy( &_nombres[2][0], direccion );
    strcpy( &_nombres[3][0], direccion );
    strcpy( &_nombres[4][0], direccion );
    strcpy( &_nombres[5][0], direccion );
    strcat( &_nombres[0][0], "Right.jpg" );
    strcat( &_nombres[1][0], "Left.jpg" );
    strcat( &_nombres[2][0], "Up.jpg" );
    strcat( &_nombres[3][0], "Down.jpg" );
    strcat( &_nombres[4][0], "Front.jpg" );
    strcat( &_nombres[5][0], "Back.jpg" );
    glGenTextures(6, &texture[0] );
    for( int n = 0; n <6 ; ++n ) {
        glBindTexture( GL_TEXTURE_2D, texture[n] );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        imagen[n] = IMG_Load( &_nombres[n][0] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imagen[n]->w, imagen[n]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen[n]->pixels);
        SDL_FreeSurface( imagen[n] );
        imagen[n] = NULL;
    }
}

Edificio::Edificio(int Tipo)
	:staticAgent()
	{

    switch(Tipo){
        case 0:
            this->dminx = 1.0f;
            this->dminy = 1.0f;
            this->dminz = 1.0f;
            this->dmaxx = 1.0f;
            this->dmaxy = 1.0f;
            this->dmaxz = 1.0f;
            break;
        case 1:
            this->dminx = 0.7f;
            this->dminy = 1.0f;
            this->dminz = 1.85f;
            this->dmaxx = 2.0f;
            this->dmaxy = 4.0f;
            this->dmaxz = 1.0f;
            break;
        case 2:
            this->dminx = 1.0f;
            this->dminy = 1.0f;
            this->dminz = 5.4f;
            this->dmaxx = 1.37f;
            this->dmaxy = 1.5f;
            this->dmaxz = 1.6f;
            break;
    }


    glListBase(0);
    lista = glGenLists(2);

    // -- CARGAMOS LOS MODELOS OBJ -----------------------------------------------
    C_Obj *Modelo_OBJ = new C_Obj[3];	
    Modelo_OBJ[0].Carga( "Modelos/Edificios/T_1/cubo.obj" );
    Modelo_OBJ[1].Carga( "Modelos/Edificios/T_2/edificio1.obj" );
    Modelo_OBJ[2].Carga( "Modelos/Edificios/T_3/edificio2.obj" );


    // -- CREAMOS LAS LISTAS COMPILADAS USANDO LOS MODELOS OBJ -------------------
    glNewList( lista + 0, GL_COMPILE ); // Sin textura
    	//glTranslatef(0,-1.25,0);
        Modelo_OBJ[Tipo].Dibuja_Todo_Shadows();
    glEndList();

    // -- CARGAMOS LAS TEXTURAS DE LOS MODELOS OBJ -------------------------------
    c_textura_2D *textura_2D[2];
    textura_2D[0] = new c_textura_2D[ Modelo_OBJ[Tipo].N_Texturas() ];
    Modelo_OBJ[Tipo].Carga_Texturas( textura_2D[0], 0 );

    glNewList( lista + 1, GL_COMPILE ); // Con textura
    	//glTranslatef(0,-1.25,0);
        Modelo_OBJ[Tipo].Dibuja_Todo();
    glEndList();
                                    

    // -- BORRAMOS LOS OBJETOS, YA NO LOS NECESITAMOS ----------------------------
    delete[] Modelo_OBJ;
        
        

	}

Edificio::~Edificio(){
	std::cout << "Destructo de Anillo "<< std::endl;
}


void Edificio::Assign(GLfloat x,GLfloat y,GLfloat z)
{
	staticAgent::Assign(x,y,z);	
}

void Edificio::Update(GLfloat Actualz){
    if(this->Alive){
        if(this->z > Actualz + 10 ){
            this->Alive = false;
	    }
    	staticAgent::Update();
	}
}

void Edificio::Draw(){
    if(this->Alive){
       
	glPushMatrix();
    		glTranslatef(this->x,this->y,this->z);		
		glCallList( lista + 1);
	glPopMatrix();              
        
         //Verificar el cubo de colision
        glBegin(GL_LINES);

	        glColor3ub(255,0,0);
	        glVertex3f(this->minx,this->miny,this->minz);
	        glVertex3f(this->maxx,this->maxy,this->maxz);

        glEnd();
        

        staticAgent::Draw();
    }
}

void Edificio::Draw_Shadow(){
	if(this->Alive){
	glPushMatrix();
    		glTranslatef(this->x,this->y,this->z);		
		glCallList( lista + 0);
	glPopMatrix();
	}
}

bool Edificio::Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
    if(this->Alive)
	    return staticAgent::Collision(minX,  minY,  minZ,  maxX, maxY,  maxZ);	
    return false;
}

bool Edificio::Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
    if(this->Alive)
	    return staticAgent::Collision2(minX,  minY,  minZ,  maxX, maxY,  maxZ);	
    return false;
}
