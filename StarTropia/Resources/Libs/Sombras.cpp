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

#include "Sombras.h"

// -----------------------------------------------------------------------------
// -- Cálculo de la Ecuación del Plano -----------------------------------------
// -----------------------------------------------------------------------------
//      Tres Puntos ->   GLfloat Puntos[9], GLfloat *Plano[4]
// -----------------------------------------------------------------------------
void Ecuacion_del_Plano( GLfloat *Puntos,   GLfloat *Plano   ) {

  GLfloat longitud;
  GLfloat v1[3], v2[3], v3[3];

  v1[0] = Puntos[3] - Puntos[0]; 
  v1[1] = Puntos[4] - Puntos[1];
  v1[2] = Puntos[5] - Puntos[2];
  
  v2[0] = Puntos[6] - Puntos[3];
  v2[1] = Puntos[7] - Puntos[4];
  v2[2] = Puntos[8] - Puntos[5];
    
  v3[0] = ( v1[1] * v2[2] ) - ( v1[2] * v2[1] );
  v3[1] = ( v1[2] * v2[0] ) - ( v1[0] * v2[2] );
  v3[2] = ( v1[0] * v2[1] ) - ( v1[1] * v2[0] );

  longitud = (GLfloat)sqrt( (v3[0]*v3[0]) + (v3[1]*v3[1]) + (v3[2]*v3[2]) );
  if( longitud == 0.0f ) longitud = 1.0f;
  v3[0] /= longitud; v3[1] /= longitud; v3[2] /= longitud;  
  
  Plano[0] = v3[0]; 
  Plano[1] = v3[1]; 
  Plano[2] = v3[2];
  Plano[3] = - ( ( Plano[0] * Puntos[6] ) + 
                 ( Plano[1] * Puntos[7] ) + 
                 ( Plano[2] * Puntos[8] ) );

  
}

// -----------------------------------------------------------------------------
// -- Hace una máscara para limitar el dibujo de las Sombras -------------------
// -----------------------------------------------------------------------------
const void Hacer_Mascara_Sombra( void ) {
  glClear( GL_STENCIL_BUFFER_BIT );
  // glColorMask( 0, 0, 0, 0 );
  glDisable( GL_DEPTH_TEST );
  glEnable( GL_STENCIL_TEST );
  glStencilFunc( GL_ALWAYS, 1, 1 );
  glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
}

const void Terminar_Mascara_Sombra( void ) {
  // glColorMask( 1, 1, 1, 1 );
  // glEnable( GL_DEPTH_TEST );
  glStencilFunc( GL_EQUAL, 1, 1 );
  glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
}

// -----------------------------------------------------------------------------
// -- Cálculo de la Matriz de Sombreado ----------------------------------------
// -----------------------------------------------------------------------------
//                     GLfloat Plano[4], GLfloat Luz_Pos[4]
// -----------------------------------------------------------------------------
const void Hacer_Sombra( GLfloat *Plano,   GLfloat *Luz_Pos   ) {

  GLfloat Dot;
  GLfloat Matriz_Sombra[4][4];

  // -- Producto mixto del plano y la posición de la luz --
  Dot = ( Plano[0] * Luz_Pos[0] ) +   
	    ( Plano[1] * Luz_Pos[1] ) +  
	    ( Plano[2] * Luz_Pos[2] ) +   
	    ( Plano[3] * Luz_Pos[3] );

  // -- Ahora hace la proyección --------------------
  Matriz_Sombra[0][0] = Dot  - Luz_Pos[0] * Plano[0];
  Matriz_Sombra[1][0] = 0.0f - Luz_Pos[0] * Plano[1];
  Matriz_Sombra[2][0] = 0.0f - Luz_Pos[0] * Plano[2];
  Matriz_Sombra[3][0] = 0.0f - Luz_Pos[0] * Plano[3];

  Matriz_Sombra[0][1] = 0.0f - Luz_Pos[1] * Plano[0];
  Matriz_Sombra[1][1] = Dot  - Luz_Pos[1] * Plano[1];
  Matriz_Sombra[2][1] = 0.0f - Luz_Pos[1] * Plano[2];
  Matriz_Sombra[3][1] = 0.0f - Luz_Pos[1] * Plano[3];

  Matriz_Sombra[0][2] = 0.0f - Luz_Pos[2] * Plano[0];
  Matriz_Sombra[1][2] = 0.0f - Luz_Pos[2] * Plano[1];
  Matriz_Sombra[2][2] = Dot  - Luz_Pos[2] * Plano[2];
  Matriz_Sombra[3][2] = 0.0f - Luz_Pos[2] * Plano[3];

  Matriz_Sombra[0][3] = 0.0f - Luz_Pos[3] * Plano[0];
  Matriz_Sombra[1][3] = 0.0f - Luz_Pos[3] * Plano[1];
  Matriz_Sombra[2][3] = 0.0f - Luz_Pos[3] * Plano[2];
  Matriz_Sombra[3][3] = Dot  - Luz_Pos[3] * Plano[3];


  glPushAttrib( GL_LIGHTING_BIT );
  glDisable( GL_LIGHTING );
  // glDisable( GL_DEPTH_TEST );
  glPushMatrix();
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glColor4f( 0.0, 0.0, 0.0, 0.4 );
  // -- Ahora Multiplica la Matriz --------------------
  glMultMatrixf( (const GLfloat *) Matriz_Sombra );

}

const void Terminar_Sombra( void ) {
  glDisable( GL_BLEND ); 
  glPopMatrix(); // Repone la proyección a normal
  // glEnable( GL_DEPTH_TEST );
  glPopAttrib(); // -- Retoma las variables de estado de la iluminación -- 
}

const void Fin_Sombras( void ) {
  glEnable( GL_DEPTH_TEST );
  glDisable( GL_STENCIL_TEST );
}
