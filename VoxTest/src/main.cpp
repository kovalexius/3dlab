#include <QtGui/QApplication>

#include <iostream>

#include "file_data.h"
#include "widget.h"

#include "generate_shapes.h"
#include "octree.h"
#include "octree_utils.h"
#include "vox_data_level.h"

int main(int argc, char *argv[])
{
    uint32_t size_in_bytes;
    const ShapeData& box_shape = GenShapes::genBox(0.5, 10, 4, 5, size_in_bytes);
    create_data_file("box.dat", box_shape.getData(), box_shape.getSize());
    
    
    const Vector3D& origin = box_shape.getOrigin();
    uint64_t vox_number = box_shape.getVoxNumber();
    float vox_metre = box_shape.getVoxMetre();
    float width = box_shape.getWidth();
    float height = box_shape.getHeight();
    float depth = box_shape.getDepth();
    std::cout << __FUNCTION__ << " orig.x=" << origin.m_x << " orig.y=" << origin.m_y << " orig.z=" << origin.m_z << " num of voxels=" << vox_number <<
                " vox_metre=" << vox_metre << " width=" << width << " height=" << height << " depth=" << depth << std::endl;
    for(uint64_t i = 0; i < vox_number; i++ )
    {
        Color col;
        const Vector3D& vec = box_shape.getVoxel(i, col.color);
        //std::cout << "r=" << col.r << " g=" << col.g << " b=" << col.b << " a=" << col.a << 
        //    " x=" << (float)vec.m_x << " y=" << (float)vec.m_y << " z=" << (float)vec.m_z << std::endl;
    }

    /*
    auto buf = read_data_file("box.dat");
    ShapeData data(buf);
    auto octree = OctreeUtils::createOctree(data);
    */

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}