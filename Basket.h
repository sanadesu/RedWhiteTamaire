#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class Basket : public GameObject
{
    int hModel_;    //���f���ԍ�

    const float HIT_HEIGHT = 5.0f;
    const float HIT_SIZE = 0.8f;

    int whiteSum;   //���ʂ̓��_
    int redSum;     //�ԋʂ̓��_
    Text* pText;
public:
    //�R���X�g���N�^
    Basket(GameObject* parent);

    //�f�X�g���N�^
    ~Basket();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
   //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //�����{�[���̍��v
    void WhiteCount();

    //�Ԃ��{�[���̍��v
    void RedCount();
};