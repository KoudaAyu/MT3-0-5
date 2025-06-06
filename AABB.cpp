#include "AABB.h"

bool IsCollisionAABBAABB(const AABB& aabb1, const AABB& aabb2)
{
	AABB fixedAABB1 = aabb1;


    // x軸のmin/maxを補正
    fixedAABB1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
    fixedAABB1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);

    // y軸
    fixedAABB1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
    fixedAABB1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);

    // z軸
    fixedAABB1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
    fixedAABB1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

    // 衝突判定
    if ((fixedAABB1.min.x <= aabb2.max.x && fixedAABB1.max.x >= aabb2.min.x) &&
        (fixedAABB1.min.y <= aabb2.max.y && fixedAABB1.max.y >= aabb2.min.y) &&
        (fixedAABB1.min.z <= aabb2.max.z && fixedAABB1.max.z >= aabb2.min.z))
    {
        return true;
    }

    return false;
}

bool IsCollisionAABBSphere(const AABB& aabb, const Sphere& sphere)
{
    AABB fixedAABB = aabb;

    // x軸のmin/maxを補正
    fixedAABB.min.x = (std::min)(aabb.min.x, aabb.max.x);
    fixedAABB.max.x = (std::max)(aabb.min.x, aabb.max.x);

    // y軸
    fixedAABB.min.y = (std::min)(aabb.min.y, aabb.max.y);
    fixedAABB.max.y = (std::max)(aabb.min.y, aabb.max.y);

    // z軸
    fixedAABB.min.z = (std::min)(aabb.min.z, aabb.max.z);
    fixedAABB.max.z = (std::max)(aabb.min.z, aabb.max.z);

    // 球の中心に対するAABB上の最近接点を求める
    Vector3 closestPoint{
        std::clamp(sphere.center.x, fixedAABB.min.x, fixedAABB.max.x),
        std::clamp(sphere.center.y, fixedAABB.min.y, fixedAABB.max.y),
        std::clamp(sphere.center.z, fixedAABB.min.z, fixedAABB.max.z)
    };

    // 最近接点と球の中心の距離ベクトル
    Vector3 diff = {
        closestPoint.x - sphere.center.x,
        closestPoint.y - sphere.center.y,
        closestPoint.z - sphere.center.z
    };

    // 距離の2乗を計算
    float distSquared = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

    // 球の半径の2乗と比較して衝突判定
    return distSquared <= (sphere.radius * sphere.radius);
}

bool IsCollisionAABBSegment(const AABB& aabb, const Segment& segment)
{
    // min/maxを補正してAABBを正しくする
    AABB fixedAABB = aabb;
    fixedAABB.min.x = (std::min)(aabb.min.x, aabb.max.x);
    fixedAABB.max.x = (std::max)(aabb.min.x, aabb.max.x);
    fixedAABB.min.y = (std::min)(aabb.min.y, aabb.max.y);
    fixedAABB.max.y = (std::max)(aabb.min.y, aabb.max.y);
    fixedAABB.min.z = (std::min)(aabb.min.z, aabb.max.z);
    fixedAABB.max.z = (std::max)(aabb.min.z, aabb.max.z);

    float tMin = 0.0f;
    float tMax = 1.0f;

    Vector3 start = segment.origin;
    Vector3 dir = segment.diff;

    // 各軸でスラブ判定
    for (int i = 0; i < 3; i++)
    {
        float startAxis = (&start.x)[i];
        float dirAxis = (&dir.x)[i];
        float minAxis = (&fixedAABB.min.x)[i];
        float maxAxis = (&fixedAABB.max.x)[i];

        if (fabsf(dirAxis) < 1e-6f)
        {
            // この軸に沿って動いていない（スラブ内にいるかチェック）
            if (startAxis < minAxis || startAxis > maxAxis)
            {
                return false; // AABBを横切らない
            }
        }
        else
        {
            float t1 = (minAxis - startAxis) / dirAxis;
            float t2 = (maxAxis - startAxis) / dirAxis;
            if (t1 > t2) std::swap(t1, t2);

            tMin = (std::max)(tMin, t1);
            tMax = (std::min)(tMax, t2);

            if (tMin > tMax)
            {
                return false; // 交差しない
            }
        }
    }

    return true; // 全軸でOK → 衝突してる！
}


void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    // AABBの8頂点
    Vector3 vertices[8] = {
        {aabb.min.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.max.y, aabb.min.z},
        {aabb.min.x, aabb.max.y, aabb.min.z},
        {aabb.min.x, aabb.min.y, aabb.max.z},
        {aabb.max.x, aabb.min.y, aabb.max.z},
        {aabb.max.x, aabb.max.y, aabb.max.z},
        {aabb.min.x, aabb.max.y, aabb.max.z}
    };

    // 変換後スクリーン座標
    Vector3 screenVertices[8];
    for (int i = 0; i < 8; ++i)
    {
        Vector3 ndc = VectorTransform(vertices[i], viewProjectionMatrix);
        screenVertices[i] = VectorTransform(ndc, viewportMatrix);
    }

    // 12本の辺を描くための頂点インデックス
    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0}, // 奥面
        {4,5},{5,6},{6,7},{7,4}, // 手前面
        {0,4},{1,5},{2,6},{3,7}  // 側面
    };

    for (int i = 0; i < 12; ++i)
    {
        int s = edges[i][0];
        int e = edges[i][1];
        Novice::DrawLine(
            static_cast<int>(screenVertices[s].x), static_cast<int>(screenVertices[s].y),
            static_cast<int>(screenVertices[e].x), static_cast<int>(screenVertices[e].y),
            color
        );
    }
}
