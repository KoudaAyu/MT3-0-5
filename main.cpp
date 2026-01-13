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

	

	// --- Quaternion sample calculation (compute once) ---
	Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };

	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);


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

		// Print quaternion results on the left
		int qx = 40;
		int qy = 40;
		Novice::ScreenPrintf(qx, qy + kRowHeight * 0, "%6.02f %6.02f %6.02f %6.02f : q1", q1.x, q1.y, q1.z, q1.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 1, "%6.02f %6.02f %6.02f %6.02f : q2", q2.x, q2.y, q2.z, q2.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 2, "%6.02f %6.02f %6.02f %6.02f : Identity", identity.x, identity.y, identity.z, identity.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 3, "%6.02f %6.02f %6.02f %6.02f : Conjugate", conj.x, conj.y, conj.z, conj.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 4, "%6.02f %6.02f %6.02f %6.02f : Inverse", inv.x, inv.y, inv.z, inv.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 5, "%6.02f %6.02f %6.02f %6.02f : Normalize", normal.x, normal.y, normal.z, normal.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 6, "%6.02f %6.02f %6.02f %6.02f : Multiply(q1, q2)", mul1.x, mul1.y, mul1.z, mul1.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 7, "%6.02f %6.02f %6.02f %6.02f : Multiply(q2, q1)", mul2.x, mul2.y, mul2.z, mul2.w);
		Novice::ScreenPrintf(qx, qy + kRowHeight * 8, "%6.02f : Norm", norm);

	

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
