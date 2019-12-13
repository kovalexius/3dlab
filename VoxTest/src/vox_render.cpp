#include "vox_render.h"

#include <cmath>
#include <vector>

void testRender()
{

    render(1024, 768, M_PI/3.0)
}

void render(const int _width, const int _height, const float _fov)
{
    /*
	framebuffer := make([][]*Vec3f, width)
	for i := 0; i < height; i++
    {
		framebuffer[i] = make([]*Vec3f, width)
	}
    */
    std::vector<std::vector<Vector3D> > raybuffer;
    /*
	raybuffer := make([][]*Vec3f, width)
	for i:= 0; i < height; i++ {
		raybuffer[i] = make([]*Vec3f, width)
	}
    */

	for (auto row = 0; row < _height; row++)
    {
        raybuffer.push_back(std::vector<Vector3D>());
		for (auto col = 0; col < _width; col++)
        {
			float dir_x =  ((float)col + 0.5) - (float)_width/2.0;
			float dir_y = -(float)row + 0.5) + (float)_height/2.0;    // this flips the image at the same time
			float dir_z = -(float)_height/(2.0*math.Tan(_fov/2.0));

			raybuffer[row][col] = Vector3D(dir_x, dir_y, dir_z).Normalize()
		}
	}
}