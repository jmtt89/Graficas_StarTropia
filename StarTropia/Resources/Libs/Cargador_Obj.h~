//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programación) www.scenebeta.com          --
//-- FECHA ÚLTIMA MODIFICACIÓN: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  código  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en él. Sin el  más --
//-- mínimo ánimo de lucro, siempre por la satisfacción del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  daño  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  ánimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este código que colabore en su mejora--
//-- y perfeccionamiento poniéndomelo en conocimiento por correo electrónico. --
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -- Cargador de Objetos ------------------------------------------------------
// -----------------------------------------------------------------------------
// -- Este cargador tiene ciertas limitaciones que vienen explicadas abajo:   --
// --                                                                         --
// -- #define Obj_N_Max 64   // Longitud máxima en carácteres de los nombres. --
// -- #define Obj_Linea 128  // Longitud máxima de la línea del archivo "OBJ" --
// --
// -- El primer carácter del archivo debe de ser un corchete '#'.             --
// --                                                                         --
// -- Los nombres de los archivos, objetos, materiales y  texturas no  pueden --
// -- contener espacios en blanco.                                            --
// -- Ejemplo: MAL-> "Textura verde.png"  BIEN-> "Textura_verde.png"          --
// --                                                                         --
// -- Es obligatorio contener la línea "mtllib Materiales.mtl" en la cual  se --
// -- especifica el archivo con los materiales. El nombre puede ser otro.     --
// --                                                                         --
// -- Es indispensable que cada objeto empiece con la  cadena  "o nombre", un --
// -- mismo archivo "OBJ" puede contener varios objetos.                      --
// --                                                                         --
// -- Los vértices (obligatorios) se definen empezando por el carácter 'v'.   --
// -- Las coordenadas de textura (opcionales) se definen con el carácter 'vt'.--
// -- Las normales de iluminación (opcionales) se definen con 'vn'.           --
// --                                                                         --
// -- Las caras después de definir el material a utilizar con "usemtl color"  --
// -- empiezan con una 'f' y siguen con los formatos posibles:                --
// --   "v", "v//", "v/vt/", "v/vt", "v//vn" o "v/vt/vn".                     --
// --                                                                         --
// -----------------------------------------------------------------------------
// -- Ejemplos de archivos OBJ y MTL válidos para este cargador               --
// -----------------------------------------------------------------------------
// -- ARCHIVO: "Triangulo_Cuadrado_y_Cubo.obj" ---------------------------------
// -----------------------------------------------------------------------------
// # Triangulo, Cuadrado y Cubo
// mtllib Materiales.mtl
// 
// o Triangulo
// v -3.0  1.0 0.0
// v -4.0 -1.0 0.0
// v -2.0 -1.0 0.0
// usemtl Amarillo
// f 1 2 3
// 
// o Cuadrado
// v -1.0  1.0 0.0
// v -1.0 -1.0 0.0
// v  1.0 -1.0 0.0
// v  1.0  1.0 0.0
// vn -0.6  0.6 0.6
// vn -0.6 -0.6 0.6
// vn  0.6 -0.6 0.6
// vn  0.6  0.6 0.6
// usemtl Verde
// f 4//1 5//2 6//3 7//4
// 
// o Cubo
// v 2.0  1.0 0.0
// v 2.0 -1.0 0.0
// v 4.0 -1.0 0.0
// v 4.0  1.0 0.0
// v 2.0  1.0 -2.0
// v 2.0 -1.0 -2.0
// v 4.0 -1.0 -2.0
// v 4.0  1.0 -2.0
// vt 0.0 1.0
// vt 0.0 0.0
// vt 1.0 0.0
// vt 1.0 1.0
// vn -0.6  0.6 0.6
// vn -0.6 -0.6 0.6
// vn  0.6 -0.6 0.6
// vn  0.6  0.6 0.6
// vn -0.6  0.6 -0.6
// vn -0.6 -0.6 -0.6
// vn  0.6 -0.6 -0.6
// vn  0.6  0.6 -0.6
// usemtl Rojo
// f 8/1/5 9/2/6 10/3/7 11/4/8
// usemtl Azul
// f 15//12 14//11 13//10 12//9
// usemtl Verde
// f 8//5 11//8 15//12 12//9
// usemtl Amarillo
// f 11//8 10//7 14//11 15//12
// usemtl Blanco
// f 12//9 13//10 9//6 8//5
// usemtl Naranja
// f 9//6 13//10 14//11 10//7
//
// -----------------------------------------------------------------------------
// -- ARCHIVO: "Materiales.mtl" ------------------------------------------------
// -----------------------------------------------------------------------------
// # Materiales
// newmtl Amarillo
// Ns 100.0
// d 0.8
// Kd 0.5 0.5 0.0
// Ka 1.0 1.0 0.0
// Ks 1.0 1.0 1.0
// Ke 0.0 0.0 0.0
// 
// newmtl Verde
// d 1.0
// Kd 0.0 0.5 0.0
// Ka 0.0 1.0 0.0
// 
// newmtl Rojo
// Ns 50.0
// Kd 0.5 0.0 0.0
// Ka 1.0 0.0 0.0
// map_Kd Cubo_1.png
// 
// newmtl Azul
// Kd 0.0 0.0 0.5
// Ka 0.0 0.0 1.0
// 
// newmtl Blanco
// Kd 0.5 0.5 0.5
// Ka 1.0 1.0 1.0
// 
// newmtl Naranja
// Kd 0.5 0.2 0.0
// Ka 1.0 0.5 0.0
//
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -- Ejemplo de uso de este cargador de archivos OBJ y MTL                   --
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
//  #include "../Includes/Cargador_Obj.h"
//
//  // -- CARGAMOS EL MODELO OBJ -------------------------------------------------
//  C_Obj *Modelo_OBJ = new C_Obj[1];
//  Modelo_OBJ[0].Carga( "Triangulo_Cuadrado_y_Cubo.obj" );
//
//  // -- Si el modelo tiene texturas las cargamos. ------------------------------
//  c_textura_2D *textura_2D[1];
//  textura_2D[0] = new c_textura_2D[ Modelo_OBJ[0].N_Texturas() ];
//  Modelo_OBJ[0].Carga_Texturas( textura_2D[0], 3 );
//
//  // -- CREAMOS LAS LISTAS COMPILADAS ------------------------------------------
//  glListBase( 0 );
//  GLuint lista = glGenLists(2);
//
//  // -- Para dibujar todos los objetos del archivo "OBJ" -----------------------
//  glNewList( lista + 0, GL_COMPILE );
//    Modelo_OBJ[0].Dibuja_Todo();
//  glEndList();
//    
//  // -- Para dibujar los objetos que queramos de un archivo "OBJ" --------------
//  glNewList( lista + 1, GL_COMPILE );
//    for ( GLuint ii = 0; ii < Modelo_OBJ[0].N_Objetos(); ii++ ) {
//      Modelo_OBJ[0].Dibuja_Objeto( ii );
//    }
//  glEndList();
//
//  // -- BORRAMOS LOS OBJETOS ---------------------------------------------------
//  delete[] Modelo_OBJ;
//
//  // -- MOSTRAR LAS LISTAS COMPILADAS ------------------------------------------ 	  
//  glCallList( lista + 0 );
//  glCallList( lista + 1 );
//
//  // -- BORRANDO OBJETOS -------------------------------------------------------
//  glDeleteLists( lista, 2 );   // -- BORRAMOS LAS LISTAS     --
//  delete[] textura_2D[0];      // -- BORRAMOS LAS TEXTURAS   --
//
// -------------------------------------------------------------------------------

#ifndef _Cargador_Obj_
#define _Cargador_Obj_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;

#include <GL/gl.h>										
#include <GL/glu.h>
#include "Texturas_2D.h"
								
#define Obj_N_Max 64
#define Obj_Linea 128

struct Obj_Grupo {
  char   nombre[ Obj_N_Max ];     // -- Nombre del Material --
  GLuint numero;                  // -- Numero del Material --
  vector< GLuint > caras;         // -- Caras: v / vt / vn  --
};

struct Obj_Objeto {
  char nombre[ Obj_N_Max ];       // -- Nombre del Objeto      --
  vector< GLfloat > v;            // -- Vértices del objeto    --
  vector< GLfloat > vt;           // -- Coordenadas de Textura --
  vector< GLfloat > vn;           // -- Normales del objeto    --
  vector< struct Obj_Grupo > grupos;
};

struct Obj_Material {
  char  nombre[Obj_N_Max ]; // -- newmtl Verde   ( nombre del material )
  GLfloat Ns;               // -- Ns 100.0       ( shininess / 128.0 * 1000.0 )
  GLfloat d;                // -- d 1.0          ( alpha )
  GLfloat Kd[4];            // -- Kd 0.0 1.0 0.0 ( diffuse   component )
  GLfloat Ka[4];            // -- Ka 0.0 1.0 0.0 ( ambient   component )
  GLfloat Ks[4];            // -- Ks 1.0 1.0 1.0 ( specular  component )
  GLfloat Ke[4];            // -- Ke 0.0 0.0 0.0 ( emmissive component )
  char  map_Kd[Obj_N_Max ]; // -- map_Kd Cubo_2.png
  GLint n_map_Kd;
};

class C_Obj {
  private:
    ifstream archivo;
    ofstream salida;
    char linea[ Obj_Linea ]; 
    char nombre_obj[ Obj_N_Max ];
    char nombre_mtl[ Obj_N_Max ];
    char *directorio;
    GLint n_text;                 // -- Numero de Texturas --
    vector< struct Obj_Objeto   > objetos;
    vector< struct Obj_Material > materiales;
    c_textura_2D   *texturas;
    bool estado;                  // -- FALSE si hay algún error --
    
    // -- TEMPORALES --
    struct Obj_Objeto   tmp_objeto;
    struct Obj_Grupo    tmp_grupo;
    struct Obj_Material tmp_material;
    GLint   n_objeto, n_grupo, n_material;
    GLuint  n_v, n_t, n_n;     // -- Numero de vertices, texturas y normales. --
    GLuint  c_v, c_t, c_n;     // -- Copia  de vertices, texturas y normales. --
    GLfloat tmp_f0, tmp_f1, tmp_f2;
    GLuint  tmp_v0, tmp_t0, tmp_n0;
    GLuint  tmp_v1, tmp_t1, tmp_n1;
    GLuint  tmp_v2, tmp_t2, tmp_n2;
    bool    b_textura, b_normal;
    
    // -- FUNCIONES PRIVADAS --
    const char* Nombre_Texturas( GLint num );
    void Dibuja_Material( GLuint n_mat );
    void Leer_Archivo_OBJ( void );
    void Leer_Archivo_MTL( void );

  public:
    // -- FUNCIONES PUBLICAS --
    C_Obj(  void );                                   // -- CONSTRUCTOR --
    ~C_Obj( void );                                   // -- DESTRUCTOR  --
    bool Carga( const char *Nombre_Archivo );         // -- CARGA ARCHIVO OBJ --
    GLint N_Texturas( void ) { return n_text; }       // -- RETORNA EL NÚMERO DE TEXTURAS --
    void Carga_Texturas( c_textura_2D *texturas, GLint efecto );  // -- CARGA LAS TEXTURAS --
    GLuint N_Objetos( void ) { return objetos.size(); } // -- RETORNA EL NÚMERO DE OBJETOS --
    void Dibuja_Objeto( GLuint n_obj );                 // -- DIBUJA UN OBJETO --
    void Dibuja_Todo( void );                         // -- DIBUJA TODOS LOS OBJETOS ..
    void Imprime( const char *Nombre_Archivo  );      // -- IMPRIME LOS DATOS DE UN OBJ + MTL --
    bool Estado( void ) { return estado; }            // -- RETORNA FALSE SI ERROR --
    void Borra( void );                               // -- BORRA MANUALMENTE LOS DATOS --
    void Borra_Normales( void );
    void Calcula_Normales( void );
    void Calcula_Normales_Suaves( void );
};

#endif
