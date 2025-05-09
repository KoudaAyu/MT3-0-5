#include <Novice.h>
#include <cstdint>
#include<imgui.h>

#include"Struct.h"
#include"Const.h"
#include"Matrix4x4.h"
#include"Camera.h"
#include"Grid.h"
#include"Sphere.h"



const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate(0.0f, 1.9f, -6.49f);
	Vector3 cameraRotate(0.26f, 0.0f, 0.0f);

	uint32_t LineColor = 0x000000FF;

	Sphere* sphere = new Sphere();

	sphere->center = { 0.0f,0.0f,0.0f };
	sphere->radius = 1.0f;
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 cameraWorld = MakeAffineMatrix(
			{ 1,1,1 },
			cameraRotate,
			cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraWorld);
		
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(float(3.14/4.0f),1280.0f/720.0f,0.1f,100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 0.0f);
		
		Matrix4x4 viewProjectMatrix = Multiply(viewMatrix, projectionMatrix);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		sphere->SphereDraw(*sphere,viewProjectMatrix,viewportMatrix,LineColor);

		DrawGrid(viewProjectMatrix, viewportMatrix);

	


		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere->center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere->radius, 0.01f);

		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
