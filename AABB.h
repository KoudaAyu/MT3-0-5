#pragma once

#include"Line.h"
#include"Struct.h"
#include"Sphere.h"
#include"Matrix4x4.h"

#include <algorithm>
#include <cstdint>

struct AABB
{
	Vector3 min;//最小点
	Vector3 max;//最大点
};

bool IsCollisionAABBAABB(const AABB& aabb1, const AABB& aabb2);

bool IsCollisionAABBSphere(const AABB& aabb, const Sphere& sphere);

bool IsCollisionAABBSegment(const AABB& aabb, const Segment& segment);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectMatrix, const Matrix4x4& ViewportMatrix, uint32_t color);