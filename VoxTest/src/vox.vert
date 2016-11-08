#version 120

uniform int num_of_nodes;      //len of array Octree
uniform int vox_tree[1];  // dynamic array, representing Octree without leafs (without color info, normals info, etc)

varying float _num_of_nodes;
varying float _vox_tree[1];

//Or

//uniform gsampler1D vox_tree;
//varying gsampler1D _vox_tree;

void main(void) 
{
    gl_Position = gl_Vertex;
}