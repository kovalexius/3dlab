#include <iostream>

#include <Geometry.h>
#include "octree.h"
#include "octree_node.h"
#include "generate_shapes.h"


Octree::Octree(const Vector3D& _origin, const Vector3D& _size, const uint32_t h) : m_number_of_leaf(0)
{
    m_origin = _origin;
    m_size = _size;
    m_h = h;
    for( int i = 0; i < 8; i++ )
        node[i] = nullptr;
}

void Octree::addVoxel(const Vector3D &point, const uint32_t color)
{
    int i;
    Vector3D vec = point;

    GetIndexAndTransponation(m_origin, i, vec);
    
    //Vector3D 
    if( !node[i] )
        node[i] = new OctreeNode(m_origin, m_size, m_h - 1, this);
    node[i]->addVoxel(vec, color);
}

void Octree::createVoxDataArray()
{
    // массив на каждом уровне иерархии
    std::vector<VoxDataLevelBase*> vox_data;
    
    int level = 0;
    uint8_t root_data = 0;
    for(int i = 0; i < 8; i++)
    {
        if(node[i])
        {
            root_data |= 1 << i;
            node[i]->createVoxDataArray(vox_data, level);
        }
    }
}


void GetIndexAndTransponation(const Vector3D& _origin, 
                            int& _index, 
                            Vector3D& _vec)
{
    if(_vec.m_x < _origin.m_x)
    {
        if(_vec.m_y < _origin.m_y)
        {
            if(_vec.m_z < _origin.m_z)
                _index = 0;
            else
            {
                _index = 4;
                _vec.m_z -= _origin.m_z;
            }
        }
        else
        {
            _vec.m_y -= _origin.m_y;
            if(_vec.m_z < _origin.m_z)
                _index = 2;
            else
            {
                _index = 6;
                _vec.m_z -= _origin.m_z;
            }
        }
    }
    else
    {
        _vec.m_x -= _origin.m_x;
        if(_vec.m_y < _origin.m_y)
        {
            if(_vec.m_z < _origin.m_z)
                _index = 1;
            else
            {
                _index = 5;
                _vec.m_z -= _origin.m_z;
            }
        }
        else
        {
            _vec.m_y -= _origin.m_y;
            if(_vec.m_z < _origin.m_z)
                _index = 3;
            else
            {
                _index = 7;
                _vec.m_z -= _origin.m_z;
            }
        }
    }
}




