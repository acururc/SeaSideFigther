#include "InGame.h"
#include <vector>

void CInGame::Init()
{
	SetFontSize(60);
	for (int i = 0; i < GAME_BG_MAX; ++i)
	{
		sprintf_s(bgImageStr, "data/background/1sr9m6p202rnexGaI1L1de_%d.png", i);
		bgImage[i] = LoadGraph(bgImageStr);
	}
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

void CInGame::Start()
{
	--time;
	// 文字列とともにFIGHT
	if (time == 60)
	{
		PlaySoundMem(gameSound->fight, DX_PLAYTYPE_BACK);
	}
	// 試合開始
	else if (time == 0)
	{
		time = 60 * 99 - 1; // 試合時間を99.59から始める
		gameState = GAME_PLAY;
	}
}

void CInGame::Update()
{
	// BGMが鳴りやんだらループ
	if (CheckSoundMem(gameSound->bgm) == false)
	{
		PlaySoundMem(gameSound->bgm, DX_PLAYTYPE_BACK);
	}
	// 背景を動かす
	++bgCount;
	if (bgCount % 10 == 0)
	{
		bgIndex++;
		if (bgIndex == GAME_BG_MAX)
		{
			bgIndex = 0;
		}
	}
	// ゲームが始まる前
	if (gameState == GAME_START)
	{
		Start();
	}
	// ゲーム中
	else if (gameState == GAME_PLAY)
	{
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

		//// プレイヤー１の玉の当たり判定
		//if (!playerChara[(int)PlayerNum::PLAYER_1]->shot.empty())
		//{
		//	for (auto i = playerChara[(int)PlayerNum::PLAYER_1]->shot.size() - 1; i >= 0; --i)
		//	{
		//		// インデックス付きの変数は少し重いから置き換える
		//		auto s = playerChara[(int)PlayerNum::PLAYER_1]->shot[i];

		//		// キャラと弾（弾の判定, やられ判定）
		//		if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->hitBox, playerChara[(int)PlayerNum::PLAYER_2]->hitBox[(int)judge::DEFEAT]))
		//		{
		//			playerChara[(int)PlayerNum::PLAYER_2]->TakeDamage(HADOU, playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->damege);
		//			auto t = std::move(playerChara[(int)PlayerNum::PLAYER_1]->shot[i]);
		//			playerChara[(int)PlayerNum::PLAYER_1]->shot.pop_back();
		//		}
		//	}
		//}

		//// プレイヤー２の玉の当たり判定
		//if (!playerChara[(int)PlayerNum::PLAYER_2]->shot.empty())
		//{
		//	for (auto i = playerChara[(int)PlayerNum::PLAYER_2]->shot.size() - 1; i >= 0; --i)
		//	{
		//		// インデックス付きの変数は少し重いから置き換える
		//		auto s = playerChara[(int)PlayerNum::PLAYER_2]->shot[i];

		//		// キャラと弾（弾の判定, やられ判定）
		//		if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->hitBox, playerChara[(int)PlayerNum::PLAYER_1]->hitBox[(int)judge::DEFEAT]))
		//		{
		//			playerChara[(int)PlayerNum::PLAYER_1]->TakeDamage(HADOU, playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->damege);
		//			auto t = std::move(playerChara[(int)PlayerNum::PLAYER_2]->shot[i]);
		//			playerChara[(int)PlayerNum::PLAYER_2]->shot.pop_back();
		//		}
		//	}
		//}
		//// キャラと弾（やられ判定, 弾の判定）
		//if (playerChara[(int)PlayerNum::PLAYER_1]->shot[i] != nullptr && playerChara[(int)PlayerNum::PLAYER_2]->shot[i] != nullptr)
		//{
		//	if (GetHitDetection(playerChara[(int)PlayerNum::PLAYER_1]->shot[i]->hitBox, playerChara[(int)PlayerNum::PLAYER_2]->shot[i]->hitBox))
		//	{
		//		delete playerChara[(int)PlayerNum::PLAYER_1]->shot[i];
		//		playerChara[(int)PlayerNum::PLAYER_1]->shot[i] = nullptr;
		//		delete playerChara[(int)PlayerNum::PLAYER_2]->shot[i];
		//		playerChara[(int)PlayerNum::PLAYER_2]->shot[i] = nullptr;
		//	}
		//}

		// HPがなくなったら終了
		if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp <= 0 && playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp <= 0)
		{
			// ドロー
			manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::MAX, &manager->sound);
		}
		else if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp <= 0 || playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp <= 0)
		{
			// どちらかがやられた瞬間に音を流す
			if (koTime == 0)
			{
				PlaySoundMem(gameSound->ko, DX_PLAYTYPE_BACK);
			}
			++koTime;
			if (koTime >= 60 * 4)
			{
				// 音止める
				if (CheckSoundMem(gameSound->bgm))
				{
					StopSoundMem(gameSound->bgm);
				}

				// どっちがやられてるか
				if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.nowMotion == KO)
				{
					manager->winNum2P++;
					manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::PLAYER_2, &manager->sound);
				}
				else if (playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.nowMotion == KO)
				{
					manager->winNum1P++;
					manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::PLAYER_1, &manager->sound);
				}
			}
		}
		// タイムアップ
		else if (time == 0)
		{
			// 音止める
			if (CheckSoundMem(gameSound->bgm))
			{
				StopSoundMem(gameSound->bgm);
			}

			// HPの量
			if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp == playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp)
			{
				// どろー
				manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::MAX, &manager->sound);
			}
			else if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp > playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp)
			{
				manager->winNum1P++;
				manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::PLAYER_1, &manager->sound);
			}
			else if (playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp < playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp)
			{
				manager->winNum2P++;
				manager->scene = std::make_shared<CEnd>(manager, charaType[(int)PlayerNum::PLAYER_1], charaType[(int)PlayerNum::PLAYER_2], (int)PlayerNum::PLAYER_2, &manager->sound);
			}
		}
		else
		{
			--time;
		}
	}
}

void CInGame::Render()
{
	int strWidth = 0;
	// 背景描画
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 2, 0, bgImage[bgIndex], true);
	// HP描画
	// HPによって色を変える
	int color[(int)PlayerNum::MAX]{ 0 };
	for (int i = 0; i < (int)PlayerNum::MAX; ++i)
	{
		// 6000以上だったら緑
		if (playerChara[i]->charaStatus.hp >= 6000)
		{
			color[i] = GetColor(0, 255, 0);
		}
		// 3000以上だったら黄色
		else if (playerChara[i]->charaStatus.hp >= 3000)
		{
			color[i] = GetColor(255, 255, 0);
		}
		else
		{
			// それ以下だったら赤色
			color[i] = GetColor(255, 0, 0);
		}
	}

	// 中
	DrawFillBox(WINDOW_W / 2 - HP_BOX_OFFSET_X - playerChara[(int)PlayerNum::PLAYER_1]->charaStatus.hp / HP_DIV_NUM, HP_BOX_OFFSET_Y, WINDOW_W / 2 - HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, color[(int)PlayerNum::PLAYER_1]);
	DrawFillBox(WINDOW_W / 2 + HP_BOX_OFFSET_X, HP_BOX_OFFSET_Y, WINDOW_W / 2 + HP_BOX_OFFSET_X + playerChara[(int)PlayerNum::PLAYER_2]->charaStatus.hp / HP_DIV_NUM, HP_BOX_OFFSET_Y + HP_BOX_OFFSET_H, color[(int)PlayerNum::PLAYER_2]);
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
		// KOっていう文字列
		if (playerChara[i]->charaStatus.nowMotion == KO)
		{
			SetFontSize(200);
			strWidth = GetDrawStringWidth("K.O.", (int)strlen("K.O."));
			DrawString(WINDOW_W / 2 - strWidth / 2, WINDOW_H / 2 - INGAME_STR_OFFSET, "K.O.", GetColor(255, 255, 255));
			SetFontSize(60);
		}
	}

	// カウントダウン
	if (gameState == GAME_START)
	{
		// ゲーム開始時
		SetFontSize(200);
		if (time / 60 != 0)
		{
			strWidth = GetDrawFormatStringWidth("%d", time / 60);
			DrawFormatString(WINDOW_W / 2 - strWidth / 2, WINDOW_H / 2 - INGAME_STR_OFFSET, GetColor(255, 255, 255), "%d", time / 60);
		}
		else
		{
			strWidth = GetDrawStringWidth("FIGHT", (int)strlen("FIGHT"));
			DrawString(WINDOW_W / 2 - strWidth / 2, WINDOW_H / 2 - INGAME_STR_OFFSET, "FIGHT", GetColor(255, 255, 0));
		}
		SetFontSize(60);
	}
	else if (gameState == GAME_PLAY)
	{
		// ゲーム中
		strWidth = GetDrawFormatStringWidth("%02d", time / 60 + 1);
		DrawFormatString(WINDOW_W / 2 - strWidth / 2, GAME_TIME_OFFSET, GetColor(255, 255, 255), "%02d", time / 60 + 1);
	}
}
// 矩形同士の当たり判定
bool CInGame::GetHitDetection(HitBox box1, HitBox box2)
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

// プレイヤー同士の当たったときの処理
void CInGame::PlayerCollision(CChara& argChara1, CChara& argChara2)
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
	// お互いに半分ずつ押し返す
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
