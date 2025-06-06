#pragma once
#include"Struct.h"
#include"Sphere.h"
#include"Matrix4x4.h"

struct Bone
{
	Vector3 translates;
	Vector3 rotates;
	Vector3 scales;

	int parentIndex;//ボーンの数

	float radius;
};

void DrawBone(const Bone* bones, int boneCount, Matrix4x4 viewProjectMatrix, Matrix4x4 viewportMatrix);