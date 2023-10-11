#ifndef THOR_POINT_H
#define THOR_POINT_H

namespace Thor {

struct Vec2 {
	float x;
	float y;
	
	Vec2(float x, float y) : x(x), y(y) {}
};

struct Vec3 {
	float x;
	float y;
	float z;

	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Vec4 {
	float x;
	float y;
	float z;
	float w;

	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

}

#endif
