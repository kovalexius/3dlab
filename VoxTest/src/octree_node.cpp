#include <iostream>
#include "octree_node.h"
#include "octree.h"
#include "octree_utils.h"

OctreeNode::OctreeNode(const Vector3D& _origin, const Vector3D& _spatial_size, uint32_t _h, Octree *_root)
{
    m_origin = _origin;
    m_spatial_size = _spatial_size;

    m_h = _h;
    if(m_h)
        is_leaf = false;
    else
        is_leaf = true;
    for( int i = 0; i < 8; i++ )
        node[i] = nullptr;
    m_root = _root;
}


void OctreeNode::addVoxel(const Vector3D& point, const uint32_t color)
{
    int i;
    Vector3D vec = point;
    GetIndexAndTransponation(m_origin, i, vec);
    
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
            node[i] = new OctreeNode(m_origin, m_spatial_size, m_h - 1, m_root);
        node[i]->addVoxel( vec, color );
    }
}


void OctreeNode::createVoxDataArray(std::vector<VoxDataLevelBase*>& _vox_data, int level)
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