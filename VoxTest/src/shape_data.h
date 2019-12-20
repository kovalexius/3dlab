#ifndef __SHAPE_DATA__H
#define __SHAPE_DATA__H

#include <cstdint>
#include <vector>

#include <Geometry.h>
#include "vox_data_level.h"

namespace VXC
{
    const int size_of_color = sizeof(int32_t);
    const int size_of_vec = sizeof(Vector3D);
    const int size_of_voxel = size_of_color + size_of_vec;
    const int size_of_head = sizeof(double) + size_of_vec + size_of_vec;
}

struct Head
{
    double  m_voxSizeDimension;
    Vector3D    m_origin;
    Vector3D    m_spatialDimension;
};

struct Voxel
{
    Color   m_color;
    Vector3D    m_vec;
};

class ShapeData
{
public:
    ShapeData();
    
    ShapeData(int _size);
    
    ShapeData(const std::vector<char>& _buf);

    ShapeData(ShapeData&& _other);
    
    ShapeData& operator=(ShapeData&& _other);
    
    char* getData() const;
    
    void setData();
    
    uint64_t getDataSize() const;

    uint64_t getVoxNumber() const;
    
    Vector3D getOrigin() const;
    void setOrigin(Vector3D& _origin);
    
    Vector3D getSpatialDimension() const;   // Получить габариты
    void setSpatialDimension(const Vector3D& _spatialDimension);

    /*
    float getWidth() const;
    
    float getHeight() const;
    
    float getDepth() const;
    */

    float getVoxMetre() const;
    
    Vector3D getVoxel(const int index, uint32_t &color) const;
    
private:
    uint64_t m_num_vox;
    std::vector<char> m_data;
};

#endif