#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Ball.h"
#include "Player1.h"
#include "Player2.h"
#include "Basket.h"
#include "PoryLine.h"

//���������Ǘ�����N���X
class WhiteBall : public GameObject
{
    int hModel_;    //���f���ԍ�

    enum Player
    {
        First,
        Second,
        Max
    };

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
    const int DROP_TIME = 600;
    const float BALLSIZE = 0.18f;
    const float POWER = 0.01f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;
    const float BOUND = 0.6f;
    const float RIGHT_HAND_LENGTH = 1.0f;
    const float LEFT_HAND_LENGTH = -1.0f;
    const float HAND_HEIGHT = 2.5f;
    const float END_MOVE = 0.001f;

    int key;
    int radius;         //�~�̔��a��2��
    int ballDrop[Max];
    int assistKey;
    float height[Max];       //�o�E���h�̍���
    float powerZ[Max];       //�����鋗��
    float powerY[Max];       //�����鍂��
    bool throwBall[Max];     //�{�[���𓊂��Ă����
    bool rightHaving[Max];   //�E��
    bool leftHaving[Max];    //����
    bool chargePower[Max];   //�͂����߂Ă��邩
    bool assist[Max];
    //XMFLOAT direction;

    Player1* pPlayer1 = (Player1*)FindObject("Player1");
    Player2* pPlayer2 = (Player2*)FindObject("Player2");
    Basket* pBasket = (Basket*)FindObject("Basket");
    GameObject* pWhiteBall = FindObject("WhiteBall");
    PoryLine* pLine;
    Transform trans;
    //Fbx* pFbx;
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