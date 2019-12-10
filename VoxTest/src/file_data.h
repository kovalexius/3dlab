#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>

void create_data_file( const std::string file_name, const char *buf, const int size );

char* read_data_file( const std::string file_name, int &size );

std::string file_to_string(const char *file);

char* filetobuf(char *file);



#endif