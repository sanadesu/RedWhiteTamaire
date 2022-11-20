#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Ball.h"
#include "Player.h"
#include "Basket.h"

const int BallCount = 10000;
//◆◆◆を管理するクラス
class WhiteBall : public GameObject
{
    int hModel_;    //モデル番号
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
    //コンストラクタ
    WhiteBall(GameObject* parent);

    //デストラクタ
    ~WhiteBall();

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