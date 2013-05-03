#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

#include "Mundo/include/Mundo.h"

using namespace std;

int Width = 800;
int Height = 600;
int FPS = 60.0f/1000.0f;
Mundo* nivel;

//Cosas de la nave
GLfloat anguloV = 180.0;
GLfloat anguloH = 80.0;
GLMmodel* modelo;
GLfloat POS[] {0,0,0};

//Componentes Material Nave
GLfloat mShininess[] = {0.1 * 128}; //Brillosidad
GLfloat DiffuseMaterial[] = {0.2,0.2,0.2,0.0}; //Color del material
//GLfloat DiffuseMaterial[] = {1,0.0,0.0,0.0}; //Color del material al ser tocado
GLfloat SpecularMaterial[] = {0.6,0.6,0.6, 0.0}; //Refleja Luz


GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Posicion de la luz de la escena


void light (void) {
glLightfv(GL_LIGHT0, GL_POSITION, light_position); // LUz de la escena
//Luces de la nave
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);

}

void drawmodel(char* C)
{
    if (!modelo) {
        modelo = glmReadOBJ(C);
        if (!modelo) 
              exit(0);
        glmUnitize(modelo);
        glmFacetNormals(modelo);
        glmVertexNormals(modelo, 90.0);
    }
    
    glmDraw(modelo, GLM_SMOOTH );
}

/** Manejo por el teclado **/
static void letra (unsigned char k, int x, int y){
    switch (k){
        case 'w':
		if (POS[2] < 2)		
	            POS[2] += 0.1;
            break;
        case 's':
		if (POS[2] > -2)
	            POS[2] -= 0.1;
            break;
        case 'a':
		if (POS[0] < 2)
	            POS[0] += 0.1;
            break;
        case 'd':
		if (POS[0] > -2)
           	 POS[0] -= 0.1;
            break;
        case 27:  /* Escape */
            exit(0);
            break;
        default:
            return;
    }

    glutPostRedisplay();
}

void init(){
    	glEnable (GL_DEPTH_TEST);
    	glEnable (GL_LIGHTING);
    	glEnable (GL_LIGHT0);
	
	//nivel = new Mundo();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void Update(){
	//nivel->Update();
}

void Draw(){

	glClearColor(0.0f, 0.0f, 0.0f ,1.0f);				
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	light();
	glMatrixMode(GL_MODELVIEW);


//Probando nave
	glTranslatef(0,0,-5);

	glPushMatrix();
		glRotatef(anguloV,0,0,1);
		glRotatef(anguloH,1,0,0);

		glTranslatef(POS[0],POS[1],POS[2]);
		drawmodel("Modelos/Batwing.obj");
	glPopMatrix();

	glutSwapBuffers();

	//nivel->Draw();
	
    glFlush();

}

void FrameBuffer(int i){
	glutPostRedisplay();
}

int main(int argc,char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Width,Height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("StarTropia");
	init();
	
	glutDisplayFunc(Draw);
	//glutIdleFunc(Update);
	glutKeyboardFunc(letra);
	glutIdleFunc (Draw);
	glutTimerFunc(FPS,FrameBuffer,1);

	glutReshapeFunc (reshape);
	glutMainLoop();
	return 0;
}
