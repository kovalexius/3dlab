#include <iostream>
#include <iomanip>

#include "generate_shapes.h"

using namespace VXC;

ShapeData GenShapes::genBox(const float vox_size,
    const uint32_t width,
    const uint32_t height,
    const uint32_t depth,
    uint32_t &size_in_bytes)
{
    const int num_voxels = 2 * ( width*height + width*(depth-2) + (height-2)*(depth-2) );
    size_in_bytes = num_voxels * size_of_voxel + size_of_head; // Шапка + Воксели
    
    ShapeData result(size_in_bytes);
    char *ptr = result.getData();
    
    //std::cout << "result=" << std::hex << std::setw(16) << std::setfill('0') << (long)result.getData() << std::endl;
    //std::cout << "ptr=" << std::hex << std::setw(16) << std::setfill('0') << (long)ptr << std::endl;
    
    // Шапка: Размер вокселя + Координаты объекта + габариты
    *((float*)ptr) = vox_size;
    ptr += sizeof(float);
    Vector3D coord(0.0, 0.0, 0.0);
    *((float*)ptr) = coord.x;
    ptr += sizeof(float);
    *((float*)ptr) = coord.y;
    ptr += sizeof(float);
    *((float*)ptr) = coord.z;
    ptr += sizeof(float);
    
    *((float*)ptr) = width * vox_size;
    ptr += sizeof(float);
    *((float*)ptr) = height * vox_size;
    ptr += sizeof(float);
    *((float*)ptr) = depth * vox_size;
    ptr += sizeof(float);
    /////
    
    int count = 0;
    for (uint32_t x = 0; x < width; x++)
    {
        for (uint32_t y = 0; y < height; y++)
        {
            Vector3D vec0( x*vox_size, y*vox_size, 0.0f );
            Vector3D vec_back( x*vox_size, y*vox_size, (depth-1)*vox_size );
            uint32_t color0 = 0x401010ff;
            uint32_t color_back = 0x104040ff;
            
            *((float*)ptr) = vec0.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color0;
            ptr += sizeof(uint32_t);
            count++;
            
            *((float*)ptr) = vec_back.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec_back.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec_back.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color_back;
            ptr += sizeof(uint32_t);
            count++;
        }
    }
    
    std::cout << "count vox = " << count << " bytes:" << count * size_of_voxel << std::endl;
    
    for (uint32_t x = 0; x < width; x++)
    {
        for(uint32_t z = 1; z < depth-1; z++)
        {
            Vector3D vec0( x*vox_size, 0.0f, z*vox_size );
            Vector3D vec_up( x*vox_size, (height-1)*vox_size, z*vox_size );
            uint32_t color0 = 0x055005ff;
            uint32_t color_up = 0x500550ff;
            
            *((float*)ptr) = vec0.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color0;
            ptr += sizeof(uint32_t);
            count++;
            
            *((float*)ptr) = vec_up.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec_up.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec_up.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color_up;
            ptr += sizeof(uint32_t);
            count++;
        }
    }
    
    std::cout << "count vox = " << count << " bytes:" << count * size_of_voxel << std::endl;
    
    for (uint32_t y = 1; y < height-1; y++)
    {
        for(uint32_t z = 1; z < depth-1; z++)
        {
            Vector3D vec0( 0.0f, y*vox_size, z*vox_size );
            Vector3D vec_right( (width-1)*vox_size, y*vox_size, z*vox_size );
            uint32_t color0 = 0x202040ff;
            uint32_t color_right = 0x404020ff;
            
            *((float*)ptr) = vec0.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec0.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color0;
            ptr += sizeof(uint32_t);
            count++;
            
            *((float*)ptr) = vec_right.x;
            ptr += sizeof(float);
            *((float*)ptr) = vec_right.y;
            ptr += sizeof(float);
            *((float*)ptr) = vec_right.z;
            ptr += sizeof(float);
            *((uint32_t*)ptr) = color_right;
            ptr += sizeof(uint32_t);
            count++;
        }
    }
    
    std::cout << "count vox = " << count << " bytes:" << count * size_of_voxel << std::endl;
    
    return result;
}