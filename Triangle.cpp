#include "Triangle.h"

// SegmentとTriangleの交差判定
bool IsCollisionTriangle(const Triangle& triangle, const Segment& segment)
{
    const Vector3& p0 = segment.origin;
    const Vector3& p1 = segment.origin + segment.diff;

    // 三角形の頂点
    const Vector3& v0 = triangle.vertices[0];
    const Vector3& v1 = triangle.vertices[1];
    const Vector3& v2 = triangle.vertices[2];

    // 三角形の法線ベクトルを計算
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;
    Vector3 normal = Cross(edge1, edge2);

    // 平面の法線と線分の方向ベクトルの内積
    Vector3 dir = p1 - p0;
    float dot = VectorDot(normal, dir);

    // 線と平面が平行なら交差しない
    if (fabs(dot) < 1e-6f) return false;

    // 線分と平面の交点を計算
    float d = VectorDot(normal, v0 - p0) / dot;
    if (d < 0.0f || d > 1.0f) return false; // 線分外

    Vector3 intersect = p0 + dir * d;

    // 交点が三角形の内部にあるかチェック（バリセンタ法 or クロス積法）
    Vector3 c0 = Cross(v1 - v0, intersect - v0);
    Vector3 c1 = Cross(v2 - v1, intersect - v1);
    Vector3 c2 = Cross(v0 - v2, intersect - v2);

    if (VectorDot(c0, normal) >= 0 &&
        VectorDot(c1, normal) >= 0 &&
        VectorDot(c2, normal) >= 0)
    {
        return true;
    }

    return false;
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    // 各頂点を変換
    Vector3 ndc0 = VectorTransform(triangle.vertices[0], viewProjectionMatrix);
    Vector3 ndc1 = VectorTransform(triangle.vertices[1], viewProjectionMatrix);
    Vector3 ndc2 = VectorTransform(triangle.vertices[2], viewProjectionMatrix);

    // ビューポート変換（スクリーン座標）
    Vector3 screen0 = VectorTransform(ndc0, viewportMatrix);
    Vector3 screen1 = VectorTransform(ndc1, viewportMatrix);
    Vector3 screen2 = VectorTransform(ndc2, viewportMatrix);

    // 描画
    Novice::DrawTriangle(
        static_cast<int>(screen0.x), static_cast<int>(screen0.y),
        static_cast<int>(screen1.x), static_cast<int>(screen1.y),
        static_cast<int>(screen2.x), static_cast<int>(screen2.y),
        color,
        kFillModeWireFrame
    );
}

