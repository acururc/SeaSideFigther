#pragma once

#include "CheckInput.h"
#include <iostream>
#include "CharaStatusDefine.h"
#include <vector>

//	定数の宣言
const int WINDOW_W = 640;	// 画面サイズ　横
const int WINDOW_H = 360;	// 画面サイズ　縦

class CManager;

// シーンの基底クラス
class CScene
{
protected:
	std::shared_ptr<CManager> manager;
	//CManager* manager;
public:

	CScene(std::shared_ptr<CManager> pManager) { manager = pManager; };
	virtual ~CScene() {};
	// 初期化
	virtual void Init() = 0;
	// 描画
	virtual void Update() = 0;
	// 更新
	virtual void Render() = 0;
};

class CManager
{
public:
	CheckInputKey checkInputKey;	// 入力関係
	//CScene* scene = nullptr;		// シーン

	std::shared_ptr<CScene> scene;	// シーン sharedポインターにしようとしてできなかった

	int winNum1P, winNum2P;			// 勝った数
	Sound sound;			// 全体的な音
	GameSound gameSound;	// ゲーム中の音
	int imageType[CHARA_MAX][IMAGE_MAX]{ 0 };
	int playGuideImage[KEY_MAX];

	CManager() 
	{
		winNum1P = 0;
		winNum2P = 0;
	};
	virtual ~CManager() 
	{
	};
	void Init();
	void Update()
	{
		checkInputKey.Update();
		scene->Update(); 
	};
	void Render() const { scene->Render(); };
	void Exit() const;

	// 角度をラジアン角に変える
	float rad(float rot)
	{
		return  rot * (float)DX_PI / 180.0f;
	};

};