#include <iostream>
#include <cstdio>
#include <fstream>
#include "file_data.h"

void create_data_file(const std::string file_name, const char *buf, const int size)
{ 
    FILE *pFile = NULL;
    pFile = fopen (file_name.c_str(), "wb");
    if( pFile != NULL )
    {
        fwrite( buf, size, 1, pFile );
        fclose( pFile );
    }
    else
        std::cout << "Can't open file for writing" << std::endl;
}

std::vector<char> read_data_file(const std::string& _file_name)
{
    FILE *pFile = NULL;
    pFile = fopen(_file_name.c_str(), "rb" );
    
    if(pFile == NULL)
        return std::vector<char>();
    
    fseek( pFile, 0, SEEK_END );

    auto size = ftell(pFile);
    rewind(pFile);
    
    std::vector<char> buf(size);
    fread(buf.data(), size, 1, pFile);

    fclose(pFile);
    
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
