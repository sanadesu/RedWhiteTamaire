#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include"Player.h"

const int ballCount = 10000;
//���������Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_[2];    //���f���ԍ�
    Transform trans[ballCount];
    int radius;
    float height;
   
    float powerX;
    float powerY;
    float gravity;
    float playerAngleY;
    bool throwBall;
    bool down;
    Player* pPlayer = new Player(nullptr);
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

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