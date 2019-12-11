#include <iostream>

#include "octree_data.h"
#include "generate_shapes.h"

using namespace VXC;

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

void OctreeUtils::createOctree(const ShapeData& _data, int _byte_len)
{
    const Vector3D &origin = _data.getOrigin();
    uint64_t num = _data.getVoxNumber();
    float vox_metre = _data.getVoxMetre();
    float width = _data.getWidth();
    float height = _data.getHeight();
    float depth = _data.getDepth();
    
    int h = getMaxDepthOctreeByData(_data);
    
    std::cout << "orig.x=" << origin.x << " orig.y=" << origin.y << " orig.z=" << origin.z << " num of voxels=" << num <<
                " vox_metre=" << vox_metre << " width=" << width << " height=" << height << " depth=" << depth << std::endl;
                
    // строительство дерева снизу вверх
    
}

Octree::Octree(float width, float height, float depth, uint32_t h)
{
    x_middle = width / 2;
    y_middle = height / 2;
    z_middle = depth / 2;
    m_h = h;
    for( int i = 0; i < 8; i++ )
        node[i] = nullptr;
}

void Octree::addVoxel( const Vector3D &point, const uint32_t color )
{
    int i;
    Vector3D vec = point;
    if( vec.x < x_middle )
    {
        if( vec.y < y_middle )
        {
            if( vec.z < z_middle )
                i = 0;
            else
            {
                i = 4;
                vec.z -= z_middle;
            }
        }
        else
        {
            vec.y -= y_middle;
            if( vec.z < z_middle )
                i = 2;
            else
            {
                i = 6;
                vec.z -= z_middle;
            }
        }
    }
    else
    {
        vec.x -= x_middle;
        if( vec.y < y_middle )
        {
            if( vec.z < z_middle )
                i = 1;
            else
            {
                i = 5;
                vec.z -= z_middle;
            }
        }
        else
        {
            vec.y -= y_middle;
            if( vec.z < z_middle )
                i = 3;
            else
            {
                i = 7;
                vec.z -= z_middle;
            }
        }
    }
    
    if( !node[i] )
        node[i] = new OctreeNode( x_middle, y_middle, z_middle, m_h - 1, this );
    node[i]->addVoxel( vec, color );
}

void Octree::createVoxDataArray()
{
     // массив на каждом уровне иерархии
    std::vector<VoxDataLevelBase*> vox_data;
    
    int level = 0;
    uint8_t root_data = 0;
    for( int i = 0; i < 8; i++ )
    {
        if(node[i])
        {
            root_data |= 1 << i;
            node[i]->createVoxDataArray( vox_data, level );
        }
    }
}


Octree::OctreeNode::OctreeNode( float width, float height, float depth, uint32_t h, Octree *root )
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
}

void Octree::OctreeNode::addVoxel(const Vector3D& point, const uint32_t color)
{
    int i;
    Vector3D vec = point;
    if( vec.x < x_middle )
    {
        if( vec.y < y_middle )
        {
            if( vec.z < z_middle )
                i = 0;
            else
            {
                i = 4;
                vec.z -= z_middle;
            }
        }
        else
        {
            vec.y -= y_middle;
            if( vec.z < z_middle )
                i = 2;
            else
            {
                i = 6;
                vec.z -= z_middle;
            }
        }
    }
    else
    {
        vec.x -= x_middle;
        if( vec.y < y_middle )
        {
            if( vec.z < z_middle )
                i = 1;
            else
            {
                i = 5;
                vec.z -= z_middle;
            }
        }
        else
        {
            vec.y -= y_middle;
            if( vec.z < z_middle )
                i = 3;
            else
            {
                i = 7;
                vec.z -= z_middle;
            }
        }
    }
    
    if( is_leaf )
    {
        if( !node[i] )
            node[i] = (OctreeNode*)new uint32_t(color);
        else
        {
            delete node[i];
            node[i] = (OctreeNode*)new uint32_t(color);
        }
    }
    else
    {
        if( !node[i] )
            node[i] = new OctreeNode( x_middle, y_middle, z_middle, m_h - 1, m_root );
        node[i]->addVoxel( vec, color );
    }
}

void Octree::OctreeNode::createVoxDataArray( std::vector<VoxDataLevelBase*> &vox_data, uint level )
{
    if( vox_data.size() < level + 1 )
    {
        VoxDataLevelBase *level_data;
        switch( OctreeUtils::getLenFieldAddress( level ) )
        {
            case OctreeUtils::ONE_BYTE:
                level_data = new VoxDataLevel<OctreeUtils::ONE_BYTE>;
                break;
            case OctreeUtils::TWO_BYTES:
                level_data = new VoxDataLevel<OctreeUtils::TWO_BYTES>;
                break;
            
        }
        vox_data.push_back( level_data );
    }
    
}