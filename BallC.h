//#pragma once
//#include "Engine/GameObject.h"
//#include "Engine/SphereCollider.h"
//#include "Player.h"
//
////���������Ǘ�����N���X
//class Ball : public GameObject
//{
//    int hModel_[2];    //���f���ԍ�
//    float height;
//    bool throwBall;
//    bool down;
//    float PowerX;
//    float PowerY;
//    float gravity;
//    Player* pPlayer = new Player(nullptr);
//public:
//    //�R���X�g���N�^
//    Ball(GameObject* parent);
//
//    //�f�X�g���N�^
//    ~Ball();
//
//    //������
//    void Initialize() override;
//
//    //�X�V
//    void Update() override;
//
//    //�`��
//    void Draw() override;
//
//    //�J��
//    void Release() override;
//
//    //�����ɓ�������
//    //�����FpTarget ������������
//    void OnCollision(GameObject* pTarget) override;
//};