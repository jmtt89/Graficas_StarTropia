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

#include "Texturas_2D.h"

// -------------------------------------------------------------------------
// Cargar Textura 2D ( Imagen cuadrada 16x16, 32x32 ... , Filtro de 0 a 1 );
// -------------------------------------------------------------------------
bool Carga_GLTextura2D( GLuint &textura, const char *nombre_archivo, GLint efecto )
{
  GLint param1, param2, int_format; GLenum format; bool alpha;
  switch( efecto ){
    case 0:  param2 = GL_NEAREST;  param1 = GL_NEAREST; break;
    case 1:  param2 = GL_LINEAR;   param1 = GL_LINEAR;  break;                    
    default: param2 = GL_NEAREST;  param1 = GL_NEAREST; break;
  }
  SDL_Surface *Temp  = IMG_Load( nombre_archivo );
  if ( Temp == NULL ) { cerr << "Falla IMG_Load: " << nombre_archivo << endl; return false; }
  if      ( Temp->format->BytesPerPixel == 3 ) { int_format = GL_RGB;  format = GL_RGB;  alpha = false; } 
  else if ( Temp->format->BytesPerPixel == 4 ) { int_format = GL_RGBA; format = GL_RGBA; alpha = true;  }
  else {
    cerr << "Falla Bytes por Pixel IMG_Load: " << nombre_archivo << endl;
    SDL_FreeSurface( Temp ); Temp = NULL; return false;
  }
  Temp = MirrorSurfaceX( Temp ); // -- La imagen es invertida en el eje X --
  glBindTexture( GL_TEXTURE_2D, textura );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param1 );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2 );
  glTexImage2D( GL_TEXTURE_2D, 0, int_format, Temp->w, Temp->h, 0, format, GL_UNSIGNED_BYTE, Temp->pixels );
  SDL_FreeSurface( Temp ); Temp = NULL; return alpha;
}

// -------------------------------------------------------------------------
// Cargar Textura 2D Mipmaps(  Imagen cualquier tamaño , Filtro de 0 a 3 );
// -------------------------------------------------------------------------
bool Carga_GLTextura2DMipmaps( GLuint &textura, const char *nombre_archivo, GLint efecto )
{
  GLint param1, param2, int_format; GLenum format; bool alpha;
  switch( efecto ){
    case 0:  param2 = GL_NEAREST;  param1 = GL_NEAREST; break;
    case 1:  param2 = GL_LINEAR;   param1 = GL_LINEAR;  break;
    case 2:  param2 = GL_LINEAR;   param1 = GL_NEAREST_MIPMAP_NEAREST; break; 
    case 3:  param2 = GL_LINEAR;   param1 = GL_LINEAR_MIPMAP_LINEAR;   break;                    
    default: param2 = GL_NEAREST;  param1 = GL_NEAREST; break;
  }
  SDL_Surface *Temp  = IMG_Load( nombre_archivo );
  if ( Temp == NULL ) { cerr << "Falla IMG_Load: " << nombre_archivo << endl; return false; }
  if      ( Temp->format->BytesPerPixel == 3 ) { int_format = GL_RGB;  format = GL_RGB;  alpha = false; } 
  else if ( Temp->format->BytesPerPixel == 4 ) { int_format = GL_RGBA; format = GL_RGBA; alpha = true;  }
  else {
    cerr << "Falla Bytes por Pixel IMG_Load: " << nombre_archivo << endl;
    SDL_FreeSurface( Temp ); Temp = NULL; return false;
  }
  Temp = MirrorSurfaceX( Temp ); // -- La imagen es invertida en el eje X --
  glBindTexture( GL_TEXTURE_2D, textura );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param1 );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2 );
  gluBuild2DMipmaps(GL_TEXTURE_2D, int_format, Temp->w, Temp->h, format, GL_UNSIGNED_BYTE, Temp->pixels );
  SDL_FreeSurface( Temp ); Temp = NULL; return alpha;
}

c_textura_2D::c_textura_2D( void ) {
  glGenTextures( 1, &this->textura );
  efecto = 0; alpha = false;
  Modo = GL_MODULATE; Repetir = GL_REPEAT;
  Modo_ST = GL_SPHERE_MAP;
  Color_Blend[0] = 1.0f; Color_Blend[1] = 1.0f; Color_Blend[2] = 1.0f;  
  Plano_S[0]= 1.0f; Plano_S[1]= 0.0f; Plano_S[2]= 0.0f; Plano_S[3]= 0.0f;
  Plano_T[0]= 0.0f; Plano_T[1]= 1.0f; Plano_T[2]= 0.0f; Plano_T[3]= 0.0f;
}

c_textura_2D::~c_textura_2D( void ) {
  glDeleteTextures( 1, &this->textura );
}

void c_textura_2D::carga_2D( const char *nombre_archivo, GLint efecto ) {
  this->efecto = efecto;
  this->alpha  = Carga_GLTextura2D( this->textura, nombre_archivo, this->efecto );
}

void c_textura_2D::carga_2DMipmaps( const char *nombre_archivo, GLint efecto ) {
  this->efecto = efecto;
  this->alpha  = Carga_GLTextura2DMipmaps( this->textura, nombre_archivo, this->efecto );
}

void c_textura_2D::activa_ST( void ) {
  glTexGeni(  GL_S, GL_TEXTURE_GEN_MODE, Modo_ST );
  glTexGeni(  GL_T, GL_TEXTURE_GEN_MODE, Modo_ST );
  glTexGenfv( GL_S, GL_OBJECT_PLANE, Plano_S );
  glTexGenfv( GL_T, GL_OBJECT_PLANE, Plano_T );
  glEnable( GL_TEXTURE_GEN_S );
  glEnable( GL_TEXTURE_GEN_T );
}

void c_textura_2D::desactiva_ST( void ) {
  glDisable( GL_TEXTURE_GEN_S );
  glDisable( GL_TEXTURE_GEN_T );
}

void c_textura_2D::activa( void ) {
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, this->textura );
  if ( Modo == GL_BLEND ) glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, Color_Blend );
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, Modo );
  if ( this->alpha ) { glAlphaFunc( GL_GREATER, 0.5f ); glEnable( GL_ALPHA_TEST ); }
}

void c_textura_2D::desactiva( void ) {
  glDisable( GL_TEXTURE_2D );
  if ( this->alpha ) glDisable( GL_ALPHA_TEST );
}

void c_textura_2D::activa_Blend( void ) { // -- Sin Canal Alpha, Fondo Negro se Transparenta --
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, this->textura );
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, Modo );
  glEnable( GL_BLEND );
  glBlendFunc( GL_ONE, GL_ONE );
}

void c_textura_2D::desactiva_Blend( void ) {
  glDisable( GL_BLEND );
  glDisable( GL_TEXTURE_2D );
}

void c_textura_2D::activa_Alpha_Blend( void ) {
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, this->textura );
  if ( Modo == GL_BLEND ) glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, Color_Blend );
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, Modo );
  glAlphaFunc( GL_ALWAYS, 1.0 ); 
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_ALPHA_TEST );
  glEnable( GL_BLEND );
}

void c_textura_2D::desactiva_Alpha_Blend( void ) {
  glDisable( GL_BLEND );
  glDisable( GL_ALPHA_TEST );
  glDisable( GL_TEXTURE_2D );
}


