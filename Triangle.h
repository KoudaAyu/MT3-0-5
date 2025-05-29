#pragma once
#include"Struct.h"
#include"Vector.h"
#include"Matrix4x4.h"

struct Triangle
{
	Vector3 vertices[3];//頂点
};

bool IsCollisionTriangle(const Triangle& triangle, const Segment& segment);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);