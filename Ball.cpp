//#include "Ball.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//
////コンストラクタ
//Ball::Ball(GameObject* parent)
//    :GameObject(parent, "Ball")
//{
//    transform_.position_.y = 0;
//    radius = 0.0f;
//    height = 0.0f;
//    throwBall = false;
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
//    
//    //memset(hModel_, -1, sizeof(hModel_));
//}
//
////デストラクタ
//Ball::~Ball()
//{
//}
//
//void Ball::ThrowBall(int buttonCode_, float angle_, float powerX_, float powerY_)
//{
//    //// 加速度の演算
//    //powerY_ += GRAVITY;
//    //// スピードの演算
//    //transform_.position_.z += powerX_;
//    //transform_.position_.y -= powerY_;
//    //powerX_ *= 0.97;
//
//    //// バウンドの判定
//    //if (transform_.position_.y <= 0.0f)
//    //{  // ボールが画面下に当たったら
//    //    transform_.position_.y = 0.0;
//    //    powerY_ = -powerY_ * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
//    //    height = powerY_; //高さ保存
//    //}
//
//    if (Input::IsKeyDown(buttonCode_) || throwBall == true)
//    {
//        throwBall = true;
//        //スペースを押したとき
//        if (Input::IsKey(buttonCode_))
//        {
//            powerX_ += 0.01;
//            //あとで向いてる角度にする
//            powerY_ -= 0.01;
//
//            //ボールを持ってたら
//            //if ()
//            //{
//            //throwBall = true;
//            //}
//        }
//        else if (Input::IsKeyUp(buttonCode_))
//        {
//            //powerY -= playerAngleY;//プレイヤーの角度
//        }
//        else
//        {
//            // 加速度の演算
//            powerY_ += GRAVITY;
//
//            // スピードの演算
//            transform_.position_.z += powerX_;
//            transform_.position_.y -= powerY_;
//            powerX_ *= 0.97;
//
//            // バウンドの判定
//            if (transform_.position_.y <= 0.0f)
//            {  // ボールが画面下に当たったら
//                transform_.position_.y = 0.0;
//                powerY_ = -powerY_ * 0.6;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
//                height = powerY_; //高さ保存
//            }
//        }
//
//        //高さ＆移動が終わる
//        if (powerX_ <= 0.001 && abs(height) <= 0.025)
//        {
//            powerX_ = 0;
//            powerY_ = 0;
//            throwBall = false;
//        }
//    }
//}
//
////
//////初期化
////void Ball::Initialize()
////{
////    std::string fileName[] = { "RedBall.fbx","WhiteBall.fbx" };
////    //モデルデータのロード
////    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
////    {
////        hModel_[i] = Model::Load(fileName[i]);
////        assert(hModel_[i] >= 0);
////    }
////
////    transform_.position_ = XMFLOAT3(3, 0, 3);
////
////    ////for (int i = 0; i < 0; i++)
////    //{
////    //    transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //    transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //    /*if (radius > 360 || radius < 15)
////    //    {
////    //        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //        i--;
////    //    }*/
////    //}
////
////    do
////    {
////        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
////    } while (radius > 360 || radius < 15);
////
////    //当たり判定
////    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
////    AddCollider(collision);
////
////
////    radius = 0;
////    height = 1;
////    powerX = 0;
////    powerY = 0;
////    playerAngleY = 0;
////    throwBall = false;
////    down = false;
////}
////
//////更新
////void Ball::Update()
////{
////    if (Input::IsKeyDown(DIK_SPACE) || throwBall == true)
////    {
////        throwBall = true;
////        //スペースを押したとき
////        if (Input::IsKey(DIK_SPACE))
////        {
////            //子クラス
////            powerX += 0.01;
////            //あとで向いてる角度にする
////            powerY -= 0.01;
////
////            //ボールを持ってたら
////            //if ()
////            //{
////            //throwBall = true;
////            //}
////        }
////        else if (Input::IsKeyUp(DIK_SPACE))
////        {
////            //子クラス
////            //powerY -= playerAngleY;//プレイヤーの角度
////        }
////        else
////        {
////            // 加速度の演算
////            powerY += gravity;
////
////            // スピードの演算
////            transform_.position_.z += powerX;
////            transform_.position_.y -= powerY;
////            powerX *= 0.97;
////
////            // バウンドの判定
////            if (transform_.position_.y <= 0.0f)
////            {  // ボールが画面下に当たったら
////                transform_.position_.y = 0.0;
////                powerY = -powerY * 0.6;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
////                height = powerY; //高さ保存
////            }
////        }
////
////        //高さ＆移動が終わる
////        if (powerX <= 0.001 && abs(height) <= 0.021)
////        {
////            powerX = 0;
////            powerY = 0;
////            throwBall = false;
////        }
////    }
////
////    //玉を持つ処理
////    //真ん中の照準から範囲決めてなんか飛ばしてクリック
////    if (Input::IsMouseButtonDown(0))
////    {
////
////    }
////
////    //デバッグ用
////    if (Input::IsKeyDown(DIK_A))
////    {
////        int a = 0;
////    }
////
////    //左シフト押したら元に戻す、後で消す
////    if (Input::IsKeyDown(DIK_LSHIFT))
////    {
////        throwBall = false;
////        transform_.position_ = XMFLOAT3(3, 3, 3);
////    }
////}
////
//////描画
////void Ball::Draw()
////{
////    //for (int i = 0; i < ballCount; i++)
////    //{
////    //    if (i < ballCount / 2)
////    //    {
////    //        radius = (trans[i].position_.x * trans[i].position_.x) + (trans[i].position_.z * trans[i].position_.z);
////    //        //transform_.position_ = XMFLOAT3(i, 3, i);
////    //        //transform_.position_.x = rand() % 20 - 10;
////    //        //円の範囲だけ表示
////    //        if (radius <= 360 && radius > 15)
////    //        {
////    //            Model::SetTransform(hModel_[0], trans[i]);
////    //            Model::Draw(hModel_[0]);
////    //        }
////    //        else
////    //        {
////    //            trans[i].position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //            trans[i].position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //            i--;
////    //        }
////
////    //    }
////    //    else
////    //    {
////    //        radius = (trans[i].position_.x * trans[i].position_.x) + (trans[i].position_.z * trans[i].position_.z);
////    //        //transform_.position_ = XMFLOAT3(i-40, 3, i-40);
////    //        //transform_.position_.x = rand() % 20 - 10;
////    //        if (radius <= 360 && radius > 15)
////    //        {
////    //            Model::SetTransform(hModel_[1], trans[i]);
////    //            Model::Draw(hModel_[1]);
////    //        }
////    //        else
////    //        {
////    //            trans[i].position_.x = rand() % 30 - 15;
////    //            trans[i].position_.z = rand() % 30 - 15;
////    //            i--;
////    //        }
////
////    //    }
////    //}
////    Model::SetTransform(hModel_[1], transform_);
////    Model::Draw(hModel_[1]);
////}
////
//////開放
////void Ball::Release()
////{
////}
////
//////当たり判定
////void Ball::OnCollision(GameObject* pTarget)
////{
////    //powerX *= 0.98;
////}