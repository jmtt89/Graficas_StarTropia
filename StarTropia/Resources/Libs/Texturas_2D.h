//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programación) www.scenebeta.com          --
//-- FECHA ÚLTIMA MODIFICACIÓN: 27/04/2010                                    --
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
// -- Texturas_2D --------------------------------------------------------------
// -----------------------------------------------------------------------------
// ----------------------------------------------------------------------------- 
// #include "../Includes/Texturas_2D.h"   
// 
// // -- CREAMOS LAS TEXTURAS ---------------------------------------------------
// c_textura_2D *textura_2D = new c_textura_2D[4];
// 
// textura_2D[0].carga_2D( "Imagen_0.jpg", 0 );
// textura_2D[0].modo( GL_MODULATE );
// 
// textura_2D[1].carga_2DMipmaps( "Imagen_Alpha_1.jpg", 3 );
// textura_2D[1].modo( GL_DECAL );
// 
// textura_2D[2].carga_2DMipmaps( "Imagen/Texturas/Agua_1.jpg", 1 );
// textura_2D[2].modo( GL_BLEND );
// textura_2D[2].color_blend( 0.8f, 0.8f, 0.0f );
// 
// textura_2D[3].carga_2DMipmaps( "Imagen/Texturas/Agua_1.jpg", 3 );
// textura_2D[3].modo( GL_DECAL );
// textura_2D[3].repetir( true );
// textura_2D[3].modo_ST( GL_EYE_LINEAR );
// textura_2D[3].plano_S( 1.0f, 0.0f, 0.0f );
// textura_2D[3].plano_T( 0.0f, 1.0f, 0.0f );
//
// // -- EN EL BUCLE PRINCIPAL -------------------------------------------------
// textura_2D[0].activa();
//   DIBUJAR FIGURA USANDO SUS COORDENADAS DE TEXTURA.
// textura_2D[0].desactiva();
//
// textura_2D[1].activa();
//   DIBUJAR FIGURA USANDO SUS COORDENADAS DE TEXTURA.
// textura_2D[1].desactiva();
//
// textura_2D[2].activa();
//   DIBUJAR FIGURA USANDO SUS COORDENADAS DE TEXTURA.
// textura_2D[2].desactiva();
//
// textura_2D[3].activa();
//   textura_2D[3].activa_ST();
//     DIBUJA FIGURA GENERANDO LAS COORDENADAS DE TEXTURA.
//   textura_2D[3].desactiva_ST();
// textura_2D[3].desactiva();
//
// // -- AL FINALIZAR --------------------------------------------------------
// delete[] textura_2D;
//
// -----------------------------------------------------------------------------

#ifndef _Texturas_2D_
#define _Texturas_2D_

#include <iostream>
using namespace std;
#include <GL/gl.h>										
#include <GL/glu.h>										
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Mirror.h"

bool Carga_GLTextura2D( GLuint &textura, const char *nombre_archivo, GLint efecto );
bool Carga_GLTextura2DMipmaps( GLuint &textura, const char *nombre_archivo, GLint efecto );

class c_textura_2D {
  public:
    c_textura_2D ( void );
    ~c_textura_2D ( void );
    void carga_2D( const char *nombre_archivo, GLint efecto );
    void carga_2DMipmaps( const char *nombre_archivo, GLint efecto );
    void modo( GLint GL_DECAL_GL_REPLACE_GL_MODULATE_GL_BLEND ) { 
      Modo = GL_DECAL_GL_REPLACE_GL_MODULATE_GL_BLEND; 
      if ( ( alpha == true ) & ( Modo == GL_DECAL ) ) Modo = GL_REPLACE;
    }
    bool es_Alpha( void ) { return alpha; }
    void repetir( bool valor ) { 
      if(valor) Repetir = GL_REPEAT; else Repetir = GL_CLAMP; 
      glBindTexture( GL_TEXTURE_2D, this->textura );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Repetir );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Repetir );
    }
    void modo_ST( GLint GL_EYE_LINEAR_GL_OBJECT_LINEAR_GL_SPHERE_MAP ) { Modo_ST = GL_EYE_LINEAR_GL_OBJECT_LINEAR_GL_SPHERE_MAP; }
    void plano_S( GLfloat xx, GLfloat yy, GLfloat zz ) { Plano_S[0]= xx; Plano_S[1]= yy; Plano_S[2]= zz; }
    void plano_T( GLfloat xx, GLfloat yy, GLfloat zz ) { Plano_T[0]= xx; Plano_T[1]= yy; Plano_T[2]= zz; }
    void color_blend( GLfloat r, GLfloat g, GLfloat b ) { Color_Blend[0] = r; Color_Blend[1] = g; Color_Blend[2] = b; }
    void activa( void );
    void desactiva( void );
    void activa_Blend( void );       // -- Sin Canal Alpha, Fondo Negro se Transparenta --
    void desactiva_Blend( void );  
    void activa_Alpha_Blend( void );
    void desactiva_Alpha_Blend( void );
    void activa_ST( void );
    void desactiva_ST( void );

  private:
    GLuint textura; 
    GLint efecto;
    bool alpha;
    GLint Modo, Repetir, Modo_ST;
    GLfloat Color_Blend[3];
    GLfloat Plano_S[4], Plano_T[4];
};

#endif
