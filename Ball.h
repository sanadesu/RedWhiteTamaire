#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include"Player.h"

const int ballCount = 10000;
//◆◆◆を管理するクラス
class Ball : public GameObject
{
    int hModel_[2];    //モデル番号
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
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;
};