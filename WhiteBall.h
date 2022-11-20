#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Ball.h"
#include "Player.h"
#include "Basket.h"

const int BallCount = 10000;
//���������Ǘ�����N���X
class WhiteBall : public GameObject
{
    int hModel_;    //���f���ԍ�
    Transform trans[BallCount];

    const float GRAVITY = 0.05f;
    const float BOUND = 0.6f;

    int radius;
    int whiteCount;
    float height;
    float powerX;
    float powerY;
    float playerAngleY;
    bool throwBall;
    bool down;
    bool rightHaving;
    bool leftHaving;

    Player* pPlayer = (Player*)FindObject("Player");
    Basket* pBasket = (Basket*)FindObject("Basket");
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