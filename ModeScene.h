#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
class ModeScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
	int hPict_2;    //�摜�ԍ�
	int hModel_;    //���f���ԍ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ModeScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	
};