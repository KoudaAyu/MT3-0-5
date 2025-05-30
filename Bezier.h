#pragma once

#include"Matrix4x4.h"
#include"Struct.h"
#include"Vector.h"

#include <cstdint>

struct Bezier
{
	Vector3 controlPositions;
};

void DrawBezier(const Vector3& controlPosition0, const Vector3& controlPosition1,
	const Vector3& controlPosition2, const Matrix4x4& viewProject,
	const Matrix4x4& viewportMatrix, uint32_t color);

void DrawControlPoint(const Vector3& point, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);