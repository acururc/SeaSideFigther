#include "Dxlib.h"
#include "Ryu.h"
#include "Game.h"

void CRyu::Init()
{
	// 初期座標と1P2Pの識別
	if (charaStatus.whichPlayer == 1)
	{
		charaStatus.x = WINDOW_W / 4 * 1;
		charaStatus.y = IDLE_POS;
	}
	else if (charaStatus.whichPlayer == 2)
	{
		charaStatus.x = WINDOW_W / 4 * 3;
		charaStatus.y = IDLE_POS;
		charaStatus.turn = true;
	}

	// 画像
	shotImage = LoadGraph("data/Ryu/shot.png"); // 球

	charaStatus.nowImage = charaStatus.imageType[IDLE];	// 最初はアイドル状態から
	// 画像の情報
	imageInfo[IDLE].num = 4;						// 分割数
	imageInfo[IDLE].w = 200 / imageInfo[IDLE].num;	// 分割された幅
	imageInfo[IDLE].h = 84;							// 高さ
	imageInfo[CROUCH].num = 1;
	imageInfo[CROUCH].w = 42;
	imageInfo[CROUCH].h = 56;
	imageInfo[WALK].num = 5;
	imageInfo[WALK].w = 250 / imageInfo[WALK].num;
	imageInfo[WALK].h = 84;
	imageInfo[JUMP].num = 2;
	imageInfo[JUMP].w = 88 / imageInfo[JUMP].num;
	imageInfo[JUMP].h = 100;
	imageInfo[FRONTJUMP].num = 6;
	imageInfo[FRONTJUMP].w = 50;
	imageInfo[FRONTJUMP].h = 120;
	imageInfo[BACKJUMP].num = imageInfo[FRONTJUMP].num;
	imageInfo[BACKJUMP].w = imageInfo[FRONTJUMP].w;
	imageInfo[BACKJUMP].h = imageInfo[FRONTJUMP].h;
	imageInfo[BLOCK].num = 1;
	imageInfo[BLOCK].w = 50 / imageInfo[BLOCK].num;
	imageInfo[BLOCK].h = 84;
	imageInfo[PUNCH].num = 5;
	imageInfo[PUNCH].w = 45;
	imageInfo[PUNCH].h = 88;
	imageInfo[KICK].num = 5;
	imageInfo[KICK].w = 50;
	imageInfo[KICK].h = 57;
	imageInfo[HADOU].num = 4;
	imageInfo[HADOU].w = 72;
	imageInfo[HADOU].h = 78;
	imageInfo[SYORYU].num = 5;
	imageInfo[SYORYU].w = 47;
	imageInfo[SYORYU].h = 140;
	imageInfo[RECOIL_PUNCH].num = 3;
	imageInfo[RECOIL_PUNCH].w = 50;
	imageInfo[RECOIL_PUNCH].h = 85;
	imageInfo[RECOIL_HADOU].num = 4;
	imageInfo[RECOIL_HADOU].w = 50;
	imageInfo[RECOIL_HADOU].h = 85;
	imageInfo[RECOIL_SYORYU].num = 1;
	imageInfo[RECOIL_SYORYU].w = 74;
	imageInfo[RECOIL_SYORYU].h = 45;
	imageInfo[KO].num = 4;
	imageInfo[KO].w = 60;
	imageInfo[KO].h = 124;
}

void CRyu::Update(float enemyX)
{
	checkInputKey.Update();
	// 画像用時間は常に動かす
	charaStatus.imageCount++;

	//// vectorの中身が1つでもあったら
	//if (!shot.empty()) {
	//	for (auto i = shot.size() - 1; i >= 0; --i) {

	//		// インデックス付きの変数は少し重いから置き換える
	//		auto s = shot[i];

	//		if (s->x - 30 >= WINDOW_W || s->x + 30 <= 0 || charaStatus.nowMotion == KO)
	//		{
	//			auto t = std::move(shot[i]);
	//			shot.pop_back();
	//		}
	//	}
	//}

	// 球の処理
	for (int i = 0; i < SHOT_MAX; ++i)
	{
		// 球が存在していたら
		if (shot[i] != nullptr)
		{
			shot[i]->Move();
			// 球が外に出るかキャラがやられたら消す
			if (shot[i]->x - 30 >= WINDOW_W || shot[i]->x + 30 <= 0 || charaStatus.nowMotion == KO)
			{
				delete shot[i];
				shot[i] = nullptr;
			}
		}
	}

	// 今のモーション
	switch (charaStatus.nowMotion)
	{
	case IDLE:		this->Idle();
		// 相手と自分の位置によって向き変える
		if (enemyX > charaStatus.x)
		{
			charaStatus.turn = false;
		}
		else
		{
			charaStatus.turn = true;
		}
		break;
	case CROUCH:		this->Crouch();
		// 相手と自分の位置によって向き変える
		if (enemyX > charaStatus.x)
		{
			charaStatus.turn = false;
		}
		else
		{
			charaStatus.turn = true;
		}
		break;
	case WALK:		this->Walk();
		// 相手と自分の位置によって向き変える
		if (enemyX > charaStatus.x)
		{
			charaStatus.turn = false;
		}
		else
		{
			charaStatus.turn = true;
		}
		break;
	case JUMP:		this->Jump();		break;
	case FRONTJUMP:	this->FrontJump();	break;
	case BACKJUMP:	this->BackJump();	break;
	case BLOCK:		this->Block();		break;
	case PUNCH:		this->Punch();		break;
	case KICK:		this->Kick();		break;
	case HADOU:		this->Hadou();		break;
	case SYORYU:	this->Syoryu();		break;
	case RECOIL:	this->Recoil();		break;
	case KO:		this->Ko();		break;
	case IMAGE_MAX:	break;
	default: break;
	}

	HpReg(&voice->uwa);
}

void CRyu::Render()
{
	//SetDrawBright(255, 100, 100);
	//DrawRectRotaGraphF(charaStatus.x - 100, charaStatus.y, charaStatus.gX, charaStatus.gY, imageInfo[charaStatus.nowMotion].w, imageInfo[charaStatus.nowMotion].h, 2.5, 0, charaStatus.nowImage, true);
	//SetDrawBright(100, 100, 255);
	//DrawRectRotaGraphF(charaStatus.x + 100, charaStatus.y, charaStatus.gX, charaStatus.gY, imageInfo[charaStatus.nowMotion].w, imageInfo[charaStatus.nowMotion].h, 2.5, 0, charaStatus.nowImage, true);
	//SetDrawBright(255, 255, 255);

	// キャラの描画
	DrawRectRotaGraphF(charaStatus.x, charaStatus.y, charaStatus.gX, charaStatus.gY, imageInfo[charaStatus.nowMotion].w, imageInfo[charaStatus.nowMotion].h, 2.5, 0, charaStatus.nowImage, true, charaStatus.turn);
	// 球の処理
	for (int i = 0; i < SHOT_MAX; ++i)
	{
		// 球が存在していたら
		if (shot[i] != nullptr)
		{
			shot[i]->Render();
		}
	}
	// DEBAGがあればあたり判定表示
#ifdef DEBUG

	// 判定範囲の描画
	// 攻撃中なら二個描画
	if (charaStatus.isAttack == TRUE)
	{
		for (int i = 0; i < (int)judge::JUDGE_MAX; ++i)
		{
			int judgeColor = GetColor(0, 255, 0);
			if (i == (int)judge::ATTACK)
			{
				judgeColor = GetColor(255, 0, 0);
			}
			DrawBoxAA(hitBox[i].x, hitBox[i].y, hitBox[i].x + hitBox[i].w, hitBox[i].y + hitBox[i].h, judgeColor, false);
		}
	}
	else
	{
		DrawBoxAA(hitBox[(int)judge::DEFEAT].x, hitBox[(int)judge::DEFEAT].y, hitBox[(int)judge::DEFEAT].x + hitBox[(int)judge::DEFEAT].w, hitBox[(int)judge::DEFEAT].y + hitBox[(int)judge::DEFEAT].h, GetColor(0, 255, 0), false);
	}

#endif // DEBUG

}

void CRyu::Exit() const
{
	DeleteGraph(shotImage);
}

void CRyu::Idle()
{
	// 当たり判定の設定
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - IDLE_HITBOX_X;
	hitBox[(int)judge::DEFEAT].y = charaStatus.y - IDLE_HITBOX_Y;
	hitBox[(int)judge::DEFEAT].w = IDLE_HITBOX_W;
	hitBox[(int)judge::DEFEAT].h = IDLE_HITBOX_H;

	// アニメーション
	if (charaStatus.imageCount % IDLE_ANIME_COUNT == 0)
	{
		charaStatus.gX += imageInfo[IDLE].w;

		// アニメーションのループ
		if (charaStatus.gX >= imageInfo[IDLE].w * imageInfo[IDLE].num)
		{
			charaStatus.gX = 0;
		}
	}

	// しゃがみ状態に切り替え
	if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_S) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_DOWN))
	{
		charaStatus.nowImage = charaStatus.imageType[CROUCH];
		charaStatus.nowMotion = CROUCH;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = CROUCH_POS;
		hitBox[(int)judge::DEFEAT].w = CROUCH_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = CROUCH_HITBOX_H;
	}
	// 歩く状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_D) || charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_A) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_LEFT) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_RIGHT))
	{
		charaStatus.nowImage = charaStatus.imageType[WALK];
		charaStatus.nowMotion = WALK;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
	}
	// ジャンプ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_W) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_UP))
	{
		charaStatus.nowImage = charaStatus.imageType[JUMP];
		charaStatus.nowMotion = JUMP;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
	}
	// パンチ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_U) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD3))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[PUNCH].w = 45;
		charaStatus.nowImage = charaStatus.imageType[PUNCH];
		charaStatus.nowMotion = PUNCH;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.damage = PUNCH_DAMAGE;
		charaStatus.isAttack = true;
	}
	// 波動拳
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_Y) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[HADOU].w = 72;
		charaStatus.nowImage = charaStatus.imageType[HADOU];
		charaStatus.nowMotion = HADOU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.isAttack = true;
	}
	// 昇竜拳に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_T) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[SYORYU].w = 47;
		charaStatus.nowImage = charaStatus.imageType[SYORYU];
		charaStatus.nowMotion = SYORYU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = SYORYU_POS;
		charaStatus.damage = SYORYU_DAMAGE;
		charaStatus.isAttack = true;
	}
}

void CRyu::Crouch()
{
	// 当たり判定の設定
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - CROUCH_HITBOX_X;
	hitBox[(int)judge::DEFEAT].y = charaStatus.y - CROUCH_HITBOX_Y;

	// キック状態に切り替え
	if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_U) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD3))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[KICK].w = 45;
		charaStatus.nowImage = charaStatus.imageType[KICK];
		charaStatus.nowMotion = KICK;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.damage = KICK_DAMAGE;
		charaStatus.isAttack = true;
		charaStatus.y = KICK_POS;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - KICK_HITBOX_Y;
		hitBox[(int)judge::DEFEAT].w = KICK_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = KICK_HITBOX_H;
	}
	// 波動拳
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_Y) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[HADOU].w = 72;
		charaStatus.nowImage = charaStatus.imageType[HADOU];
		charaStatus.nowMotion = HADOU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.isAttack = true;
		charaStatus.y = IDLE_POS;
		hitBox[(int)judge::DEFEAT].w = HADOU_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = HADOU_HITBOX_H;
	}
	// 昇竜拳に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_T) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[SYORYU].w = 47;
		charaStatus.nowImage = charaStatus.imageType[SYORYU];
		charaStatus.nowMotion = SYORYU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = SYORYU_POS;
		charaStatus.damage = SYORYU_DAMAGE;
		charaStatus.isAttack = true;
		hitBox[(int)judge::DEFEAT].w = SYORYU_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = SYORYU_HITBOX_H;
	}
	// しゃがみ状態を保持
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_S) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_DOWN))
	{

	}
	// 歩く状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_D) || charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_A) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_LEFT) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_RIGHT))
	{
		charaStatus.nowImage = charaStatus.imageType[WALK];
		charaStatus.nowMotion = WALK;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = IDLE_POS;
	}
	// ジャンプ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_W) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_UP))
	{
		charaStatus.nowImage = charaStatus.imageType[JUMP];
		charaStatus.nowMotion = JUMP;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = IDLE_POS;
	}
	// 何も押されなかったらアイドル状態に
	else
	{
		charaStatus.nowImage = charaStatus.imageType[IDLE];
		charaStatus.nowMotion = IDLE;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.y = IDLE_POS;
	}
}

void CRyu::Walk()
{
	// 当たり判定の設定
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - IDLE_HITBOX_X;
	hitBox[(int)judge::DEFEAT].y = charaStatus.y - IDLE_HITBOX_Y;
	hitBox[(int)judge::DEFEAT].w = IDLE_HITBOX_W;
	hitBox[(int)judge::DEFEAT].h = IDLE_HITBOX_H;

	// アニメーション
	if (charaStatus.imageCount % WALK_ANIME_COUNT == 0)
	{
		charaStatus.gX += imageInfo[WALK].w;

		// アニメーションのループ
		if (charaStatus.gX >= imageInfo[WALK].w * imageInfo[WALK].num)
		{
			charaStatus.gX = 0;
		}
	}

	// パンチ状態に切り替え
	if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_U) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD3))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[PUNCH].w = 45;
		charaStatus.nowImage = charaStatus.imageType[PUNCH];
		charaStatus.nowMotion = PUNCH;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.damage = PUNCH_DAMAGE;
		charaStatus.isAttack = true;
	}
	// 波動拳に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_Y) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[HADOU].w = 72;
		charaStatus.nowImage = charaStatus.imageType[HADOU];
		charaStatus.nowMotion = HADOU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.isAttack = true;
	}
	// 昇竜拳に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_T) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		PlaySoundMem(voice->attack, DX_PLAYTYPE_BACK);
		imageInfo[SYORYU].w = 47;
		charaStatus.nowImage = charaStatus.imageType[SYORYU];
		charaStatus.nowMotion = SYORYU;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = SYORYU_POS;
		charaStatus.damage = SYORYU_DAMAGE;
		charaStatus.isAttack = true;
	}
	// 前ジャンプ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP))
	{
		imageInfo[FRONTJUMP].w = 50;
		charaStatus.nowImage = charaStatus.imageType[FRONTJUMP];
		charaStatus.nowMotion = FRONTJUMP;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
	}
	// 後ろジャンプ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP))
	{
		imageInfo[BACKJUMP].w = 50;
		charaStatus.nowImage = charaStatus.imageType[BACKJUMP];
		charaStatus.nowMotion = BACKJUMP;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
	}
	// しゃがみ状態に切り替え
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_S) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_DOWN))
	{
		charaStatus.nowImage = charaStatus.imageType[CROUCH];
		charaStatus.nowMotion = CROUCH;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		charaStatus.y = CROUCH_POS;
		hitBox[(int)judge::DEFEAT].w = CROUCH_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = CROUCH_HITBOX_H;
	}
	// 右に移動
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_D) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (charaStatus.turn)
		{
			charaStatus.x += BACK_SPEED;
		}
		else
		{
			charaStatus.x += WALK_SPEED;
		}
		if (charaStatus.x + IDLE_HITBOX_X >= WINDOW_W)
		{
			charaStatus.x = WINDOW_W - IDLE_HITBOX_X;
		}
	}
	// 左に移動
	else if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_A) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_LEFT))
	{
		if (charaStatus.turn)
		{
			charaStatus.x -= WALK_SPEED;
		}
		else
		{
			charaStatus.x -= BACK_SPEED;
		}
		if (charaStatus.x - IDLE_HITBOX_X <= 0)
		{
			charaStatus.x = IDLE_HITBOX_X;
		}
	}
	else
	{
		// 何も押されなかったらアイドル状態に
		charaStatus.nowImage = charaStatus.imageType[IDLE];
		charaStatus.nowMotion = IDLE;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
	}
}

void CRyu::Jump()
{
	// アニメーションが1枚目の時は上に
	switch (charaStatus.imageChengeNum)
	{
	case 0:
		charaStatus.y -= JUMP_SPEED;

		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - JUMPUP_HITBOX_X;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - JUMPUP_HITBOX_Y;
		hitBox[(int)judge::DEFEAT].w = JUMPUP_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = JUMPUP_HITBOX_H;
		break;
		// アニメーションが2枚目の時は下に
	case 1:
		charaStatus.y += JUMP_SPEED;

		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - JUMPDOWN_HITBOX_X;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - JUMPDOWN_HITBOX_Y;
		hitBox[(int)judge::DEFEAT].w = JUMPDOWN_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = JUMPDOWN_HITBOX_H;
		break;
	}

	// アニメーション
	if (charaStatus.imageCount % JUMP_ANIME_COUNT == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[JUMP].w;

		// アニメーションが最後まで行ったら
		if (charaStatus.gX >= imageInfo[JUMP].w * imageInfo[JUMP].num)
		{
			// アイドル状態に
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
		}
	}
}

void CRyu::FrontJump()
{
	// アニメーション
	if (charaStatus.imageCount % MOVEJUMP_ANIME_COUNT == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[FRONTJUMP].w;

		if (charaStatus.gX >= imageInfo[FRONTJUMP].w * imageInfo[FRONTJUMP].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
		}

		// アニメーションの移動
		switch (charaStatus.imageChengeNum)
		{
		case 0: imageInfo[FRONTJUMP].w = 50; break;
		case 1: imageInfo[FRONTJUMP].w = 75; break;
		case 2: imageInfo[FRONTJUMP].w = 45; break;
		case 3:	imageInfo[FRONTJUMP].w = 90; break;
		case 4: imageInfo[FRONTJUMP].w = 60; break;
		case 5: imageInfo[FRONTJUMP].w = 46; break;
		}
	}

	// 移動と当たり判定
	charaStatus.x += MOVEJUMP_SPEEDX;
	if (charaStatus.x + 40 >= WINDOW_W)
	{
		charaStatus.x = WINDOW_W - 40;
	}
	switch (charaStatus.imageChengeNum)
	{
	case 0:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 140;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 220;
		break;
	case 1:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 80;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 90;
		hitBox[(int)judge::DEFEAT].w = 150;
		hitBox[(int)judge::DEFEAT].h = 90;
		break;
	case 2:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 140;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 160;
		break;
	case 3:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 80;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 120;
		hitBox[(int)judge::DEFEAT].w = 150;
		hitBox[(int)judge::DEFEAT].h = 90;
		break;
	case 4:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 150;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 150;
		break;
	case 5:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 150;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 200;
		break;
	}
}

void CRyu::BackJump()
{
	// アニメーション
	charaStatus.animeCount = MOVEJUMP_ANIME_COUNT;

	if (charaStatus.imageCount % charaStatus.animeCount == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[BACKJUMP].w;

		if (charaStatus.gX >= imageInfo[BACKJUMP].w * imageInfo[BACKJUMP].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
		}
		// アニメーションの移動
		switch (charaStatus.imageChengeNum)
		{
		case 0: imageInfo[BACKJUMP].w = 50; break;
		case 1: imageInfo[BACKJUMP].w = 75; break;
		case 2: imageInfo[BACKJUMP].w = 45; break;
		case 3:	imageInfo[BACKJUMP].w = 90; break;
		case 4: imageInfo[BACKJUMP].w = 60; break;
		case 5: imageInfo[BACKJUMP].w = 46; break;
		}
	}
	// 移動と当たり判定
	// 移動
	charaStatus.x -= MOVEJUMP_SPEEDX;
	if (charaStatus.x - 40 <= 0)
	{
		charaStatus.x = 40;
	}
	switch (charaStatus.imageChengeNum)
	{
	case 0:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 140;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 220;
		break;
	case 1:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 80;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 90;
		hitBox[(int)judge::DEFEAT].w = 150;
		hitBox[(int)judge::DEFEAT].h = 90;
		break;
	case 2:
		// キャラの移動
		charaStatus.y -= MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 140;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 160;
		break;
	case 3:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 80;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 120;
		hitBox[(int)judge::DEFEAT].w = 150;
		hitBox[(int)judge::DEFEAT].h = 90;
		break;
	case 4:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 150;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 150;
		break;
	case 5:
		// キャラの移動
		charaStatus.y += MOVEJUMP_SPEEDY;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 150;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 200;
		break;
	}
}

void CRyu::Block()
{
	// アニメーション
	charaStatus.animeCount++;

	// ガード時に後ろに下げる
	if (charaStatus.turn)
	{
		charaStatus.x += BLOCK_MOVE_SPEED;
		if (charaStatus.x + IDLE_HITBOX_X >= WINDOW_W)
		{
			charaStatus.x = WINDOW_W - IDLE_HITBOX_X;
		}
		else
		{
			hitBox[(int)judge::DEFEAT].x += 1;
		}
	}
	else
	{
		charaStatus.x -= BLOCK_MOVE_SPEED;
		if (charaStatus.x - IDLE_HITBOX_X <= 0)
		{
			charaStatus.x = IDLE_HITBOX_X;
		}
		else
		{
			hitBox[(int)judge::DEFEAT].x += 1;
		}
	}
	// 当たり判定を合わせる
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - IDLE_HITBOX_X;

	// 戻す
	if (charaStatus.animeCount >= BLOCK_ANIME_COUNT)
	{
		// しゃがみ状態に戻す
		if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_S) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_DOWN))
		{
			charaStatus.nowImage = charaStatus.imageType[CROUCH];
			charaStatus.nowMotion = CROUCH;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.y = CROUCH_POS;
		}
		// 立ち状態の戻す
		else
		{
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.y = IDLE_POS;
		}
	}
}

void CRyu::Punch()
{
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - PUNCH_HITBOX_X;
	hitBox[(int)judge::DEFEAT].y = charaStatus.y - PUNCH_HITBOX_Y;

	// アニメーション
	if (charaStatus.imageCount % PUNCH_ANIME_COUNT == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[PUNCH].w;

		if (charaStatus.gX >= imageInfo[PUNCH].w * imageInfo[PUNCH].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.damage = 0;
			charaStatus.isAttack = false;
			hitBox[(int)judge::ATTACK].x = -100;
			hitBox[(int)judge::ATTACK].y = -100;
			hitBox[(int)judge::ATTACK].w = -100;
			hitBox[(int)judge::ATTACK].h = -100;
		}
	}
	// アニメーションの移動
	switch (charaStatus.imageChengeNum)
	{
	case 0: imageInfo[PUNCH].w = 45; break;
	case 1: imageInfo[PUNCH].w = 55; break;
	case 2: imageInfo[PUNCH].w = 78;
		// 当たり判定
		if (charaStatus.turn)
		{
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 110;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 75;
			hitBox[(int)judge::ATTACK].w = 80;
			hitBox[(int)judge::ATTACK].h = 30;
		}
		else
		{
			hitBox[(int)judge::ATTACK].x = charaStatus.x + 30;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 75;
			hitBox[(int)judge::ATTACK].w = 80;
			hitBox[(int)judge::ATTACK].h = 30;
		}
		break;
	case 3:	imageInfo[PUNCH].w = 55;
		// 当たり判定
		hitBox[(int)judge::ATTACK].x = -100;
		hitBox[(int)judge::ATTACK].y = -100;
		hitBox[(int)judge::ATTACK].w = -100;
		hitBox[(int)judge::ATTACK].h = -100;
		break;
	case 4: imageInfo[PUNCH].w = 47; break;
	}
}

void CRyu::Kick()
{
	hitBox[(int)judge::DEFEAT].x = charaStatus.x - KICK_HITBOX_X;
	hitBox[(int)judge::DEFEAT].y = charaStatus.y - KICK_HITBOX_Y;

	// アニメーション
	if (charaStatus.imageCount % KICK_ANIME_COUNT == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[KICK].w;

		if (charaStatus.gX >= imageInfo[KICK].w * imageInfo[KICK].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[CROUCH];
			charaStatus.nowMotion = CROUCH;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.damage = 0;
			charaStatus.isAttack = false;
			hitBox[(int)judge::ATTACK].x = -100;
			hitBox[(int)judge::ATTACK].y = -100;
			hitBox[(int)judge::ATTACK].w = -100;
			hitBox[(int)judge::ATTACK].h = -100;
		}
	}
	// アニメーションの移動
	switch (charaStatus.imageChengeNum)
	{
	case 0: imageInfo[KICK].w = 50; break;
	case 1: imageInfo[KICK].w = 81;
		// 当たり判定
		if (charaStatus.turn)
		{
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 120;
			hitBox[(int)judge::ATTACK].y = charaStatus.y + 30;
			hitBox[(int)judge::ATTACK].w = 80;
			hitBox[(int)judge::ATTACK].h = 30;
		}
		else
		{
			hitBox[(int)judge::ATTACK].x = charaStatus.x + 40;
			hitBox[(int)judge::ATTACK].y = charaStatus.y + 30;
			hitBox[(int)judge::ATTACK].w = 80;
			hitBox[(int)judge::ATTACK].h = 30;
		}
		break;
	case 2: imageInfo[KICK].w = 55;
		// 当たり判定
		hitBox[(int)judge::ATTACK].x = -100;
		hitBox[(int)judge::ATTACK].y = -100;
		hitBox[(int)judge::ATTACK].w = -100;
		hitBox[(int)judge::ATTACK].h = -100;
		break;
	case 3:	imageInfo[KICK].w = 54; break;
	case 4: imageInfo[KICK].w = 47; break;
	}
}

void CRyu::Hadou()
{
	// アニメーション時間
	int animeCount = HADOU_ANIME_COUNT;

	// 後隙を増やす
	if (charaStatus.imageChengeNum == 3)
	{
		animeCount = HADOU_GAP;
	}

	// アニメーション
	if (charaStatus.imageCount % animeCount == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[HADOU].w;

		if (charaStatus.gX >= imageInfo[HADOU].w * imageInfo[HADOU].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.isAttack = false;
			hitBox[(int)judge::ATTACK].x = -100;
			hitBox[(int)judge::ATTACK].y = -100;
			hitBox[(int)judge::ATTACK].w = -100;
			hitBox[(int)judge::ATTACK].h = -100;
		}
		// 球の発射
		if (charaStatus.imageChengeNum == 2)
		{
			if (charaStatus.turn)
			{
				/*		auto c = std::make_shared<CHadou>(charaStatus.x - 100, charaStatus.y - 30, &shotImage, charaStatus.turn);
						shot.push_back(c);*/

				for (int i = 0; i < SHOT_MAX; ++i)
				{
					if (shot[i] == nullptr)
					{
						shot[i] = new CHadou(charaStatus.x - 100, charaStatus.y - 30, &shotImage, charaStatus.turn);
						break;
					}
				}
			}
			else
			{
				/*	auto c = std::make_shared<CHadou>(charaStatus.x + 100, charaStatus.y - 30, &shotImage, charaStatus.turn);
					shot.push_back(c);*/
				for (int i = 0; i < SHOT_MAX; ++i)
				{
					if (shot[i] == nullptr)
					{
						shot[i] = new CHadou(charaStatus.x + 100, charaStatus.y - 30, &shotImage, charaStatus.turn);
						break;
					}
				}
			}
		}
	}
	// アニメーションの移動
	switch (charaStatus.imageChengeNum)
	{
	case 0: imageInfo[HADOU].w = 72;

		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
		break;
	case 1: imageInfo[HADOU].w = 74;

		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
		break;
	case 2: imageInfo[HADOU].w = 87;
		// 反転してもいいように
		if (charaStatus.turn)
		{
			// 当たり判定の設定
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 90;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
			// 当たり判定が飛び出さないよう
			if (charaStatus.x + hitBox[(int)judge::DEFEAT].w / 2 >= WINDOW_W)
			{
				hitBox[(int)judge::DEFEAT].x = charaStatus.x - hitBox[(int)judge::DEFEAT].w / 2;
			}
			else
			{
				hitBox[(int)judge::DEFEAT].w = 140;
			}
			hitBox[(int)judge::DEFEAT].h = 200;
		}
		else
		{
			// 当たり判定の設定
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 50;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
			// 当たり判定が飛び出さないよう
			if (charaStatus.x - hitBox[(int)judge::DEFEAT].w / 2 <= 0)
			{
				hitBox[(int)judge::DEFEAT].x = charaStatus.x - hitBox[(int)judge::DEFEAT].w / 2;
			}
			else
			{
				hitBox[(int)judge::DEFEAT].w = 140;
			}
			hitBox[(int)judge::DEFEAT].h = 200;
		}
		break;
	case 3:	imageInfo[HADOU].w = 71;
		// 反転してもいいように
		if (charaStatus.turn)
		{
			// 当たり判定の設定
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 90;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;

			// 当たり判定が飛び出さないよう
			if (charaStatus.x + hitBox[(int)judge::DEFEAT].w / 2 >= WINDOW_W)
			{
				hitBox[(int)judge::DEFEAT].x = charaStatus.x - hitBox[(int)judge::DEFEAT].w / 2;
			}

		}
		else
		{
			// 当たり判定の設定
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 50;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
		}
		break;
	}
}

void CRyu::Syoryu()
{
	// アニメーション
	if (charaStatus.imageCount % SYORYU_ANIME_COUNT == 0)
	{
		charaStatus.imageChengeNum++;	// アニメーションの移動を数える

		charaStatus.gX += imageInfo[SYORYU].w;

		if (charaStatus.gX >= imageInfo[SYORYU].w * imageInfo[SYORYU].num)
		{
			// 戻す
			charaStatus.nowImage = charaStatus.imageType[IDLE];
			charaStatus.nowMotion = IDLE;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.y = IDLE_POS;
			charaStatus.damage = 0;
			charaStatus.isAttack = false;
			hitBox[(int)judge::ATTACK].x = -100;
			hitBox[(int)judge::ATTACK].y = -100;
			hitBox[(int)judge::ATTACK].w = -100;
			hitBox[(int)judge::ATTACK].h = -100;
		}
	}
	// アニメーションの移動
	switch (charaStatus.imageChengeNum)
	{
	case 0:
		imageInfo[SYORYU].w = 47;
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 30;
		break;
	case 1:
		imageInfo[SYORYU].w = 55;
		// 反転してもいいように
		if (charaStatus.turn)
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 80;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 30;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 100;
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 30;
		}
		else
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x + 30;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 30;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 100;
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 30;
		}
		break;
	case 2: imageInfo[SYORYU].w = 46;
		// 反転してもいいように
		if (charaStatus.turn)
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 40;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 110;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 130;
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 30;
		}
		else
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 10;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 110;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 130;
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - 30;
		}
		break;
	case 3:	imageInfo[SYORYU].w = 49;
		// 反転してもいいように
		if (charaStatus.turn)
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 40;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 160;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 130;
		}
		else
		{
			// 攻撃判定
			hitBox[(int)judge::ATTACK].x = charaStatus.x - 10;
			hitBox[(int)judge::ATTACK].y = charaStatus.y - 160;
			hitBox[(int)judge::ATTACK].w = 50;
			hitBox[(int)judge::ATTACK].h = 130;
		}
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 100;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 200;
		break;
	case 4: imageInfo[SYORYU].w = 52;

		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 150;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 200;

		// 攻撃判定
		hitBox[(int)judge::ATTACK].x = -100;
		hitBox[(int)judge::ATTACK].y = -100;
		hitBox[(int)judge::ATTACK].w = -100;
		hitBox[(int)judge::ATTACK].h = -100;
		break;
	case 5: imageInfo[SYORYU].w = 51;
		// 当たり判定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - 40;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - 50;
		hitBox[(int)judge::DEFEAT].w = 80;
		hitBox[(int)judge::DEFEAT].h = 200;
		break;
	}
}

void CRyu::Recoil()
{
	// 食らったのが昇龍拳または空中なら
	if (charaStatus.animeCount == RECOIL_AIR)
	{
		if (charaStatus.turn)
		{
			// 後ろに下がる
			if (charaStatus.x + 50 >= WINDOW_W)
			{
				charaStatus.x = WINDOW_W - 50;
			}
			else
			{
				charaStatus.x += RECOIL_MOVE_SPEED_X;
				hitBox[(int)judge::DEFEAT].x += RECOIL_MOVE_SPEED_X;
			}
		}
		else
		{
			if (charaStatus.x - 50 <= 0)
			{
				charaStatus.x = 50;
			}
			else
			{
				charaStatus.x -= RECOIL_MOVE_SPEED_X;
				hitBox[(int)judge::DEFEAT].x -= RECOIL_MOVE_SPEED_X;
			}
		}
		// 上下に動く
		if (charaStatus.imageCount <= RECOIL_ANIME_COUNT)
		{
			charaStatus.y -= RECOIL_MOVE_SPEED_Y;
			hitBox[(int)judge::DEFEAT].y -= RECOIL_MOVE_SPEED_Y;
		}
		else
		{
			charaStatus.y += RECOIL_MOVE_SPEED_Y;
			hitBox[(int)judge::DEFEAT].y += RECOIL_MOVE_SPEED_Y;
			// 下まで落ちたら
			if (charaStatus.y > IDLE_POS)
			{
				// 戻す
				charaStatus.nowImage = charaStatus.imageType[IDLE];
				charaStatus.nowMotion = IDLE;
				charaStatus.imageCount = 0;
				charaStatus.gX = 0;
				charaStatus.imageChengeNum = 0;
				charaStatus.y = IDLE_POS;
			}
		}
	}
	else if (charaStatus.animeCount == RECOIL_GROUND)
	{
		// アニメーション
		if (charaStatus.imageCount % charaStatus.animeCount == 0)
		{
			charaStatus.gX += imageInfo[RECOIL].w;
			if (charaStatus.gX >= imageInfo[RECOIL].w * imageInfo[RECOIL].num)
			{
				// 戻す
				charaStatus.nowImage = charaStatus.imageType[IDLE];
				charaStatus.nowMotion = IDLE;
				charaStatus.imageCount = 0;
				charaStatus.gX = 0;
				charaStatus.imageChengeNum = 0;
			}
		}
	}
}

void CRyu::Ko()
{
	if (charaStatus.imageChengeNum != 3)
	{
		// キャラの移動
		if (charaStatus.turn)
		{
			charaStatus.x += 5;
			if (charaStatus.x + 100 >= WINDOW_W)
			{
				charaStatus.x = WINDOW_W - 100;
			}
		}
		else
		{
			charaStatus.x -= 5;
			if (charaStatus.x - 100 <= 0)
			{
				charaStatus.x = 100;
			}
		}
		if (charaStatus.imageChengeNum == 0)
		{
			charaStatus.y -= 6;
		}
		else
		{
			charaStatus.y += 2;
		}
	}

	// アニメーション
	if (charaStatus.imageCount % KO_ANIME_COUNT == 0)
	{
		if (charaStatus.imageChengeNum != 3)
		{
			charaStatus.imageChengeNum++;	// アニメーションの移動を数える
			charaStatus.gX += imageInfo[KO].w;
		}
		// アニメーションの移動
		switch (charaStatus.imageChengeNum)
		{
		case 0: imageInfo[KO].w = 60;
			break;
		case 1: imageInfo[KO].w = 63;
			break;
		case 2: imageInfo[KO].w = 75;
			break;
		case 3:	imageInfo[KO].w = 80;
			break;
		}
	}
}

void CRyu::TakeDamage(Motion attackType, int argDamage)
{
	if (attackType != PUNCH && attackType != KICK && attackType != HADOU && attackType != SYORYU || charaStatus.nowMotion == BLOCK || charaStatus.nowMotion == RECOIL)
	{
		return;
	}

	// 後ろに入力していたらガード
	if (charaStatus.nowMotion == IDLE || charaStatus.nowMotion == WALK)
	{
		// 下段はたちガードできない
		if (attackType != KICK)
		{
			// 反転してるとき
			if (charaStatus.turn)
			{
				if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_D) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_RIGHT))
				{
					charaStatus.nowImage = charaStatus.imageType[BLOCK];
					charaStatus.nowMotion = BLOCK;
					charaStatus.imageCount = 0;
					charaStatus.gX = 0;
					charaStatus.imageChengeNum = 0;
					charaStatus.animeCount = 0;
					charaStatus.hp -= argDamage / 5;
					return;
				}
			}
			else
			{
				if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_A) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_LEFT))
				{
					charaStatus.nowImage = charaStatus.imageType[BLOCK];
					charaStatus.nowMotion = BLOCK;
					charaStatus.imageCount = 0;
					charaStatus.gX = 0;
					charaStatus.imageChengeNum = 0;
					charaStatus.animeCount = 0;
					charaStatus.hp -= argDamage / 5;
					return;
				}
			}
		}
	}
	// 下入力してたらしゃがみガード
	if (charaStatus.nowMotion == CROUCH)
	{
		if (charaStatus.whichPlayer == 1 && CheckHitKey(KEY_INPUT_S) || charaStatus.whichPlayer == 2 && CheckHitKey(KEY_INPUT_DOWN))
		{
			charaStatus.nowImage = charaStatus.imageType[CROUCH_BLOCK];
			charaStatus.nowMotion = BLOCK;
			charaStatus.imageCount = 0;
			charaStatus.gX = 0;
			charaStatus.imageChengeNum = 0;
			charaStatus.animeCount = 0;
			charaStatus.hp -= argDamage / 5;
			return;
		}
	}

	// HPを減らしてボイスを流す
	charaStatus.hp -= argDamage;
	PlaySoundMem(voice->hit, DX_PLAYTYPE_BACK);

	// 地面にいるときに食らう
	if (charaStatus.nowMotion == IDLE || charaStatus.nowMotion == WALK || charaStatus.nowMotion == PUNCH || charaStatus.nowMotion == HADOU)
	{
		// くらった攻撃によってモーションを変える
		switch (attackType)
		{
		case PUNCH:
			charaStatus.nowImage = charaStatus.imageType[RECOIL_PUNCH];
			imageInfo[RECOIL].num = imageInfo[RECOIL_PUNCH].num;
			imageInfo[RECOIL].w = imageInfo[RECOIL_PUNCH].w;
			imageInfo[RECOIL].h = imageInfo[RECOIL_PUNCH].h;
			charaStatus.animeCount = RECOIL_GROUND;

			break;
		case HADOU:
			charaStatus.nowImage = charaStatus.imageType[RECOIL_HADOU];
			imageInfo[RECOIL].num = imageInfo[RECOIL_HADOU].num;
			imageInfo[RECOIL].w = imageInfo[RECOIL_HADOU].w;
			imageInfo[RECOIL].h = imageInfo[RECOIL_HADOU].h;
			charaStatus.animeCount = RECOIL_GROUND;
			break;
		case SYORYU: case KICK:
			charaStatus.nowImage = charaStatus.imageType[RECOIL_SYORYU];
			imageInfo[RECOIL].num = imageInfo[RECOIL_SYORYU].num;
			imageInfo[RECOIL].w = imageInfo[RECOIL_SYORYU].w;
			imageInfo[RECOIL].h = imageInfo[RECOIL_SYORYU].h;
			charaStatus.animeCount = RECOIL_AIR;

			// 当たり判定の設定
			hitBox[(int)judge::DEFEAT].x = charaStatus.x - AIR_RECOIL_HITBOX_X;
			hitBox[(int)judge::DEFEAT].y = charaStatus.y - AIR_RECOIL_HITBOX_Y;
			hitBox[(int)judge::DEFEAT].w = AIR_RECOIL_HITBOX_W;
			hitBox[(int)judge::DEFEAT].h = AIR_RECOIL_HITBOX_H;
			break;
		default:
			break;
		}
	}
	else
	{
		charaStatus.nowImage = charaStatus.imageType[RECOIL_SYORYU];
		imageInfo[RECOIL].num = imageInfo[RECOIL_SYORYU].num;
		imageInfo[RECOIL].w = imageInfo[RECOIL_SYORYU].w;
		imageInfo[RECOIL].h = imageInfo[RECOIL_SYORYU].h;
		charaStatus.animeCount = RECOIL_AIR;
		// 当たり判定の設定
		hitBox[(int)judge::DEFEAT].x = charaStatus.x - AIR_RECOIL_HITBOX_X;
		hitBox[(int)judge::DEFEAT].y = charaStatus.y - AIR_RECOIL_HITBOX_Y;
		hitBox[(int)judge::DEFEAT].w = AIR_RECOIL_HITBOX_W;
		hitBox[(int)judge::DEFEAT].h = AIR_RECOIL_HITBOX_H;
	}

	charaStatus.nowMotion = RECOIL;
	charaStatus.imageCount = 0;
	charaStatus.gX = 0;
	charaStatus.imageChengeNum = 0;
	hitBox[(int)judge::ATTACK].x = -100;
	hitBox[(int)judge::ATTACK].y = -100;
	hitBox[(int)judge::ATTACK].w = -100;
	hitBox[(int)judge::ATTACK].h = -100;
}

void CHadou::Move()
{
	if (turn)
	{
		x -= MOVE_SPEED;
		hitBox.x = x - hitBox.w / 2;
		hitBox.y = y - hitBox.h / 2;
	}
	else
	{
		x += MOVE_SPEED;
		hitBox.x = x - hitBox.w / 2;
		hitBox.y = y - hitBox.h / 2;
	}
}

void CHadou::Render()
{
	if (this != nullptr)
	{
		DrawRotaGraphF(x, y, 2, 0, *image, true, turn);

		// DEBAGがあればあたり判定表示
#ifdef DEBUG
		DrawBoxAA(hitBox.x, hitBox.y, hitBox.x + hitBox.w, hitBox.y + hitBox.h, GetColor(255, 0, 0), false);
#endif // DEBUG
	}
}
