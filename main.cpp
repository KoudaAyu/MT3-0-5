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

	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;

	Vector3 rotate{ 0.4f,1.43f,-0.8f };

	Matrix4x4 rotateXMatrix = MakeRotateXFloatMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYFloatMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZFloatMatrix(rotate.z);

	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;


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

		

		Matrix4x4 cameraWorld = MakeAffineMatrix(
			{ 1,1,1 },
			cameraRotate,
			cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraWorld);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(float(3.14 / 4.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 0.0f);

		Matrix4x4 viewProjectMatrix = Multiply(viewMatrix, projectionMatrix);

		


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		//ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		DrawGrid(viewProjectMatrix, viewportMatrix);

		ImGui::Begin("Windows");
		ImGui::Text("c:%f,%f,%f", c.x, c.y, c.z);
		ImGui::Text("d:%f,%f,%f", d.x, d.y, d.z);
		ImGui::Text("e:%f,%f,%f", e.x, e.y, e.z);
		ImGui::Text("matix\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);


		ImGui::End();


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
