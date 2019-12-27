#ifndef GENERATE_SHAPES_H
#define GENERATE_SHAPES_H

#include <cstdint>
#include <memory>
#include <vector>

#include <Geometry.h>
#include "shape_data.h"


class GenShapes
{
public:
    static ShapeData genBox(const float vox_size, 
                             const uint32_t width, 
                             const uint32_t height, 
                             const uint32_t depth);
    static ShapeData genSpere(const float vox_size,
                               uint32_t &size_bytes);
};

#endif