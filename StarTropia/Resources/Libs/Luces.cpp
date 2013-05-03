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

#include "Luces.h"

c_luz::c_luz( void ) {
  Diffuse[0]  =  1.0f; Diffuse[1]  =  1.0f; Diffuse[2]  =  1.0f; Diffuse[3]  = 1.0f;
  Ambient[0]  =  0.2f; Ambient[1]  =  0.2f; Ambient[2]  =  0.2f; Ambient[3]  = 1.0f;
  Specular[0] =  1.0f; Specular[1] =  1.0f; Specular[2] =  1.0f; Specular[3] = 1.0f;
  Position[0] =  5.0f; Position[1] =  5.0f; Position[2] =  5.0f; Position[3] = 0.0f; 
  Direction[0]= -1.0f; Direction[1]= -1.0f; Direction[2]= -1.0f;
  Spot_CutOff = 45.0f; Spot_Exponent =  1.0f; Luz_Numero = GL_LIGHT0;
}

c_luz::~c_luz( void ) {
  // cerr << "Luces Destruido." << endl;
}

void c_luz::direccional( GLenum Luz_N ) {
  Luz_Numero = Luz_N;
  Position[3] = 0.0f;
  glLightfv( Luz_Numero, GL_DIFFUSE,  Diffuse  );
  glLightfv( Luz_Numero, GL_AMBIENT,  Ambient  );
  glLightfv( Luz_Numero, GL_SPECULAR, Specular );
  glLightfv( Luz_Numero, GL_POSITION, Position );
}

void c_luz::puntual( GLenum Luz_N ) {
  Luz_Numero = Luz_N;
  Position[3] = 1.0f;
  glLightfv( Luz_Numero, GL_DIFFUSE,  Diffuse  );
  glLightfv( Luz_Numero, GL_AMBIENT,  Ambient  );
  glLightfv( Luz_Numero, GL_SPECULAR, Specular );
  glLightfv( Luz_Numero, GL_POSITION, Position );
}

void c_luz::focal( GLenum Luz_N ) {
  Luz_Numero = Luz_N;
  Position[3] = 1.0f;
  glLightfv( Luz_Numero, GL_DIFFUSE,  Diffuse  );
  glLightfv( Luz_Numero, GL_AMBIENT,  Ambient  );
  glLightfv( Luz_Numero, GL_SPECULAR, Specular );
  glLightfv( Luz_Numero, GL_POSITION, Position );
  glLightfv( Luz_Numero, GL_SPOT_DIRECTION, Direction     );
  glLightf(  Luz_Numero, GL_SPOT_CUTOFF   , Spot_CutOff   );
  glLightf(  Luz_Numero, GL_SPOT_EXPONENT , Spot_Exponent );
}

void c_luz::posiciona( void ) {
  glLightfv( Luz_Numero, GL_POSITION, Position );
}

void c_luz::direcciona( void ) {
  glLightfv( Luz_Numero, GL_SPOT_DIRECTION, Direction  );
}

void c_luz::ver_direccional( void ) {
  if ( glIsEnabled( Luz_Numero ) ) {
    glPointSize( 8.0f ); 
    glBegin( GL_POINTS  );
      glVertex3f( Position[0], Position[1], Position[2] );
    glEnd();
    glBegin( GL_LINES  );
      glVertex3f( Position[0], Position[1], Position[2] );
      glVertex3f( 0.0f, 0.0f, 0.0f );
    glEnd();
  }
}

void c_luz::ver_puntual( void ) {
  if ( glIsEnabled( Luz_Numero ) ) {
    glPointSize( 8.0f ); 
    glBegin( GL_POINTS  );
      glVertex3f( Position[0], Position[1], Position[2] );
    glEnd();
  }
}

void c_luz::ver_focal( void ) {
  if ( glIsEnabled( Luz_Numero ) ) {
    glPointSize( 8.0f ); 
    glBegin( GL_POINTS  );
      glVertex3f( Position[0], Position[1], Position[2] );
    glEnd();
    glBegin( GL_LINES  );
      glVertex3f( Position[0],  Position[1],  Position[2] );
      glVertex3f( Position[0] + Direction[0], Position[1] + Direction[1], Position[2] + Direction[2] );
    glEnd();
  }
}
