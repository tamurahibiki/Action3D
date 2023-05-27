#pragma once
#include <CollisionObject.h>
#include "IBgActor.h"

/// <summary>
/// �u���b�N�N���X
/// </summary>
namespace App {
	class Block :public IBgActor
	{
	public:
		Block();
		~Block();
		bool Start();
		void Update();
		//�����蔻��B
		void Collision();
		//�Փˌ�̏����B
		void CollisionEstablishment();
		void Render(RenderContext& rc);
	};
}