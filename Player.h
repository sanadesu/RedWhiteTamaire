#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"
#include "Ball.h"
#include "Basket.h"
#include "StateWalk.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    
    enum PlayerNumber
    {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        MAX
    };

    enum State
    {
        WALK_STATE = 0,
        CHARGE_STATE,
        THROW_STATE,
        MAX_STATE
    };

    int hModel_;    //モデル番号
    int hPict_;    //画像番号

    const int CIRCLE_RANGE = 360;//丸の範囲？？？？
    const int PORY_LENGTH = 15;
    const float POWER = 0.01;
    const float START_POS_X = 0.0f;
    const float START_POS_Z = -3.0f;
    const float HIT_SIZE = 1.2f;
    const float PLAYER_MOVE = 0.1f;//移動距離
    const float CAMERA_Z = 20.0f; //Z座標
    const float HAND_HEIGHT = 2.5f;
    const float GRAVITY = 0.05f;
    const float RESISTANCE = 0.97f;


    int nowState;
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
    float goalLength;
    //bool rightHand;         //右手
    //bool leftHand;          //左手
    bool damage;            //攻撃を受けたか
    bool chargePower;
    Transform prevPos; //1フレーム前の場所

    Transform trans;
    PoryLine* pLine;
    Ball* pBall = (Ball*)FindObject("Ball");
    Ball* pBallRight = nullptr;
    Ball* pBallLeft = nullptr;
    Ball* pBallThrow = nullptr;
    Basket* pBasket = (Basket*)FindObject("Basket");
    StateWalk* pStateWalk = (StateWalk*)FindObject("StateWalk");
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

    int GetState();
};