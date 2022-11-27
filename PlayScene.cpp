#include "PlayScene.h"
#include"Player1.h"
#include"Ground.h"
#include "Basket.h"
#include "WhiteBall.h"
#include "RedBall.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player1>(this);
	Instantiate<Basket>(this);
	for (int i = 0; i < ALL_BALL; i++)
	{
		Instantiate<WhiteBall>(this);
	}
	for (int i = 0; i < ALL_BALL; i++)
	{
		Instantiate<RedBall>(this);
	}
	Instantiate<Ground>(this);
}

//更新
void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_1))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (Input::IsKeyDown(DIK_2))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}