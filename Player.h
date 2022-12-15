#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "Ball.h"
#include "Basket.h"
#include "StateWalk.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�

    enum PlayerNumber
    {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        MAX
    };

    enum State
    {
        WALK_STATE = 0,
        CHARGE_STATE,
        THROW_STATE,

    };

    const int CIRCLE_RANGE = 360;//�ۂ͈̔́H�H�H�H
    const float POWER = 0.01;
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -3.0f;
    const float HIT_SIZE = 1.2f;
    const float RETURN_MOVE = 0.01f;
    const float PLAYER_MOVE = 0.1f;//�ړ�����
    const float CAMERA_Z = 20.0f; //Z���W
    const float HAND_HEIGHT = 2.5f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;

    int nowState;
    int key;
    int button;
    int processID;
    int rightHand;
    int leftHand;
    float powerY;
    float powerZ;
    float trajectoryY;
    float trajectoryZ;
    float y_;               //Y���W
    float moveLimit;        //�ړ��͈�
    //bool rightHand;         //�E��
    //bool leftHand;          //����
    bool damage;            //�U�����󂯂���
    bool chargePower;

    Transform trans;
    PoryLine* pLine;
    Ball* pBall = (Ball*)FindObject("Ball");
    Ball* pBallRight = nullptr;
    Ball* pBallLeft = nullptr;
    Ball* pBallThrow = nullptr;
    Basket* pBasket = (Basket*)FindObject("Basket");
    StateWalk* pStateWalk = (StateWalk*)FindObject("StateWalk");
public:
    int playerID;

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

    ////�{�[��������
    //void SetHand(bool rightHand_, bool leftHand_);

    ////�{�[���������Ă��邩
    //std::pair<bool, bool> GetHand();

    //�U�����󂯂�
    void SetDamage(bool damage_);

    //�U������
    bool GetDamage();

    Transform GetPlayerPosition(bool right_);

};