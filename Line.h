#pragma once
#include <cstdint>


#include"Struct.h"


struct Plane;

//直線
struct Line
{
	Vector3 origin;//! < 始発
	Vector3 diff;//! < 終点への差分ベクトル
};

//半直線
struct Ray
{
	Vector3 origin;//! < 始発
	Vector3 diff;//! < 終点への差分ベクトル
};

//線分
struct Segment
{
	Vector3 origin;//! < 始発
	Vector3 diff ;//! < 終点への差分ベクトル
};

bool IsCollisionSegment(const Segment& segment,const Plane& plane);

void SegmentDraw(const Segment& segment, const Matrix4x4& viewProjectionMatrix,const Matrix4x4& viewportmatrix, uint32_t color);