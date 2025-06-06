
#include "Sphere.h"

#include<imgui.h>

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivition = 20; // 分割数
	const float kLonEvery = float(2.0f * M_PI) / kSubdivition; // 経度の分割
	const float kLatEvery =float( M_PI )/ kSubdivition; // 緯度の分割

	// 経度方向の線を描画
	for (uint32_t lonIndex = 0; lonIndex < kSubdivition; ++lonIndex)
	{
		float lon = kLonEvery * lonIndex;

		// 経度方向に沿った縦線を描く
		for (uint32_t latIndex = 0; latIndex < kSubdivition; ++latIndex)
		{
			float lat =float( - M_PI_2 )+ kLatEvery * latIndex;

			// 頂点計算 (経度方向)
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};

			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon)
			};

			// 頂点をスクリーン座標系に変換
			Vector3 aScreen = VectorTransform(a, viewProjectMatrix);
			aScreen = VectorTransform(aScreen, viewportMatrix);
			Vector3 bScreen = VectorTransform(b, viewProjectMatrix);
			bScreen = VectorTransform(bScreen, viewportMatrix);

		
			// 描画
			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y), static_cast<int>(bScreen.x), static_cast<int>(bScreen.y), color);
		}
	}

	

	// 緯度方向の線を描画
	for (uint32_t latIndex = 0; latIndex < kSubdivition; ++latIndex)
	{
		float lat = float( - M_PI_2 )+ kLatEvery * latIndex;

		// 緯度方向に沿った横線を描く
		for (uint32_t lonIndex = 0; lonIndex < kSubdivition; ++lonIndex)
		{
			float lon = kLonEvery * lonIndex;

			// 頂点計算 (緯度方向)
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};

			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery)
			};

			// 頂点をスクリーン座標系に変換
			Vector3 aScreen = VectorTransform(a, viewProjectMatrix);
			aScreen = VectorTransform(aScreen, viewportMatrix);
			Vector3 bScreen = VectorTransform(b, viewProjectMatrix);
			bScreen = VectorTransform(bScreen, viewportMatrix);

			// 描画
			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y), static_cast<int>(bScreen.x), static_cast<int>(bScreen.y), color);
		}
	}
}

float Sphere::GetDistanceBetweenCenters(const Sphere& a, const Sphere& b)
{
	Vector3 diff = {
		b.center.x - a.center.x,
		b.center.y - a.center.y,
		b.center.z - a.center.z
	};
	return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}
