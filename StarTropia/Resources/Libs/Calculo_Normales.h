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
// -- Calculo_Normales.h -------------------------------------------------------
// -----------------------------------------------------------------------------
#ifndef _Calculo_Normales_
#define _Calculo_Normales_

// #include <iostream>
// using namespace std;

#include <GL/gl.h>										
#include <GL/glu.h>
#include <math.h>

void Calcula_Normales_3( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos );

void Calcula_Normales_4( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos );

void Suavizado_Normales( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos );

#endif
