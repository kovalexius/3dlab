#ifndef OCTREEDATA_H
#define OCTREEDATA_H

#include <stdint.h>

#include "generate_shapes.h"

#pragma pack(push, 1)
union Color
{
    uint32_t color;
    struct
    {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };
};
#pragma pack(pop)

class OctreeUtils
{
public:
    enum LEN_ADDR
    {
        ZERO_BYTES=0,
        ONE_BYTE=1,
        TWO_BYTES=2,
        THREE_BYTES=3,
        FOUR_BYTES=4,
        FIVE_BYTES=5
    };
    
public:
    static int getMaxDepthOctreeByData(const ShapeData& _data);
    
    static int getLenFieldAddress(int _depth);

    static int getLenFieldAddress(const ShapeData& _data);
    
    static void createOctree(const ShapeData& _data, int _byte_len);
};

struct VoxDataLevelBase
{};

template<OctreeUtils::LEN_ADDR L>
struct VoxDataLevel : public VoxDataLevelBase
{
    
    #pragma pack(push, 1)
    template<OctreeUtils::LEN_ADDR _L>
    struct VoxData
    {
        uint8_t offset[_L];
        uint8_t octree_mask;
    };
    #pragma pack(pop)
    std::vector<VoxData<L>> data;
};

class Octree
{
    class OctreeNode
    {
    public:
        OctreeNode( float width, float height, float depth, uint32_t h, Octree *root );
        void addVoxel( const Vector3D &point, const uint32_t color );
        void createVoxDataArray( std::vector<VoxDataLevelBase*> &vox_data, uint level );
        
    private:
        float x_middle;
        float y_middle;
        float z_middle;
        uint32_t m_h;
        OctreeNode *node[8];
        bool is_leaf;
        Octree *m_root; 
    };
    
public:
    Octree(float _width, float _height, float _depth, uint32_t _h);
    void addVoxel(const Vector3D& _point, const uint32_t _color);
    void createVoxDataArray();
    
private:
    float x_middle;
    float y_middle;
    float z_middle;
    uint32_t m_h;
    OctreeNode *node[8];
};



#endif