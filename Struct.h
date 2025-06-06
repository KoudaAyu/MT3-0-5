#pragma once

struct Vector3
{
	float x, y, z;

    // ベクトル減算
    Vector3 operator-(const Vector3& other) const
    {
        return {
            x - other.x,
            y - other.y,
            z - other.z
        };
    }

    // ベクトル加算
    Vector3 operator+(const Vector3& other) const
    {
        return {
            x + other.x,
            y + other.y,
            z + other.z
        };
    }

    // スカラー倍（ベクトル * float）
    Vector3 operator*(float scalar) const
    {
        return {
            x * scalar,
            y * scalar,
            z * scalar
        };
    }

};

struct Matrix4x4
{
    float m[4][4];

    // メンバ関数版
    Matrix4x4 operator*(const Matrix4x4& rhs) const
    {
        Matrix4x4 result = {};
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                result.m[row][col] = 0.0f;
                for (int k = 0; k < 4; ++k)
                {
                    result.m[row][col] += m[row][k] * rhs.m[k][col];
                }
            }
        }
        return result;
    }
};


