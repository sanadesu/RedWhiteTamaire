#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Player1 : public GameObject
{
    int hModel_;    //���f���ԍ�

    const int CIRCLE_RANGE = 360;//�ۂ͈̔́H�H�H�H
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -3.0f;
    const float HIT_SIZE = 1.2f;
    const float RETURN_MOVE = 0.01f;
    const float PLAYER_MOVE = 0.1f;//�ړ�����
    const float CAMERA_Z = 20.0f; //Z���W
    float y_;               //Y���W
    float moveLimit;        //�ړ��͈�
    bool rightHand;         //�E��
    bool leftHand;          //����
    bool damage;            //�U�����󂯂���
public:
    //�R���X�g���N�^
    Player1(GameObject* parent);

    //�f�X�g���N�^
    ~Player1();

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

    //�{�[��������
    void SetHand(bool rightHand_, bool leftHand_);

    //�{�[���������Ă��邩
    std::pair<bool,bool> GetHand();

    //�U�����󂯂�
    void SetDamage(bool damage_);

    //�U������
    bool GetDamage();
};