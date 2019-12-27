#include "octree_utils.h"
#include <iostream>

int OctreeUtils::getMaxDepthOctreeByData(const ShapeData& _data)
{
    int num_vox = _data.getVoxNumber();
    
    int depth = 1;
    if ( num_vox % 8 )
        depth++;
    while( num_vox / 8 )
    {
        num_vox = num_vox/8;
        depth++;
    }
    
    return depth;
}

int OctreeUtils::getLenFieldAddress(int depth)
{
    int num_bits = 0;
    num_bits = 3 * depth;
    int result = num_bits / 8;
    result += num_bits % 8 ? 1 : 0;
    return result;
}

int OctreeUtils::getLenFieldAddress(const ShapeData& _data)
{
    uint64_t num_vox = _data.getVoxNumber();
    int num_bits = 0;
    if (num_vox % 2)
        num_bits++;
    while (num_vox / 2)
    {
        num_vox = num_vox / 2;
        num_bits++;
    }

    int result = num_bits / 8;
    result += num_bits % 8 ? 1 : 0;
    return result;
}

Octree OctreeUtils::createOctree(const ShapeData& _data)
{
    Vector3D origin = _data.getOrigin();
    uint64_t voxCount = _data.getVoxNumber();
    auto spatialSize = _data.getSpatialSize();
    
    int treeheight = OctreeUtils::getMaxDepthOctreeByData(_data);
    std::cout << "Height of octree = " << treeheight << std::endl;
    std::cout << "Get Len in bytes from depth = " << OctreeUtils::getLenFieldAddress(treeheight) << std::endl;
    std::cout << "Get Len in bytes from number= " << OctreeUtils::getLenFieldAddress(_data) << std::endl;
                
    // строительство дерева снизу вверх
    std::cout << __FUNCTION__ << " origin: " << origin << std::endl << " spatial size: " << spatialSize << std::endl;
    Octree octree(origin, spatialSize, treeheight);

    for(auto i = 0; i < voxCount; i++)
    {
        uint32_t color;
        auto vec = _data.getVoxel(i, color);
        octree.addVoxel(vec, color);
    }

    std::cout << "Number of leafs: " << octree.getLeafNumber() << std::endl;

    return octree;
}