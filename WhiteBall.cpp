#include "WhiteBall.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//コンストラクタ
WhiteBall::WhiteBall(GameObject* parent)
    :GameObject(parent, "WhiteBall")
{
    hModel_ = -1;
}

//デストラクタ
WhiteBall::~WhiteBall()
{
}

//初期化
void WhiteBall::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;

    radius = 0;
    height = 1;
    powerZ = 0;
    powerY = 0;
    throwBall = false;
    rightHaving = false;
    leftHaving = false;

    //モデルデータのロード
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(0, 0, 0);

    do
    {
        transform_.position_.x = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
        transform_.position_.z = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
       
        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius >= CIRCLE_RANGE || radius < NEAR_GOAL);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALLSIZE);
    AddCollider(collision);
}

//更新
void WhiteBall::Update()
{
    //スペースキーを押したら
    if ((Input::IsKeyDown(DIK_SPACE) || throwBall == true))
    {
        //スペースを押してるとき
        if (Input::IsKey(DIK_SPACE)&& (rightHaving == true || leftHaving == true))
        {
            if (rightHaving == true)
            {
                powerZ += POWER;
                //あとで向いてる角度にする
                powerY -= POWER;
                throwBall = true;
            }
        }
        else if (Input::IsKeyUp(DIK_SPACE))
        {
            //ボールを2個もってたら
            if (pPlayer1->GetHand().second == true)
            {
                pPlayer1->SetHand(false, true);
            }
            else
            {
                pPlayer1->SetHand(false, false);
            }
            //powerY + Player1の向いてる角度
        }
        else
        {
            rightHaving = false;
            leftHaving = false;
            // 加速度の演算
            powerY += GRAVITY;

            // スピードの演算
            transform_.position_.z += powerZ;
            transform_.position_.y -= powerY;
            powerZ *= RESISTANCE;//抵抗

            // バウンドの判定
            if (transform_.position_.y <= 0.0f)
            {  // ボールが下に当たったら
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
                height = powerY; //高さ保存
                powerZ *= RESISTANCE;//抵抗
            }
            
            //移動が終わる
            if (powerZ <= END_MOVE)
            {
                powerZ = 0;
                powerY = 0;
                throwBall = false;
            }
        }
    }

    //右手で持ってたら
    if (rightHaving == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //左手で持ってたら
    if (leftHaving == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //ボールを右手に持ちかえる
    if (pPlayer1->GetHand().first == false && leftHaving == true)
    {
        rightHaving = true;
        leftHaving = false;
        pPlayer1->SetHand(true, false);
    }

    //玉を持つ処理
    //真ん中の照準から範囲決めてなんか飛ばしてクリック
    if (Input::IsMouseButtonDown(0))
    {

    }

    //デバッグ用
    if (Input::IsKey(DIK_B))
    {
       int a = 0;
    }

    
    ////円の範囲外なら消える
    radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (radius > CIRCLE_OUTSIDE)
    {
        KillMe();
    }
}

//描画
void WhiteBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void WhiteBall::Release()
{
}

//当たり判定
void WhiteBall::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Basket")
    {
        //ゴールに入ったら得点＋消える
        pBasket->WhiteCount();
        KillMe();
        
        //ゴールじゃなかったら落ちる

    }
    else if (pTarget->GetObjectName() == "Player1" && pPlayer1->GetHand().second == false && throwBall == false)
    {
        //ボールを持っていないとき
        if (pPlayer1->GetHand().first == false)
        {
            //右手でボール持つ
            pPlayer1->SetHand(true,false);
            rightHaving = true;
        }
        else
        {
            //左手でボール持つ
            pPlayer1->SetHand(true, true);
            leftHaving = true;
        }
    }
}

