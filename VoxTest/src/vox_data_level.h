#ifndef __VOX_DATA_LEVEL__H
#define __VOX_DATA_LEVEL__H

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

struct VoxDataLevelBase
{
     enum LEN_ADDR
    {
        ZERO_BYTES=0,
        ONE_BYTE=1,
        TWO_BYTES=2,
        THREE_BYTES=3,
        FOUR_BYTES=4,
        FIVE_BYTES=5
    };
};

template<VoxDataLevelBase::LEN_ADDR L>
struct VoxDataLevel : public VoxDataLevelBase
{
    
    #pragma pack(push, 1)
    template<VoxDataLevelBase::LEN_ADDR _L>
    struct VoxData
    {
        uint8_t offset[_L];
        uint8_t octree_mask;
    };
    #pragma pack(pop)
    std::vector<VoxData<L>> data;
};


#endif