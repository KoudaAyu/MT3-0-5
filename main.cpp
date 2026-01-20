#include <Novice.h>
#include <cstdint>
#include <cmath>
#include<imgui.h>

#include"AABB.h"
#include"Bezier.h"
#include"Bone.h"
#include"Const.h"
#include"Line.h"
#include"Matrix4x4.h"
#include"Camera.h"
#include"Grid.h"
#include"Plane.h"
#include"Struct.h"
#include"Sphere.h"
#include"Triangle.h"
#include"Vector.h"



const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 cameraTranslate(0.0f, 1.9f, -6.49f);
	Vector3 cameraRotate(0.26f, 0.0f, 0.0f);


	// マウス状態
	int prevMouseX = 0;
	int prevMouseY = 0;

	bool isDebug_ = false;

	

	


	Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f, 0.4f, -0.2f }), 0.45f);
	Vector3 pointY = { 2.1f, -0.9f, 1.3f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = VectorTransform(pointY, rotateMatrix);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		int mouseX, mouseY;
		Novice::GetMousePosition(&mouseX, &mouseY);

		//SPACEを押すと起動される
		//もう一度押すとOFF
		if (keys[DIK_SPACE])
		{
			isDebug_ = !isDebug_;
		}
		if (isDebug_)
		{
			if (Novice::IsTriggerMouse(0))
			{
				// クリック開始時に前のマウス位置をセット
				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}
			else if (Novice::IsPressMouse(0))
			{
				// ボタン押され続けているなら移動量で回転
				int deltaX = mouseX - prevMouseX;
				int deltaY = mouseY - prevMouseY;

				const float sensitivity = 0.005f;

				cameraRotate.y += deltaX * sensitivity;
				cameraRotate.x += deltaY * sensitivity;

				if (cameraRotate.x > 1.57f) cameraRotate.x = 1.57f;
				if (cameraRotate.x < -1.57f) cameraRotate.x = -1.57f;

				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}
			else
			{


				prevMouseX = mouseX;
				prevMouseY = mouseY;

			}
		}

		

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		//ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		

		ImGui::Begin("Windows");
		ImGui::End();

	
		
	
		int rx = 420;
		int ry = 40;
		
		Novice::ScreenPrintf(rx, ry + kRowHeight * 0, "%6.02f %6.02f %6.02f %6.02f : rotation", rotation.x, rotation.y, rotation.z, rotation.w);
		
		MatrixScreenPrintf(rx, ry + kRowHeight * 1, rotateMatrix, " : rotateMatrix");
		
		VectorScreenPrintf(rx, ry + kRowHeight * 6, rotateByQuaternion, " : rotateByQuaternion");
		VectorScreenPrintf(rx, ry + kRowHeight * 9, rotateByMatrix, " : rotateByMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
