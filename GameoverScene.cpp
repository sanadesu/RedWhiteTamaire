#include "GameoverScene.h"
#include "Engine/Image.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
GameoverScene::GameoverScene(GameObject* parent)
	: GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

//初期化
void GameoverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Gameover.jpg");
	assert(hPict_ >= 0);
}

//更新
void GameoverScene::Update()
{
    //タイトルへ
    if (Input::IsKeyDown(DIK_1))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }

    //モード選択へ
    if (Input::IsKeyDown(DIK_2))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_Mode);
    }

    //もう一度
    if (Input::IsKeyDown(DIK_3))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
    }
}

//描画
void GameoverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameoverScene::Release()
{
}