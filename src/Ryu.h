#pragma once

#include "Chara.h"

class CHadou :public CShot
{
	const float MOVE_SPEED = 10;
public:

	CHadou(float argX, float argY, int* argImage, bool argTurn)
	{
		x = argX;
		y = argY;
		image = argImage;
		turn = argTurn;
		hitBox.w = 60;
		hitBox.h = 60;
		hitBox.x = x - hitBox.w / 2;
		hitBox.y = y - hitBox.h / 2;
		damege = 1500;
	}
	~CHadou()
	{
	}

	void Move();	// 動き
	void Render();	// 描画
};

class CRyu :public CChara
{
	// くらい判定
// IDLE状態
	const float IDLE_HITBOX_X = 40;
	const float IDLE_HITBOX_Y = 100;
	const float IDLE_HITBOX_W = 80;
	const float IDLE_HITBOX_H = 200;
	// しゃがみ状態
	const float CROUCH_HITBOX_X = 40;
	const float CROUCH_HITBOX_Y = 60;
	const float CROUCH_HITBOX_W = 80;
	const float CROUCH_HITBOX_H = 130;
	// JUMP状態の上がっているとき
	const float JUMPUP_HITBOX_X = 40;
	const float JUMPUP_HITBOX_Y = 100;
	const float JUMPUP_HITBOX_W = 80;
	const float JUMPUP_HITBOX_H = 200;
	// JUMP状態の下がっているとき
	const float JUMPDOWN_HITBOX_X = 40;
	const float JUMPDOWN_HITBOX_Y = 80;
	const float JUMPDOWN_HITBOX_W = 80;
	const float JUMPDOWN_HITBOX_H = 150;
	// パンチ状態の時
	const float PUNCH_HITBOX_X = 40;
	const float PUNCH_HITBOX_Y = 100;
	const float PUNCH_HITBOX_W = 80;
	const float PUNCH_HITBOX_H = 200;
	// キック状態の時
	const float KICK_HITBOX_X = 40;
	const float KICK_HITBOX_Y = 60;
	const float KICK_HITBOX_W = 80;
	const float KICK_HITBOX_H = 130;
	// 波動状態の時
	const float HADOU_HITBOX_X = 40;
	const float HADOU_HITBOX_Y = 100;
	const float HADOU_HITBOX_W = 80;
	const float HADOU_HITBOX_H = 200;
	// 昇竜状態の時
	const float SYORYU_HITBOX_X = 40;
	const float SYORYU_HITBOX_Y = 100;
	const float SYORYU_HITBOX_W = 80;
	const float SYORYU_HITBOX_H = 200;
	// 空中ぐらいのとき
	const float AIR_RECOIL_HITBOX_X = 70;
	const float AIR_RECOIL_HITBOX_Y = 30;
	const float AIR_RECOIL_HITBOX_W = 150;
	const float AIR_RECOIL_HITBOX_H = 70;

	// アニメーションの時間
	const int IDLE_ANIME_COUNT = 10;
	const int WALK_ANIME_COUNT = 10;
	const int JUMP_ANIME_COUNT = 25;
	const int MOVEJUMP_ANIME_COUNT = 7;
	const int BLOCK_ANIME_COUNT = 20;
	const int PUNCH_ANIME_COUNT = 7;
	const int KICK_ANIME_COUNT = 7;
	const int HADOU_ANIME_COUNT = 12;
	const int SYORYU_ANIME_COUNT = 7;
	const int RECOIL_ANIME_COUNT = 20;
	const int KO_ANIME_COUNT = 20;

	const float WALK_SPEED = 7.0f;			// 歩く速度
	const float BACK_SPEED = 5.0f;			// 後ろに歩く速度
	const float JUMP_SPEED = 10.0f;		// ジャンプ速度
	const float MOVEJUMP_SPEEDX = 7.0f;	// 動きジャンプ速度
	const float MOVEJUMP_SPEEDY = 10.0f;	// 動きジャンプ速度
	const int PUNCH_DAMAGE = 3500;		// パンチのダメージ
	const int KICK_DAMAGE = 2000;		// キックのダメージ
	const int SYORYU_DAMAGE = 2000;		// 昇竜のダメージ

	int shotImage = 0;	// たま画像
	CharaVoice* voice;

	const int RYU_HP_MAX = 10000;	// リュウのHPの最大

public:

	CRyu(CharaVoice* argVoice, int* argImage)
	{
		voice = argVoice;
		for (int i = 0; i < IMAGE_MAX; ++i)
		{
			charaStatus.imageType[i] = argImage[i];
			charaStatus.hp = RYU_HP_MAX;
		}
	};
	~CRyu()
	{
	};

	void Init();
	void Update(float enemyX);
	void Render();
	void Exit() const;

	void Idle();
	void Crouch();
	void Walk();
	void Jump();
	void FrontJump();
	void BackJump();
	void Block();
	void Punch();
	void Kick();
	void Hadou();
	void Syoryu();
	void Recoil();
	void Ko();

	void TakeDamage(Motion attackType, int argDamage);
};

// 波動後の後隙
constexpr auto HADOU_GAP = 75;