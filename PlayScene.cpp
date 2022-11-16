#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "Ball.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	for (int i = 0; i < 40; i++)
	{
		Instantiate<Ball>(this);
	}
	Instantiate<Ground>(this);
	Instantiate<Basket>(this);
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