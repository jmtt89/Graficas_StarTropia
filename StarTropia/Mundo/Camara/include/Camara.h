#ifndef CAMARA_H
#define CAMARA_H

#include "../../../Jugador/include/Jugador.h"
class Camara{
	public:
		//Atributos
			//Look At
		GLfloat Lx,Ly,Lz; //Hacia donde vemos
		GLfloat Px,Py,Pz; //Poiscion de la Camara
		GLfloat Ux,Uy,Uz; //Arriba
		
			//Perspectiva
		GLint pCerca,pLejos;
		GLfloat Aperture, Aspect;
		
        GLfloat width;
        GLfloat height;		
		
		GLfloat colorNiebla[4];
		
        bool color_material;
        bool lighting;		
		
		//Funciones
		Camara(Jugador *Nave);
		virtual ~Camara();
		
		void Update(Jugador *Nave);
		void Begin();
		void End();		
		void Draw_Zero();		
		void Keyboard(unsigned char k);
        void Reshape(int w, int h);
	    void Perspective();
	    
	    
	    void Begin_Ortho2D();
	    void End_Ortho2D();
	    
    private:
        void configuracion_3D();
		
};

#endif
