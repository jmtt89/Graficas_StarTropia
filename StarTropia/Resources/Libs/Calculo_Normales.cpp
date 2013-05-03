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

#include "Calculo_Normales.h"

// -----------------------------------------------------------------------------
// -- Cálculo de Normales en Triángulos ----------------------------------------
// -----------------------------------------------------------------------------
void Calcula_Normales_3( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos ) {
  GLfloat longitud;
  GLfloat v1[3], v2[3], v3[3];
  for( GLuint i = 0; i < N_Puntos; i+=9 ) {

    v1[0] = Vertex[i+3] - Vertex[i+0]; 
    v1[1] = Vertex[i+4] - Vertex[i+1];
    v1[2] = Vertex[i+5] - Vertex[i+2];
  
    v2[0] = Vertex[i+6] - Vertex[i+3];
    v2[1] = Vertex[i+7] - Vertex[i+4];
    v2[2] = Vertex[i+8] - Vertex[i+5];
    
    v3[0] = ( v1[1] * v2[2] ) - ( v1[2] * v2[1] );
    v3[1] = ( v1[2] * v2[0] ) - ( v1[0] * v2[2] );
    v3[2] = ( v1[0] * v2[1] ) - ( v1[1] * v2[0] );

    longitud = (GLfloat)sqrt( (v3[0]*v3[0]) + (v3[1]*v3[1]) + (v3[2]*v3[2]) );
    if( longitud == 0.0f ) longitud = 1.0f;
    v3[0] /= longitud; v3[1] /= longitud; v3[2] /= longitud;  
  
    Normal[i+0] = v3[0]; Normal[i+1] = v3[1]; Normal[i+2] = v3[2];
    Normal[i+3] = v3[0]; Normal[i+4] = v3[1]; Normal[i+5] = v3[2];
    Normal[i+6] = v3[0]; Normal[i+7] = v3[1]; Normal[i+8] = v3[2];
    
  } 
  
}


// -----------------------------------------------------------------------------
// -- Cálculo de Normales en Cuadrados -----------------------------------------
// -----------------------------------------------------------------------------
void Calcula_Normales_4( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos ) {
  GLfloat longitud;
  GLfloat v1[3], v2[3], v3[3];
  for( GLuint i = 0; i < N_Puntos; i+=12 ) {

    v1[0] = Vertex[i+3] - Vertex[i+0]; 
    v1[1] = Vertex[i+4] - Vertex[i+1];
    v1[2] = Vertex[i+5] - Vertex[i+2];
  
    v2[0] = Vertex[i+6] - Vertex[i+3];
    v2[1] = Vertex[i+7] - Vertex[i+4];
    v2[2] = Vertex[i+8] - Vertex[i+5];
    
    v3[0] = ( v1[1] * v2[2] ) - ( v1[2] * v2[1] );
    v3[1] = ( v1[2] * v2[0] ) - ( v1[0] * v2[2] );
    v3[2] = ( v1[0] * v2[1] ) - ( v1[1] * v2[0] );

    longitud = (GLfloat)sqrt( (v3[0]*v3[0]) + (v3[1]*v3[1]) + (v3[2]*v3[2]) );
    if( longitud == 0.0f ) longitud = 1.0f;
    v3[0] /= longitud; v3[1] /= longitud; v3[2] /= longitud;  
  
    Normal[i+0] = v3[0]; Normal[i+ 1] = v3[1]; Normal[i+ 2] = v3[2];
    Normal[i+3] = v3[0]; Normal[i+ 4] = v3[1]; Normal[i+ 5] = v3[2];
    Normal[i+6] = v3[0]; Normal[i+ 7] = v3[1]; Normal[i+ 8] = v3[2];
    Normal[i+9] = v3[0]; Normal[i+10] = v3[1]; Normal[i+11] = v3[2];
    
  } 
  
}


void Suavizado_Normales( GLfloat *Vertex, GLfloat *Normal, GLuint N_Puntos ) {
  GLfloat longitud;
  GLuint n_puntos_iguales;
  GLuint *puntos_iguales = new GLuint[32];
  
  GLuint saltar;
  GLuint n_puntos_a_saltar = 0;
  GLuint *puntos_a_saltar = new GLuint[ GLuint( N_Puntos / 3 ) ];
  
  GLfloat v[3];
  
  for( GLuint i = 0; i < (N_Puntos - 3); i+=3 ) {
       
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f;
    n_puntos_iguales = 0;
    
    for( GLuint j = i+3; j < N_Puntos; j+=3 ) {
      
      saltar = 1;   
      for( GLuint l = 0; l < n_puntos_a_saltar; ++l ) {
        if ( puntos_a_saltar[l] == j ) saltar = 0;
      }

      if ( saltar && ( Vertex[i] == Vertex[j] ) && ( Vertex[i+1] == Vertex[j+1] ) && ( Vertex[i+2] == Vertex[j+2] ) ) {
        if ( ( v[0] == 0.0f ) && ( v[1] == 0.0f ) && ( v[2] == 0.0f ) ) {
          puntos_iguales[n_puntos_iguales] = i; ++n_puntos_iguales;
          puntos_iguales[n_puntos_iguales] = j; ++n_puntos_iguales;
          puntos_a_saltar[n_puntos_a_saltar] = i; ++n_puntos_a_saltar;
          puntos_a_saltar[n_puntos_a_saltar] = j; ++n_puntos_a_saltar;
          v[0] = Normal[i]   + Normal[j];
          v[1] = Normal[i+1] + Normal[j+1];
          v[2] = Normal[i+2] + Normal[j+2];
        } else {
          puntos_iguales[n_puntos_iguales] = j; ++n_puntos_iguales;
          puntos_a_saltar[n_puntos_a_saltar] = j; ++n_puntos_a_saltar;
          v[0] += Normal[j];
          v[1] += Normal[j+1];
          v[2] += Normal[j+2];
        }
        
      }
    
    }

    if ( n_puntos_iguales > 0 ) {
      // cerr << "n_puntos_iguales = " << n_puntos_iguales << endl;
      longitud = (GLfloat)sqrt( (v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]) );
      if( longitud == 0.0f ) longitud = 1.0f;
      v[0] /= longitud; v[1] /= longitud; v[2] /= longitud;

    
      for ( GLuint k = 0; k < n_puntos_iguales; ++k ) {
        // cerr << "    puntos_iguales = " << puntos_iguales[k] << endl;
        Normal[ puntos_iguales[k]     ] = v[0];
        Normal[ puntos_iguales[k] + 1 ] = v[1];
        Normal[ puntos_iguales[k] + 2 ] = v[2];
      }
      // cerr << endl;
    }
    
  } 
  
  delete[] puntos_iguales;
  delete[] puntos_a_saltar;
}
