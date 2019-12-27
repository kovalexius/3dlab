#include <QtGui/QApplication>

#include <iostream>

#include "file_data.h"
#include "widget.h"

#include "generate_shapes.h"
#include "octree.h"
#include "octree_utils.h"
#include "vox_data_level.h"

void testGenBox()
{
    ShapeData box_shape;

    Vector3D firstOrigin(1.5f, 2.2f, 3.3f);
    box_shape.setOrigin(firstOrigin);
    box_shape.addVoxel(Vector3D(1.0,1.0,1.0), 555);
    box_shape.addVoxel(Vector3D(1.2,1.3,1.8), 777);
    box_shape.addVoxel(Vector3D(-1.2,-1.3,-1.8), 345);

    auto origin = box_shape.getOrigin();
    uint64_t vox_number = box_shape.getVoxNumber();
    auto spatialSize = box_shape.getSpatialSize();
   
    std::cout << __FUNCTION__ << std::endl << 
                                " origin = " << origin << std::endl <<
                                " num of voxels=" << vox_number << std::endl <<
                                " spatial size: " << spatialSize << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    //testGenBox();
    //*
    const ShapeData& box_shape = GenShapes::genBox(0.5, 10, 4, 5);
    
    create_data_file("box.dat", box_shape.getData(), box_shape.getDataSize());
    
    

    auto buf = read_data_file("box.dat");
    ShapeData data(buf);
    auto vox_number = data.getVoxNumber();
    auto origin = data.getOrigin();
    auto spatialSize = data.getSpatialSize();
    auto minimum = data.getMinimum();
    auto maximum = data.getMaximum();
    std::cout << __FUNCTION__ << std::endl << 
                                " origin: \'" << origin << "\'" << std::endl <<
                                " num of voxels: " << vox_number << std::endl <<
                                " spatial size: \'" << spatialSize << "\'" << std::endl << 
                                " minimum: \'" << minimum << "\'" << std::endl <<
                                " maximum: \'" << maximum << "\'" << std::endl << std::endl;
    
    //auto octree = OctreeUtils::createOctree(data);

    //*
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
    /**/
}