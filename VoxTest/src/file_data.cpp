#include <iostream>
#include <cstdio>
#include <fstream>
#include "file_data.h"

void create_data_file( const std::string file_name, const char *buf, const int size )
{ 
    FILE *pFile = NULL;
    pFile = fopen ( file_name.c_str(), "wb" );
    if( pFile != NULL )
    {
        fwrite( buf, size, 1, pFile );
        fclose( pFile );
    }
    else
        std::cout << "Can't open file for writing" << std::endl;
}

char* read_data_file( const std::string file_name, int &size )
{
    FILE *pFile = NULL;
    pFile = fopen( file_name.c_str(), "rb" );
    
    if( pFile == NULL )
        return NULL;
    
    fseek( pFile, 0, SEEK_END );
    size = ftell( pFile );
    rewind( pFile );
    
    char *buf = new char[size];
    fread( buf, size, 1, pFile );
    
    return buf;
}

std::string file_to_string(const char *file)
{
    std::string result;
    std::string word;

    std::ifstream f;
    f.open(file);
    if (!f.is_open())
        return std::string();
    while (!f.eof())
    {
        f >> word;
        result += word;
        char c;
        if (f.get(c))
            result += c;
    }

    std::cout << result << std::endl;

    return result; // Вернуть буфер
}

char* filetobuf(char *file)
{
    FILE *fptr;
    long length;
    char *buf;

    fptr = fopen(file, "rb"); // Открыть файл на чтение
    if (!fptr) // выйти если ошибка при инициализации fptr
        return NULL;
    fseek(fptr, 0, SEEK_END); // Переместиться в конец файла
    length = ftell(fptr); // Найти размер файла
    buf = (char*)malloc(length+1); // Выделить буфер в который будет читаться файл
    fseek(fptr, 0, SEEK_SET); // Переместиться в начало файла
    fread(buf, length, 1, fptr); // Прочитать содержимое файла в буфер
    fclose(fptr); // Закрыть файл
    buf[length] = 0; // Символ конца буфера (иногда нужен ибо некоторые функции old C не принимают размер буфера)

    return buf; // Вернуть буфер
}