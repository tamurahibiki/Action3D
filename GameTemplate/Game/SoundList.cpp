#include "stdafx.h"
#include "SoundList.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

SoundList::SoundList(){}
SoundList::~SoundList(){}
bool SoundList::Start()
{
	//Œø‰Ê‰¹‚ð“Ç‚Ýž‚ÞB
	g_soundEngine->ResistWaveFileBank(DASH, "Assets/sound/Dash.wav");
	g_soundEngine->ResistWaveFileBank(WALK, "Assets/sound/Walk.wav");
	g_soundEngine->ResistWaveFileBank(DASHFIRST, "Assets/sound/Dash_Start.wav");
	g_soundEngine->ResistWaveFileBank(DASHMAX, "Assets/sound/Dash_Max.wav");
	g_soundEngine->ResistWaveFileBank(JUMPEND, "Assets/sound/Jump_End.wav");
	g_soundEngine->ResistWaveFileBank(DROP, "Assets/sound/Drop_End.wav");
	g_soundEngine->ResistWaveFileBank(JUMP, "Assets/sound/Jump.wav");
	g_soundEngine->ResistWaveFileBank(DMM, "Assets/sound/Dash_Max_Move.wav");
	//8
	g_soundEngine->ResistWaveFileBank(ENEMYDOWN, "Assets/sound/Enemy_Down.wav");
	g_soundEngine->ResistWaveFileBank(ENEMYDOWN2, "Assets/sound/Enemy_Down2.wav");
	g_soundEngine->ResistWaveFileBank(ENEMYDOWNHIP, "Assets/sound/Enemy_Down_Hip.wav");
	g_soundEngine->ResistWaveFileBank(BARDMOVE, "Assets/sound/Bard_Move.wav");
	g_soundEngine->ResistWaveFileBank(ENEMYMOVE, "Assets/sound/Enemy_Move.wav");
	g_soundEngine->ResistWaveFileBank(ENEMYMOVE2, "Assets/sound/Enemy_Move2.wav");
	g_soundEngine->ResistWaveFileBank(FORTIDLE, "Assets/sound/Fort_Idle.wav");
	g_soundEngine->ResistWaveFileBank(FORTSTAY, "Assets/sound/Fort_Stay.wav");
	g_soundEngine->ResistWaveFileBank(FORTMOVE, "Assets/sound/Fort_Move.wav");
	g_soundEngine->ResistWaveFileBank(GAMEBGM, "Assets/sound/BGM.wav");
	g_soundEngine->ResistWaveFileBank(ENEMYJUMPCOUNT, "Assets/sound/Enemy_JumpCountSE.wav");
	g_soundEngine->ResistWaveFileBank(TITLEA, "Assets/sound/Title_A.wav");
	g_soundEngine->ResistWaveFileBank(TITLEBGM, "Assets/sound/Title_BGM.wav");
	g_soundEngine->ResistWaveFileBank(BLOCK, "Assets/sound/Block.wav");
	g_soundEngine->ResistWaveFileBank(FALL, "Assets/sound/Fall.wav");

	return true;
}