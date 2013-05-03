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
// -- Materiales --------------------------------------------------------------
// -----------------------------------------------------------------------------
// #include "../Includes/Materiales.h"
// c_material *material = new c_material[3];  /* CREAMOS 3 MATERIALES */
//
// /* MATERIAL EMISIVO */
// material[0].diffuse(  1.0f, 1.0f, 1.0f );
// material[0].ambient(  0.5f, 0.5f, 0.5f );
// material[0].specular( 1.0f, 1.0f, 1.0f ); 
// material[0].emissive( 0.5f, 0.5f, 0.5f );
//
// /* MATERIAL TRANSPARENTE */
// material[1].alpha( 0.5f );
//
// /* MATERIAL SUPER PULIDO */
// material[2].phongsize( 128.0f );
//
// /* DENTRO DEL BUCLE PRINCIPAL */
// material[0].activa();
// material[1].activa();
// material[2].activa();
//
// material[0].desactiva(); // -- OPCIONAL     SI EL MATERIAL TIENE ALPHA = 1.0f --
// material[1].desactiva(); // -- RECOMENDABLE SI EL MATERIAL TIENE ALPHA < 1.0f --
//
// bool b_alpha = material[1].es_Alpha(); // -- RETORNA BOLEANO --
//
// delete[] material;
//
// -----------------------------------------------------------------------------
#ifndef _Materiales_
#define _Materiales_

#include <iostream>
using namespace std;
#include <GL/gl.h>										
#include <GL/glu.h>										

class c_material {
  public:
    c_material( void );
    ~c_material( void );
    void diffuse(  GLfloat r, GLfloat g, GLfloat b ) { Diffuse[0] = r; Diffuse[1] = g; Diffuse[2] = b; }
    void ambient(  GLfloat r, GLfloat g, GLfloat b ) { Ambient[0] = r; Ambient[1] = g; Ambient[2] = b; }
    void specular( GLfloat r, GLfloat g, GLfloat b ) { Specular[0]= r; Specular[1]= g; Specular[2]= b; }
    void emissive( GLfloat r, GLfloat g, GLfloat b );
    void alpha( GLfloat a );
    bool es_Alpha( void )     { return Blend; }
    void phongsize( GLfloat p ) { Phongsize = p; }
    void activa( void );
    void desactiva( void );
  private:
    GLfloat Ambient[4], Diffuse[4], Specular[4], Emissive[4];
    GLfloat Alpha, Phongsize;
    bool  Blend;
};

#endif
