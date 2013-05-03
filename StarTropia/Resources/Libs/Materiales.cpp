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

#include "Materiales.h"

c_material::c_material( void ) {
  Alpha = 1.0f; Phongsize = 32.0f; Blend = false;
  Ambient[0]  = 1.0f; Ambient[1]  = 1.0f; Ambient[2]  = 1.0f; Ambient[3]  = 1.0f;
  Diffuse[0]  = 1.0f; Diffuse[1]  = 1.0f; Diffuse[2]  = 1.0f; Diffuse[3]  = 1.0f;
  Specular[0] = 1.0f; Specular[1] = 1.0f; Specular[2] = 1.0f; Specular[3] = 1.0f;
  Emissive[0] = 0.0f; Emissive[1] = 0.0f; Emissive[2] = 0.0f; Emissive[3] = 0.0f;
}

c_material::~c_material( void ) {
  // cerr << "Materiales Destruido." << endl;
}

void c_material::emissive( GLfloat r, GLfloat g, GLfloat b ) { 
  Emissive[0]= r; Emissive[1]= g; Emissive[2]= b; 
  if ( ( Emissive[0] + Emissive[1] + Emissive[2] ) > 0.0f ) Emissive[3] = Alpha;
}

void c_material::alpha( GLfloat a ) { 
  Alpha = a; 
  Diffuse[3] = Alpha; Ambient[3] = Alpha; Specular[3] = Alpha; 
  if ( ( Emissive[0] + Emissive[1] + Emissive[2] ) > 0.0f ) Emissive[3] = Alpha;
  if ( Alpha < 1.0f ) Blend = true; else Blend = false;
}
    
void c_material::activa( void ) {
  glColor4fv( Diffuse );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   Diffuse   );
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   Ambient   );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  Specular  );
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  Emissive  );
  glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, Phongsize );
  if ( Blend ) { glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND ); }
}

void c_material::desactiva( void ) {
  if ( Blend ) glDisable( GL_BLEND );
}
