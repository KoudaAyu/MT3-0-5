#include "Grid.h"


void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	//Gridの半分の幅
	const float kGridHalfWidth = 2.0f;

	//分割数
	const uint32_t kSubdivision = 10;

	//1つ分の大きさ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

    uint32_t color = 0xFFFFFFFF;

    // 手前から奥（Z方向の線）
    for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
    {
        float x = -kGridHalfWidth + kGridEvery * float(xIndex);
        Vector3 start = { x, 0.0f, -kGridHalfWidth };
        Vector3 end = { x, 0.0f,  kGridHalfWidth };

        // ★ 真ん中の線だけ色を変える
        color = (xIndex == kSubdivision / 2) ? 0x000000FF : 0xFFFFFFFF; // 赤 : 緑

        start = VectorTransform(start, viewProjectionMatrix);
        end = VectorTransform(end, viewProjectionMatrix);
        start = VectorTransform(start, viewportMatrix);
        end = VectorTransform(end, viewportMatrix);

        Novice::DrawLine(
            static_cast<int>(start.x), static_cast<int>(start.y),
            static_cast<int>(end.x), static_cast<int>(end.y),
            color
        );
    }

    // 横方向の線（X方向に沿ってZ位置でカット）
    for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
    {
        float z = -kGridHalfWidth + kGridEvery * float(zIndex);
        Vector3 start = { -kGridHalfWidth, 0.0f, z };
        Vector3 end = { kGridHalfWidth, 0.0f, z };

        start = VectorTransform(start, viewProjectionMatrix);
        end = VectorTransform(end, viewProjectionMatrix);
        start = VectorTransform(start, viewportMatrix);
        end = VectorTransform(end, viewportMatrix);

        color = (zIndex == kSubdivision / 2) ? 0x000000FF : 0xFFFFFFFF;

        Novice::DrawLine(
            static_cast<int>(start.x), static_cast<int>(start.y),
            static_cast<int>(end.x), static_cast<int>(end.y),
            color // 黄
        );
    }
}
