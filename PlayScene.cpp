#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "WhiteBall.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
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

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}