#include "Vector.h"

Vector3 VectorAdd(const Vector3& a, const Vector3& b)
{
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 VectorSubtract(const Vector3& a, const Vector3& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 VectorMultiply(float scalar, const Vector3& vec)
{
    Vector3 result;
    result.x = scalar * vec.x;
    result.y = scalar * vec.y;
    result.z = scalar * vec.z;
    return result;
}

Vector3 VectorProject(const Vector3& v1, const Vector3& v2)
{
    float dotVV = v2.x * v2.x + v2.y * v2.y + v2.z * v2.z;
    if (dotVV == 0.0f) return { 0, 0, 0 }; // 0除算防止

    float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float t = dot / dotVV;

    return { v2.x * t, v2.y * t, v2.z * t };
}

float Length(const Vector3& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 VectorClosestPoint(const Vector3& point, const Segment& segment)
{
    Vector3 diff = segment.diff;
    Vector3 toPoint = VectorSubtract(point, segment.origin);

    // 投影係数 t を求める
    float d = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    float t = (diff.x * toPoint.x + diff.y * toPoint.y + diff.z * toPoint.z) / d;

    // t を 0〜1 にクランプ（線分の範囲内に収める）
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // 線分上の最近点を計算
    return {
        segment.origin.x + diff.x * t,
        segment.origin.y + diff.y * t,
        segment.origin.z + diff.z * t
    };
}

Vector3 Normalize(const Vector3& v)
{
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    Vector3 result = { 0.0f, 0.0f, 0.0f };
    if (length != 0.0f)
    {
        result.x = v.x / length;
        result.y = v.y / length;
        result.z = v.z / length;
    }
    return result;
}

float VectorDot(const Vector3& v1,const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
    Vector3 result;
    result.x = (1 - t) * v1.x + t * v2.x;
    result.y = (1 - t) * v1.y + t * v2.y;
    result.z = (1 - t) * v1.z + t * v2.z;
    return result;
}
