#include <QtGui/QApplication>

#include <iostream>

#include "file_data.h"
#include "widget.h"

#include "generate_shapes.h"
#include "octree_data.h"
#include "octree_utils.h"

int main(int argc, char *argv[])
{
    uint32_t size_in_bytes;
    const ShapeData& box_shape = GenShapes::genBox(0.5, 10, 4, 5, size_in_bytes);
    create_data_file("box.dat", box_shape.getData(), box_shape.getSize());
    
    auto buf = read_data_file("box.dat");

    ShapeData data(buf);
    
    int height = OctreeUtils::getMaxDepthOctreeByData(data);
    std::cout << "Height of octree = " << height << std::endl;
    std::cout << "Get Len in bytes from depth = " << OctreeUtils::getLenFieldAddress(height) << std::endl;
    int byte_len = OctreeUtils::getLenFieldAddress(data);
    std::cout << "Get Len in bytes from number= " << OctreeUtils::getLenFieldAddress(data) << std::endl;
    
    auto octree = OctreeUtils::createOctree(data);
    
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}