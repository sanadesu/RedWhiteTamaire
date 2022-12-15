#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "WhiteBall.h"
#include "Ball.h"
#include "Basket.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号

    enum PlayerNumber
    {
        First,
        Second,
        Third,
        Fourth,
        Max
    };

    const int CIRCLE_RANGE = 360;//丸の範囲？？？？
    const float POWER = 0.01;
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -3.0f;
    const float HIT_SIZE = 1.2f;
    const float RETURN_MOVE = 0.01f;
    const float PLAYER_MOVE = 0.1f;//移動距離
    const float CAMERA_Z = 20.0f; //Z座標
    const float HAND_HEIGHT = 2.5f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;

    int key;
    int button;
    int processID;
    int rightHand;
    int leftHand;
    float powerY;
    float powerZ;
    float trajectoryY;
    float trajectoryZ;
    float y_;               //Y座標
    float moveLimit;        //移動範囲
    //bool rightHand;         //右手
    //bool leftHand;          //左手
    bool damage;            //攻撃を受けたか
    bool chargePower;

    PoryLine* pLine;
    Transform trans;
    Ball* pBall = (Ball*)FindObject("Ball");
    Ball* pBallRight = nullptr;
    Ball* pBallLeft = nullptr;
    Basket* pBasket = (Basket*)FindObject("Basket");
public:
    int playerID;

    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

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

    //角度取得
    float GetAngle();

    ////ボールを持つ
    //void SetHand(bool rightHand_, bool leftHand_);

    ////ボールを持っているか
    //std::pair<bool, bool> GetHand();

    //攻撃を受ける
    void SetDamage(bool damage_);

    //攻撃治る
    bool GetDamage();

    Transform GetPlayerPosition(bool right_);

};