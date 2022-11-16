#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "Ball.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
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

//�X�V
void PlayScene::Update()
{
	//GameObject* Title = FindObject("SceneManager");
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}