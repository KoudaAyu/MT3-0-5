#include "Bone.h"

void BoneDraw(const Bone& bone1, const Bone& bone2, const Bone& bone3)
{
    Matrix4x4 localMatrix[3];

    // ボーン1（肩）のローカル行列
    localMatrix[0] =
        MakeScaleMatrix(bone1.scales) *
        MakeRotateMatrix(bone1.rotates) *
        MakeTranslateMatrix(bone1.translates);

    // ボーン2（肘）のローカル行列
    localMatrix[1] =
        MakeScaleMatrix(bone2.scales) *
        MakeRotateMatrix(bone2.rotates) *
        MakeTranslateMatrix(bone2.translates);

    // ボーン3（手）のローカル行列
    localMatrix[2] =
        MakeScaleMatrix(bone3.scales) *
        MakeRotateMatrix(bone3.rotates) *
        MakeTranslateMatrix(bone3.translates);

    // ↓ このあとの処理（ワールド行列の計算など）は後で追加
    Matrix4x4 worldMatrix[3];

    worldMatrix[0] = localMatrix[0];

    worldMatrix[1] = localMatrix[1] * worldMatrix[0];

    worldMatrix[2] = localMatrix[2] * worldMatrix[1];
}
