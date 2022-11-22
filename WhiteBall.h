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
    const float BALLSIZE = 0.18f;

    int radius;         //�~�̔��a��2��
    int fieldWhiteBall;      //�t�B�[���h�ɗ����Ă�{�[���̍��v
    float height;       //�o�E���h�̍���
    float powerZ;       //�����鋗��
    float powerY;       //�����鍂��
    bool throwBall;     //�{�[���𓊂��Ă����
    bool rightHaving;   //�E��
    bool leftHaving;    //����

    Player* pPlayer = (Player*)FindObject("Player");
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