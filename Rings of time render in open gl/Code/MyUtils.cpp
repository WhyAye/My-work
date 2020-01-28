#include "MyUtils.hpp"

/*
 * Tutorial: use this source and its associated header file to declare
 *           and define your own helper functions.
 */

namespace Ryan_Mcdonnell
{
	// thse are the different functions which preform the different tralations, rotats.

	// traslates(moves) the object usi x,y,z.
tyga::Matrix4x4 translate(float x, float y, float z)
{
    return tyga::Matrix4x4(1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           x, y, z, 1);
}

float continuous(float start_value, float speed, float time)
{
    return start_value + speed * time;
}

// rotates the object on its z axies. 
tyga::Matrix4x4 rotateZ(float z)
{
	float cs = cos(z);
	float s = sin(z);
	return tyga::Matrix4x4(cs, -s, 0, 0,
							s, cs, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

}

tyga::Matrix4x4 rotateX(float x)
{
	float cs = cos(x);
	float s = sin(x);
	return tyga::Matrix4x4(1, 0, 0, 0,
							0, cs, -s, 0,
							0, s, cs, 0,
							0, 0, 0, 1);

}

tyga::Matrix4x4 rotateY(float y)
{
	float cs = cos(y);
	float s = sin(y);
	return tyga::Matrix4x4(cs, 0, s, 0,
							0, 1, 0, 0,
							-s, 0, cs, 0,
							0, 0, 0, 1);

}
tyga::Matrix4x4 Scale(float val)
{

	return tyga::Matrix4x4(val, 0, 0, 0,
		0, val, 0, 0,
		0, 0, val, 0,
		0, 0, 0, 1);

}

}
