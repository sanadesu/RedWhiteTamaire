#include "SetumeiScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
SetumeiScene::SetumeiScene(GameObject* parent)
	: GameObject(parent, "SetumeiScene"), hPict_(-1)
{
}

//������
void SetumeiScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Setumei.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void SetumeiScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void SetumeiScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void SetumeiScene::Release()
{
}
