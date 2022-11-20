#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Basket : public GameObject
{
    int hModel_;    //���f���ԍ�
    int whiteSum;
    int redSum;
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