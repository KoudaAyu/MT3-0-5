#pragma once
#include <cstdint>
#include<Novice.h>

#include"Struct.h"
#include"Sphere.h"
#include"Matrix4x4.h"
#include"Vector.h"

struct Plane
{
	Vector3 normal = { 0.0f,0.0f,1.0f };//! < 法線
	float distance;//! < 距離
};


	bool IsCollision(const Sphere& sphere, const Plane& plane);

	Vector3 Prependicular(const Vector3& vector);


	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewMatrix, uint32_t color);
