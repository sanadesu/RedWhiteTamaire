#include "titleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
titleScene::titleScene(GameObject* parent)
	: GameObject(parent, "titleScene"), hPict_(-1)
{
}

//初期化
void titleScene::Initialize()
{

}

//更新
void titleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_Mode);
	}
}

//描画
void titleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void titleScene::Release()
{
}
