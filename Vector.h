#pragma once
#include<cmath>
#include"Struct.h"
#include"Line.h"


Vector3 VectorAdd(const Vector3& a, const Vector3& b);;

Vector3 VectorSubtract(const Vector3& a, const Vector3& b);

Vector3 VectorMultiply(float scalar, const Vector3& vec);

Vector3 VectorProject(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 VectorClosestPoint(const Vector3& point, const Segment& segment);

Vector3 Normalize(const Vector3& v);

float VectorDot(const Vector3& v1,const Vector3& v2);
