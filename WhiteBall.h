#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Ball.h"
#include "Player1.h"
#include "Player2.h"
#include "Basket.h"
#include "PoryLine.h"

//◆◆◆を管理するクラス
class WhiteBall : public GameObject
{
    int hModel_;    //モデル番号

    enum Player
    {
        First,
        Second,
        Max
    };

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
    const int DROP_TIME = 600;
    const float BALLSIZE = 0.18f;
    const float POWER = 0.01f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;
    const float BOUND = 0.6f;
    const float RIGHT_HAND_LENGTH = 1.0f;
    const float LEFT_HAND_LENGTH = -1.0f;
    const float HAND_HEIGHT = 2.5f;
    const float END_MOVE = 0.001f;

    int key;
    int radius;         //円の半径の2乗
    int ballDrop[Max];
    int assistKey;
    float height[Max];       //バウンドの高さ
    float powerZ[Max];       //投げる距離
    float powerY[Max];       //投げる高さ
    bool throwBall[Max];     //ボールを投げている間
    bool rightHaving[Max];   //右手
    bool leftHaving[Max];    //左手
    bool chargePower[Max];   //力をためているか
    bool assist[Max];
    //XMFLOAT direction;

    Player1* pPlayer1 = (Player1*)FindObject("Player1");
    Player2* pPlayer2 = (Player2*)FindObject("Player2");
    Basket* pBasket = (Basket*)FindObject("Basket");
    GameObject* pWhiteBall = FindObject("WhiteBall");
    PoryLine* pLine;
    Transform trans;
    //Fbx* pFbx;
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