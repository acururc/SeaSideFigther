#include "Select.h"
#include "InGame.h"
#include "Title.h"
#include "Training.h"

void CSelect::Init()
{
	SetFontSize(60);
	bgImage[0] = LoadGraph("data/select/training.png");
	bgImage[1] = LoadGraph("data/select/fight.png");

	guideBgImage[0] = LoadGraph("data/select/A.png");
	guideBgImage[1] = LoadGraph("data/select/D.png");
	guideBgImage[2] = LoadGraph("data/select/ARROW.png");
	guideBgImage[3] = LoadGraph("data/select/ENTER.png");

	for (int i = 0; i < SELECT_MAX; ++i)
	{
		strWidth[i] = GetDrawStringWidth(str[i], (int)strlen(str[i]));
		strY[i] = (float)(WINDOW_H / 2);
	}
}

void CSelect::Update()
{
	// 音を鳴らす
	// 二重にならないようになっているか確認
	if (CheckSoundMem(sound->titleBgm) == FALSE)
	{
		PlaySoundMem(sound->titleBgm, DX_PLAYTYPE_BACK, TRUE);
	}

	// 文字列を動かす
	if (strWitchMove == STR_UP)
	{
		diffY += STR_MOVE_ACCS;
		if (diffY == STR_LIMIT)
			strWitchMove = STR_DOWN;
	}
	if (strWitchMove == STR_DOWN)
	{
		diffY -= STR_MOVE_ACCS;
		if (diffY == -STR_LIMIT)
			strWitchMove = STR_UP;
	}
	strY[nowSelect] += diffY;

	// トレーニング
	if (nowSelect == SELECT_TRAINING)
	{
		// 対戦に変える
		if (manager->checkInputKey.PushHitKey(KEY_INPUT_RIGHT) || manager->checkInputKey.PushHitKey(KEY_INPUT_D))
		{
			strY[nowSelect] = (float)(WINDOW_H / 2);
			nowSelect = SELECT_FIGHT; 
		}


		// エンターでトレーニングに行く
		if (manager->checkInputKey.PushHitKey(KEY_INPUT_RETURN))
		{
			// 音がなっていたら消す
			if (CheckSoundMem(sound->titleBgm))
			{
				StopSoundMem(sound->titleBgm);
			}

			manager->scene = std::make_shared<CTraining>(manager, RYU, RYU, &manager->gameSound, manager->playGuideImage);
			return;
		}
	}
	// 対戦
	else if (nowSelect == SELECT_FIGHT)
	{
		// トレーニングに変える
		if (manager->checkInputKey.PushHitKey(KEY_INPUT_LEFT) || manager->checkInputKey.PushHitKey(KEY_INPUT_A))
		{
			strY[nowSelect] = (float)(WINDOW_H / 2);
			nowSelect = SELECT_TRAINING;
		}

		// エンターで対戦に行く
		if (manager->checkInputKey.PushHitKey(KEY_INPUT_RETURN))
		{
			// 音がなっていたら消す
			if (CheckSoundMem(sound->titleBgm))
			{
				StopSoundMem(sound->titleBgm);
			}

			manager->scene = std::make_shared<CInGame>(manager, RYU, RYU, &manager->gameSound);
			return;
		}
	}
	// タイトルに戻る
	if (manager->checkInputKey.PushHitKey(KEY_INPUT_ESCAPE))
	{
		manager->scene = std::make_shared<CTitle>(manager, &manager->sound);
	}
}

void CSelect::Render()
{
	// トレーニングに行く画像
	DrawRotaGraph(WINDOW_W / 4 * 1 - 200, WINDOW_H / 2, 1.7, 0, bgImage[0], false);
	DrawRotaGraph(WINDOW_W / 4 * 3 + 200 + 5, WINDOW_H / 2, 1.7, 0, bgImage[1], false);

	// 選ばれていない方の画像を薄く
	if (nowSelect == SELECT_TRAINING)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
		DrawBox(WINDOW_W / 2, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (nowSelect == SELECT_FIGHT)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
		DrawBox(0, 0, WINDOW_W / 2, WINDOW_H, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	// 文字列を描画
	for (int i = 0; i < SELECT_STR_MAX; ++i)
	{
		float x = (float)(WINDOW_W / 4 * (i * 2 + 1) - strWidth[i] / 2);
		float y = strY[i];
		DrawStringF(x, y, str[i], GetColor(255, 255, 255));
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawFillBox(0, WINDOW_H - 50, 400, WINDOW_H, GetColor(128, 128, 128));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// ガイド
	SetFontSize(30);
	DrawRotaGraph(25, WINDOW_H - 25, 0.05, 0, guideBgImage[0], true);
	DrawRotaGraph(75, WINDOW_H - 25, 0.05, 0, guideBgImage[1], true);
	DrawRotaGraph(125, WINDOW_H - 25, 0.05, 0, guideBgImage[2], true, true);
	DrawRotaGraph(175, WINDOW_H - 25, 0.05, 0, guideBgImage[2], true);
	DrawString(200, WINDOW_H - 43, guideStr[0], GetColor(255, 255, 255));
	DrawRotaGraph(300, WINDOW_H - 25, 0.05, 0, guideBgImage[3], true);
	DrawString(325, WINDOW_H - 43, guideStr[1], GetColor(255, 255, 255));
	SetFontSize(60);
	// 真ん中に線
	DrawLine(WINDOW_W / 2, 0, WINDOW_W / 2, WINDOW_H, GetColor(255, 255, 0));
}
