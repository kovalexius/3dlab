#ifndef __SHAPE_DATA__H
#define __SHAPE_DATA__H

#include <cstdint>
#include <vector>

#include <Geometry.h>

namespace VXC
{
    const int size_of_color = sizeof(int32_t);
    const int size_of_vec = 3 * sizeof(float);
    const int size_of_voxel = size_of_color + size_of_vec;
    const int size_of_head = sizeof(float) + size_of_vec + 3 * sizeof(float);
}

class ShapeData
{
public:
    ShapeData()
    {
        m_num_vox = 0;
    }
    
    ShapeData(int _size) : m_data(_size)
    {
        m_num_vox = (m_data.size() - VXC::size_of_head) / VXC::size_of_voxel;
    }
    
    ShapeData(const std::vector<char>& _buf) : m_data(_buf)
    {
        m_num_vox = (m_data.size() - VXC::size_of_head) / VXC::size_of_voxel;
    }

    ShapeData(ShapeData&& _other)
    {
        m_num_vox = _other.m_num_vox;
        m_data = std::move(_other.m_data);
    }
    
    ShapeData& operator=(ShapeData&& _other)
    {
        m_num_vox = _other.m_num_vox;
        m_data = std::move(_other.m_data);
        
        return *this;
    }
    
    char* getData() const
    {
        return (char*)m_data.data();
    }
    
    void setData()
    {
    }
    
    uint64_t getSize() const
    {
        return m_data.size();
    }

    uint64_t getVoxNumber() const
    {
        return m_num_vox;
    }
    
    Vector3D getOrigin() const
    {
        float *f_data = (float*)m_data.data();
        Vector3D result( f_data[1], f_data[2], f_data[3] );
        return result;
    }
    
    float getWidth() const
    {
        float *f_data = (float*)m_data.data();
        return f_data[4];
    }
    
    float getHeight() const
    {
        float *f_data = (float*)m_data.data();
        return f_data[5];
    }
    
    float getDepth() const
    {
        float *f_data = (float*)m_data.data();
        return f_data[6];
    }

    float getVoxMetre() const
    {
        float *f_data = (float*)m_data.data();
        return f_data[0];
    }
    
    Vector3D getVoxel(const int index, uint32_t &color) const
    {
        float *f_data = (float*)(m_data.data() + VXC::size_of_head + VXC::size_of_voxel * index);
        uint32_t *i_data = (uint32_t*)(m_data.data() + VXC::size_of_head + VXC::size_of_voxel * index + VXC::size_of_vec);
        color = i_data[0];
        return Vector3D(f_data[0], f_data[1], f_data[2]);
    }
    
private:
    uint64_t m_num_vox;
    std::vector<char> m_data;
};

#endif