#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include "Basket.h"
#include "Ball.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	/*Instantiate<Player1>(this);
	Instantiate<Player2>(this);*/
	Instantiate<Basket>(this);
	Ball* pBall[80];
	for (int i = 0; i < ALL_BALL; i++)
	{
		pBall[i] = Instantiate<Ball>(this);
		pBall[i]->ballID = i;

		
	}
	p1 = Instantiate<Player>(this);
	p1->playerID = playerNumber;
	playerNumber++;
	p2 = Instantiate<Player>(this);
	p2->playerID = playerNumber;
	//for (int i = 0; i < ALL_BALL; i++)
	/*{
		Instantiate<WhiteBall>(this);
		Instantiate<RedBall>(this);
	}*/
	

	pText = new Text;
	pText->Initialize();
	time = END_TIME;
	playerNumber = 0;
}

//�X�V
void PlayScene::Update()
{
	////�摜�f�[�^�̃��[�h
	//hPict_ = Image::Load("�t�@�C����");
	//assert(hPict_ >= 0); 
	//p2->GetState();

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