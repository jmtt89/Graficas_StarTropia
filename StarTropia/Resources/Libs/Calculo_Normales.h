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
