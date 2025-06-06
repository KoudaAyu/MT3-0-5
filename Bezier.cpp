#include "Bezier.h"

void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2,
    const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    // 制御点を丸で描画
    DrawControlPoint(p0, viewProjectionMatrix, viewportMatrix);
    DrawControlPoint(p1, viewProjectionMatrix, viewportMatrix);
    DrawControlPoint(p2, viewProjectionMatrix, viewportMatrix);

    // ベジエ曲線を描画
    const int kDivisions = 30;
    Vector3 prevPoint = p0;

    for (int i = 1; i <= kDivisions; ++i)
    {
        float t = i / static_cast<float>(kDivisions);

        Vector3 a = Lerp(p0, p1, t);
        Vector3 b = Lerp(p1, p2, t);
        Vector3 point = Lerp(a, b, t);

        Vector3 ndcPrev = VectorTransform(prevPoint, viewProjectionMatrix);
        Vector3 ndcPoint = VectorTransform(point, viewProjectionMatrix);

        Vector3 screenPrev = VectorTransform(ndcPrev, viewportMatrix);
        Vector3 screenPoint = VectorTransform(ndcPoint, viewportMatrix);

        Novice::DrawLine(
            static_cast<int>(screenPrev.x), static_cast<int>(screenPrev.y),
            static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y),
            color
        );

        prevPoint = point;
    }
}


void DrawControlPoint(const Vector3& point, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
    Vector3 ndc = VectorTransform(point, viewProjectionMatrix);
    Vector3 screen = VectorTransform(ndc, viewportMatrix);

    int x = static_cast<int>(screen.x);
    int y = static_cast<int>(screen.y);

    const int radius = 5;  // 円の半径

    Novice::DrawEllipse(x, y, radius, radius, 0.0f,BLACK,kFillModeSolid);
}