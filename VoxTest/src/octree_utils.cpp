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
    double vox_metre = static_cast<double>(_data.getVoxMetre());
    double width = static_cast<double>(_data.getWidth());
    double height = static_cast<double>(_data.getHeight());
    double depth = static_cast<double>(_data.getDepth());
    
    int treeheight = OctreeUtils::getMaxDepthOctreeByData(_data);
    std::cout << "Height of octree = " << height << std::endl;
    std::cout << "Get Len in bytes from depth = " << OctreeUtils::getLenFieldAddress(treeheight) << std::endl;
    std::cout << "Get Len in bytes from number= " << OctreeUtils::getLenFieldAddress(_data) << std::endl;

    //std::cout << "orig.x=" << origin.x << " orig.y=" << origin.y << " orig.z=" << origin.z << " count of voxels=" << voxCount <<
    //            " vox_metre=" << vox_metre << " width=" << width << " height=" << height << " depth=" << depth << std::endl;
                
    // строительство дерева снизу вверх
    std::cout << __FUNCTION__ << " origin: " << origin << std::endl << " size: " << Vector3D(width, height, depth) << std::endl;
    Octree octree(origin, Vector3D(width, height, depth), treeheight);

    for(auto i = 0; i < voxCount; i++)
    {
        uint32_t color;
        auto vec = _data.getVoxel(i, color);
        octree.addVoxel(vec, color);
    }

    std::cout << "Number of leafs: " << octree.getLeafNumber() << std::endl;

    return octree;
}