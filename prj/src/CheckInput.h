#pragma once

#include "dxlib.h"

class CheckInputKey
{
#define KEY_NUM 256

	// キーの入力状態
	char Key_buffer[KEY_NUM];
	// キーの押されている時間
	int key_push_fream[KEY_NUM];
public:

	// コンストラクター
	CheckInputKey()
	{
		for (int i = 0; i < KEY_NUM; ++i)
		{
			Key_buffer[i] = 0;
			key_push_fream[i] = 0;
		}
	}

	/// <summary>
	/// 入力状態を更新
	/// </summary>
	void Update();

	/// <summary>
	/// 押された瞬間を取得
	/// </summary>
	/// <param name="key"><確認したいキー/param>
	/// <returns><true:押された false:押されていない/returns>
	bool PushHitKey(int key) const;

	/// <summary>
	/// 離した瞬間を取得
	/// </summary>
	/// <param name="key"><確認したいキー/param>
	/// <returns><true:離された false:離されていない/returns>
	bool ReleaseHitKey(int key) const;
};