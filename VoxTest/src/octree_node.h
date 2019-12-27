#ifndef __OCTREE_NODE__H
#define __OCTREE_NODE__H

#include <Geometry.h>
#include "vox_data_level.h"

class Octree;
class OctreeNode
{
    
    public:
        OctreeNode(const Vector3D& _origin, const Vector3D& _size, uint32_t h, Octree *root);
        void addVoxel(const Vector3D& _point, const uint32_t color);
        void createVoxDataArray(std::vector<VoxDataLevelBase*> &vox_data, uint level);
        
    private:
        Vector3D    m_origin;   // Центр узла
        Vector3D    m_spatial_size;     // Размер узла
        uint32_t m_h;
        OctreeNode *node[8];
        bool is_leaf;
        Octree *m_root; 
};

#endif