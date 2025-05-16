#include <Novice.h>
#include <cstdint>
#include <cmath>
#include<imgui.h>

#include"Struct.h"
#include"Const.h"
#include"Line.h"
#include"Matrix4x4.h"
#include"Camera.h"
#include"Grid.h"
#include"Sphere.h"
#include"Vector.h"


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

	/*uint32_t LineColor = 0x000000FF;*/

	Sphere* sphere[2];
	sphere[0] = new Sphere();
	sphere[1] = new Sphere();
	

	sphere[0]->center = { 0.0f,0.0f,0.0f };
	sphere[0]->radius = 1.0f;

	sphere[1]->center = { 1.0f,0.0f,1.0f };
	sphere[1]->radius = 0.4f;

	uint32_t colors[2] = { WHITE,WHITE };

	float distance = 0.0f;

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = VectorProject(VectorSubtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = VectorClosestPoint(point, segment);

	// マウス状態
	int prevMouseX = 0;
	int prevMouseY = 0;

	bool isDebug_ = false;
	
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

		int mouseX, mouseY;
		Novice::GetMousePosition(&mouseX, &mouseY);
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
		
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(float(3.14/4.0f),1280.0f/720.0f,0.1f,100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 0.0f);
		
		Matrix4x4 viewProjectMatrix = Multiply(viewMatrix, projectionMatrix);
		
		distance = Sphere::GetDistanceBetweenCenters(*sphere[0], *sphere[1]);

		if (distance < sphere[0]->radius + sphere[1]->radius)
		{
			colors[0] = RED;
		}
		else
		{
			colors[0] = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


	
	
		

		
		DrawGrid(viewProjectMatrix, viewportMatrix);

		
		sphere[0]->SphereDraw(*sphere[0], viewProjectMatrix, viewportMatrix, colors[0]);
		sphere[1]->SphereDraw(*sphere[1], viewProjectMatrix, viewportMatrix, colors[1]);

		

		

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("Sphere0 Center", &sphere[0]->center.x, 0.01f);
		ImGui::DragFloat("Sphere0 Radius", &sphere[0]->radius, 0.01f);
		ImGui::DragFloat3("Sphere1 Center", &sphere[1]->center.x, 0.01f);
		ImGui::DragFloat("Sphere1 Radius", &sphere[1]->radius, 0.01f);

		/*ImGui::InputFloat3("Project",&project.x,"%0.3f",ImGuiInputFlags_ReadOnly);*/

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
