#pragma once
#define _USE_MATH_DEFINES
#include <cmath>


#include <cstdint>

#include"Struct.h"
#include"Matrix4x4.h"




class Sphere
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="sphere"></param>
	/// <param name="viewProjectMatrix"></param>
	/// <param name="viewportMatrix"></param>
	/// <param name="color"></param>
	

	static float GetDistanceBetweenCenters(const Sphere& a, const Sphere& b);

	Vector3 center; //! < 中心点
	float radius; //! < 半径
	

};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color);