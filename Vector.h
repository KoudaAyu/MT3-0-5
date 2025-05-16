#pragma once
#include"Struct.h"
#include"Line.h"

Vector3 VectorAdd(const Vector3& a, const Vector3& b);;

Vector3 VectorSubtract(const Vector3& a, const Vector3& b);

Vector3 VectorProject(const Vector3& v1, const Vector3& v2);



Vector3 VectorClosestPoint(const Vector3& point, const Segment& segment);
