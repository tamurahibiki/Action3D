#pragma once
#include <CollisionObject.h>
#include "InGame/Bg/IBgActor.h"
class Game;
class Player;

/// <summary>
/// �S�[���|�C���g�N���X
/// </summary>
namespace App {
	class GoalPoint :public IBgActor
	{
	public:
		GoalPoint();
		~GoalPoint();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		/// <summary>
		/// �v���C���[��T������B
		/// </summary>
		/// <returns>�v���C���[������������true�B</returns>
		const bool SearchPlayer() const;
		Game* m_game = nullptr;          //�Q�[��
	};
}