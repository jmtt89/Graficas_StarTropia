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
// -- Luces --------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Luz Direccional -- El Sol, rayos paralelos.
// Luz Puntual     -- Una Bombilla, rayos en todas direcciones.
// Luz Focal       -- Un Foco, rayos en forma de cono atenuado.
// obertura        -- Angulo de obertura del cono [ 0 - 90 grados ]
// atenuacion_foco -- Perdida intensidad al centro cono [ 0-128 ] 
// posiciona       -- Posiciona una Luz.
// direcciona      -- Si es focal también hay que direccionar el foco.
//
// #include "../Includes/Luces.h"
// c_luz *luz = new c_luz[3];  /* CREAMOS 3 LUCES */
// 
// /* LUZ DIRECCIONAL */
// luz[0].position( -5.0f,  5.0f, 0.0f );
// luz[0].diffuse(   1.0f,  0.0f, 0.0f );
// luz[0].ambient(   0.0f,  0.0f, 0.0f );
// luz[0].direccional( GL_LIGHT0 );
// 
// /* LUZ PUNTUAL */
// luz[1].position(  5.0f,  0.0f, 0.0f );
// luz[1].diffuse(   0.0f,  0.0f, 1.0f );
// luz[1].ambient(   0.0f,  0.0f, 0.0f );
// luz[1].puntual( GL_LIGHT1 );
// 
// /* LUZ FOCAL */
// luz[2].position(  0.0f, 10.0f, 0.0f );
// luz[2].diffuse(   0.0f,  1.0f, 0.0f );
// luz[2].ambient(   0.0f,  0.0f, 0.0f );
// luz[2].direction( 0.0f, -1.0f, 0.0f );
// luz[2].obertura( 45.0f );
// luz[2].atenuacion_foco( 16.0f );
// luz[2].focal( GL_LIGHT2 );
// 
// /* ACTIVAR LAS LUCES */
// glEnable( GL_LIGHTING );
// glEnable( GL_LIGHT0);
// glEnable( GL_LIGHT1);
// glEnable( GL_LIGHT2);
//
// /* DENTRO DEL BUCLE PRINCIPAL */
// luz[0].posiciona();
// luz[1].posiciona();
// luz[2].posiciona(); luz[2].direcciona();
//
// /* OPCIONAL, SIRVE PARA VER LA POSICION DE LAS LUCES */
// luz[0].ver_direccional();
// luz[1].ver_puntual();
// luz[2].ver_focal();
//
// /* BORRAR LAS LUCES */
// delete[] luz;
//
// -----------------------------------------------------------------------------
#ifndef _Luces_
#define _Luces_

#include <iostream>
using namespace std;
#include <GL/gl.h>										
#include <GL/glu.h>										

class c_luz {
  public:
    c_luz( void );
    ~c_luz( void );

    void diffuse(  GLfloat r, GLfloat g, GLfloat b )  { Diffuse[0] = r; Diffuse[1] = g; Diffuse[2] = b; Diffuse[3] = 1.0f; }
    void ambient(  GLfloat r, GLfloat g, GLfloat b )  { Ambient[0] = r; Ambient[1] = g; Ambient[2] = b; Ambient[3] = 1.0f; }
    void specular( GLfloat r, GLfloat g, GLfloat b )  { Specular[0]= r; Specular[1]= g; Specular[2]= b; Specular[3]= 1.0f; }
    void position( GLfloat x, GLfloat y, GLfloat z )  { Position[0]= x; Position[1]= y; Position[2]= z; }
    GLfloat *position( void ) { return Position; }
    void direction( GLfloat x, GLfloat y, GLfloat z ) { Direction[0]= x; Direction[1]= y; Direction[2]= z; }
    void obertura(        GLfloat valor ) { Spot_CutOff   = valor; }
    void atenuacion_foco( GLfloat valor ) { Spot_Exponent = valor; }
    
    void direccional( GLenum Luz_N );
    void puntual(     GLenum Luz_N );
    void focal(       GLenum Luz_N );
    void posiciona( void );
    void direcciona( void );
     
    void ver_direccional( void );
    void ver_puntual( void );
    void ver_focal( void );

  private:
    GLfloat Diffuse[4], Ambient[4], Specular[4], Position[4], Direction[3];
    GLfloat Spot_CutOff, Spot_Exponent;
    GLenum Luz_Numero;
};

#endif
