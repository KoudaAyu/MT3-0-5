#include "Bone.h"
#include "Novice.h" // Novice::DrawLineを使うために必要
#include "Struct.h" // VectorTransformを使うために必要 (もしMatrix4x4とVectorの宣言が別ファイルなら必要)
#include "Matrix4x4.h" // MakeScaleMatrixなどを使うために必要
#include "Sphere.h" // DrawSphereを使うために必要

#include<imgui.h>

// DrawSphere 関数の前方宣言 (もしSphere.hでDrawSphereが定義されていなければ必要)
// void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color);


void DrawBone(const Bone* bones, int boneCount, Matrix4x4 viewProjectMatrix, Matrix4x4 viewportMatrix)
{
    Matrix4x4* localMatrix = new Matrix4x4[boneCount];
    Matrix4x4* worldMatrix = new Matrix4x4[boneCount];

    // ローカル行列の計算
    for (int i = 0; i < boneCount; ++i)
    {
        localMatrix[i] =
            MakeScaleMatrix(bones[i].scales) *
            MakeRotateMatrix(bones[i].rotates) *
            MakeTranslateMatrix(bones[i].translates);
    }

    // ワールド行列の計算 (階層構造)
    for (int i = 0; i < boneCount; ++i)
    {
        if (bones[i].parentIndex == -1)
        {
            worldMatrix[i] = localMatrix[i];
        }
        else
        {
            worldMatrix[i] = localMatrix[i] * worldMatrix[bones[i].parentIndex];
        }
    }

    // ボーン（線）の描画
    for (int i = 0; i < boneCount; ++i)
    {
        if (bones[i].parentIndex != -1)
        {
            // 親ボーンのワールド座標をスクリーン座標に変換
            Vector3 parentPos = VectorTransform(Vector3{ 0, 0, 0 }, worldMatrix[bones[i].parentIndex]);
            parentPos = VectorTransform(parentPos, viewProjectMatrix);
            parentPos = VectorTransform(parentPos, viewportMatrix);

            // 現在のボーンのワールド座標をスクリーン座標に変換
            Vector3 currentPos = VectorTransform(Vector3{ 0, 0, 0 }, worldMatrix[i]);
            currentPos = VectorTransform(currentPos, viewProjectMatrix);
            currentPos = VectorTransform(currentPos, viewportMatrix);

            Novice::DrawLine(
                static_cast<int>(parentPos.x),
                static_cast<int>(parentPos.y),
                static_cast<int>(currentPos.x),
                static_cast<int>(currentPos.y),
                0xFFFFFFFF // 白線で描画
            );
        }
    }

    // 関節（球体）の描画
    for (int i = 0; i < boneCount; ++i)
    {
        Vector3 jointPos = VectorTransform(Vector3{ 0, 0, 0 }, worldMatrix[i]);

        // ★ImGuiで jointPos を表示する
       

        Sphere jointSphere;
        jointSphere.center = jointPos;
        jointSphere.radius = 0.05f; // テスト中の値

        uint32_t color = 0xFFFFFFFF;

        if (i == 0)
        {
           color = 0xFF0000FF;
        }
        else if (i == 1)
        {
            color = 0x00FF00FF;
        }
        else if (i == 2)
        {
            color = 0x0000FFFF;
        }

        DrawSphere(jointSphere, viewProjectMatrix, viewportMatrix, color);


        ImGui::End();
    }

    // メモリ解放
    delete[] localMatrix;
    delete[] worldMatrix;
}