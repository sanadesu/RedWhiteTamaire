#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
class Basket : public GameObject
{
    int hModel_;    //モデル番号
    int whiteSum;   //白玉の得点
    int redSum;     //赤玉の得点
    Text* pText;
public:
    //コンストラクタ
    Basket(GameObject* parent);

    //デストラクタ
    ~Basket();

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

    //白いボールの合計
    void WhiteCount();

    //赤いボールの合計
    void RedCount();
};