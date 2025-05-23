#include "Plane.h"

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	// 法線は単位ベクトルであることを前提とする（Normalizeされている）
	float dot = sphere.center.x * plane.normal.x +
		sphere.center.y * plane.normal.y +
		sphere.center.z * plane.normal.z;

	float distance = dot - plane.distance; // 符号付き距離

	// 衝突していれば true（距離の絶対値 <= 半径）
	return std::abs(distance) <= sphere.radius;
}

Vector3 Prependicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = VectorMultiply(plane.distance, plane.normal); // 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Prependicular(plane.normal));    // 2
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z }; // 3
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);    // 4
	perpendiculars[3] = { perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };   // 5

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index)
	{
		Vector3 extend = VectorMultiply(2.0f, perpendiculars[index]);
		Vector3 point = VectorAdd(center, extend);
		// 修正: まず viewProjectionMatrix で変換し、その結果を viewportMatrix で変換
		Vector3 temp = VectorTransform(point, viewProjectionMatrix);
		points[index] = VectorTransform(temp, viewportMatrix);
	}

	// pointsをそれぞれ結んでDrawLineで矩形描画する
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		static_cast<int>(points[1].x), static_cast<int>(points[1].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y), color);
}
