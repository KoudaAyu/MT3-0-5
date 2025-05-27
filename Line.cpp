#include "Line.h"
#include"Plane.h"
#include"Vector.h"

bool IsCollisionSegment(const Segment& segment, const Plane& plane)
{
    //まず垂直判定を行う為に、法線と線の内積を求める
    float dot = VectorDot(plane.normal, segment.diff);

    //垂直 = 平行であるので衝突しているはずがない
    if (fabs(dot) < 1e-6f)
    {
        return false;
    }

    float t = (plane.distance - VectorDot(segment.origin, plane.normal)) / dot;

    if (t >= 0.0f && t <= 1.0f)
    {
        return true;
    }

    return false;
}


void SegmentDraw(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    Vector3 start = segment.origin;
    Vector3 end = {
        segment.origin.x + segment.diff.x,
        segment.origin.y + segment.diff.y,
        segment.origin.z + segment.diff.z
    };

    // 変換（viewProjection → viewport）
    Vector3 clipStart = VectorTransform(start, viewProjectionMatrix);
    Vector3 screenStart = VectorTransform(clipStart, viewportMatrix);

    Vector3 clipEnd = VectorTransform(end, viewProjectionMatrix);
    Vector3 screenEnd = VectorTransform(clipEnd, viewportMatrix);

    // 描画
    Novice::DrawLine(
        static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
        static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y),
        color
    );
}