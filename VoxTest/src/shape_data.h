#ifndef __SHAPE_DATA__H
#define __SHAPE_DATA__H

#include <cstdint>
#include <vector>

#include <Geometry.h>
#include "vox_data_level.h"



struct Head
{
    double      m_voxSizeDimension;
    Vector3D    m_origin;
    Vector3D    m_spatialSize;
    Vector3D    m_minimum;
    Vector3D    m_maximum;
};

struct Voxel
{
    Color       m_color;
    Vector3D    m_vec;
};

namespace VXC
{
    const int size_of_color = sizeof(Color);
    const int size_of_vec = sizeof(Vector3D);
    const int size_of_voxel = sizeof(Voxel);
    const int size_of_head = sizeof(Head);
}

class ShapeData
{
public:
    ShapeData();
    
    ShapeData(const std::vector<char>& _buf);

    ShapeData(ShapeData&& _other);
    
    ShapeData& operator=(ShapeData&& _other);
    
    char* getData() const;
    
    uint64_t getDataSize() const;

    uint64_t getVoxNumber() const;
    
    Vector3D getOrigin() const;
    void setOrigin(const Vector3D& _origin);
    
    // Габариты всей фигуры
    Vector3D getSpatialSize() const;                           
    void setSpatialSize(const Vector3D& _spatialDimension);

    // Размер вокселя в пространстве
    float getVoxMetre() const;
    void setVoxMetre(const float _voxSpatialSize);
    
    Vector3D getVoxel(const int index, uint32_t &color) const;
    void addVoxel(const Vector3D& _vec, const uint32_t _color);
    
    Vector3D getMinimum() const;
    Vector3D getMaximum() const;

private:
    
    std::vector<char> m_data;
};

void updateHead(Head *_head, const Vector3D& _newVec);

void updateOrigin(Head *_head);

void updateSpatialSize(Head *_head); 

#endif