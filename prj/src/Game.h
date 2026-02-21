#pragma once

#include <ctime>		// 標準C ライブラリ ヘッダー <time.h> をインクルードし、関連する名前を std 名前空間に追加します。
#include "DxLib.h"		// DxLib
#include "SceneManager.h"

// ゲーム関係
class CGame
{
	std::shared_ptr<CManager>manager;
	//CManager* manager = nullptr;

	// 更新処理
	void Update();

	// 画面更新関数
	void Render();

public:

	CGame() {

	}
	~CGame() {

	}

	// Dxlib関係
	// 初期化関数
	bool Init();

	// 更新関数
	void Loop();

	// 終了関数
	void End();
};