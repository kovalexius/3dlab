#include "shape_data.h"

ShapeData::ShapeData()
{
    m_num_vox = 0;
}

ShapeData::ShapeData(int _size) : m_data(_size)
{
    m_num_vox = (m_data.size() - VXC::size_of_head) / VXC::size_of_voxel;
}

ShapeData::ShapeData(const std::vector<char>& _buf) : m_data(_buf)
{
    m_num_vox = (m_data.size() - VXC::size_of_head) / VXC::size_of_voxel;
}


ShapeData::ShapeData(ShapeData&& _other)
{
    m_num_vox = _other.m_num_vox;
    m_data = std::move(_other.m_data);
}

ShapeData& ShapeData::operator=(ShapeData&& _other)
{
    m_num_vox = _other.m_num_vox;
    m_data = std::move(_other.m_data);
    
    return *this;
}

char* ShapeData::getData() const
{
    return (char*)m_data.data();
}

void ShapeData::setData()
{
}

uint64_t ShapeData::getSize() const
{
    return m_data.size();
}
uint64_t ShapeData::getVoxNumber() const
{
    return m_num_vox;
}

Vector3D ShapeData::getOrigin() const
{
    /*
    float *vec_ptr = (Vector3D*)m_data.data();
    Vector3D result(static_cast<double>(f_data[1]), 
                    static_cast<double>(f_data[2]), 
                    static_cast<double>(f_data[3]));
    return result;
    */

    auto vec_ptr = static_cast<Vector3D*>(m_data.data() + sizeof(double));
    return *vec_ptr;
}

void ShapeData::setOrigin(Vector3D& _origin)
{
    auto vec_ptr = static_cast<Vector3D*>(m_data.data() + sizeof(double));
    *vec_ptr = _origin;
}

/*
float ShapeData::getWidth() const
{
    float *f_data = (float*)m_data.data();
    return f_data[4];
}

float ShapeData::getHeight() const
{
    float *f_data = (float*)m_data.data();
    return f_data[5];
}

float ShapeData::getDepth() const
{
    float *f_data = (float*)m_data.data();
    return f_data[6];
}
*/

Vector3D ShapeData::getSpatialDimension() const
{
    
}

void ShapeData::setSpatialDimension(const Vector3D& _spatialDimension)
{}

float ShapeData::getVoxMetre() const
{
    float *f_data = (float*)m_data.data();
    return f_data[0];
}

Vector3D ShapeData::getVoxel(const int index, uint32_t &color) const
{
    float *f_data = (float*)(m_data.data() + VXC::size_of_head + VXC::size_of_voxel * index);
    uint32_t *i_data = (uint32_t*)(m_data.data() + VXC::size_of_head + VXC::size_of_voxel * index + VXC::size_of_vec);
    color = i_data[0];

    std::cout << __FUNCTION__ << " f_data[0]: " << f_data[0] << " f_data[1]: " << f_data[1] << " f_data[2]: " << f_data[2] << std::endl;

    return Vector3D(static_cast<double>(f_data[0]), 
                    static_cast<double>(f_data[1]), 
                    static_cast<double>(f_data[2]));
}