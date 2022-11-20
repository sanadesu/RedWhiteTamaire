////#pragma once
////#include "Engine/GameObject.h"
////#include "Engine/SphereCollider.h"
////#include"Player.h"
////
////const int ballCount = 10000;
//////◆◆◆を管理するクラス
////class Ball : public GameObject
////{
////    //int hModel_[2];    //モデル番号
////
////    const float BOUND = 0.6f;//どのくらい跳ねるか
////    const float GRAVITY = 0.05f;//重力
////
////    float radius;
////    float height;//跳ね返る高さ
////    bool throwBall;
////
////    /*float powerX;
////    float powerY;
////    float playerAngleY;
////    bool down;
////    Player* pPlayer = new Player(nullptr);*/
////public:
////    //コンストラクタ
////    Ball(GameObject* parent);
////
////    //デストラクタ
////    ~Ball();
////
////    //ボールを投げる
////    //引数 : どのボタンを押したか,角度,強さX,Y
////    void ThrowBall(int buttonCode_, float angle_, float powerX_, float powerY_);
////
////    ////初期化
////    //void Initialize() override;
////
////    ////更新
////    //void Update() override;
////
////    ////描画
////    //void Draw() override;
////
////    ////開放
////    //void Release() override;
////
////    ////何かに当たった
////    ////引数：pTarget 当たった相手
////    //void OnCollision(GameObject* pTarget) override;
////};
//
//
//
//
//
//
//
//
//
//
//#include "WhiteBall.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//#include "Basket.h"
//
////コンストラクタ
//WhiteBall::WhiteBall(GameObject* parent)
//    :GameObject(parent, "WhiteBall")
//{
//    hModel_ = -1;
//}
//
////デストラクタ
//WhiteBall::~WhiteBall()
//{
//}
//
////初期化
//void WhiteBall::Initialize()
//{
//    //モデルデータのロード
//    hModel_ = Model::Load("WhiteBall.fbx");
//    assert(hModel_ >= 0);
//
//    transform_.position_ = XMFLOAT3(0, 0, 0);
//
//    do
//    {
//        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
//        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
//        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
//    } while (radius > 360 || radius < 15);
//
//    //当たり判定
//    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
//    AddCollider(collision);
//
//    radius = 0;
//    whiteCount = 0;
//    height = 1;
//    powerX = 0;
//    powerY = 0;
//    playerAngleY = 0;
//    throwBall = false;
//    down = false;
//    rightHaving = false;
//    leftHaving = false;
//}
//
////更新
//void WhiteBall::Update()
//{
//    //スペースキーを押したら
//    if ((Input::IsKeyDown(DIK_SPACE) || throwBall == true))
//    {
//
//        //スペースを押してるとき
//        if (Input::IsKey(DIK_SPACE))
//        {
//            if (rightHaving == true)
//            {
//
//                powerX += 0.01;
//                //あとで向いてる角度にする
//                powerY -= 0.01;
//                throwBall = true;
//            }
//        }
//        else if (Input::IsKeyUp(DIK_SPACE))
//        {
//            //powerY -= playerAngleY;//プレイヤーの角度
//            if (pPlayer->GetRightHave().second == true)
//            {
//                pPlayer->SetRightHave(false, true);
//                //leftHaving = false;
//                //rightHaving = true;
//            }
//            else
//            {
//                pPlayer->SetRightHave(false, false);
//
//            }
//
//        }
//        else
//        {
//            rightHaving = false;
//            leftHaving = false;
//            // 加速度の演算
//            powerY += GRAVITY;
//
//            // スピードの演算
//            transform_.position_.z += powerX;
//            transform_.position_.y -= powerY;
//            powerX *= 0.97;
//
//            // バウンドの判定
//            if (transform_.position_.y <= 0.0f)
//            {  // ボールが画面下に当たったら
//                transform_.position_.y = 0.0;
//                powerY = -powerY * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
//                height = powerY; //高さ保存
//                powerX *= 0.98;
//            }
//        }
//
//        //高さ＆移動が終わる
//        if (powerX <= 0.001 && abs(height) <= 0.021)
//        {
//            powerX = 0;
//            powerY = 0;
//            throwBall = false;
//        }
//
//    }
//
//    if (rightHaving == true)
//    {
//        transform_.position_ = pPlayer->GetPosition();
//        transform_.position_.x += 1;
//        transform_.position_.y += 2.5;
//    }
//
//    if (leftHaving == true)
//    {
//        transform_.position_ = pPlayer->GetPosition();
//        transform_.position_.x += -1;
//        transform_.position_.y += 2.5;
//    }
//
//    if (pPlayer->GetRightHave().first == false && pPlayer->GetRightHave().second == true)
//    {
//        pPlayer->SetRightHave(true, false);
//        rightHaving = pPlayer->GetRightHave().first;
//        leftHaving = pPlayer->GetRightHave().second;
//
//
//    }
//
//    /*if (pPlayer->GetRightHave().first == false && rightHaving == true)
//    {
//        rightHaving = false;
//        leftHaving = false;
//        pPlayer->SetRightHave(false, false);
//    }*/
//
//    //玉を持つ処理
//    //真ん中の照準から範囲決めてなんか飛ばしてクリック
//    if (Input::IsMouseButtonDown(0))
//    {
//
//    }
//
//    //デバッグ用
//    if (Input::IsKey(DIK_B))
//    {
//        int a = 0;
//    }
//
//    //左シフト押したら元に戻す、後で消す
//    if (Input::IsKeyDown(DIK_LSHIFT))
//    {
//        throwBall = false;
//        transform_.position_ = XMFLOAT3(3, 3, 3);
//    }
//}
//
////描画
//void WhiteBall::Draw()
//{
//    Model::SetTransform(hModel_, transform_);
//    Model::Draw(hModel_);
//}
//
////開放
//void WhiteBall::Release()
//{
//}
//
////当たり判定
//void WhiteBall::OnCollision(GameObject* pTarget)
//{
//    //弾に当たったとき
//    if (pTarget->GetObjectName() == "Basket")
//    {
//        //ゴールに入ったら得点＋消える
//        pBasket->WhiteCount();
//        KillMe();
//
//        //ゴールじゃなかったら落ちる
//
//    }
//    else if (pTarget->GetObjectName() == "Player" && pPlayer->GetRightHave().second == false)
//    {
//        //ボールを持っていないとき
//        if (pPlayer->GetRightHave().first == false)
//        {
//            //右手でボール持つ
//            pPlayer->SetRightHave(true, false);
//            rightHaving = true;
//        }
//        else
//        {
//            //左手でボール持つ
//            pPlayer->SetRightHave(true, true);
//            leftHaving = true;
//        }
//    }
//}