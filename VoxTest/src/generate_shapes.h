#ifndef GENERATE_SHAPES_H
#define GENERATE_SHAPES_H

#include <stdint.h>
#include <memory>
//#include <boost/concept_check.hpp>

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
        m_size = 0;
        m_num_vox = 0;
    }
    
    ShapeData( int size ) : m_data( new char[size], std::default_delete<char[]>() )
    {
        m_size = size;
        m_num_vox = (m_size - VXC::size_of_head) / VXC::size_of_voxel;
    }
    
    ShapeData( int size, char *buf ) : m_data( buf, std::default_delete<char[]>() )
    {
        m_size = size;
        m_num_vox = (m_size - VXC::size_of_head) / VXC::size_of_voxel;
    }

    ShapeData( ShapeData &&other )
    {
        m_size = other.m_size;
        m_num_vox = other.m_num_vox;
        m_data = std::move( other.m_data );
    }
    
    ShapeData& operator=( ShapeData &&other )
    {
        m_size = other.m_size;
        m_num_vox = other.m_num_vox;
        m_data = std::move( other.m_data );
        
        return *this;
    }
    
    char* getData() const
    {
        return m_data.get();
    }
    
    void setData()
    {
    }
    
    uint64_t getSize() const
    {
        return m_size;
    }

    uint64_t getVoxNumber() const
    {
        return m_num_vox;
    }
    
    Vector3D getOrigin() const
    {
        float *f_data = (float*)m_data.get();
        Vector3D result( f_data[1], f_data[2], f_data[3] );
        return result;
    }
    
    float getWidth() const
    {
        float *f_data = (float*)m_data.get();
        return f_data[4];
    }
    
    float getHeight() const
    {
        float *f_data = (float*)m_data.get();
        return f_data[5];
    }
    
    float getDepth() const
    {
        float *f_data = (float*)m_data.get();
        return f_data[6];
    }

    float getVoxMetre() const
    {
        float *f_data = (float*)m_data.get();
        return f_data[0];
    }
    
    Vector3D getVoxel( const int index, uint32_t &color ) const
    {
        float *f_data = (float*)( m_data.get() + VXC::size_of_head + VXC::size_of_voxel * index );
        uint32_t *i_data = (uint32_t*)( m_data.get() + VXC::size_of_head + VXC::size_of_voxel * index + VXC::size_of_vec );
        color = i_data[0];
        return Vector3D( f_data[0], f_data[1], f_data[2] );
    }
    
private:
    uint64_t m_num_vox;
    uint64_t m_size;
    std::unique_ptr<char[]> m_data;
    //std::shared_ptr< char > m_data;
};

class GenShapes
{
public:
    static ShapeData genBox( const float vox_size, 
                             const uint32_t width, 
                             const uint32_t height, 
                             const uint32_t depth, 
                             uint32_t &size_bytes );
    static ShapeData genSpere( const float vox_size,
                               uint32_t &size_bytes );
};

#endif