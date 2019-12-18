#include "vox_render.h"

#include <cmath>



void testRender()
{

    auto raybuffer = render(1024, 768, M_PI/3.0);
}

std::vector<std::vector<Vector3D> > render(const int _width, const int _height, const float _fov)
{
    std::vector<std::vector<Vector3D> > raybuffer;

	for (auto row = 0; row < _height; row++)
    {
        raybuffer.push_back(std::vector<Vector3D>());
		for (auto col = 0; col < _width; col++)
        {
			float dir_x =  ((float)col + 0.5) - (float)_width/2.0;
			float dir_y = -((float)row + 0.5) + (float)_height/2.0;    // this flips the image at the same time
			float dir_z = -(float)_height/(2.0*std::tan(_fov/2.0));

			//raybuffer[row][col] = Vector3D(dir_x, dir_y, dir_z).Normalize();
            raybuffer[row].push_back(Vector3D(dir_x, dir_y, dir_z).Normalize());
		}
	}

    return raybuffer;
}