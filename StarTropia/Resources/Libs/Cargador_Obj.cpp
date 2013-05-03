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

#include "Cargador_Obj.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- Función privada que devuelve el directorio del archivo. -------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
char* Obj_Directorio( char* path ) {
  char* dir;
  char* s;
  dir = strdup(path);
  s = strrchr(dir, '/');
  if (s) s[1]   = '\0';
  else   dir[0] = '\0';
  return dir;
}

// -----------------------------------------------------------------------------
// -- Función privada que calcula la Normal de un Triángulo --------------------
// -----------------------------------------------------------------------------
void Producto_en_Cruz( GLfloat *Vertex, GLfloat *Normal ) {
  GLfloat longitud;
  GLfloat v1[3], v2[3], v3[3];
  v1[0] = Vertex[3] - Vertex[0]; 
  v1[1] = Vertex[4] - Vertex[1];
  v1[2] = Vertex[5] - Vertex[2];
  v2[0] = Vertex[6] - Vertex[3];
  v2[1] = Vertex[7] - Vertex[4];
  v2[2] = Vertex[8] - Vertex[5];
  v3[0] = ( v1[1] * v2[2] ) - ( v1[2] * v2[1] );
  v3[1] = ( v1[2] * v2[0] ) - ( v1[0] * v2[2] );
  v3[2] = ( v1[0] * v2[1] ) - ( v1[1] * v2[0] );
  longitud = (GLfloat)sqrt( (v3[0]*v3[0]) + (v3[1]*v3[1]) + (v3[2]*v3[2]) );
  if( longitud == 0.0f ) longitud = 1.0f;
  v3[0] /= longitud; v3[1] /= longitud; v3[2] /= longitud;  
  Normal[0] = v3[0]; Normal[1] = v3[1]; Normal[2] = v3[2];
}

// -----------------------------------------------------------------------------
// -- Función privada que retorna el producto dot de dos vectores  -------------
// -- GLfloats (GLfloat u[3]), GLfloats (GLfloat v[3]) -------------------------
// -----------------------------------------------------------------------------
GLfloat Dot( GLfloat *u, GLfloat *v ) {
  return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- INICIO DE FUNCIONES PÚBLICAS ----------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CONSTRUCTOR ---------------------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
C_Obj::C_Obj( void ) {
  //-- Inicialización de variables ---------------------------------------------
  estado = 0; nombre_obj[0] = '\0'; nombre_mtl[0] = '\0'; texturas = 0;
  n_objeto = -1; n_grupo  = -1; n_material = 0; n_text = 0;
  n_v = 0; n_t = 0; n_n = 0; c_v = 0; c_t = 0; c_n = 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- DESTRUCTOR ----------------------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
C_Obj::~C_Obj( void ) {          
  this->Borra();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CARGA UN ARCHIVO OBJ + MTL ------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
bool C_Obj::Carga( const char *Nombre_Archivo ) {
  strcpy( nombre_obj, Nombre_Archivo );
  directorio = Obj_Directorio( nombre_obj );
  estado = 1;
  //----------------------------------------------------------------------------
  //-- CARGA DE ARCHIVO OBJ ----------------------------------------------------
  if ( strlen( nombre_obj ) > 0 ) this->Leer_Archivo_OBJ();
  else { 
    estado = 0; 
    cerr << "No hay nombre de archivo OBJ." << endl; 
    return estado;
  }
  //----------------------------------------------------------------------------
  //-- CARGA DE ARCHIVO MTL ----------------------------------------------------
  if ( strlen( nombre_mtl ) > 0 ) { 
    this->Leer_Archivo_MTL();
    for (     GLuint ii = 0; ii < materiales.size();         ii++ ) {
      for (   GLuint jj = 0; jj < objetos.size();            jj++ ) {
        for ( GLuint kk = 0; kk < objetos[jj].grupos.size(); kk++ ) {
          if ( strcmp( materiales[ii].nombre, objetos[jj].grupos[kk].nombre ) == 0 ) {
            objetos[jj].grupos[kk].numero = ii;
          }
          if ( !strlen( materiales[ii].map_Kd ) ) materiales[ii].n_map_Kd = -1;
  } } } } 
  //----------------------------------------------------------------------------
  return estado;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CARGA LAS TEXTURAS DE UN ARCHIVO OBJ + MTL --------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
void C_Obj::Carga_Texturas( c_textura_2D *texturas, GLint efecto ) { 
  this->texturas = texturas;
  if ( n_text > 0 ) {
    for ( GLint ii = 0; ii < n_text; ii++ ) {
      texturas[ii].carga_2DMipmaps( this->Nombre_Texturas( ii ), efecto );
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- DIBUJA UN OBJETO DE UN ARCHIVO OBJ ----------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
void C_Obj::Dibuja_Objeto( GLuint n_obj ) {
  for ( GLuint jj = 0; jj < objetos[n_obj].grupos.size(); jj++ ) {
    n_material = objetos[n_obj].grupos[jj].numero;
    this->Dibuja_Material( n_material );
    if ( texturas && ( materiales[ n_material ].n_map_Kd >= 0 )  ) 
      texturas[ materiales[ n_material ].n_map_Kd ].activa();   
    for ( GLuint kk = 0; kk < objetos[n_obj].grupos[jj].caras.size(); kk+=9 ) {
      b_textura = 0; b_normal = 0;
      tmp_v0 = objetos[n_obj].grupos[jj].caras[kk];
      if ( tmp_v0 > 0 ) {
        tmp_v0 = ( tmp_v0 - 1 ) * 3;
        tmp_v1 = ( objetos[n_obj].grupos[jj].caras[kk+3] - 1 ) * 3;
        tmp_v2 = ( objetos[n_obj].grupos[jj].caras[kk+6] - 1 ) * 3;
      }
      tmp_t0 = objetos[n_obj].grupos[jj].caras[kk+1];
      if ( texturas && ( tmp_t0 > 0 ) ) {
        tmp_t0 = ( tmp_t0 - 1 ) * 2;
        tmp_t1 = ( objetos[n_obj].grupos[jj].caras[kk+4] - 1 ) * 2;
        tmp_t2 = ( objetos[n_obj].grupos[jj].caras[kk+7] - 1 ) * 2;
        b_textura = 1;
      }
      tmp_n0 = objetos[n_obj].grupos[jj].caras[kk+2];
      if (  tmp_n0 > 0 ) {
        tmp_n0 = ( tmp_n0 - 1 ) * 3;
        tmp_n1 = ( objetos[n_obj].grupos[jj].caras[kk+5] - 1 ) * 3;
        tmp_n2 = ( objetos[n_obj].grupos[jj].caras[kk+8] - 1 ) * 3;
        b_normal = 1;
      }
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glBegin( GL_TRIANGLES );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n0 ], objetos[n_obj].vn[ tmp_n0 + 1 ], objetos[n_obj].vn[ tmp_n0 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t0 ], objetos[n_obj].vt[ tmp_t0 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v0 ], objetos[n_obj].v[  tmp_v0 + 1 ], objetos[n_obj].v[  tmp_v0 + 2 ] );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n1 ], objetos[n_obj].vn[ tmp_n1 + 1 ], objetos[n_obj].vn[ tmp_n1 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t1 ], objetos[n_obj].vt[ tmp_t1 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v1 ], objetos[n_obj].v[  tmp_v1 + 1 ], objetos[n_obj].v[  tmp_v1 + 2 ] );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n2 ], objetos[n_obj].vn[ tmp_n2 + 1 ], objetos[n_obj].vn[ tmp_n2 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t2 ], objetos[n_obj].vt[ tmp_t2 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v2 ], objetos[n_obj].v[  tmp_v2 + 1 ], objetos[n_obj].v[  tmp_v2 + 2 ] );
      glEnd();
    } // -- Fin de Caras  --
    if ( materiales[ n_material ].d < 1.0f ) glDisable( GL_BLEND );
    if ( texturas && ( materiales[ n_material ].n_map_Kd >= 0 ) ) 
      texturas[ materiales[ n_material ].n_map_Kd ].desactiva();
  }   // -- Fin de Grupos  --
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- DIBUJA UN OBJETO DE UN ARCHIVO OBJ ----------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
void C_Obj::Dibuja_Shadows( GLuint n_obj ) {
  for ( GLuint jj = 0; jj < objetos[n_obj].grupos.size(); jj++ ) { 
    for ( GLuint kk = 0; kk < objetos[n_obj].grupos[jj].caras.size(); kk+=9 ) {
      b_textura = 0; b_normal = 0;
      tmp_v0 = objetos[n_obj].grupos[jj].caras[kk];
      if ( tmp_v0 > 0 ) {
        tmp_v0 = ( tmp_v0 - 1 ) * 3;
        tmp_v1 = ( objetos[n_obj].grupos[jj].caras[kk+3] - 1 ) * 3;
        tmp_v2 = ( objetos[n_obj].grupos[jj].caras[kk+6] - 1 ) * 3;
      }
      tmp_t0 = objetos[n_obj].grupos[jj].caras[kk+1];
      if ( texturas && ( tmp_t0 > 0 ) ) {
        tmp_t0 = ( tmp_t0 - 1 ) * 2;
        tmp_t1 = ( objetos[n_obj].grupos[jj].caras[kk+4] - 1 ) * 2;
        tmp_t2 = ( objetos[n_obj].grupos[jj].caras[kk+7] - 1 ) * 2;
        b_textura = 1;
      }
      tmp_n0 = objetos[n_obj].grupos[jj].caras[kk+2];
      if (  tmp_n0 > 0 ) {
        tmp_n0 = ( tmp_n0 - 1 ) * 3;
        tmp_n1 = ( objetos[n_obj].grupos[jj].caras[kk+5] - 1 ) * 3;
        tmp_n2 = ( objetos[n_obj].grupos[jj].caras[kk+8] - 1 ) * 3;
        b_normal = 1;
      }
      glBegin( GL_TRIANGLES );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n0 ], objetos[n_obj].vn[ tmp_n0 + 1 ], objetos[n_obj].vn[ tmp_n0 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t0 ], objetos[n_obj].vt[ tmp_t0 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v0 ], objetos[n_obj].v[  tmp_v0 + 1 ], objetos[n_obj].v[  tmp_v0 + 2 ] );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n1 ], objetos[n_obj].vn[ tmp_n1 + 1 ], objetos[n_obj].vn[ tmp_n1 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t1 ], objetos[n_obj].vt[ tmp_t1 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v1 ], objetos[n_obj].v[  tmp_v1 + 1 ], objetos[n_obj].v[  tmp_v1 + 2 ] );
        if ( b_normal )
          glNormal3f(   objetos[n_obj].vn[ tmp_n2 ], objetos[n_obj].vn[ tmp_n2 + 1 ], objetos[n_obj].vn[ tmp_n2 + 2 ] );
        if ( b_textura )
          glTexCoord2f( objetos[n_obj].vt[ tmp_t2 ], objetos[n_obj].vt[ tmp_t2 + 1 ] );
          glVertex3f(   objetos[n_obj].v[  tmp_v2 ], objetos[n_obj].v[  tmp_v2 + 1 ], objetos[n_obj].v[  tmp_v2 + 2 ] );
      glEnd();
    } // -- Fin de Caras  --

  }   // -- Fin de Grupos  --
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- DIBUJA TODOS LOS OBJETOS DE UN ARCHIVO OBJ --------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
void C_Obj::Dibuja_Todo( void ) {
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
    this->Dibuja_Objeto( ii );
  }
}

void C_Obj::Dibuja_Todo_Shadows(void){
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
    this->Dibuja_Shadows( ii );
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- IMPRIME UN ARCHIVO OBJ + MTL ----------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
void C_Obj::Imprime( const char *Nombre_Archivo  ) {
  //----------------------------------------------------------------------------
  salida.open( Nombre_Archivo, ios::out );
  if ( !salida.is_open() ) {
    cerr << "No se puede abrir archivo \"" << Nombre_Archivo << "\"." << endl;
    return;
  }
  //----------------------------------------------------------------------------
  salida << "-------------------------------------------------------------------" << endl;
  salida << "-- IMPRIME ARCHIVO OBJ + MTL, por PIPAGERARDO                    --" << endl;  
  salida << "-------------------------------------------------------------------" << endl << endl;
  salida << "Nombre archivo obj: " << nombre_obj << endl << endl;
  salida << "Numero de Objetos : " << objetos.size() << endl << "----------------------" << endl << endl;
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
    salida << "  " << ii << " " << objetos[ii].nombre << endl << "  ----------------------" << endl;
    salida << "    Numero de vertices : " << objetos[ii].v.size() / 3 << endl << "    ----------------------" << endl;
    for ( GLuint jj = 0; jj < objetos[ii].v.size(); jj += 3 ) {
      salida << "      " << objetos[ii].v[jj] << " " << objetos[ii].v[jj+1] << " "  << objetos[ii].v[jj+2] << endl;
    }
    salida << "    Numero de normales : " << objetos[ii].vn.size() / 3 << endl << "    ----------------------" << endl;
    for ( GLuint jj = 0; jj < objetos[ii].vn.size(); jj += 3 ) {
      salida << "      " << objetos[ii].vn[jj] << " " << objetos[ii].vn[jj+1] << " "  << objetos[ii].vn[jj+2] << endl;
    }
    salida << "    Numero de textcoord: " << objetos[ii].vt.size() / 2 << endl << "    ----------------------" << endl;
    for ( GLuint jj = 0; jj < objetos[ii].vt.size(); jj += 2 ) {
      salida << "      " << objetos[ii].vt[jj] << " " << objetos[ii].vt[jj+1] << endl;
    }
    salida << "    Numero de Grupos   : " << objetos[ii].grupos.size() << endl << "    ----------------------" << endl;
    for ( GLuint jj = 0; jj < objetos[ii].grupos.size(); ++jj ) {
      salida << "      " << objetos[ii].grupos[jj].numero << " " << objetos[ii].grupos[jj].nombre << endl;
      for ( GLuint kk = 0; kk < objetos[ii].grupos[jj].caras.size(); kk+=9 ) {
        salida << "        ";
        salida << objetos[ii].grupos[jj].caras[kk+0] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+1] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+2] << " ";
        salida << objetos[ii].grupos[jj].caras[kk+3] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+4] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+5] << " ";
        salida << objetos[ii].grupos[jj].caras[kk+6] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+7] << "/";
        salida << objetos[ii].grupos[jj].caras[kk+8] << endl;
      }
    }    
    salida << endl;
  }
  if ( strlen( nombre_mtl ) > 0 ) {
  salida << "-------------------------------------------------------------------" << endl << endl;
  salida << "Nombre archivo mtl: " << nombre_mtl << endl << endl;
  salida << "Numero de Materiales : " << materiales.size() << endl << "----------------------" << endl << endl;
  for ( GLuint ii = 0; ii < materiales.size(); ii++ ) {
    salida << "  " << ii << " " << materiales[ii].nombre << endl;
    salida << "    Ns   : " << materiales[ii].Ns << endl;
    salida << "    d    : " << materiales[ii].d << endl;
    salida << "    Kd   : " << materiales[ii].Kd[0] << 
                       ", " << materiales[ii].Kd[1] << 
                       ", " << materiales[ii].Kd[2] << 
                       ", " << materiales[ii].Kd[3] << endl;
    salida << "    Ka   : " << materiales[ii].Ka[0] << 
                       ", " << materiales[ii].Ka[1] << 
                       ", " << materiales[ii].Ka[2] << 
                       ", " << materiales[ii].Ka[3] << endl;
    salida << "    Ks   : " << materiales[ii].Ks[0] << 
                       ", " << materiales[ii].Ks[1] << 
                       ", " << materiales[ii].Ks[2] << 
                       ", " << materiales[ii].Ks[3] << endl;
    salida << "    Ke   : " << materiales[ii].Ke[0] << 
                       ", " << materiales[ii].Ke[1] << 
                       ", " << materiales[ii].Ke[2] << 
                       ", " << materiales[ii].Ke[3] << endl;
    if ( materiales[ii].n_map_Kd >= 0 ) {
      salida << "    map_Kd : " << materiales[ii].n_map_Kd << " " << materiales[ii].map_Kd << endl << endl;
    } else salida << endl;
  }
  salida << endl;
  }
  salida << "-------------------------------------------------------------------" << endl;
  salida << "TOTAL : " << endl << "-------" << endl;
  salida << "  n_v: " << n_v << "   n_t: " << n_t << "   n_n: " << n_n << "   n_mat: " << materiales.size() << endl;
  salida << "-------------------------------------------------------------------" << endl;
  //----------------------------------------------------------------------------
  salida.close();
  if( salida.is_open() ) { 
    cerr << "Error cerrando archivo \"" << Nombre_Archivo << "\"." << endl;
    return;
  }
  //---------------------------------------------------------------------------- 
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- BORRA MANUALMENTE LOS OBJETOS Y LOS MATERIALES ----------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
void C_Obj::Borra( void ) {          
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
    objetos[ii].v.clear();
    objetos[ii].vn.clear();
    objetos[ii].vt.clear();  
    for ( GLuint jj = 0; jj < objetos[ii].grupos.size(); jj++ ) {
      objetos[ii].grupos[jj].caras.clear();
    }
    objetos[ii].grupos.clear();
  }
  objetos.clear();
  materiales.clear();
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- BORRA LAS NORMALES --------------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
void C_Obj::Borra_Normales( void ) {
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
    objetos[ii].vn.clear();
    for ( GLuint jj = 0; jj < objetos[ii].grupos.size(); jj++ ) {
      for ( GLuint kk = 0; kk < objetos[ii].grupos[jj].caras.size(); kk+=3 ) {
      objetos[ii].grupos[jj].caras[kk+2] = 0;
      }
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CALCULA LAS NORMALES ------------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
void C_Obj::Calcula_Normales( void ) {       
  GLfloat Vertex[9], Normal[3];
  GLuint Repetida;
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
  tmp_n0 = 1;
  for ( GLuint jj = 0; jj < objetos[ii].grupos.size(); jj++ ) {
  for ( GLuint kk = 0; kk < objetos[ii].grupos[jj].caras.size(); kk+=9 ) {
    if ( objetos[ii].grupos[jj].caras[kk+2] == 0 ) {
        tmp_v0 = ( objetos[ii].grupos[jj].caras[kk+0] - 1 ) * 3;
        tmp_v1 = ( objetos[ii].grupos[jj].caras[kk+3] - 1 ) * 3;
        tmp_v2 = ( objetos[ii].grupos[jj].caras[kk+6] - 1 ) * 3;
        Vertex[0] = objetos[ii].v[  tmp_v0 + 0 ];
        Vertex[1] = objetos[ii].v[  tmp_v0 + 1 ];
        Vertex[2] = objetos[ii].v[  tmp_v0 + 2 ];
        Vertex[3] = objetos[ii].v[  tmp_v1 + 0 ];
        Vertex[4] = objetos[ii].v[  tmp_v1 + 1 ];
        Vertex[5] = objetos[ii].v[  tmp_v1 + 2 ];
        Vertex[6] = objetos[ii].v[  tmp_v2 + 0 ];
        Vertex[7] = objetos[ii].v[  tmp_v2 + 1 ];
        Vertex[8] = objetos[ii].v[  tmp_v2 + 2 ];       
        Producto_en_Cruz( Vertex, Normal );
        // -- Verificar si está repetida la normal --
        Repetida = 0;
        for ( GLuint ll = 0; ll < objetos[ii].vn.size(); ll+=3 ) {
          /*
          if( ( Normal[0] == objetos[ii].vn[ll]   ) &&
              ( Normal[1] == objetos[ii].vn[ll+1] ) &&
              ( Normal[2] == objetos[ii].vn[ll+2] ) ) 
              { Repetida = ( ll / 3 ) + 1; break;   }
          */
          if( ( fabs( Normal[0] - objetos[ii].vn[ll] )   < 0.0005f  ) &&
              ( fabs( Normal[1] - objetos[ii].vn[ll+1] ) < 0.0005f  ) &&
              ( fabs( Normal[2] - objetos[ii].vn[ll+2] ) < 0.0005f  ) )
              { Repetida = ( ll / 3 ) + 1; break;   }
        }
        if ( Repetida ) {
          objetos[ii].grupos[jj].caras[kk+2] = Repetida;
          objetos[ii].grupos[jj].caras[kk+5] = Repetida;
          objetos[ii].grupos[jj].caras[kk+8] = Repetida;  
        } else {
          objetos[ii].vn.push_back( Normal[0] );
          objetos[ii].vn.push_back( Normal[1] ); 
          objetos[ii].vn.push_back( Normal[2] ); 
          objetos[ii].grupos[jj].caras[kk+2] = tmp_n0;
          objetos[ii].grupos[jj].caras[kk+5] = tmp_n0;
          objetos[ii].grupos[jj].caras[kk+8] = tmp_n0;
          ++tmp_n0;   
        } 
  } } } }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CALCULA LAS NORMALES SUAVES -----------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
void C_Obj::Calcula_Normales_Suaves( void ) {
  GLfloat Vertex[9], Normal[3], Suma_Normal[3], longitud;
  GLuint Punto;
  for ( GLuint ii = 0; ii < objetos.size(); ii++ ) {
  for ( GLuint jj = 0; jj < ( objetos[ii].v.size() / 3 ); jj++ ) {    
    Suma_Normal[0] = 0.0f; Suma_Normal[1] = 0.0f; Suma_Normal[2] = 0.0f; 
    for ( GLuint kk = 0; kk < objetos[ii].grupos.size(); kk++ ) {
    for ( GLuint ll = 0; ll < objetos[ii].grupos[kk].caras.size(); ll+=9 ) {
      // -- Buscamos triángulos que contengan el Punto --
      Punto = jj + 1;
      tmp_v0 = objetos[ii].grupos[kk].caras[ll+0];
      tmp_v1 = objetos[ii].grupos[kk].caras[ll+3];
      tmp_v2 = objetos[ii].grupos[kk].caras[ll+6];
      if ( ( tmp_v0 == Punto ) || ( tmp_v1 == Punto ) || ( tmp_v2 == Punto ) ) {
        // -- Asignamos el número de la normal a la cara --
        if      ( tmp_v0 == Punto ) objetos[ii].grupos[kk].caras[ll+2] = Punto;
        else if ( tmp_v1 == Punto ) objetos[ii].grupos[kk].caras[ll+5] = Punto;
        else if ( tmp_v2 == Punto ) objetos[ii].grupos[kk].caras[ll+8] = Punto;
        // -- Calculamos la Normal --                                    
        tmp_v0 = ( tmp_v0 - 1 ) * 3;
        tmp_v1 = ( tmp_v1 - 1 ) * 3;
        tmp_v2 = ( tmp_v2 - 1 ) * 3;
        Vertex[0] = objetos[ii].v[  tmp_v0 + 0 ];
        Vertex[1] = objetos[ii].v[  tmp_v0 + 1 ];
        Vertex[2] = objetos[ii].v[  tmp_v0 + 2 ];
        Vertex[3] = objetos[ii].v[  tmp_v1 + 0 ];
        Vertex[4] = objetos[ii].v[  tmp_v1 + 1 ];
        Vertex[5] = objetos[ii].v[  tmp_v1 + 2 ];
        Vertex[6] = objetos[ii].v[  tmp_v2 + 0 ];
        Vertex[7] = objetos[ii].v[  tmp_v2 + 1 ];
        Vertex[8] = objetos[ii].v[  tmp_v2 + 2 ];       
        Producto_en_Cruz( Vertex, Normal );  
        Suma_Normal[0] += Normal[0];
        Suma_Normal[1] += Normal[1];
        Suma_Normal[2] += Normal[2];                           
      }
    } // Fin for kk
    } // Fin for ll
    longitud = (GLfloat)sqrt( (Suma_Normal[0]*Suma_Normal[0]) 
                            + (Suma_Normal[1]*Suma_Normal[1]) 
                            + (Suma_Normal[2]*Suma_Normal[2]) );
    if( longitud == 0.0f ) longitud = 1.0f; 
    Suma_Normal[0] /= longitud; 
    Suma_Normal[1] /= longitud; 
    Suma_Normal[2] /= longitud;
    objetos[ii].vn.push_back( Suma_Normal[0] );
    objetos[ii].vn.push_back( Suma_Normal[1] ); 
    objetos[ii].vn.push_back( Suma_Normal[2] );
  } // Fin for jj
  } // Fin for ii
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- FIN DE FUNCIONES PÚBLICAS -------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- INICO DE FUNCIONES PRIVADAS -----------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- RETORNA LOS NOMBRES DE LAS TEXTURAS DE UN OBJ -----------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
const char* C_Obj::Nombre_Texturas( GLint num ) {
  for (  GLuint ii = 0; ii < materiales.size(); ii++ ) {
    if ( materiales[ii].n_map_Kd >= 0 ) {
       if ( num == materiales[ii].n_map_Kd ) return materiales[ii].map_Kd; 
    }   
  }
  return "Error_Nombre_Textura";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- DIBUJA UN MATERIAL --------------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------  
void C_Obj::Dibuja_Material( GLuint n_mat ) {
  glColor4fv( materiales[ n_mat ].Kd );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   materiales[ n_mat ].Kd );
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   materiales[ n_mat ].Ka );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  materiales[ n_mat ].Ks );
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  materiales[ n_mat ].Ke );
  glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, materiales[ n_mat ].Ns );
  if ( materiales[ n_mat ].d < 1.0f ) {
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
    glEnable(  GL_BLEND );
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CARGA LOS DATOS DE UN ARCHIVO OBJ -----------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
void C_Obj::Leer_Archivo_OBJ( void ) {
  //----------------------------------------------------------------------------
  archivo.open( nombre_obj, ios::in  );
  if ( !archivo.is_open() ) {
    estado = 0; 
    cerr << "No se puede abrir archivo \"" << nombre_obj << "\"." << endl;
    return;
  }
  //----------------------------------------------------------------------------
  //-- VERIFICA QUE ES UN ARCHIVO OBJ ------------------------------------------
  //----------------------------------------------------------------------------
  archivo.getline( linea, Obj_Linea );
  if ( linea[0]!='#' ) {
    estado = 0; 
    cerr << "El archivo \"" << nombre_obj << "\" no es correcto." << endl;
    archivo.close();
    return;
  }
  while ( !archivo.eof() ) {       
    archivo.getline( linea, Obj_Linea );
    //--------------------------------------------------------------------------
    switch( linea[0] ) {
      //------------------------------------------------------------------------
      case 'm':               // -- ARCHIVO DE MATERIALES --
        // sscanf( linea, "mtllib %s", nombre_mtl );
        { 
          char tmp_char[ Obj_N_Max ]; tmp_char[0] = '\0'; 
          sscanf( linea, "mtllib %s", tmp_char );
          strcat( nombre_mtl, directorio );
          strcat( nombre_mtl, tmp_char   );
        }
        break;
      //------------------------------------------------------------------------
      case 'o':               // -- OBJETO -- 
        sscanf( linea, "o %s", tmp_objeto.nombre );
        objetos.push_back( tmp_objeto );
        ++n_objeto; n_grupo = -1;
        c_v = n_v; c_t = n_t; c_n = n_n;
        break;
      //------------------------------------------------------------------------
      case 'u':               // -- GRUPO -- 
        sscanf( linea, "usemtl %s", tmp_grupo.nombre );
        tmp_grupo.numero = 0;
        objetos[ n_objeto ].grupos.push_back( tmp_grupo );
        ++n_grupo;
        break;
      //------------------------------------------------------------------------
      case 'v':               // -- V, VT, VN --
        switch( linea[1] ) {
          case ' ':          // -- VERTICE --
            sscanf( linea, "v %f %f %f", &tmp_f0, &tmp_f1, &tmp_f2 ); 
            objetos[ n_objeto ].v.push_back( tmp_f0 );
            objetos[ n_objeto ].v.push_back( tmp_f1 );
            objetos[ n_objeto ].v.push_back( tmp_f2 );
            ++n_v;              
            break;
          case 't':          // -- TEXTURA --
            sscanf( linea, "vt %f %f", &tmp_f0, &tmp_f1 ); 
            objetos[ n_objeto ].vt.push_back( tmp_f0 );
            objetos[ n_objeto ].vt.push_back( tmp_f1 );  
            ++n_t;      
            break;
          case 'n':          // -- NORMAL --
            sscanf( linea, "vn %f %f %f", &tmp_f0, &tmp_f1, &tmp_f2 ); 
            objetos[ n_objeto ].vn.push_back( tmp_f0 );
            objetos[ n_objeto ].vn.push_back( tmp_f1 );
            objetos[ n_objeto ].vn.push_back( tmp_f2 ); 
            ++n_n;         
            break;
          default:
            break;
        } // -- FIN -- switch( linea[1] ) --
        break;
      //------------------------------------------------------------------------
      case 'f':               // -- V, VN, VT --
        // -- CASOS ->   v//n   o   v//   -------------------------------------- 
        if ( strstr( linea, "//" ) ) {
          // -------------------------------------------------------------------
          // -- CASO -> v//n ---------------------------------------------------
          // -------------------------------------------------------------------
          if ( sscanf( linea, "f %d//%d %d//%d %d//%d", 
               &tmp_v0, &tmp_n0, &tmp_v1, &tmp_n1, &tmp_v2, &tmp_n2 ) == 6 ) {
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n0 - c_n );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n1 - c_n );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n2 - c_n );
            // -- Caso de no ser un triángulo ----------------------------------
            char *p;
            p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
            while(p) {
              p = strtok(NULL, " ");
              if(p) { 
                sscanf( p, "%d//%d", &tmp_v1, &tmp_n1 );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n0 - c_n );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n2 - c_n );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n1 - c_n );
                tmp_v2 = tmp_v1; tmp_n2 = tmp_n1;
              }
            }
          // -------------------------------------------------------------------
          // -- CASO ->   v// --------------------------------------------------
          // -------------------------------------------------------------------  
          } else {
            sscanf( linea, "f %d// %d// %d//", &tmp_v0, &tmp_v1, &tmp_v2 );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
            // -- Caso de no ser un triángulo ----------------------------------
            char *p;
            p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
            while(p) {
              p = strtok(NULL, " ");
              if(p) { 
                sscanf( p, "%d//", &tmp_v1 );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
                tmp_v2 = tmp_v1;
              }
            } 
          }
        // ---------------------------------------------------------------------
        // -- CASO ->   v/t/n  -------------------------------------------------
        // ---------------------------------------------------------------------
        } else if ( sscanf( linea, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
                                   &tmp_v0, &tmp_t0, &tmp_n0, 
                                   &tmp_v1, &tmp_t1, &tmp_n1, 
                                   &tmp_v2, &tmp_t2, &tmp_n2          ) == 9 ) {
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n0 - c_n );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n1 - c_n );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n2 - c_n );
          // -- Caso de no ser un triángulo ------------------------------------
          char *p;
          p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
          while(p) {
            p = strtok(NULL, " ");
            if(p) { 
              sscanf( p, "%d/%d/%d", &tmp_v1, &tmp_t1, &tmp_n1 );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n0 - c_n );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n2 - c_n );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_n1 - c_n );
              tmp_v2 = tmp_v1; tmp_t2 = tmp_t1; tmp_n2 = tmp_n1;
            }
          }
        // ---------------------------------------------------------------------
        // -- CASO ->   v/t/  --------------------------------------------------
        // ---------------------------------------------------------------------
        } else if ( sscanf( linea, "f %d/%d/ %d/%d/ %d/%d/", 
                                   &tmp_v0, &tmp_t0,  
                                   &tmp_v1, &tmp_t1,  
                                   &tmp_v2, &tmp_t2                   ) == 6 ) {
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          // -- Caso de no ser un triángulo ------------------------------------
          char *p;
          p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
          while(p) {
            p = strtok(NULL, " ");
            if(p) { 
              sscanf( p, "%d/%d/", &tmp_v1, &tmp_t1 );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              tmp_v2 = tmp_v1; tmp_t2 = tmp_t1;
            }
          }
        // ---------------------------------------------------------------------
        // -- CASO ->   v/t   --------------------------------------------------
        // ---------------------------------------------------------------------
        } else if ( sscanf( linea, "f %d/%d %d/%d %d/%d", 
                                   &tmp_v0, &tmp_t0,  
                                   &tmp_v1, &tmp_t1,  
                                   &tmp_v2, &tmp_t2                   ) == 6 ) {
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          // -- Caso de no ser un triángulo ------------------------------------
          char *p;
          p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
          while(p) {
            p = strtok(NULL, " ");
            if(p) { 
              sscanf( p, "%d/%d", &tmp_v1, &tmp_t1 );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t0 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t2 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_t1 - c_t );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              tmp_v2 = tmp_v1; tmp_t2 = tmp_t1;
            }
          }
        // ---------------------------------------------------------------------
        // -- CASO -> v   ------------------------------------------------------
        // ---------------------------------------------------------------------
        } else {
          sscanf( linea, "f %d %d %d", &tmp_v0, &tmp_v1, &tmp_v2              );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
          // -- Caso de no ser un triángulo ------------------------------------
          char *p;
          p = strtok(linea, " "); p = strtok(NULL, " "); p = strtok(NULL, " "); p = strtok(NULL, " ");
          while(p) {
            p = strtok(NULL, " ");
            if(p) { 
              sscanf( p, "%d", &tmp_v1 );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v0 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v2 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back( tmp_v1 - c_v );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              objetos[ n_objeto ].grupos[ n_grupo ].caras.push_back(      0       );
              tmp_v2 = tmp_v1;
            }
          }
        }        
        break;
      //------------------------------------------------------------------------
      default:
        break;
    } // -- FIN -- switch( linea[0] ) --
    //--------------------------------------------------------------------------
  } // -- FIN -- while --
  //----------------------------------------------------------------------------
  archivo.clear();  
  archivo.close();
  if( archivo.is_open() ) { 
    estado = 0; 
    cerr << "Error cerrando archivo \"" << nombre_obj << "\"." << endl;
    return;
  }
  //----------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- CARGA LOS DATOS DE UN ARCHIVO MTL -----------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------   
void C_Obj::Leer_Archivo_MTL( void ) {
  //----------------------------------------------------------------------------
  archivo.open( nombre_mtl, ios::in  );
  if ( !archivo.is_open() ) {
    estado = 0; 
    cerr << "No se puede abrir archivo \"" << nombre_mtl << "\"." << endl;
    return;
  }
  //----------------------------------------------------------------------------
  while ( !archivo.eof() ) {       
    archivo.getline( linea, Obj_Linea );
    //--------------------------------------------------------------------------
    switch( linea[0] ) {
      //------------------------------------------------------------------------
      case 'n':               // -- NUEVO MATERIAL --
        if ( n_material == 1 ) materiales.push_back( tmp_material );
        else n_material = 1;
        sscanf( linea, "newmtl %s", tmp_material.nombre );
        tmp_material.Ns    = 12.8f;
        tmp_material.d     = 1.0f;
        tmp_material.Kd[0] = 1.0f;
        tmp_material.Kd[1] = 1.0f;
        tmp_material.Kd[2] = 1.0f;
        tmp_material.Kd[3] = 1.0f;
        tmp_material.Ka[0] = 0.25f;
        tmp_material.Ka[1] = 0.25f;
        tmp_material.Ka[2] = 0.25f;
        tmp_material.Ka[3] = 1.0f;
        tmp_material.Ks[0] = 1.0f;
        tmp_material.Ks[1] = 1.0f;
        tmp_material.Ks[2] = 1.0f;
        tmp_material.Ks[3] = 1.0f;
        tmp_material.Ke[0] = 0.0f;
        tmp_material.Ke[1] = 0.0f;
        tmp_material.Ke[2] = 0.0f;
        tmp_material.Ke[3] = 0.0f;
        tmp_material.map_Kd[0] = '\0';
        tmp_material.n_map_Kd = -1;
        break;
      //------------------------------------------------------------------------
      case 'N':               // -- ( shininess / 128.0 * 1000.0 ) --
        sscanf( linea, "Ns %f", &tmp_material.Ns );
        tmp_material.Ns /= 1000.0f;
        tmp_material.Ns *= 128.0f;
        break;
      //------------------------------------------------------------------------
      case 'd':               // -- ( alpha ) --
        sscanf( linea, "d %f", &tmp_material.d );
        tmp_material.Kd[3] = tmp_material.d;
        tmp_material.Ka[3] = tmp_material.d;
        tmp_material.Ks[3] = tmp_material.d;
        break;
      //------------------------------------------------------------------------
      case 'K':               // -- Kd, Ka, Ks, Ke --
        switch( linea[1] ) {
          case 'd':          // -- Kd --
            sscanf( linea, "Kd %f %f %f", &tmp_material.Kd[0], &tmp_material.Kd[1], &tmp_material.Kd[2] ); 
            break;
          case 'a':          // -- Ka --
            sscanf( linea, "Ka %f %f %f", &tmp_material.Ka[0], &tmp_material.Ka[1], &tmp_material.Ka[2] ); 
            break;
          case 's':          // -- Ks --
            sscanf( linea, "Ks %f %f %f", &tmp_material.Ks[0], &tmp_material.Ks[1], &tmp_material.Ks[2] ); 
            break;
          case 'e':          // -- Ke --
            sscanf( linea, "Ke %f %f %f", &tmp_material.Ke[0], &tmp_material.Ke[1], &tmp_material.Ke[2] ); 
            if ( tmp_material.Ke[0] + tmp_material.Ke[1] + tmp_material.Ke[2] > 0.0f ) tmp_material.Ke[3] = tmp_material.d;
            break;
          default:
            break;
        } // -- FIN -- switch( linea[1] ) --
        break;
      //------------------------------------------------------------------------
      case 'm':               // -- ( map_Kd ) --
        switch( linea[5] ) {
          case 'd':          // -- Kd --
            { 
              char tmp_char[Obj_N_Max ]; tmp_char[0] = '\0'; 
              sscanf( linea, "map_Kd %s", tmp_char );
              strcat( tmp_material.map_Kd, directorio );
              strcat( tmp_material.map_Kd, tmp_char   );
            }
            tmp_material.n_map_Kd = n_text;
            ++n_text;
            break;
          default:
            break;
        }
        break;
      //------------------------------------------------------------------------
      default:
        break;
    } // -- FIN -- switch( linea[0] ) --
    //-------------------------------------------------------------------------- 
  } // -- FIN -- while --
  materiales.push_back( tmp_material ); // -- El último material --
  //----------------------------------------------------------------------------
  archivo.close();
  if( archivo.is_open() ) { 
    estado = 0; 
    cerr << "Error cerrando archivo \"" << nombre_mtl << "\"." << endl;
    return;
  }
  //----------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- FIN DE FUNCIONES PRIVADAS -------------------------------------------------
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
