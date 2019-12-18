#include <iostream>

#include "octree_data.h"
#include "generate_shapes.h"
#include "octree_utils.h"

Octree::Octree(float width, float height, float depth, uint32_t h) : m_number_of_leaf(0)
{
    x_middle = width / 2;
    y_middle = height / 2;
    z_middle = depth / 2;
    m_h = h;
    for( int i = 0; i < 8; i++ )
        node[i] = nullptr;
}

void Octree::addVoxel(const Vector3D &point, const uint32_t color)
{
    int i;
    Vector3D vec = point;
    if(vec.m_x < x_middle)
    {
        if(vec.m_y < y_middle)
        {
            if(vec.m_z < z_middle)
                i = 0;
            else
            {
                i = 4;
                vec.m_z -= z_middle;
            }
        }
        else
        {
            vec.m_y -= y_middle;
            if( vec.m_z < z_middle )
                i = 2;
            else
            {
                i = 6;
                vec.m_z -= z_middle;
            }
        }
    }
    else
    {
        vec.m_x -= x_middle;
        if(vec.m_y < y_middle)
        {
            if(vec.m_z < z_middle)
                i = 1;
            else
            {
                i = 5;
                vec.m_z -= z_middle;
            }
        }
        else
        {
            vec.m_y -= y_middle;
            if(vec.m_z < z_middle)
                i = 3;
            else
            {
                i = 7;
                vec.m_z -= z_middle;
            }
        }
    }
    
    if( !node[i] )
        node[i] = new OctreeNode(x_middle, y_middle, z_middle, m_h - 1, this);
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


Octree::OctreeNode::OctreeNode(float width, float height, float depth, uint32_t h, Octree *root)
{
    x_middle = width / 2;
    y_middle = height / 2;
    z_middle = depth / 2;
    m_h = h;
    if(m_h)
        is_leaf = false;
    else
        is_leaf = true;
    for( int i = 0; i < 8; i++ )
        node[i] = nullptr;
    m_root = root;

    std::cout << "x_middle: " << x_middle << " y_middle: " << y_middle << " z_middle: " << z_middle << std::endl;
}

void Octree::OctreeNode::addVoxel(const Vector3D& point, const uint32_t color)
{
    int i;
    Vector3D vec = point;
    if(vec.m_x < x_middle)
    {
        if(vec.m_y < y_middle)
        {
            if(vec.m_z < z_middle)
                i = 0;
            else
            {
                i = 4;
                vec.m_z -= z_middle;
            }
        }
        else
        {
            vec.m_y -= y_middle;
            if(vec.m_z < z_middle)
                i = 2;
            else
            {
                i = 6;
                vec.m_z -= z_middle;
            }
        }
    }
    else
    {
        vec.m_x -= x_middle;
        if(vec.m_y < y_middle)
        {
            if(vec.m_z < z_middle)
                i = 1;
            else
            {
                i = 5;
                vec.m_z -= z_middle;
            }
        }
        else
        {
            vec.m_y -= y_middle;
            if(vec.m_z < z_middle)
                i = 3;
            else
            {
                i = 7;
                vec.m_z -= z_middle;
            }
        }
    }
    
    if(is_leaf)
    {
        if( !node[i] )
        {
            node[i] = (OctreeNode*)new uint32_t(color);
            m_root->m_number_of_leaf++;
        }
        else
        {
            delete node[i];
            node[i] = (OctreeNode*)new uint32_t(color);
        }
    }
    else
    {
        if( !node[i] )
            node[i] = new OctreeNode(x_middle, y_middle, z_middle, m_h - 1, m_root);
        node[i]->addVoxel( vec, color );
    }
}

void Octree::OctreeNode::createVoxDataArray(std::vector<VoxDataLevelBase*>& _vox_data, uint level)
{
    if(_vox_data.size() < level + 1)
    {
        VoxDataLevelBase *level_data;
        switch( OctreeUtils::getLenFieldAddress( level ) )
        {
            case VoxDataLevelBase::ONE_BYTE:
                level_data = new VoxDataLevel<VoxDataLevelBase::ONE_BYTE>;
                break;
            case VoxDataLevelBase::TWO_BYTES:
                level_data = new VoxDataLevel<VoxDataLevelBase::TWO_BYTES>;
                break;
            
        }
        _vox_data.push_back( level_data );
    }
    
}