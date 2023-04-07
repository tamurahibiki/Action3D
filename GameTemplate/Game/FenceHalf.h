#pragma once
#include"IBgActor.h"
/// <summary>
/// ハーフフェンスクラス
/// </summary>
class FenceHalf :public IBgActor
{
public:
	FenceHalf();
	~FenceHalf();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};
