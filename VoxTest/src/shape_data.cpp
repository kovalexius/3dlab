#include "shape_data.h"
#include <limits>

ShapeData::ShapeData()
{
    m_data.resize(sizeof(Head));
    Head *head = reinterpret_cast<Head*>(m_data.data());
    setMaximum(head->m_minimum);
    setMinimum(head->m_maximum);
}

ShapeData::ShapeData(const std::vector<char>& _buf) : m_data(_buf)
{
}


ShapeData::ShapeData(ShapeData&& _other)
{
    m_data = std::move(_other.m_data);
}

ShapeData& ShapeData::operator=(ShapeData&& _other)
{
    m_data = std::move(_other.m_data);
    
    return *this;
}

char* ShapeData::getData() const
{
    return (char*)m_data.data();
}

uint64_t ShapeData::getDataSize() const
{
    return m_data.size();
}

uint64_t ShapeData::getVoxNumber() const
{
    return (m_data.size() - sizeof(Head))/sizeof(Voxel);
}

Vector3D ShapeData::getOrigin() const
{
    const Head *head_ptr = reinterpret_cast<const Head*>(m_data.data());
    return head_ptr->m_origin;
}

void ShapeData::setOrigin(const Vector3D& _origin)
{
    Head *head_ptr = reinterpret_cast<Head*>(m_data.data());
    head_ptr->m_origin = _origin;
}

Vector3D ShapeData::getSpatialSize() const
{
    const Head *head = reinterpret_cast<const Head*>(m_data.data());
    return head->m_spatialSize;
}

void ShapeData::setSpatialSize(const Vector3D& _spatialSize)
{
    Head *head = reinterpret_cast<Head*>(m_data.data());
    head->m_spatialSize = _spatialSize;
}

float ShapeData::getVoxMetre() const
{
    const Head *head = reinterpret_cast<const Head*>(m_data.data());
    return head->m_voxSizeDimension;
}

void ShapeData::setVoxMetre(const float _voxSpatialSize)
{
    Head *head = reinterpret_cast<Head*>(m_data.data());
    head->m_voxSizeDimension = _voxSpatialSize;
}

Vector3D ShapeData::getVoxel(const int _index, uint32_t& _color) const
{
    const Voxel *voxel = reinterpret_cast<const Voxel*>(m_data.data() + VXC::size_of_head);
    _color = voxel[_index].m_color.color;
    
    return voxel[_index].m_vec;
}


void ShapeData::addVoxel(const Vector3D& _vec, const uint32_t _color)
{
    auto prevSize = m_data.size();
    m_data.resize(prevSize + sizeof(Voxel));
    Head *head = reinterpret_cast<Head*>(m_data.data());
    updateHead(head, _vec);
    Voxel *voxel = reinterpret_cast<Voxel*>(m_data.data() + prevSize);
    voxel->m_vec = _vec;
    voxel->m_color.color = _color;
}

Vector3D ShapeData::getMinimum() const
{
    const Head *head = reinterpret_cast<const Head*>(m_data.data());
    return head->m_minimum;
}

Vector3D ShapeData::getMaximum() const
{
    const Head *head = reinterpret_cast<const Head*>(m_data.data());
    return head->m_maximum;
}

void updateHead(Head *_head, const Vector3D& _vec)
{
    if(_vec.m_x > _head->m_maximum.m_x)
        _head->m_maximum.m_x = _vec.m_x;
    if(_vec.m_y > _head->m_maximum.m_y)
        _head->m_maximum.m_y = _vec.m_y;
    if(_vec.m_z > _head->m_maximum.m_z)
        _head->m_maximum.m_z = _vec.m_z;
    
    if(_vec.m_x < _head->m_minimum.m_x)
        _head->m_minimum.m_x = _vec.m_x;
    if(_vec.m_y < _head->m_minimum.m_y)
        _head->m_minimum.m_y = _vec.m_y;
    if(_vec.m_z < _head->m_minimum.m_z)
        _head->m_minimum.m_z = _vec.m_z;

    updateOrigin(_head);
    updateSpatialSize(_head);
}

void updateOrigin(Head *_head)
{
    _head->m_origin = (_head->m_minimum + _head->m_maximum) / 2.0;
}

void updateSpatialSize(Head *_head)
{
    _head->m_spatialSize = _head->m_maximum - _head->m_minimum;
}