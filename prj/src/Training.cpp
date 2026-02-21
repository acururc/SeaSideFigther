#include "Training.h"
#include "Select.h"

void CTraining::Init()
{
	SetFontSize(25);
	// 背景をロード
	bgImage = LoadGraph("data/background/training.png");

	// プレイヤーキャラを登録
	for (int i = 0; i < (int)PlayerNum::MAX; ++i)
	{
		switch (charaType[i])
		{
		case RYU:
			playerChara[i] = new CRyu(&gameSound->voice, manager->imageType[RYU]);
			break;
		default:
			break;
		}
		playerChara[i]->charaStatus.whichPlayer = i + 1;	// 1P2P登録
		playerChara[i]->Init();
	}
}

void CTraining::Update()
{
	// BGMが鳴りやんだらループ
	if (CheckSoundMem(gameSound->bgm) == false)
	{
		PlaySoundMem(gameSound->bgm, DX_PLAYTYPE_BACK);
	}

	// プレイヤーのHPが削れていたら戻す
	for(int i = 0;i< (int)PlayerNum::MAX;++i)
	{
		if (playerChara[i]->charaStatus.hp != 10000 && playerChara[i]->charaStatus.nowMotion == IDLE)
		{
			playerChara[i]->charaStatus.hp = 10000;
		}
	}

	// プレイヤー更新
	playerChara[(int)PlayerNum::PLAYER_1]->Update(playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.x);
	playerChara[(int)PlayerNum::PLAYER_2]->Update(playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.x);

	// 当たり判定
	// キャラ同士（やられ判定, やられ判定)
	if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->hitBox[(int)judge::DEFEAT], playerChara[(int)PlayerNum::PLAYER_2]->hitBox[(int)judge::DEFEAT]))
	{
		PlayerCollision(*playerChara[(int)PlayerNum::PLAYER_1], *playerChara[(int)PlayerNum::PLAYER_2]);
	}
	// キャラ同士（攻撃判定, やられ判定）
	if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->hitBox[(int)judge::ATTACK], playerChara[(int)PlayerNum::PLAYER_2]->hitBox[(int)judge::DEFEAT]))
	{
		playerChara[(int)PlayerNum::PLAYER_2]->TakeDamage(playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.nowMotion, playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.damage);
	}
	// キャラ同士（やられ判定, 攻撃判定）
	if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->hitBox[(int)judge::DEFEAT], playerChara[(int)PlayerNum::PLAYER_2]->hitBox[(int)judge::ATTACK]))
	{
		playerChara[(int)PlayerNum::PLAYER_1]->TakeDamage(playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.nowMotion, playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.damage);
	}

	// たま
	for (int i = 0; i < SHOT_MAX; ++i)
	{
		// キャラと弾（弾の判定, やられ判定）
		if (playerChara[(int)PlayerNum::PLAYER_1]->shot[i] != nullptr)
		{
			if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->hitBox, playerChara[(int)PlayerNum::PLAYER_2]->hitBox[(int)judge::DEFEAT]))
			{
				playerChara[(int)PlayerNum::PLAYER_2]->TakeDamage(HADOU, playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->damege);
				delete playerChara[(int)PlayerNum::PLAYER_1]->shot[i];
				playerChara[(int)PlayerNum::PLAYER_1]->shot[i] = nullptr;
			}
		}
		// キャラと弾（やられ判定, 弾の判定）
		if (playerChara[(int)PlayerNum::PLAYER_2]->shot[i] != nullptr)
		{
			if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->hitBox[(int)judge::DEFEAT], playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->hitBox))
			{
				playerChara[(int)PlayerNum::PLAYER_1]->TakeDamage(HADOU, playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->damege);
				delete playerChara[(int)PlayerNum::PLAYER_2]->shot[i];
				playerChara[(int)PlayerNum::PLAYER_2]->shot[i] = nullptr;
			}
		}
		// キャラと弾（やられ判定, 弾の判定）
		if (playerChara[(int)PlayerNum::PLAYER_1]->shot[i] != nullptr && playerChara[(int)PlayerNum::PLAYER_2]->shot[i] != nullptr)
		{
			if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->hitBox, playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->hitBox))
			{
				delete playerChara[(int)PlayerNum::PLAYER_1]->shot[i];
				playerChara[(int)PlayerNum::PLAYER_1]->shot[i] = nullptr;
				delete playerChara[(int)PlayerNum::PLAYER_2]->shot[i];
				playerChara[(int)PlayerNum::PLAYER_2]->shot[i] = nullptr;
			}
		}
	}

	// セレクト画面に戻す
	if (manager->checkInputKey.PushHitKey(KEY_INPUT_RETURN))
	{
		// 音止める
		if (CheckSoundMem(gameSound->bgm))
		{
			StopSoundMem(gameSound->bgm);
		}

		manager->scene = std::make_shared<CSelect>(manager, &manager->sound);
	}
}

void CTraining::Render()
{
	// 背景描画
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 2, 0, bgImage, true);

	// HP描画
	// 中
	DrawFillBox(WINDOW_W / 2 - HP_BOX_OFFSET_X - playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp / HP_DIV_NUM, HP_BOX_OFFSET_Y, WINDOW_W / 2 - HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, GetColor(0, 255, 0));
	DrawFillBox(WINDOW_W / 2 + HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y, WINDOW_W / 2 + HP_BOX_OFFSET_X + playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp / HP_DIV_NUM, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, GetColor(0, 255, 0));
	// 外枠
	DrawLineBox(HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y, WINDOW_W / 2 - HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, GetColor(0, 0, 0));
	DrawLineBox(WINDOW_W / 2 + HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y, WINDOW_W - HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, GetColor(0, 0, 0));

	// キャラ描画
	for (int i = 0; i < (int)PlayerNum::MAX; ++i)
	{
		if (i == (int)PlayerNum::PLAYER_1)
		{
			playerChara[i]->Render();
		}
		if (i == (int)PlayerNum::PLAYER_2)
		{
			SetDrawBright(255, 0, 0);
			playerChara[i]->Render();
			SetDrawBright(255, 255, 255);
		}
	}

	// 説明が見やすいように
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawFillBox(PLAY_GUIDE_BOX_X, PLAY_GUIDE_BOX_Y, PLAY_GUIDE_BOX_X + PLAY_GUIDE_BOX_W, PLAY_GUIDE_BOX_Y + PLAY_GUIDE_BOX_H, GetColor(0, 128, 128));
	DrawFillBox(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W, PLAY_GUIDE_BOX_Y, WINDOW_W - PLAY_GUIDE_BOX_X, PLAY_GUIDE_BOX_Y + PLAY_GUIDE_BOX_H, GetColor(0, 128, 128));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 説明
	// 1P
	int strWidth = GetDrawStringWidth(str[0], (int)strlen(str[0]));	// 文字列のサイズを取得
	DrawString(PLAY_GUIDE_BOX_X + PLAY_GUIDE_BOX_W / 2 - strWidth / 2, PLAY_GUIDE_BOX_Y + 5, str[0], GetColor(255, 255, 255));
	DrawString(PLAY_GUIDE_BOX_X + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 1, str[2], GetColor(255, 255, 255));
	DrawString(PLAY_GUIDE_BOX_X + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 2, str[3], GetColor(255, 255, 255));
	DrawString(PLAY_GUIDE_BOX_X + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 3, str[4], GetColor(255, 255, 255));
	DrawString(PLAY_GUIDE_BOX_X + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 4, str[5], GetColor(255, 255, 255));

	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize, 0.05, 0, guideImage[KEY_A], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2 + imageSize, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize, 0.05, 0, guideImage[KEY_D], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 2, 0.05, 0, guideImage[KEY_W], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 3, 0.05, 0, guideImage[KEY_S], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2 + imageSize * 0, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_T], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2 + imageSize * 1, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_Y], true);
	DrawRotaGraph(PLAY_GUIDE_BOX_X + imageSize / 2 + imageSize * 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_U], true);

	// 2P
	strWidth = GetDrawStringWidth(str[1], (int)strlen(str[1]));	// 文字列のサイズを取得
	DrawString(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + PLAY_GUIDE_BOX_W / 2 - strWidth / 2, PLAY_GUIDE_BOX_Y + 5, str[1], GetColor(255, 255, 255));
	DrawString(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 1, str[2], GetColor(255, 255, 255));
	DrawString(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 2, str[3], GetColor(255, 255, 255));
	DrawString(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 3, str[4], GetColor(255, 255, 255));
	DrawString(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + GUIDE_STR_OFFSET, PLAY_GUIDE_BOX_Y + imageSize * 4, str[5], GetColor(255, 255, 255));

	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize, 0.05, 0, guideImage[KEY_ARROW], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2 + imageSize, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize, 0.05, manager->rad(180), guideImage[KEY_ARROW], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 2, 0.05, manager->rad(270), guideImage[KEY_ARROW], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 3, 0.05, manager->rad(90), guideImage[KEY_ARROW], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2 + imageSize * 0, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_NUMPAD1], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2 + imageSize * 1, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_NUMPAD2], true);
	DrawRotaGraph(WINDOW_W - PLAY_GUIDE_BOX_X - PLAY_GUIDE_BOX_W + imageSize / 2 + imageSize * 2, PLAY_GUIDE_BOX_Y + imageSize / 2 + imageSize * 4, 0.05, 0, guideImage[KEY_NUMPAD3], true);

	// 時間は無限
	SetFontSize(60);
	strWidth = GetDrawStringWidth("∞", (int)strlen("∞"));	// 文字列のサイズを取得
	DrawString(WINDOW_W / 2 - strWidth / 2, GAME_TIME_OFFSET, "∞", GetColor(255, 255, 255));
	SetFontSize(40);

	// エンターで戻るっていう文字列とその回るに箱を描画
	strWidth = GetDrawStringWidth("ENTERで戻る", (int)strlen("ENTERで戻る"));	// 文字列のサイズを取得
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawFillBox(WINDOW_W / 2 - strWidth / 2, WINDOW_H - RETURN_STR_OFFSET, WINDOW_W / 2 + strWidth / 2, WINDOW_H, GetColor(128, 128, 128));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(WINDOW_W / 2 - strWidth / 2, WINDOW_H - RETURN_STR_OFFSET, "ENTERで戻る", GetColor(255, 255, 0));
	SetFontSize(25);
}

bool CTraining::GetHitDetection(HitBox box1, HitBox box2)
{
	// 矩形１の左辺と矩形２の右辺の確認
	if (box1.x <= box2.x + box2.w)
	{
		// 矩形１の右辺と矩形２の左辺の確認
		if (box1.x + box1.w >= box2.x)
		{
			// 矩形１の上辺と矩形２の下辺の確認
			if (box1.y <= box2.y + box2.h)
			{
				// 矩形１の下辺と矩形２の上辺の確認
				if (box1.y + box1.h >= box2.y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CTraining::PlayerCollision(CChara& argChara1, CChara& argChara2)
{
	// プレイヤー同士の重なり幅
	float overlapWidth = min(argChara1.hitBox[(int)judge::DEFEAT].x + argChara1.hitBox[(int)judge::DEFEAT].w, argChara2.hitBox[(int)judge::DEFEAT].x + argChara2.hitBox[(int)judge::DEFEAT].w) - max(argChara1.hitBox[(int)judge::DEFEAT].x, argChara2.hitBox[(int)judge::DEFEAT].x);


	// 左右に押し出されないように
	if (argChara1.charaStatus.x - argChara1.hitBox[(int)judge::DEFEAT].w / 2 <= 0)
	{
		argChara1.charaStatus.x = 0 + argChara1.hitBox[(int)judge::DEFEAT].w / 2;
		argChara2.charaStatus.x += overlapWidth;
	}
	else if (argChara2.charaStatus.x - argChara2.hitBox[(int)judge::DEFEAT].w / 2 <= 0)
	{
		argChara2.charaStatus.x = 0 + argChara2.hitBox[(int)judge::DEFEAT].w / 2;
		argChara1.charaStatus.x += overlapWidth;
	}
	else if (argChara1.charaStatus.x + argChara1.hitBox[(int)judge::DEFEAT].w / 2 >= WINDOW_W)
	{
		argChara1.charaStatus.x = WINDOW_W - argChara1.hitBox[(int)judge::DEFEAT].w / 2;
		argChara2.charaStatus.x -= overlapWidth;
	}
	else if (argChara2.charaStatus.x + argChara2.hitBox[(int)judge::DEFEAT].w / 2 >= WINDOW_W)
	{
		argChara2.charaStatus.x = WINDOW_W - argChara2.hitBox[(int)judge::DEFEAT].w / 2;
		argChara1.charaStatus.x -= overlapWidth;
	}
	// 左右に押し返す：お互いに半分ずつ
	else if (argChara1.charaStatus.x < argChara2.charaStatus.x) {
		argChara1.charaStatus.x -= overlapWidth / 1.5f;
		argChara2.charaStatus.x += overlapWidth / 1.5f;
	}
	else if (argChara1.charaStatus.x > argChara2.charaStatus.x)
	{
		argChara1.charaStatus.x += overlapWidth / 1.5f;
		argChara2.charaStatus.x -= overlapWidth / 1.5f;
	}
}
