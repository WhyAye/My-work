#pragma once

#include <tyga/Math.hpp>

/*
 * Tutorial: use this header and its associated source file to declare
 *           and define your own helper functions.
 */

namespace Ryan_Mcdonnell
{

/**
 * Create a translation transformation matrix.
 * 
 * @param x  The amount of X translation.
 * @param y  The amount of Y translation.
 * @param z  The amount of Z translation.
 * @return   A 4x4 transformation matrix for use with row-vectors.
 */
tyga::Matrix4x4 translate(float x, float y, float z);
tyga::Matrix4x4 rotateZ(float z);
tyga::Matrix4x4 scale(float z);
tyga::Matrix4x4 rotateX(float x);
tyga::Matrix4x4 rotateY(float y);

/**
 * Compute a linear (continuous) animated value.
 *
 * @param start_value  What the return value should be at animation time = 0,
 *                     or it's the current animated value when using delta time.
 * @param speed        The rate-of-change of the return value (i.e. the speed of
 *                     the animation).  Must be a constant when using elapsed
 *                     animation time rather than delta time.
 * @param time         The elapsed animation time or the delta time.
 * @return             The animated value as defined by the input parameters.
 */
float continuous(float start_value, float speed, float time);


}
