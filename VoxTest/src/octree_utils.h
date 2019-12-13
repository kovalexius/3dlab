#ifndef __OCTREE_UTILS__H
#define __OCTREE_UTILS__H

#include "shape_data.h"
#include "octree_data.h"

class OctreeUtils
{
public:
    static int getMaxDepthOctreeByData(const ShapeData& _data);
    
    static int getLenFieldAddress(int _depth);

    static int getLenFieldAddress(const ShapeData& _data);
    
    static Octree createOctree(const ShapeData& _data);
};

#endif