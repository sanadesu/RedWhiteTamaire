#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号

    const float MOVE = 0.1f;//移動距離
    const float Z_ = 10.0f; //Z座標
    float y_;               //Y座標
    float moveLimit;        //移動範囲
    bool rightHand;         //右手
    bool leftHand;          //左手
    //Transform trans;
public:
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

    //右手でボールを持つ
    void SetHand(bool rightHand_, bool leftHand_);

    //右手でボールを持っているか
    std::pair<bool,bool> GetHand();

    ////左手でボールを持つ
    //void SetLeftHave(bool rightHand_,bool leftHand_);

    ////左手でボールを持っているか
    //bool GetLeftHave();
};