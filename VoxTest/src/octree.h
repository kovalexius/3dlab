#ifndef OCTREEDATA_H
#define OCTREEDATA_H

#include <stdint.h>

#include <vector>
#include <Geometry.h>


class OctreeNode;
class Octree
{
    friend class OctreeNode;
public:
    Octree(const Vector3D& _origin, const Vector3D& _size, const uint32_t _h);
    void addVoxel(const Vector3D& _point, const uint32_t _color);
    void createVoxDataArray();
    
    int getLeafNumber()
    {
        return m_number_of_leaf;
    }
    
private:
    Vector3D    m_origin;   // Центр узла
    Vector3D    m_size;     // Размер узла
    int     m_number_of_leaf;
    uint32_t    m_h;
    OctreeNode *node[8];
};

void GetIndexAndTransponation(const Vector3D& _origin, 
                                int& _index, 
                                Vector3D& _vec);

#endif