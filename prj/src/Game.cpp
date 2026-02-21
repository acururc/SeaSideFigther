#include "Game.h"
#include "Title.h"

void CGame::Update()
{
	manager->Update();
}

void CGame::Render()
{
	manager->Render();
}

bool CGame::Init()
{
	// このクラスがnullptrにされてたら処理しない
	if (this == nullptr)
	{
		return false;
	}

	// シーンの管理システム
	manager = std::make_shared<CManager>();
	manager->Init();

	manager->scene = std::make_shared<CTitle>(manager, &manager->sound);

	// ログの書き出しを無効化
	SetOutApplicationLogValidFlag(FALSE);	// ログの書き出しを無効化

	// ウィンドウモードの設定
	ChangeWindowMode(TRUE);					// ウインドウモードを有効化

	// ウィンドウサイズとカラービットの設定
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	// ウィンドウのタイトル
	SetMainWindowText("DxLib Template");

	// 背景色の設定
	SetBackgroundColor(128, 128, 128);

	// ウィンドウ描画モード設定
	SetDrawScreen(DX_SCREEN_BACK);			// 裏画面に描画する



	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;						// エラーが起きたら直ちに終了
	}

	return true;
}

void CGame::Loop()
{
	while (ProcessMessage() == 0)
	{
		// リフレッシュレートを設定するための処理
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

		// マウスカーソル表示設定
		SetMouseDispFlag(TRUE);

		// printfDxの初期化
		clsDx();

		// 画面上の描画を初期化（画面を消去）
		ClearDrawScreen();

		// 更新処理
		this->Update();

		// 描画処理
		this->Render();
		// リフレッシュレートが一定になるまで待つ処理
		while (clock() < check_fps) {}

		// 裏画面の描画を表に反映
		ScreenFlip();

	}
}

void CGame::End()
{
	manager->Exit();
	// ＤＸライブラリ使用の終了処理
	DxLib_End();							// ＤＸライブラリ使用の終了処理
}