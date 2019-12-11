#ifndef __GL_HELPERS__H
#define __GL_HELPERS__H

#include <string>

#include <Windows.h>
#include "GL/glu.h"


void checkOpenGLerror();

//! Функция печати лога шейдера
void shaderLog(unsigned int shader);

char* filetobuf(const std::string &file);

//-----------Создание шейдеров из файла и компилиция----------
void create_shader(const std::string & vert_,
	const std::string & frag_,
	GLuint & vertexShader,
	GLuint & fragmentShader);

#endif