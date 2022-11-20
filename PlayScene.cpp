#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "WhiteBall.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Basket>(this);
	for (int i = 0; i < 100; i++)
	{
		Instantiate<WhiteBall>(this);
	}
	Instantiate<Ground>(this);
	
}

//更新
void PlayScene::Update()
{
	//GameObject* Title = FindObject("SceneManager");
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}