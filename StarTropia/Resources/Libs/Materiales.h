//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programaci�n) www.scenebeta.com          --
//-- FECHA �LTIMA MODIFICACI�N: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  c�digo  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en �l. Sin el  m�s --
//-- m�nimo �nimo de lucro, siempre por la satisfacci�n del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  da�o  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  �nimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este c�digo que colabore en su mejora--
//-- y perfeccionamiento poni�ndomelo en conocimiento por correo electr�nico. --
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
