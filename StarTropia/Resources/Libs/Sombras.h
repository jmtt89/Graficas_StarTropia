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
// -- Sombras.h ----------------------------------------------------------------
// -----------------------------------------------------------------------------
//
//  #include "../Includes/Sombras.h"
//
//  // -- TRES PUNTOS DEL SUELO EN SENTIDO ANTIHORARIO ---------------------------
//  GLfloat Puntos[9] = { -15, -3, -15,   -15, -3,  15,   15, -3,  15  };
//  GLfloat Plano[4];
//  Ecuacion_del_Plano( Puntos, Plano );
//
//  // -- EN EL BUCLE DE DIBUJADO ----------------------------------------------
//
//    // -- DIBUJAR EL SUELO ---------------------------------------------------
//    Hacer_Mascara_Sombra();
//      material[1].activa();  glCallList( lista + 1 );
//    Terminar_Mascara_Sombra();
//
//    // -- DIBUJAR LAS SOMBRAS ------------------------------------------------
//    if ( glIsEnabled( GL_LIGHT0 ) ) {
//      Hacer_Sombra( Plano, luz[0].position() );
//      glCallList( lista + 0 ); // -- DIBUJAR LOS OBJETOS CON SOMBRA ----------
//      Terminar_Sombra();
//    }
//
//    if ( glIsEnabled( GL_LIGHT1 ) ) {
//      Hacer_Sombra( Plano, luz[1].position() );
//      glCallList( lista + 0 ); // -- DIBUJAR LOS OBJETOS CON SOMBRA ----------
//      Terminar_Sombra();
//    }
//
//    Fin_Sombras();
//    
//    // -- DIBUJAR LOS OBJETOS ------------------------------------------------
//    material[2].activa(); glCallList( lista + 0 );
//
//  // -- FIN BUCLE DE DIBUJADO ------------------------------------------------
//
// -----------------------------------------------------------------------------

#ifndef _Sombras_
#define _Sombras_

// #include <iostream>
// using namespace std;

#include <GL/gl.h>										
#include <GL/glu.h>
#include <math.h>

void Ecuacion_del_Plano( GLfloat *Puntos, GLfloat *Plano );
const void Hacer_Mascara_Sombra( void );
const void Terminar_Mascara_Sombra( void );
const void Hacer_Sombra( GLfloat *Plano, GLfloat *Luz_Pos );
const void Terminar_Sombra( void );
const void Fin_Sombras( void );

#endif
