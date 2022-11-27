#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Ball.h"
#include "Player1.h"
#include "Basket.h"

//���������Ǘ�����N���X
class WhiteBall : public GameObject
{
    int hModel_;    //���f���ԍ�

    /*struct WhiteConstParam
    {
        static const int DIAMETER;
        static const int RADIUS;
        static const int NEAR_GOAL;
    };*/
   
    const int DIAMETER = 3800;
    const int HALF = 2;
    const int CHANGE_DECIMAL = 100;
    const int CIRCLE_RANGE = 360;
    const int NEAR_GOAL = 15;
    const int CIRCLE_OUTSIDE = 400;
    const float BALLSIZE = 0.18f;
    const float POWER = 0.01f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;
    const float BOUND = 0.6f;
    const float RIGHT_HAND_LENGTH = 1.0f;
    const float LEFT_HAND_LENGTH = -1.0f;
    const float HAND_HEIGHT = 2.5f;
    const float END_MOVE = 0.001f;

    int radius;         //�~�̔��a��2��
    float height;       //�o�E���h�̍���
    float powerZ;       //�����鋗��
    float powerY;       //�����鍂��
    bool throwBall;     //�{�[���𓊂��Ă����
    bool rightHaving;   //�E��
    bool leftHaving;    //����

    Player1* pPlayer1 = (Player1*)FindObject("Player1");
    Basket* pBasket = (Basket*)FindObject("Basket");
    GameObject* pWhiteBall = FindObject("WhiteBall");
public:
    //�R���X�g���N�^
    WhiteBall(GameObject* parent);

    //�f�X�g���N�^
    ~WhiteBall();

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

};