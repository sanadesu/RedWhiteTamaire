#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Ball.h"
#include "Player1.h"
#include "Basket.h"

//◆◆◆を管理するクラス
class WhiteBall : public GameObject
{
    int hModel_;    //モデル番号

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

    int radius;         //円の半径の2乗
    float height;       //バウンドの高さ
    float powerZ;       //投げる距離
    float powerY;       //投げる高さ
    bool throwBall;     //ボールを投げている間
    bool rightHaving;   //右手
    bool leftHaving;    //左手

    Player1* pPlayer1 = (Player1*)FindObject("Player1");
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