#pragma once
#include "Engine/GameObject.h"
#include "WhiteBall.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	const int ALL_BALL = 30;
	const int END_TIME = 7200;
	int time;
	Text* pText;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};