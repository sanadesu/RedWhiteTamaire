#include "PlayScene.h"
#include"Player1.h"
#include"Player2.h"
#include"Player.h"
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
	Instantiate<Ground>(this);
	Instantiate<Player1>(this);
	Instantiate<Player2>(this);
	Player* p1 = Instantiate<Player>(this);
	p1->playerID = playerNumber;
	playerNumber++;
	Player* p2 = Instantiate<Player>(this);
	p2->playerID = playerNumber;
	Instantiate<Basket>(this);
	for (int i = 0; i < ALL_BALL; i++)
	{
		Instantiate<WhiteBall>(this);
	}
	for (int i = 0; i < ALL_BALL; i++)
	{
		Instantiate<RedBall>(this);
	}

	pText = new Text;
	pText->Initialize();
	time = END_TIME;
	playerNumber = 0;
}

//�X�V
void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_1))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (time <= 0)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	time--;
}

//�`��
void PlayScene::Draw()
{
	pText->Draw(30, 90, (time/60));
}

//�J��
void PlayScene::Release()
{
}