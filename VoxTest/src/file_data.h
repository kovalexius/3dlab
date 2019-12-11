#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>

void create_data_file( const std::string file_name, const char *buf, const int size );

std::vector<char> read_data_file(const std::string& _file_name);

std::string file_to_string(const char *file);




#endif