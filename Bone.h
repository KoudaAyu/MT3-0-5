#pragma once
#include"Struct.h"
#include"Matrix4x4.h"

struct Bone
{
	Vector3 translates;
	Vector3 rotates;
	Vector3 scales;
};

void BoneDraw(const Bone& bone1, const Bone& bone2, const Bone& bone3);

