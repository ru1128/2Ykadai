#include "main.h"
#include "Scene.h"

void Scene::Draw2D()
{
	switch (NowScene)
	{
	case Title:
		break;
	case Select:
		break;
	case Game:
		break;
	case Reslet:
		break;
	default:
		break;
	}

}

void Scene::Update()
{

	switch (NowScene)
	{
	case Title:
		break;
	case Select:
		break;
	case Game:
		break;
	case Reslet:
		break;
	default:
		break;
	}
	
}

void Scene::Init()
{
	// 画像の読み込み処理
	charaTex.Load("player.png");
}

void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
