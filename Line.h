#pragma once
#include"Struct.h"

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
	Vector3 diff;//! < 終点への差分ベクトル
};