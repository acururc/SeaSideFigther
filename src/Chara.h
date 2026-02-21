#pragma once
#include "Game.h"
#include "CheckInput.h"
//#define DEBUG

// 当たり判定かやられ判定か
enum class judge {
	ATTACK,
	DEFEAT,
	JUDGE_MAX,
};

// 画像のステータス
struct imageInfo
{
	int num = 0;// 画像の数
	int w = 0;	// 画像の幅
	int h = 0;	// 画像の高さ
};
// ステータス
struct CharaStatus
{
	// 画像
	int nowImage = 0;			// 現在の画像
	int imageType[IMAGE_MAX]{ 0 };
	int imageCount = 0;			// 画像の番号
	int imageChengeNum = 0;		// アニメーションが切り替わった数
	int animeCount = 0;			// アニメーション時間
	// ステータス
	int whichPlayer = 0;		// どっちのプレイヤーか
	int damage = 0;				// 攻撃力
	int hp = 10000;				// HP	
	float x = 0;				// X座標
	float y = 0;				// Y座標
	int gX = 0;					// 画像のX座標
	int gY = 0;					// 画像のY座標
	Motion nowMotion = IDLE;	// 現在のモーション 
	bool turn = false;			// 反転してるか
	bool isAttack = false;		// 攻撃しているか
};

// 当たり判定の座標
struct HitBox
{
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;
};

// 弾のベース
class CShot
{
public:
	float x = 0;				// 座標
	float y = 0;				// 座標
	int* image = 0;			// 画像
	int damege = 0;
	HitBox hitBox{ 0 };
	bool turn = false;

	CShot() {}
	virtual ~CShot() {}


	virtual void Move() = 0;	// 動き
	virtual void Render() = 0;	// 描画
};

const int SHOT_MAX = 10;	// たまの上限

// キャラのベース
class CChara
{
protected:
	// くらい時の後ろに下がる速さ
	const float RECOIL_MOVE_SPEED_X = 3;
	// くらい時の上下の速さ
	const float RECOIL_MOVE_SPEED_Y = 5;

	// ガード時に後ろに下がる速さ
	const float BLOCK_MOVE_SPEED = 2;
public:
	// 入力関係
	CheckInputKey checkInputKey;

	// ステータス
	CharaStatus charaStatus{ 0 };			// キャラのステータス
	imageInfo imageInfo[IMAGE_MAX]{ 0 };	// 画像の情報

	CShot* shot[SHOT_MAX]{ nullptr };
	//std::vector<std::shared_ptr<CShot>> shot;

	HitBox hitBox[(int)judge::JUDGE_MAX]{ 0 };

	CChara()
	{
	};
	virtual ~CChara() {};

	//初期化処理
	virtual void Init() = 0;
	// 更新処理
	virtual void Update(float enemyX) = 0;
	// 描画処理
	virtual void Render() = 0;

	// 攻撃用関数
	virtual void Idle() = 0;
	virtual void Crouch() = 0;
	virtual void Walk() = 0;
	virtual void Jump() = 0;
	virtual void FrontJump() = 0;
	virtual void BackJump() = 0;
	virtual void Block() = 0;
	virtual void Punch() = 0;
	virtual void Kick() = 0;
	virtual void Hadou() = 0;
	virtual void Syoryu() = 0;
	virtual void Recoil() = 0;
	virtual void Ko() = 0;

	// 攻撃を受ける
	virtual void TakeDamage(Motion attackType, int argDamage) = 0;

	// HPが0になった時の処理
	void HpReg(int *argVoice);
};