#include "PlayScene.h"
#include"Player1.h"
#include"Ground.h"
#include "Basket.h"
#include "WhiteBall.h"
#include "RedBall.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
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

//�X�V
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

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}