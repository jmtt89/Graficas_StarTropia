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
// -- Entorno_con_Cube_Map.h ---------------------------------------------------
// -----------------------------------------------------------------------------
// -- Creación de un Fondo con Cube_Map compuesto por 6 imagenes  --------------
// -----------------------------------------------------------------------------
// #include "../Includes/Entorno.h"
//  c_entorno *mi_entorno = new c_entorno( "Imagen/Cube_Maps/" ); 
//  mi_entorno->crea_cube_map();
//  mi_entorno->mostrar();
//  mi_entorno->activa_cube_map();
//  mi_entorno->desactiva_cube_map();
//  delete mi_entorno;
// -----------------------------------------------------------------------------

#ifndef _Entorno_
#define _Entorno_

#include <iostream>
using namespace std;
#include <cstring>
#include <GL/gl.h>										
#include <GL/glu.h>										
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#ifndef GL_EXT_texture_cube_map
#define GL_EXT_texture_cube_map             1
#define GL_NORMAL_MAP_EXT                   0x8511
#define GL_REFLECTION_MAP_EXT               0x8512
#define GL_TEXTURE_CUBE_MAP_EXT             0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT     0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT  0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT       0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT    0x851C
#endif

struct vec2{
    float x;
    float y;
};

class c_entorno {
  public:
    c_entorno( const char *direccion );
    c_entorno::c_entorno(int width, int height, const char *direccion);
    ~c_entorno( void );
    void mostrar( void );
    void crea_cube_map( void );
    void activa_cube_map( void );
    void desactiva_cube_map( void );
    void Dibujar_Suelo(void);
    void c_entorno::Dibujar_Todo(void);
    void c_entorno::Dibujar_Fondo(void); 
  private:
    char entorno_nombres[6][60];
    SDL_Surface *imagen[6];
    GLuint tex_fondo[6];
    GLuint lista_fondo;
    GLenum cubefaces[6];
    GLuint tex_cube_map;
    GLint  env;
    
    float Wi(float A,float Dx,float Dy,float Px, float Py,float w);
    float Hi(float A1,float A2,float D1x,float D1y,float D2x,float D2y,float Px,float Py,float w1,float w2);
    float dxHi(float A1,float A2,float D1x,float D1y,float D2x,float D2y,float Px,float Py,float w1,float w2);
    float dzHi(float A1,float A2,float D1x,float D1y,float D2x,float D2y,float Px,float Py,float w1,float w2);
    float dot(float Ax,float Ay, float Bx, float By);
    
};

#endif
