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

	/*uint32_t LineColor = 0x000000FF;*/

	Sphere* sphere[2];
	sphere[0] = new Sphere();
	sphere[1] = new Sphere();

	Plane* plane = new Plane();
	plane->normal = Normalize({ 1.0f, 1.0f, 0.0f });
	plane->distance = 0.0f;



	sphere[0]->center = { 0.0f,0.0f,0.0f };
	sphere[0]->radius = 1.0f;

	sphere[1]->center = { 1.0f,0.0f,1.0f };
	sphere[1]->radius = 0.4f;

	uint32_t colors[2] = { WHITE,WHITE };


	Segment segment;

	//値変えられるようにする
	segment.origin = { -0.7f, 0.3f, 0.0f };
	segment.diff = VectorSubtract({ 2.0f, -0.5f, 0.0f }, segment.origin);  // 初期値として差分を設定;

	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = VectorProject(VectorSubtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = VectorClosestPoint(point, segment);

	/*Triangle triangle;
	triangle.vertices[0] = { -1.0f,0.0f,0.0f };
	triangle.vertices[1] = { 0.0f,1.0f,0.0f };
	triangle.vertices[2] = { 1.0f,0.0f,0.0f };*/

	AABB aabb[2];
	aabb[0].min = { -0.5f,-0.5f,-0.5f };
	aabb[0].max = { 0.5f,0.5f,0.5f };

	aabb[1].min = { 0.2f,0.2f,0.2f };
	aabb[1].max = { 1.0f,1.0f,1.0f };

	Bezier bezier[3];
	bezier[0].controlPositions = { -0.8f,0.58f,1.0f };
	bezier[1].controlPositions = { -1.76f,1.0f,-0.3f };
	bezier[2].controlPositions = { -0.94f,-0.7f,2.3f };

	Bone bone[3];
	bone[0].translates = { 0.2f,1.0f,0.0f };
	bone[1].translates = { 0.4f,0.0f,0.0f };
	bone[2].translates = { 0.3f,0.0f,0.0f };

	bone[0].rotates = { 0.0f,0.0f,-6.8f };
	bone[1].rotates = { 0.0f,0.0f,-1.4f };
	bone[2].rotates = { 0.0f,0.0f,0.0f };

	bone[0].scales = { 1.0f,1.0f,1.0f };
	bone[1].scales = { 1.0f,1.0f,1.0f };
	bone[2].scales = { 1.0f,1.0f,1.0f };

	// マウス状態
	int prevMouseX = 0;
	int prevMouseY = 0;

	bool isDebug_ = false;

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

		plane->distance = VectorDot(plane->normal, { 1.0f, 0.0f, 0.0f });

		Matrix4x4 cameraWorld = MakeAffineMatrix(
			{ 1,1,1 },
			cameraRotate,
			cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraWorld);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(float(3.14 / 4.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 0.0f);

		Matrix4x4 viewProjectMatrix = Multiply(viewMatrix, projectionMatrix);

		Prependicular(plane->normal);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		DrawGrid(viewProjectMatrix, viewportMatrix);

		/*sphere[0]->DrawSphere(*sphere[0], viewProjectMatrix, viewportMatrix, WHITE);
		ImGui::DragFloat3("Sphere.center", &sphere[0]->center.x, 0.1f);
		ImGui::DragFloat("SphereRadius", &sphere[0]->radius, 0.1f);*/

		

		//SegmentDraw(segment, viewProjectMatrix, viewportMatrix,WHITE);
		//ImGui::DragFloat3("Segment.Origine", &segment.origin.x, 0.01f);
		//ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);

		/*ImGui::DragFloat3("Plane.Normal", &plane->normal.x, 0.01f);
		plane->normal = Normalize(plane->normal);*/



		/*DrawTriangle(triangle, viewProjectMatrix, viewportMatrix, WHITE);
		ImGui::DragFloat3("Trianglev0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Trianglev1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Trianglev2", &triangle.vertices[2].x, 0.01f);*/

		/*DrawAABB(aabb[0], viewProjectMatrix, viewportMatrix, colors[0]);*/
		/*DrawAABB(aabb[1], viewProjectMatrix, viewportMatrix, WHITE);*/



		/*ImGui::DragFloat3("aabb0.min", &aabb[0].min.x, 0.1f);
		ImGui::DragFloat3("aabb0.max", &aabb[0].max.x, 0.1f);*/
		/*	ImGui::DragFloat3("aabb2.min", &aabb[1].min.x, 0.1f);
			ImGui::DragFloat3("aabb2.max", &aabb[1].max.x, 0.1f);*/

		DrawBezier(bezier[0].controlPositions, bezier[1].controlPositions, bezier[2].controlPositions,
			viewProjectMatrix, viewportMatrix, BLUE);
		ImGui::DragFloat3("controlPosition[0]", &bezier[0].controlPositions.x, 0.1f);
		ImGui::DragFloat3("controlPosition[1]", &bezier[1].controlPositions.x, 0.1f);
		ImGui::DragFloat3("controlPosition[2]", &bezier[2].controlPositions.x, 0.1f);

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
