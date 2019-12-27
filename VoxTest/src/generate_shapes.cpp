#include <iostream>
#include <iomanip>

#include "generate_shapes.h"

using namespace VXC;

ShapeData GenShapes::genBox(const float vox_size,
    const uint32_t width,
    const uint32_t height,
    const uint32_t depth)
{   
    ShapeData result;
    
    int count = 0;
    for (uint32_t x = 0; x < width; x++)
    {
        for (uint32_t y = 0; y < height; y++)
        {
            Vector3D vec0(x*vox_size, y*vox_size, 0.0f);
            Vector3D vec_back(x*vox_size, y*vox_size, (depth-1)*vox_size);
            uint32_t color0 = 0x401010ff;
            uint32_t color_back = 0x104040ff;

            result.addVoxel(vec0, color0);
            count++;

            result.addVoxel(vec_back, color_back);
            count++;
        }
    }
    
    for (uint32_t x = 0; x < width; x++)
    {
        for(uint32_t z = 1; z < depth-1; z++)
        {
            Vector3D vec0( x*vox_size, 0.0f, z*vox_size );
            Vector3D vec_up( x*vox_size, (height-1)*vox_size, z*vox_size );
            uint32_t color0 = 0x055005ff;
            uint32_t color_up = 0x500550ff;
            
            result.addVoxel(vec0,color0 );
            count++;

            result.addVoxel(vec_up, color_up);
            count++;
        }
    }
    
    for (uint32_t y = 1; y < height-1; y++)
    {
        for(uint32_t z = 1; z < depth-1; z++)
        {
            Vector3D vec0( 0.0f, y*vox_size, z*vox_size );
            Vector3D vec_right( (width-1)*vox_size, y*vox_size, z*vox_size );
            uint32_t color0 = 0x202040ff;
            uint32_t color_right = 0x404020ff;

            result.addVoxel(vec0, color0);
            count++;
            
            result.addVoxel(vec_right, color_right);
            count++;
        }
    }
    
    //std::cout << "count vox = " << count << " bytes:" << count * size_of_voxel << std::endl;
    
    return result;
}