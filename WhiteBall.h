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
    const float BALLSIZE = 0.18f;

    int radius;         //円の半径の2乗
    int fieldWhiteBall;      //フィールドに落ちてるボールの合計
    float height;       //バウンドの高さ
    float powerZ;       //投げる距離
    float powerY;       //投げる高さ
    bool throwBall;     //ボールを投げている間
    bool rightHaving;   //右手
    bool leftHaving;    //左手

    Player* pPlayer = (Player*)FindObject("Player");
    Basket* pBasket = (Basket*)FindObject("Basket");
    GameObject* pWhiteBall = FindObject("WhiteBall");
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