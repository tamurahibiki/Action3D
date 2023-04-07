#include "stdafx.h"
#include "EffectList.h"
#include "graphics/effect/EffectEmitter.h"

EffectList::EffectList(){}
EffectList::~EffectList(){}
bool EffectList::Start()
{
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(MOVE, u"Assets/effect/efk/move.efk");
	EffectEngine::GetInstance()->ResistEffect(WALK, u"Assets/effect/efk/walk.efk");
	EffectEngine::GetInstance()->ResistEffect(DASHFIRST, u"Assets/effect/efk/dash_first.efk");
	EffectEngine::GetInstance()->ResistEffect(DASHMAX, u"Assets/effect/efk/dash_max.efk");
	EffectEngine::GetInstance()->ResistEffect(BLOCK, u"Assets/effect/efk/block.efk");
	EffectEngine::GetInstance()->ResistEffect(DMF, u"Assets/effect/efk/dash_max_first.efk");
	EffectEngine::GetInstance()->ResistEffect(JUMP, u"Assets/effect/efk/jump.efk");
	EffectEngine::GetInstance()->ResistEffect(DROP, u"Assets/effect/efk/drop_end.efk");
	EffectEngine::GetInstance()->ResistEffect(DMF2, u"Assets/effect/efk/dash_max_first2.efk");
	EffectEngine::GetInstance()->ResistEffect(ENEMYMOVE, u"Assets/effect/efk/enemy_move.efk");
	EffectEngine::GetInstance()->ResistEffect(FORTMOVE, u"Assets/effect/efk/fort_move.efk");
	EffectEngine::GetInstance()->ResistEffect(CLEAR, u"Assets/effect/efk/clear.efk");
	EffectEngine::GetInstance()->ResistEffect(ENEMYDAMAGE, u"Assets/effect/efk/enemy_damage.efk");
	return true;
}
