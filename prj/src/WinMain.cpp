// =======================================
//  ライブラリ読込
// =======================================
#include "Game.h"

// ------------------------------
// WinMain
// ------------------------------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	// =======================================
	//  初期化処理
	// =======================================
	std::unique_ptr<CGame>gamePtr(new CGame());
	gamePtr->Init();

	// Init()がfalseで帰ってきたらその時点で終了
	if (gamePtr->Init() == false)
	{
		return -1;
	}

	// ------------------------------
	//  ゲームループ
	// ------------------------------
	gamePtr->Loop();

	// =======================================
	//  終了処理
	// =======================================
	gamePtr->End();

	// ソフトの終了
	return 0;
}