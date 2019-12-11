#include "gl_helpers.h"

#include <iostream>
#include <glExtInit.h>

void checkOpenGLerror()
{
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

//! Функция печати лога шейдера
void shaderLog(unsigned int shader)
{
	int   infologLen = 0;
	int   charsWritten = 0;
	char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << __FUNCTION__ << " ERROR: Could not allocate InfoLog buffer" << std::endl << std::endl;
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << __FUNCTION__ << " InfoLog: " << infoLog << std::endl << std::endl;
		delete[] infoLog;
	}
}

char* filetobuf(const std::string &file)
{
	FILE *fptr;
	long length;
	char *buf;

	fptr = fopen(file.c_str(), "rb"); // Открыть файл на чтение
	if (!fptr) // выйти если ошибка при инициализации fptr
		return NULL;
	fseek(fptr, 0, SEEK_END); // Переместиться в конец файла
	length = ftell(fptr); // Найти размер файла
	buf = (char*)malloc(length + 1); // Выделить буфер в который будет читаться файл
	fseek(fptr, 0, SEEK_SET); // Переместиться в начало файла
	fread(buf, length, 1, fptr); // Прочитать содержимое файла в буфер
	fclose(fptr); // Закрыть файл
	buf[length] = 0; // Символ конца буфера (иногда нужен ибо некоторые функции old C не принимают размер буфера)

	//std::cout << buf << std::endl;

	return buf; // Вернуть буфер
}

//-----------Создание шейдеров из файла и компилиция----------
void create_shader(const std::string & vert_,
	const std::string & frag_,
	GLuint & vertexShader,
	GLuint & fragmentShader
	)
{
	GLchar *vertexSource = filetobuf(vert_);
	GLchar *fragmentSource = filetobuf(frag_);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	free(vertexSource);
	free(fragmentSource);
	glCompileShader(vertexShader);
	shaderLog(vertexShader);
	glCompileShader(fragmentShader);
	shaderLog(fragmentShader);
}