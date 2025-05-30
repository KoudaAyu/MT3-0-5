#include "Bone.h"

void BoneDraw(const Bone& bone1, const Bone& bone2, const Bone& bone3)
{
    Matrix4x4 localMatrix[3];

    // �{�[��1�i���j�̃��[�J���s��
    localMatrix[0] =
        MakeScaleMatrix(bone1.scales) *
        MakeRotateMatrix(bone1.rotates) *
        MakeTranslateMatrix(bone1.translates);

    // �{�[��2�i�I�j�̃��[�J���s��
    localMatrix[1] =
        MakeScaleMatrix(bone2.scales) *
        MakeRotateMatrix(bone2.rotates) *
        MakeTranslateMatrix(bone2.translates);

    // �{�[��3�i��j�̃��[�J���s��
    localMatrix[2] =
        MakeScaleMatrix(bone3.scales) *
        MakeRotateMatrix(bone3.rotates) *
        MakeTranslateMatrix(bone3.translates);

    // �� ���̂��Ƃ̏����i���[���h�s��̌v�Z�Ȃǁj�͌�Œǉ�
    Matrix4x4 worldMatrix[3];

    worldMatrix[0] = localMatrix[0];

    worldMatrix[1] = localMatrix[1] * worldMatrix[0];

    worldMatrix[2] = localMatrix[2] * worldMatrix[1];
}
