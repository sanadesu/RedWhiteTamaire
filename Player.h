#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�

    const float MOVE = 0.1f;//�ړ�����
    const float Z_ = 10.0f; //Z���W
    float y_;               //Y���W
    float moveLimit;        //�ړ��͈�
    bool rightHand;         //�E��
    bool leftHand;          //����
    //Transform trans;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

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

    //�p�x�擾
    float GetAngle();

    //�E��Ń{�[��������
    void SetHand(bool rightHand_, bool leftHand_);

    //�E��Ń{�[���������Ă��邩
    std::pair<bool,bool> GetHand();

    ////����Ń{�[��������
    //void SetLeftHave(bool rightHand_,bool leftHand_);

    ////����Ń{�[���������Ă��邩
    //bool GetLeftHave();
};