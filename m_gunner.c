/*
==============================================================================

GUNNER

==============================================================================
*/

#include "g_local.h"
#include "m_gunner.h"

static int	sound_pain;
static int	sound_pain2;
static int	sound_death;
static int	sound_idle;
static int	sound_open;
static int	sound_search;
static int	sound_sight;
// petunindan tad
static int	sound_death_tr;
static int	sound_pain_tr;
static int	sound_pain2_tr;
static int	sound_sight_tr;
//
static int	sound_death_fetr;
static int	sound_pain_fetr;
static int	sound_pain2_fetr;
static int	sound_sight_fetr;
//

// NOTE: Original gunner grenade velocity was 600 units/sec, but then 
//       fire_grenade added 200 units/sec in a direction perpendicular
//       to the aim direction. We've removed that from fire_grenade 
//       (for the gunner, not for players) since the gunner now shoots 
//       smarter, and adjusted things so that the initial velocity out 
//       of the barrel is the same.
#define GRENADE_VELOCITY 632.4555320337
#define GRENADE_VELOCITY_SQUARED 400000

void gunner_idlesound (edict_t *self)
{
	if(!(self->spawnflags & SF_MONSTER_AMBUSH))
		gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

// petunindan tad
void traitor_idlesound (edict_t *self)
{
	NULL;
}

void gunner_sight (edict_t *self, edict_t *other)
{
	gi.sound (self, CHAN_VOICE, sound_sight, 1, ATTN_NORM, 0);
}

void gunner_search (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, sound_search, 1, ATTN_NORM, 0);
}

// petunindan tad
void traitor_sight (edict_t *self, edict_t *other)
{
	gi.sound (self, CHAN_VOICE, sound_sight_tr, 1, ATTN_NORM, 0);
}

void traitor_female_sight (edict_t *self, edict_t *other)
{
	gi.sound (self, CHAN_VOICE, sound_sight_fetr, 1, ATTN_NORM, 0);
}

void traitor_search (edict_t *self)
{
	NULL;
}
//


qboolean visible (edict_t *self, edict_t *other);
void GunnerGrenade (edict_t *self);
void GunnerFire (edict_t *self);
void gunner_fire_chain(edict_t *self);
void gunner_refire_chain(edict_t *self);
// petunindan tad
void TraitorFire (edict_t *self);
void TraitorFireFemaleChaingun (edict_t *self);
void TraitorRocket (edict_t *self);
void TraitorBfg (edict_t *self);
void TraitorPlasma (edict_t *self);
void TraitorHyper (edict_t *self);
void traitor_fire_rocket(edict_t *self);
void traitor_fire_bfg(edict_t *self);
void traitor_fire_plasma(edict_t *self);
//hyper boss
void traitor_refire_hyper_boss_1(edict_t *self);
void traitor_refire_hyper_boss_1(edict_t *self);
void traitor_refire_hyper_boss_2(edict_t *self);
void traitor_refire_hyper_boss_3(edict_t *self);
void traitor_refire_hyper_boss_4(edict_t *self);
void traitor_refire_hyper_boss_5(edict_t *self);
void traitor_refire_hyper_boss_6(edict_t *self);
void traitor_refire_hyper_boss_7(edict_t *self);
void traitor_refire_hyper_boss_8(edict_t *self);
void traitor_refire_hyper_boss_9(edict_t *self);
void traitor_refire_hyper_boss_10(edict_t *self);
void traitor_refire_hyper_boss_11(edict_t *self);
void traitor_refire_hyper_boss_12(edict_t *self);
void traitor_refire_hyper_boss_13(edict_t *self);
void traitor_refire_hyper_boss_14(edict_t *self);
void traitor_refire_hyper_boss_15(edict_t *self);
void traitor_refire_hyper_boss_16(edict_t *self);
// hyper
void traitor_fire_hyper(edict_t *self);
void traitor_refire_hyper1(edict_t *self);
void traitor_refire_hyper1(edict_t *self);
void traitor_refire_hyper2(edict_t *self);
void traitor_refire_hyper3(edict_t *self);
void traitor_refire_hyper4(edict_t *self);
void traitor_refire_hyper5(edict_t *self);
void traitor_refire_hyper6(edict_t *self);
void traitor_refire_hyper7(edict_t *self);
void traitor_refire_hyper8(edict_t *self);
void traitor_refire_hyper9(edict_t *self);
void traitor_refire_hyper10(edict_t *self);
void traitor_refire_hyper11(edict_t *self);
void traitor_refire_hyper12(edict_t *self);
void traitor_refire_hyper13(edict_t *self);
void traitor_refire_hyper14(edict_t *self);
void traitor_refire_hyper15(edict_t *self);
void traitor_refire_hyper16(edict_t *self);
// chaingun
void traitor_fire_chain(edict_t *self);
void traitor_fire_chain_female(edict_t *self);
void traitor_refire_chain1(edict_t *self);
void traitor_refire_chain1(edict_t *self);
void traitor_refire_chain2(edict_t *self);
void traitor_refire_chain3(edict_t *self);
void traitor_refire_chain4(edict_t *self);
void traitor_refire_chain5(edict_t *self);
void traitor_refire_chain6(edict_t *self);
void traitor_refire_chain7(edict_t *self);
void traitor_refire_chain8(edict_t *self);
void traitor_refire_chain9(edict_t *self);
void traitor_refire_chain10(edict_t *self);
void traitor_refire_chain11(edict_t *self);
void traitor_refire_chain12(edict_t *self);
void traitor_refire_chain13(edict_t *self);
void traitor_refire_chain14(edict_t *self);
void traitor_refire_chain15(edict_t *self);
void traitor_refire_chain16(edict_t *self);
// boss chaingun
void traitor_refire_chain_boss_1(edict_t *self);
void traitor_refire_chain_boss_1(edict_t *self);
void traitor_refire_chain_boss_2(edict_t *self);
void traitor_refire_chain_boss_3(edict_t *self);
void traitor_refire_chain_boss_4(edict_t *self);
void traitor_refire_chain_boss_5(edict_t *self);
void traitor_refire_chain_boss_6(edict_t *self);
void traitor_refire_chain_boss_7(edict_t *self);
void traitor_refire_chain_boss_8(edict_t *self);
void traitor_refire_chain_boss_9(edict_t *self);
void traitor_refire_chain_boss_10(edict_t *self);
void traitor_refire_chain_boss_11(edict_t *self);
void traitor_refire_chain_boss_12(edict_t *self);
void traitor_refire_chain_boss_13(edict_t *self);
void traitor_refire_chain_boss_14(edict_t *self);
void traitor_refire_chain_boss_15(edict_t *self);
void traitor_refire_chain_boss_16(edict_t *self);
//
void traitor_refire_allguns(edict_t *self);
void traitor_refire_boss(edict_t *self);
//
//cloak
void traitor_cloakon(edict_t *self);
void traitor_cloakoff(edict_t *self);


void gunner_stand (edict_t *self);

mframe_t gunner_frames_fidget [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, gunner_idlesound,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t	gunner_move_fidget = {FRAME_stand31, FRAME_stand70, gunner_frames_fidget, gunner_stand};

void gunner_fidget (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		return;
	if (random() <= 0.05)
		self->monsterinfo.currentmove = &gunner_move_fidget;
}

mframe_t gunner_frames_stand [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, gunner_fidget,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, gunner_fidget,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, gunner_fidget
};
mmove_t	gunner_move_stand = {FRAME_stand01, FRAME_stand30, gunner_frames_stand, NULL};

void gunner_stand (edict_t *self)
{
		self->monsterinfo.currentmove = &gunner_move_stand;
}

// petunindan tad

void traitor_stand (edict_t *self);

mframe_t traitor_frames_stand [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t	traitor_move_stand = {0, 39, traitor_frames_stand, traitor_stand};

void traitor_stand (edict_t *self)
{
		self->monsterinfo.currentmove = &traitor_move_stand;
}

mframe_t gunner_frames_walk [] =
{
	ai_walk, 0, NULL,
	ai_walk, 3, NULL,
	ai_walk, 4, NULL,
	ai_walk, 5, NULL,
	ai_walk, 7, NULL,
	ai_walk, 2, NULL,
	ai_walk, 6, NULL,
	ai_walk, 4, NULL,
	ai_walk, 2, NULL,
	ai_walk, 7, NULL,
	ai_walk, 5, NULL,
	ai_walk, 7, NULL,
	ai_walk, 4, NULL
};
mmove_t gunner_move_walk = {FRAME_walk07, FRAME_walk19, gunner_frames_walk, NULL};

void gunner_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &gunner_move_walk;
}

// petunindan tad
mframe_t traitor_frames_walk [] =
{
	ai_walk, 0, NULL,
	ai_walk, 3, NULL,
	ai_walk, 4, NULL,
	ai_walk, 5, NULL,
	ai_walk, 7, NULL,
	ai_walk, 2, NULL,
	ai_walk, 6, NULL,
	ai_walk, 4, NULL,
	ai_walk, 2, NULL,
	ai_walk, 7, NULL,
	ai_walk, 5, NULL,
	ai_walk, 7, NULL,
	ai_walk, 4, NULL
};
mmove_t traitor_move_walk = {40, 45, traitor_frames_walk, NULL};

void traitor_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_walk;
}
//

mframe_t gunner_frames_run [] =
{
	ai_run, 26, NULL,
	ai_run, 9,  NULL,
	ai_run, 9,  NULL,
	ai_run, 9,  monster_done_dodge,
	ai_run, 15, NULL,
	ai_run, 10, NULL,
	ai_run, 13, NULL,
	ai_run, 6,  NULL
};

mmove_t gunner_move_run = {FRAME_run01, FRAME_run08, gunner_frames_run, NULL};

void gunner_run (edict_t *self)
{
	monster_done_dodge(self);
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &gunner_move_stand;
	else
		self->monsterinfo.currentmove = &gunner_move_run;
}

// petunindan rose
mframe_t traitor_frames_run [] =
{
	ai_run, 26, NULL,
	ai_run, 9,  NULL,
	ai_run, 9,  NULL,
	ai_run, 9,  monster_done_dodge,
	ai_run, 15, NULL,
	ai_run, 10, NULL,
	ai_run, 13, NULL,
	ai_run, 6,  NULL
};

mmove_t traitor_move_run = {40, 45, traitor_frames_run, NULL};

void traitor_run (edict_t *self)
{
	monster_done_dodge(self);
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &traitor_move_stand;
	else
		self->monsterinfo.currentmove = &traitor_move_run;
}

void traitor_run_boss (edict_t *self)
{
	monster_done_dodge(self);
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &traitor_move_stand;
	else
		self->monsterinfo.currentmove = &traitor_move_run;
	traitor_cloakon (self);
}
//

mframe_t gunner_frames_runandshoot [] =
{
	ai_run, 32, NULL,
	ai_run, 15, NULL,
	ai_run, 10, NULL,
	ai_run, 18, NULL,
	ai_run, 8,  NULL,
	ai_run, 20, NULL
};

mmove_t gunner_move_runandshoot = {FRAME_runs01, FRAME_runs06, gunner_frames_runandshoot, NULL};

void gunner_runandshoot (edict_t *self)
{
	self->monsterinfo.currentmove = &gunner_move_runandshoot;
}

mframe_t gunner_frames_pain3 [] =
{
	ai_move, -3, NULL,
	ai_move, 1,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 1,	 NULL
};
mmove_t gunner_move_pain3 = {FRAME_pain301, FRAME_pain305, gunner_frames_pain3, gunner_run};

mframe_t gunner_frames_pain2 [] =
{
	ai_move, -2, NULL,
	ai_move, 11, NULL,
	ai_move, 6,	 NULL,
	ai_move, 2,	 NULL,
	ai_move, -1, NULL,
	ai_move, -7, NULL,
	ai_move, -2, NULL,
	ai_move, -7, NULL
};
mmove_t gunner_move_pain2 = {FRAME_pain201, FRAME_pain208, gunner_frames_pain2, gunner_run};

mframe_t gunner_frames_pain1 [] =
{
	ai_move, 2,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -5, NULL,
	ai_move, 3,	 NULL,
	ai_move, -1, NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 2,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -2, NULL,
	ai_move, -2, NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t gunner_move_pain1 = {FRAME_pain101, FRAME_pain118, gunner_frames_pain1, gunner_run};

// petunindan tad
mframe_t traitor_frames_pain3 [] =
{
	ai_move, -3, NULL,
	ai_move, 1,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 1,	 NULL
};
mmove_t traitor_move_pain3 = {62, 65, traitor_frames_pain3, traitor_run};

mframe_t traitor_frames_pain2 [] =
{
	ai_move, -2, NULL,
	ai_move, 11, NULL,
	ai_move, 6,	 NULL,
	ai_move, 2,	 NULL,
	ai_move, -1, NULL,
	ai_move, -7, NULL,
	ai_move, -2, NULL,
	ai_move, -7, NULL
};
mmove_t traitor_move_pain2 = {58, 61, traitor_frames_pain2, traitor_run};

mframe_t traitor_frames_pain1 [] =
{
	ai_move, 2,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -5, NULL,
	ai_move, 3,	 NULL,
	ai_move, -1, NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 2,	 NULL,
	ai_move, 1,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -2, NULL,
	ai_move, -2, NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t traitor_move_pain1 = {54, 57, traitor_frames_pain1, traitor_run};
//

void gunner_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;

	monster_done_dodge (self);

	if (!self->groundentity)
	{
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("gunner: pain avoided due to no ground\n");
		return;
	}

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;

	if (rand()&1)
		gi.sound (self, CHAN_VOICE, sound_pain, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if (damage <= 10)
		self->monsterinfo.currentmove = &gunner_move_pain3;
	else if (damage <= 25)
		self->monsterinfo.currentmove = &gunner_move_pain2;
	else
		self->monsterinfo.currentmove = &gunner_move_pain1;

	self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;

	// PMM - clear duck flag
	if (self->monsterinfo.aiflags & AI_DUCKED)
		monster_duck_up(self);
}

void traitor_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;

	monster_done_dodge (self);

	if (!self->groundentity)
	{
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("gunner: pain avoided due to no ground\n");
		return;
	}

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;

	if (rand()&1)
		gi.sound (self, CHAN_VOICE, sound_pain_tr, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_pain2_tr, 1, ATTN_NORM, 0);

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if (damage <= 10)
		self->monsterinfo.currentmove = &traitor_move_pain3;
	else if (damage <= 25)
		self->monsterinfo.currentmove = &traitor_move_pain2;
	else
		self->monsterinfo.currentmove = &traitor_move_pain1;

	self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;

	// PMM - clear duck flag
	if (self->monsterinfo.aiflags & AI_DUCKED)
		monster_duck_up(self);
}

void traitor_female_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;

	monster_done_dodge (self);

	if (!self->groundentity)
	{
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("gunner: pain avoided due to no ground\n");
		return;
	}

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;

	if (rand()&1)
		gi.sound (self, CHAN_VOICE, sound_pain_fetr, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_pain2_fetr, 1, ATTN_NORM, 0);

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if (damage <= 10)
		self->monsterinfo.currentmove = &traitor_move_pain3;
	else if (damage <= 25)
		self->monsterinfo.currentmove = &traitor_move_pain2;
	else
		self->monsterinfo.currentmove = &traitor_move_pain1;

	self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;

	// PMM - clear duck flag
	if (self->monsterinfo.aiflags & AI_DUCKED)
		monster_duck_up(self);
}

void gunner_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);

	// Lazarus monster fade
	if(world->effects & FX_WORLDSPAWN_CORPSEFADE)
	{
		self->think=FadeDieSink;
		self->nextthink=level.time+corpse_fadetime->value;
	}
}

// petunindan tad
void traitor_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);

	// Lazarus monster fade
	if(world->effects & FX_WORLDSPAWN_CORPSEFADE)
	{
		self->think=FadeDieSink;
		self->nextthink=level.time+corpse_fadetime->value;
	}
}
//

mframe_t gunner_frames_death [] =
{
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -7, NULL,
	ai_move, -3, NULL,
	ai_move, -5, NULL,
	ai_move, 8,	 NULL,
	ai_move, 6,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t gunner_move_death = {FRAME_death01, FRAME_death11, gunner_frames_death, gunner_dead};

// petunindan tad
mframe_t traitor_frames_death1 [] =
{
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -7, NULL,
	ai_move, -3, NULL,
	ai_move, -5, NULL,
	ai_move, 8,	 NULL,
	ai_move, 6,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t traitor_move_death1 = {178, 183, traitor_frames_death1, traitor_dead};

mframe_t traitor_frames_death2 [] =
{
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -7, NULL,
	ai_move, -3, NULL,
	ai_move, -5, NULL,
	ai_move, 8,	 NULL,
	ai_move, 6,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t traitor_move_death2 = {184, 189, traitor_frames_death2, traitor_dead};

mframe_t traitor_frames_death3 [] =
{
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, -7, NULL,
	ai_move, -3, NULL,
	ai_move, -5, NULL,
	ai_move, 8,	 NULL,
	ai_move, 6,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL,
	ai_move, 0,	 NULL
};
mmove_t traitor_move_death3 = {190, 197, traitor_frames_death3, traitor_dead};
//

void gunner_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	self->s.skinnum |= 1;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;
// check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

// regular death
	gi.sound (self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.currentmove = &gunner_move_death;
}

// petunindan tad
void traitor_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;
	float   r;

	self->s.skinnum |= 1;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;
// check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

// regular death
	gi.sound (self, CHAN_VOICE, sound_death_tr, 1, ATTN_NORM, 0);
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	
	r = random();
	
	if (random() <= 0.35)
		self->monsterinfo.currentmove = &traitor_move_death1;
	else if (random() >= 0.70)
		self->monsterinfo.currentmove = &traitor_move_death2;
	else
		self->monsterinfo.currentmove = &traitor_move_death3;
		
	self->s.modelindex2 = NULL;
	
}

void traitor_female_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;
	float   r;

	self->s.skinnum |= 1;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;
// check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

// regular death
	gi.sound (self, CHAN_VOICE, sound_death_fetr, 1, ATTN_NORM, 0);
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	
	r = random();
	
	if (random() <= 0.35)
		self->monsterinfo.currentmove = &traitor_move_death1;
	else if (random() >= 0.70)
		self->monsterinfo.currentmove = &traitor_move_death2;
	else
		self->monsterinfo.currentmove = &traitor_move_death3;
		
	self->s.modelindex2 = NULL;
	
}
//

qboolean gunner_grenade_check(edict_t *self)
{
	vec3_t		start;
	vec3_t		forward, right;
	vec3_t		target;
	trace_t		tr;
	vec3_t		dir;
	vec3_t		vhorz;
	float		horz,vertmax;

	if(!self->enemy)
		return false;

	// if the player is above my head, use machinegun.

//	if(self->absmax[2] <= self->enemy->absmin[2])
//		return false;

	// Lazarus: We can do better than that... see below


	// check to see that we can trace to the player before we start
	// tossing grenades around.
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[MZ2_GUNNER_GRENADE_1], forward, right, start);

	// see if we're too close
	VectorSubtract (self->enemy->s.origin, self->s.origin, dir);
	if (VectorLength(dir) < 100)
		return false;

	// Lazarus: Max vertical distance - this is approximate and conservative
	VectorCopy(dir,vhorz);
	vhorz[2] = 0;
	horz = VectorLength(vhorz);
	vertmax = (GRENADE_VELOCITY_SQUARED)/(2*sv_gravity->value) -
		0.5*sv_gravity->value*horz*horz/GRENADE_VELOCITY_SQUARED;
	if(dir[2] > vertmax) 
		return false;

	// Lazarus: Make sure there's a more-or-less clear flight path to target
	// Rogue checked target origin, but if target is above gunner then the trace
	// would almost always hit the platform the target was standing on
	VectorCopy(self->enemy->s.origin,target);
	target[2] = self->enemy->absmax[2];
	tr = gi.trace(start, vec3_origin, vec3_origin, target, self, MASK_SHOT);
	if(tr.ent == self->enemy || tr.fraction == 1)
		return true;
	// Repeat for feet... in case we're looking down at a target standing under,
	// for example, a short doorway
	target[2] = self->enemy->absmin[2];
	tr = gi.trace(start, vec3_origin, vec3_origin, target, self, MASK_SHOT);
	if(tr.ent == self->enemy || tr.fraction == 1)
		return true;

	return false;
}

// PMM - changed to duck code for new dodge

//
// this is specific to the gunner, leave it be
//
void gunner_duck_down (edict_t *self)
{
//	if (self->monsterinfo.aiflags & AI_DUCKED)
//		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	if (skill->value >= 2)
	{
		if (random() > 0.5)
			GunnerGrenade (self);
	}

//	self->maxs[2] -= 32;
	self->maxs[2] = self->monsterinfo.base_height - 32;
	self->takedamage = DAMAGE_YES;
	if (self->monsterinfo.duck_wait_time < level.time)
		self->monsterinfo.duck_wait_time = level.time + 1;
	gi.linkentity (self);
}

// petunindan tad
void traitor_duck_down (edict_t *self)
{
//	if (self->monsterinfo.aiflags & AI_DUCKED)
//		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	if (skill->value >= 2)
	{
		if (random() > 0.5)
		//	GunnerGrenade (self);
		NULL;
	}

//	self->maxs[2] -= 32;
	self->maxs[2] = self->monsterinfo.base_height - 32;
	self->takedamage = DAMAGE_YES;
	if (self->monsterinfo.duck_wait_time < level.time)
		self->monsterinfo.duck_wait_time = level.time + 1;
	gi.linkentity (self);
}
//

mframe_t gunner_frames_duck [] =
{
	ai_move, 1,  gunner_duck_down,
	ai_move, 1,  NULL,
	ai_move, 1,  monster_duck_hold,
	ai_move, 0,  NULL,
	ai_move, -1, NULL,
	ai_move, -1, NULL,
	ai_move, 0,  monster_duck_up,
	ai_move, -1, NULL
};
mmove_t	gunner_move_duck = {FRAME_duck01, FRAME_duck08, gunner_frames_duck, gunner_run};

// petunindan tad
mframe_t traitor_frames_duck [] =
{
	ai_move, 1,  traitor_duck_down,
	ai_move, 1,  NULL,
	ai_move, 1,  monster_duck_hold,
	ai_move, 0,  NULL,
	ai_move, -1, NULL,
	ai_move, -1, NULL,
	ai_move, 0,  monster_duck_up,
	ai_move, -1, NULL
};
mmove_t	traitor_move_duck = {135, 142, traitor_frames_duck, traitor_run};
//

// PMM - gunner dodge moved below so I know about attack sequences

void gunner_opengun (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, sound_open, 1, ATTN_IDLE, 0);
}

void GunnerFire (edict_t *self)
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	target;
	vec3_t	aim;
	int		flash_number;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	flash_number = MZ2_GUNNER_MACHINEGUN_1 + (self->s.frame - FRAME_attak216);

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

	// project enemy back a bit and target there
	VectorCopy (self->enemy->s.origin, target);
	VectorMA (target, -0.2, self->enemy->velocity, target);
	target[2] += self->enemy->viewheight;

	// Lazarus fog reduction of accuracy
	if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
	{
		target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
	}

	VectorSubtract (target, start, aim);
	VectorNormalize (aim);
	monster_fire_bullet (self, start, aim, 3, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}

// petunindan tad
void TraitorFire (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->svflags &= ~SVF_NOCLIENT;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}

	monster_fire_bullet (self, start, forward, 7, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}

void TraitorFireFemaleChaingun (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->s.modelindex2 = gi.modelindex ("players/female/w_chaingun.md2");
	
	self->svflags &= ~SVF_NOCLIENT;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}

	monster_fire_bullet (self, start, forward, 7, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}

void TraitorRocket (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->s.modelindex2 = gi.modelindex ("players/female/w_rlauncher.md2");

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}
	
	gi.sound (self, CHAN_VOICE, gi.soundindex ("flyer/chkatck2.wav"), 1, ATTN_NORM, 0);
	monster_fire_rocket (self, start, forward, 80, 500, flash_number,
		(self->spawnflags & SF_MONSTER_SPECIAL ? self->enemy : NULL) );
}

void TraitorBfg (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->s.modelindex2 = gi.modelindex ("players/female/w_bfg.md2");

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}
	
	gi.sound (self, CHAN_VOICE, gi.soundindex ("boss3/bs3atck2.wav"), 1, ATTN_NORM, 0);
	monster_fire_bfg (self, start, forward, 80, 500, 300, 200, MZ2_JORG_BFG_1);
}

void TraitorPlasma (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->s.modelindex2 = gi.modelindex ("players/female/w_railgun.md2");

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}
	
	gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/plasshot.wav"), 1, ATTN_NORM, 0);
	fire_tadplasma (self, start, forward, 50, 725, 60, 60);
}

void TraitorHyper (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
	vec3_t	vec;
	int		flash_number;
	
	self->s.modelindex2 = gi.modelindex ("players/female/w_hyperblaster.md2");

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm - new attack start frame
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

		if (self->enemy)
		{
			VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
			target[2] += self->enemy->viewheight;

			// Lazarus fog reduction of accuracy
			if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
			{
				target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
				target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			}

			VectorSubtract (target, start, forward);
			VectorNormalize (forward);
		}
		else
		{
			AngleVectors (self->s.angles, forward, right, NULL);
		}
	
	gi.sound (self, CHAN_VOICE, gi.soundindex ("flyer/flyatck3.wav"), 1, ATTN_NORM, 0);
	monster_fire_blaster (self, start, forward, 9, 1000, flash_number, EF_HYPERBLASTER, BLASTER_ORANGE);
}
//

void GunnerGrenade (edict_t *self)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec_t	monster_speed;
	int		flash_number;
	float	spread;
//	float	pitch;
	// PMM
	vec3_t	target;	
	qboolean blindfire;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	// pmm
	if (self->monsterinfo.aiflags & AI_MANUAL_STEERING)
		blindfire = true;

	if (self->s.frame == FRAME_attak105)
	{
		spread = .02;
		flash_number = MZ2_GUNNER_GRENADE_1;
	}
	else if (self->s.frame == FRAME_attak108)
	{
		spread = .05;
		flash_number = MZ2_GUNNER_GRENADE_2;
	}
	else if (self->s.frame == FRAME_attak111)
	{
		spread = .08;
		flash_number = MZ2_GUNNER_GRENADE_3;
	}
	else // (self->s.frame == FRAME_attak114)
	{
		self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;
		spread = .11;
		flash_number = MZ2_GUNNER_GRENADE_4;
	}

	//	pmm
	// if we're shooting blind and we still can't see our enemy
	if ((blindfire) && (!visible(self, self->enemy)))
	{
		// and we have a valid blind_fire_target
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;
		
//		gi.dprintf ("blind_fire_target = %s\n", vtos (self->monsterinfo.blind_fire_target));
//		gi.dprintf ("GunnerGrenade: ideal yaw is %f\n", self->ideal_yaw);
		VectorCopy (self->monsterinfo.blind_fire_target, target);
	}
	else
		VectorCopy (self->s.origin, target);
	// pmm

	AngleVectors (self->s.angles, forward, right, up);	//PGM
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

//PGM
	if(self->enemy)
	{
		float	dist;

//		VectorSubtract(self->enemy->s.origin, self->s.origin, aim);
		VectorSubtract(target, self->s.origin, aim);
		dist = VectorLength(aim);

		// aim at enemy's feet if he's at same elevation or lower. otherwise aim at origin
		VectorCopy(self->enemy->s.origin,target);
		if(self->enemy->absmin[2] <= self->absmax[2]) target[2] = self->enemy->absmin[2];

		// Lazarus fog reduction of accuracy
		if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
		{
			target[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			target[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			target[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		}

		// lead target... 20, 35, 50, 65 chance of leading
		if( random() < (0.2 + skill->value * 0.15) )
		{
			float	dist;
			float	time;

			VectorSubtract(target, start, aim);
			dist = VectorLength (aim);
			time = dist/GRENADE_VELOCITY;  // Not correct, but better than nothin'
			VectorMA(target, time, self->enemy->velocity, target);
		}

		// aim up if they're on the same level as me and far away.
		if((dist > 512) && (aim[2] < 64) && (aim[2] > -64))
			aim[2] += (dist - 512);

/*		VectorNormalize (aim);
		pitch = aim[2];
		if(pitch > 0.4)
			pitch = 0.4;
		else if(pitch < -0.5)
			pitch = -0.5;*/
	}
//PGM

	AimGrenade (self, start, target, GRENADE_VELOCITY, aim);
	// Lazarus - take into account (sort of) feature of adding shooter's velocity to
	// grenade velocity
	monster_speed = VectorLength(self->velocity);
	if(monster_speed > 0)
	{
		vec3_t	v1;
		vec_t	delta;

		VectorCopy(self->velocity,v1);
		VectorNormalize(v1);
		delta = -monster_speed/GRENADE_VELOCITY;
		VectorMA(aim,delta,v1,aim);
		VectorNormalize(aim);
	}
	//FIXME : do a spread -225 -75 75 225 degrees around forward
//	VectorCopy (forward, aim);
//	VectorMA (forward, spread, right, aim);
//	VectorMA (aim, pitch, up, aim);

	monster_fire_grenade (self, start, aim, 50, 600, flash_number);
}

mframe_t gunner_frames_attack_chain [] =
{
	/*
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	*/
	ai_charge, 0, gunner_opengun,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t gunner_move_attack_chain = {FRAME_attak209, FRAME_attak215, gunner_frames_attack_chain, gunner_fire_chain};

mframe_t gunner_frames_fire_chain [] =
{
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire,
	ai_charge,   0, GunnerFire
};
mmove_t gunner_move_fire_chain = {FRAME_attak216, FRAME_attak223, gunner_frames_fire_chain, gunner_refire_chain};

// petunindan tad

// hyper boss

mframe_t traitor_frames_fire_hyper_boss_16 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_16 = {46, 46, traitor_frames_fire_hyper_boss_16, traitor_refire_boss};

mframe_t traitor_frames_fire_hyper_boss_15 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_15 = {46, 46, traitor_frames_fire_hyper_boss_15, traitor_refire_hyper_boss_15};

mframe_t traitor_frames_fire_hyper_boss_14 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_14 = {46, 46, traitor_frames_fire_hyper_boss_14, traitor_refire_hyper_boss_14};

mframe_t traitor_frames_fire_hyper_boss_13 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_13 = {46, 46, traitor_frames_fire_hyper_boss_13, traitor_refire_hyper_boss_13};

mframe_t traitor_frames_fire_hyper_boss_12 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_12 = {46, 46, traitor_frames_fire_hyper_boss_12, traitor_refire_hyper_boss_12};

mframe_t traitor_frames_fire_hyper_boss_11 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_11 = {46, 46, traitor_frames_fire_hyper_boss_11, traitor_refire_hyper_boss_11};

mframe_t traitor_frames_fire_hyper_boss_10 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_10 = {46, 46, traitor_frames_fire_hyper_boss_10, traitor_refire_hyper_boss_10};

mframe_t traitor_frames_fire_hyper_boss_9 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_9 = {46, 46, traitor_frames_fire_hyper_boss_9, traitor_refire_hyper_boss_9};

mframe_t traitor_frames_fire_hyper_boss_8 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_8 = {46, 46, traitor_frames_fire_hyper_boss_8, traitor_refire_hyper_boss_8};

mframe_t traitor_frames_fire_hyper_boss_7 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_7 = {46, 46, traitor_frames_fire_hyper_boss_7, traitor_refire_hyper_boss_7};

mframe_t traitor_frames_fire_hyper_boss_6 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_6 = {46, 46, traitor_frames_fire_hyper_boss_6, traitor_refire_hyper_boss_6};

mframe_t traitor_frames_fire_hyper_boss_5 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_5 = {46, 46, traitor_frames_fire_hyper_boss_5, traitor_refire_hyper_boss_5};

mframe_t traitor_frames_fire_hyper_boss_4 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_4 = {46, 46, traitor_frames_fire_hyper_boss_4, traitor_refire_hyper_boss_4};

mframe_t traitor_frames_fire_hyper_boss_3 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_3 = {46, 46, traitor_frames_fire_hyper_boss_3, traitor_refire_hyper_boss_3};

mframe_t traitor_frames_fire_hyper_boss_2 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_2 = {46, 46, traitor_frames_fire_hyper_boss_2, traitor_refire_hyper_boss_2};

mframe_t traitor_frames_fire_hyper_boss_1 [] =
{
	ai_charge, 0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper_boss_1 = {45, 46, traitor_frames_fire_hyper_boss_1, traitor_refire_hyper_boss_1};
//


// hyper

mframe_t traitor_frames_fire_hyper16 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper16 = {46, 46, traitor_frames_fire_hyper16, traitor_refire_allguns};

mframe_t traitor_frames_fire_hyper15 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper15 = {46, 46, traitor_frames_fire_hyper15, traitor_refire_hyper15};

mframe_t traitor_frames_fire_hyper14 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper14 = {46, 46, traitor_frames_fire_hyper14, traitor_refire_hyper14};

mframe_t traitor_frames_fire_hyper13 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper13 = {46, 46, traitor_frames_fire_hyper13, traitor_refire_hyper13};

mframe_t traitor_frames_fire_hyper12 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper12 = {46, 46, traitor_frames_fire_hyper12, traitor_refire_hyper12};

mframe_t traitor_frames_fire_hyper11 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper11 = {46, 46, traitor_frames_fire_hyper11, traitor_refire_hyper11};

mframe_t traitor_frames_fire_hyper10 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper10 = {46, 46, traitor_frames_fire_hyper10, traitor_refire_hyper10};

mframe_t traitor_frames_fire_hyper9 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper9 = {46, 46, traitor_frames_fire_hyper9, traitor_refire_hyper9};

mframe_t traitor_frames_fire_hyper8 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper8 = {46, 46, traitor_frames_fire_hyper8, traitor_refire_hyper8};

mframe_t traitor_frames_fire_hyper7 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper7 = {46, 46, traitor_frames_fire_hyper7, traitor_refire_hyper7};

mframe_t traitor_frames_fire_hyper6 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper6 = {46, 46, traitor_frames_fire_hyper6, traitor_refire_hyper6};

mframe_t traitor_frames_fire_hyper5 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper5 = {46, 46, traitor_frames_fire_hyper5, traitor_refire_hyper5};

mframe_t traitor_frames_fire_hyper4 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper4 = {46, 46, traitor_frames_fire_hyper4, traitor_refire_hyper4};

mframe_t traitor_frames_fire_hyper3 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper3 = {46, 46, traitor_frames_fire_hyper3, traitor_refire_hyper3};

mframe_t traitor_frames_fire_hyper2 [] =
{
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper2 = {46, 46, traitor_frames_fire_hyper2, traitor_refire_hyper2};

mframe_t traitor_frames_fire_hyper1 [] =
{
	ai_charge, 0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_hyper,
	ai_charge,   0, traitor_fire_hyper
};
mmove_t traitor_move_fire_hyper1 = {45, 46, traitor_frames_fire_hyper1, traitor_refire_hyper1};
//

mframe_t traitor_frames_fire_plasma [] =
{
	ai_charge, 0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_plasma,
	ai_charge,   0, traitor_fire_plasma,
	ai_charge,   0, traitor_fire_plasma,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t traitor_move_fire_plasma = {45, 50, traitor_frames_fire_plasma, traitor_refire_boss};

mframe_t traitor_frames_fire_bfg [] =
{
	ai_charge, 0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_bfg,
	ai_charge, 0, NULL,
	ai_charge,   0, traitor_fire_bfg,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t traitor_move_fire_bfg = {45, 50, traitor_frames_fire_bfg, traitor_refire_boss};

mframe_t traitor_frames_fire_rocket [] =
{
	ai_charge, 0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_rocket,
	ai_charge,   0, traitor_fire_rocket,
	ai_charge,   0, traitor_fire_rocket,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
	
};
mmove_t traitor_move_fire_rocket = {45, 50, traitor_frames_fire_rocket, traitor_refire_boss};

// boss chaingun
mframe_t traitor_frames_fire_chain_boss_16 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_16 = {46, 46, traitor_frames_fire_chain_boss_16, traitor_refire_boss};

mframe_t traitor_frames_fire_chain_boss_15 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_15 = {46, 46, traitor_frames_fire_chain_boss_15, traitor_refire_chain_boss_15};

mframe_t traitor_frames_fire_chain_boss_14 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_14 = {46, 46, traitor_frames_fire_chain_boss_14, traitor_refire_chain_boss_14};

mframe_t traitor_frames_fire_chain_boss_13 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_13 = {46, 46, traitor_frames_fire_chain_boss_13, traitor_refire_chain_boss_13};

mframe_t traitor_frames_fire_chain_boss_12 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_12 = {46, 46, traitor_frames_fire_chain_boss_12, traitor_refire_chain_boss_12};

mframe_t traitor_frames_fire_chain_boss_11 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_11 = {46, 46, traitor_frames_fire_chain_boss_11, traitor_refire_chain_boss_11};

mframe_t traitor_frames_fire_chain_boss_10 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_10 = {46, 46, traitor_frames_fire_chain_boss_10, traitor_refire_chain_boss_10};

mframe_t traitor_frames_fire_chain_boss_9 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_9 = {46, 46, traitor_frames_fire_chain_boss_9, traitor_refire_chain_boss_9};

mframe_t traitor_frames_fire_chain_boss_8 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_8 = {46, 46, traitor_frames_fire_chain_boss_8, traitor_refire_chain_boss_8};

mframe_t traitor_frames_fire_chain_boss_7 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_7 = {46, 46, traitor_frames_fire_chain_boss_7, traitor_refire_chain_boss_7};

mframe_t traitor_frames_fire_chain_boss_6 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_6 = {46, 46, traitor_frames_fire_chain_boss_6, traitor_refire_chain_boss_6};

mframe_t traitor_frames_fire_chain_boss_5 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_5 = {46, 46, traitor_frames_fire_chain_boss_5, traitor_refire_chain_boss_5};

mframe_t traitor_frames_fire_chain_boss_4 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_4 = {46, 46, traitor_frames_fire_chain_boss_4, traitor_refire_chain_boss_4};

mframe_t traitor_frames_fire_chain_boss_3 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_3 = {46, 46, traitor_frames_fire_chain_boss_3, traitor_refire_chain_boss_3};

mframe_t traitor_frames_fire_chain_boss_2 [] =
{
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_2 = {46, 46, traitor_frames_fire_chain_boss_2, traitor_refire_chain_boss_2};

mframe_t traitor_frames_fire_chain_boss_1 [] =
{
	ai_charge,   0, traitor_cloakoff,
	ai_charge,   0, traitor_fire_chain_female,
	ai_charge,   0, traitor_fire_chain_female
};
mmove_t traitor_move_fire_chain_boss_1 = {45, 46, traitor_frames_fire_chain_boss_1, traitor_refire_chain_boss_1};
//
// chaingun
mframe_t traitor_frames_fire_chain16 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain16 = {46, 46, traitor_frames_fire_chain16, traitor_refire_allguns};

mframe_t traitor_frames_fire_chain15 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain15 = {46, 46, traitor_frames_fire_chain15, traitor_refire_chain15};

mframe_t traitor_frames_fire_chain14 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain14 = {46, 46, traitor_frames_fire_chain14, traitor_refire_chain14};

mframe_t traitor_frames_fire_chain13 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain13 = {46, 46, traitor_frames_fire_chain13, traitor_refire_chain13};

mframe_t traitor_frames_fire_chain12 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain12 = {46, 46, traitor_frames_fire_chain12, traitor_refire_chain12};

mframe_t traitor_frames_fire_chain11 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain11 = {46, 46, traitor_frames_fire_chain11, traitor_refire_chain11};

mframe_t traitor_frames_fire_chain10 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain10 = {46, 46, traitor_frames_fire_chain10, traitor_refire_chain10};

mframe_t traitor_frames_fire_chain9 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain9 = {46, 46, traitor_frames_fire_chain9, traitor_refire_chain9};

mframe_t traitor_frames_fire_chain8 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain8 = {46, 46, traitor_frames_fire_chain8, traitor_refire_chain8};

mframe_t traitor_frames_fire_chain7 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain7 = {46, 46, traitor_frames_fire_chain7, traitor_refire_chain7};

mframe_t traitor_frames_fire_chain6 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain6 = {46, 46, traitor_frames_fire_chain6, traitor_refire_chain6};

mframe_t traitor_frames_fire_chain5 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain5 = {46, 46, traitor_frames_fire_chain5, traitor_refire_chain5};

mframe_t traitor_frames_fire_chain4 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain4 = {46, 46, traitor_frames_fire_chain4, traitor_refire_chain4};

mframe_t traitor_frames_fire_chain3 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain3 = {46, 46, traitor_frames_fire_chain3, traitor_refire_chain3};

mframe_t traitor_frames_fire_chain2 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain2 = {46, 46, traitor_frames_fire_chain2, traitor_refire_chain2};

mframe_t traitor_frames_fire_chain1 [] =
{
	ai_charge,   0, traitor_fire_chain,
	ai_charge,   0, traitor_fire_chain
};
mmove_t traitor_move_fire_chain1 = {46, 46, traitor_frames_fire_chain1, traitor_refire_chain1};
//

mframe_t gunner_frames_endfire_chain [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t gunner_move_endfire_chain = {FRAME_attak224, FRAME_attak230, gunner_frames_endfire_chain, gunner_run};

// petunindan tad
mframe_t traitor_frames_endfire_chain [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t traitor_move_endfire_chain = {51, 53, traitor_frames_endfire_chain, traitor_run};

mframe_t traitor_frames_endfire_chain_cloakon [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, traitor_cloakon
};
mmove_t traitor_move_endfire_chain_cloakon = {51, 53, traitor_frames_endfire_chain_cloakon, traitor_run_boss};
//

void gunner_blind_check (edict_t *self)
{
	vec3_t	aim;

	if (self->monsterinfo.aiflags & AI_MANUAL_STEERING)
	{
		VectorSubtract(self->monsterinfo.blind_fire_target, self->s.origin, aim);
		self->ideal_yaw = vectoyaw(aim);
		
//		gi.dprintf ("blind_fire_target = %s\n", vtos (self->monsterinfo.blind_fire_target));
//		gi.dprintf ("gunner_attack: ideal yaw is %f\n", self->ideal_yaw);
	}
}

mframe_t gunner_frames_attack_grenade [] =
{
	ai_charge, 0, gunner_blind_check,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, GunnerGrenade,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, GunnerGrenade,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, GunnerGrenade,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, GunnerGrenade,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t gunner_move_attack_grenade = {FRAME_attak101, FRAME_attak121, gunner_frames_attack_grenade, gunner_run};

void gunner_attack(edict_t *self)
{
	float chance, r;

	monster_done_dodge(self);

	// PMM 
	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		// setup shot probabilities
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
		{
//			if ((g_showlogic) && (g_showlogic->value))
//				gi.dprintf ("blindfire - NO SHOT\n");
			return;
		}

		// turn on manual steering to signal both manual steering and blindfire
		//self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.monsterflags |= AI_MANUAL_STEERING;
		if (gunner_grenade_check(self))
		{
			// if the check passes, go for the attack
			self->monsterinfo.currentmove = &gunner_move_attack_grenade;
			self->monsterinfo.attack_finished = level.time + 2*random();
		}
		// pmm - should this be active?
//		else
//			self->monsterinfo.currentmove = &gunner_move_attack_chain;
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("blind grenade check failed, doing nothing\n");

		// turn off blindfire flag
		self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;
		return;
	}
	// pmm

	// PGM - gunner needs to use his chaingun if he's being attacked by a tesla.
	if ((range (self, self->enemy) == RANGE_MELEE) || self->bad_area)
	{
		self->monsterinfo.currentmove = &gunner_move_attack_chain;
	}
	else
	{
		if (random() <= 0.5 && gunner_grenade_check(self))
			self->monsterinfo.currentmove = &gunner_move_attack_grenade;
		else
			self->monsterinfo.currentmove = &gunner_move_attack_chain;
	}
}

// petunindan tad
void traitor_attack(edict_t *self)
{
	float chance, r;

	monster_done_dodge(self);

	// PMM 
	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		// setup shot probabilities
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
		{
//			if ((g_showlogic) && (g_showlogic->value))
//				gi.dprintf ("blindfire - NO SHOT\n");
			return;
		}

		// turn on manual steering to signal both manual steering and blindfire
		//self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.monsterflags |= AI_MANUAL_STEERING;
		if (gunner_grenade_check(self))
		{
			// if the check passes, go for the attack
			self->monsterinfo.currentmove = &traitor_move_fire_chain1;
			self->monsterinfo.attack_finished = level.time + 2*random();
		}
		// pmm - should this be active?
//		else
//			self->monsterinfo.currentmove = &gunner_move_attack_chain;
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("blind grenade check failed, doing nothing\n");

		// turn off blindfire flag
		self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;
		return;
	}
	// pmm

	// PGM - gunner needs to use his chaingun if he's being attacked by a tesla.
	if ((range (self, self->enemy) == RANGE_MELEE) || self->bad_area)
	{
		self->monsterinfo.currentmove = &traitor_move_fire_chain1;
	}
	else
	{
		self->monsterinfo.currentmove = &traitor_move_fire_chain1;
	}
}

void traitor_attack_boss(edict_t *self)
{
	float chance, r;

	monster_done_dodge(self);

	// PMM 
	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		// setup shot probabilities
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
		{
//			if ((g_showlogic) && (g_showlogic->value))
//				gi.dprintf ("blindfire - NO SHOT\n");
			return;
		}

		// turn on manual steering to signal both manual steering and blindfire
		//self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.monsterflags |= AI_MANUAL_STEERING;
		if (gunner_grenade_check(self))
		{
			// if the check passes, go for the attack
			r = random();
	
			if (random() <= 0.2)
			{
				self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_1;
			}
			else if (random() > 0.2 <= 0.4)
			{
				self->monsterinfo.currentmove = &traitor_move_fire_rocket;
			}
			else if (random() > 0.4 <= 0.6)
			{
				self->monsterinfo.currentmove = &traitor_move_fire_bfg;
			}
			else if (random() > 0.6 <= 0.8)
			{
				self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_1;
			}
			else
			{
				self->monsterinfo.currentmove = &traitor_move_fire_plasma;
			self->monsterinfo.attack_finished = level.time + 2*random();
			}
		}
		// pmm - should this be active?
//		else
//			self->monsterinfo.currentmove = &gunner_move_attack_chain;
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("blind grenade check failed, doing nothing\n");

		// turn off blindfire flag
		self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;
		return;
	}
	// pmm

	// PGM - gunner needs to use his chaingun if he's being attacked by a tesla.
	r = random();
	
	if (random() <= 0.2)
		self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_1;
	else if (random() > 0.2 <= 0.4)
		self->monsterinfo.currentmove = &traitor_move_fire_rocket;
	else if (random() > 0.4 <= 0.6)
		self->monsterinfo.currentmove = &traitor_move_fire_bfg;
	else if (random() > 0.6 <= 0.8)
		self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_1;
	else
		self->monsterinfo.currentmove = &traitor_move_fire_plasma;
}
//

void gunner_fire_chain(edict_t *self)
{
	self->monsterinfo.currentmove = &gunner_move_fire_chain;
}

void gunner_refire_chain(edict_t *self)
{
	if (self->enemy->health > 0)
		if ( visible (self, self->enemy) )
			if (random() <= 0.5)
			{
				self->monsterinfo.currentmove = &gunner_move_fire_chain;
				return;
			}
	self->monsterinfo.currentmove = &gunner_move_endfire_chain;
}

// petunindan tad 
void traitor_fire_chain(edict_t *self)
{
	TraitorFire (self);
}

void traitor_fire_chain_female(edict_t *self)
{
	TraitorFireFemaleChaingun (self);
}

void traitor_fire_rocket(edict_t *self)
{
	TraitorRocket (self);
}

void traitor_fire_bfg(edict_t *self)
{
	TraitorBfg (self);
}

void traitor_fire_plasma(edict_t *self)
{
	TraitorPlasma (self);
}

void traitor_fire_hyper(edict_t *self)
{
	TraitorHyper (self);
}

//hyper
void traitor_refire_hyper16(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_endfire_chain;
}

void traitor_refire_hyper15(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper16;
}

void traitor_refire_hyper14(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper15;
}

void traitor_refire_hyper13(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper14;
}

void traitor_refire_hyper12(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper13;
}

void traitor_refire_hyper11(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper12;
}

//

void traitor_refire_hyper10(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper11;
}

void traitor_refire_hyper9(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper10;
}

void traitor_refire_hyper8(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper9;
}

void traitor_refire_hyper7(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper8;
}

void traitor_refire_hyper6(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper7;
}

void traitor_refire_hyper5(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper6;
}

void traitor_refire_hyper4(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper5;
}

void traitor_refire_hyper3(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper4;
}
void traitor_refire_hyper2(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper3;
}
void traitor_refire_hyper1(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper2 ;
}

//hyper boss
void traitor_refire_hyper_boss_16(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_frames_endfire_chain_cloakon;
}

void traitor_refire_hyper_boss_15(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_16;
}

void traitor_refire_hyper_boss_14(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_15;
}

void traitor_refire_hyper_boss_13(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_14;
}

void traitor_refire_hyper_boss_12(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_13;
}

void traitor_refire_hyper_boss_11(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_12;
}

//

void traitor_refire_hyper_boss_10(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_11;
}

void traitor_refire_hyper_boss_9(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_10;
}

void traitor_refire_hyper_boss_8(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_9;
}

void traitor_refire_hyper_boss_7(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_8;
}

void traitor_refire_hyper_boss_6(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_7;
}

void traitor_refire_hyper_boss_5(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_6;
}

void traitor_refire_hyper_boss_4(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_5;
}

void traitor_refire_hyper_boss_3(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_4;
}
void traitor_refire_hyper_boss_2(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_3;
}
void traitor_refire_hyper_boss_1(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_hyper_boss_2 ;
}

// chaingun

void traitor_refire_chain16(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_endfire_chain;
}

void traitor_refire_chain15(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain16;
}

void traitor_refire_chain14(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain15;
}

void traitor_refire_chain13(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain14;
}

void traitor_refire_chain12(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain13;
}

void traitor_refire_chain11(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain12;
}

//

void traitor_refire_chain10(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain11;
}

void traitor_refire_chain9(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain10;
}

void traitor_refire_chain8(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain9;
}

void traitor_refire_chain7(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain8;
}

void traitor_refire_chain6(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain7;
}

void traitor_refire_chain5(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain6;
}

void traitor_refire_chain4(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain5;
}

void traitor_refire_chain3(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain4;
}
void traitor_refire_chain2(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain3;
}
void traitor_refire_chain1(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain2 ;
}

// boss chaingun

void traitor_refire_chain_boss_16(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_frames_endfire_chain_cloakon;
}

void traitor_refire_chain_boss_15(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_16;
}

void traitor_refire_chain_boss_14(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_15;
}

void traitor_refire_chain_boss_13(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_14;
}

void traitor_refire_chain_boss_12(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_13;
}

void traitor_refire_chain_boss_11(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_12;
}

//

void traitor_refire_chain_boss_10(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_11;
}

void traitor_refire_chain_boss_9(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_10;
}

void traitor_refire_chain_boss_8(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_9;
}

void traitor_refire_chain_boss_7(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_8;
}

void traitor_refire_chain_boss_6(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_7;
}

void traitor_refire_chain_boss_5(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_6;
}

void traitor_refire_chain_boss_4(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_5;
}

void traitor_refire_chain_boss_3(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_4;
}
void traitor_refire_chain_boss_2(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_3;
}
void traitor_refire_chain_boss_1(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_fire_chain_boss_2 ;
}
//

/*
void gunner_dodge (edict_t *self, edict_t *attacker, float eta, trace_t *tr)
{
// original quake2 dodge code

	if (random() > 0.25)
		return;

	if (!self->enemy)
		self->enemy = attacker;

	self->monsterinfo.currentmove = &gunner_move_duck;

//===========
//PMM - rogue rewrite of gunner dodge code.
	float	r;
	float	height;
	int		shooting = 0;

	if (!self->enemy)
	{
		self->enemy = attacker;
		FoundTarget (self);
	}

	// PMM - don't bother if it's going to hit anyway; fix for weird in-your-face etas (I was
	// seeing numbers like 13 and 14)
	if ((eta < 0.1) || (eta > 5))
		return;

	r = random();
	if (r > (0.25*((skill->value)+1)))
		return;

	if ((self->monsterinfo.currentmove == &gunner_move_attack_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_fire_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_attack_grenade)
		)
	{
		shooting = 1;
	}
	if (self->monsterinfo.aiflags & AI_DODGING)
	{
		height = self->absmax[2];
	}
	else
	{
		height = self->absmax[2]-32-1;  // the -1 is because the absmax is s.origin + maxs + 1
	}

	// check to see if it makes sense to duck
	if (tr->endpos[2] <= height)
	{
		vec3_t right, diff;
		if (shooting)
		{
			self->monsterinfo.attack_state = AS_SLIDING;
			return;
		}
		AngleVectors (self->s.angles, NULL, right, NULL);
		VectorSubtract (tr->endpos, self->s.origin, diff);
		if (DotProduct (right, diff) < 0)
		{
			self->monsterinfo.lefty = 1;
		}
		// if it doesn't sense to duck, try to strafe away
		monster_done_dodge (self);
		self->monsterinfo.currentmove = &gunner_move_run;
		self->monsterinfo.attack_state = AS_SLIDING;
		return;
	}

	if (skill->value == 0)
	{
		self->monsterinfo.currentmove = &gunner_move_duck;
		// PMM - stupid dodge
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
		self->monsterinfo.aiflags |= AI_DODGING;
		return;
	}

	if (!shooting)
	{
		self->monsterinfo.currentmove = &gunner_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));
		self->monsterinfo.aiflags |= AI_DODGING;
	}
	return;
//PMM
//===========
}
*/
//===========
//PGM
void gunner_jump_now (edict_t *self)
{
	vec3_t	forward,up;

	monster_jump_start (self);

	AngleVectors (self->s.angles, forward, NULL, up);
	VectorMA(self->velocity, 100, forward, self->velocity);
	VectorMA(self->velocity, 300, up, self->velocity);
}

void gunner_jump2_now (edict_t *self)
{
	vec3_t	forward,up;

	monster_jump_start (self);

	AngleVectors (self->s.angles, forward, NULL, up);
	VectorMA(self->velocity, 150, forward, self->velocity);
	VectorMA(self->velocity, 400, up, self->velocity);
}

void gunner_jump_wait_land (edict_t *self)
{
	if(self->groundentity == NULL)
	{
		self->monsterinfo.nextframe = self->s.frame;

		if(monster_jump_finished (self))
			self->monsterinfo.nextframe = self->s.frame + 1;
	}
	else 
		self->monsterinfo.nextframe = self->s.frame + 1;
}

mframe_t gunner_frames_jump [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, gunner_jump_now,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, gunner_jump_wait_land,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t gunner_move_jump = { FRAME_jump01, FRAME_jump10, gunner_frames_jump, gunner_run };

mframe_t gunner_frames_jump2 [] =
{
	ai_move, -8, NULL,
	ai_move, -4, NULL,
	ai_move, -4, NULL,
	ai_move, 0, gunner_jump_now,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, gunner_jump_wait_land,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t gunner_move_jump2 = { FRAME_jump01, FRAME_jump10, gunner_frames_jump2, gunner_run };

void gunner_jump (edict_t *self)
{
	if(!self->enemy)
		return;

	monster_done_dodge (self);

	if(self->enemy->s.origin[2] > self->s.origin[2])
		self->monsterinfo.currentmove = &gunner_move_jump2;
	else
		self->monsterinfo.currentmove = &gunner_move_jump;
}

// petunindan
void traitor_jump_now (edict_t *self)
{
	vec3_t	forward,up;

	monster_jump_start (self);

	AngleVectors (self->s.angles, forward, NULL, up);
	VectorMA(self->velocity, 100, forward, self->velocity);
	VectorMA(self->velocity, 300, up, self->velocity);
}

void traitor_jump2_now (edict_t *self)
{
	vec3_t	forward,up;

	monster_jump_start (self);

	AngleVectors (self->s.angles, forward, NULL, up);
	VectorMA(self->velocity, 150, forward, self->velocity);
	VectorMA(self->velocity, 400, up, self->velocity);
}

void traitor_jump_wait_land (edict_t *self)
{
	if(self->groundentity == NULL)
	{
		self->monsterinfo.nextframe = self->s.frame;

		if(monster_jump_finished (self))
			self->monsterinfo.nextframe = self->s.frame + 1;
	}
	else 
		self->monsterinfo.nextframe = self->s.frame + 1;
}

mframe_t traitor_frames_jump [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, traitor_jump_now,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, traitor_jump_wait_land,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t traitor_move_jump = { 66, 71, traitor_frames_jump, traitor_run };

mframe_t traitor_frames_jump2 [] =
{
	ai_move, -8, NULL,
	ai_move, -4, NULL,
	ai_move, -4, NULL,
	ai_move, 0, traitor_jump_now,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, traitor_jump_wait_land,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t traitor_move_jump2 = { 66, 71, traitor_frames_jump2, traitor_run };

void traitor_jump (edict_t *self)
{
	if(!self->enemy)
		return;

	monster_done_dodge (self);

	if(self->enemy->s.origin[2] > self->s.origin[2])
		self->monsterinfo.currentmove = &traitor_move_jump2;
	else
		self->monsterinfo.currentmove = &traitor_move_jump;
}
//

//===========
//PGM
qboolean gunner_blocked (edict_t *self, float dist)
{
	if(blocked_checkshot (self, 0.25 + (0.05 * skill->value) ))
		return true;

	if(blocked_checkplat (self, dist))
		return true;

	if(blocked_checkjump (self, dist, 192, 40))
	{
		gunner_jump(self);
		return true;
	}

	return false;
}

// petunindan tad
qboolean traitor_blocked (edict_t *self, float dist)
{
	if(blocked_checkshot (self, 0.25 + (0.05 * skill->value) ))
		return true;

	if(blocked_checkplat (self, dist))
		return true;

	if(blocked_checkjump (self, dist, 192, 40))
	{
		traitor_jump(self);
		return true;
	}

	return false;
}
//

//PGM
//===========

// PMM - new duck code
void gunner_duck (edict_t *self, float eta)
{
	if ((self->monsterinfo.currentmove == &gunner_move_jump2) ||
		(self->monsterinfo.currentmove == &gunner_move_jump))
	{
		return;
	}

	if ((self->monsterinfo.currentmove == &gunner_move_attack_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_fire_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_attack_grenade)
		)
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->value)
		{
			self->monsterinfo.aiflags &= ~AI_DUCKED;
			return;
		}
	}

	if (skill->value == 0)
		// PMM - stupid dodge
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
	else
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));

	// has to be done immediately otherwise he can get stuck
	gunner_duck_down(self);

	self->monsterinfo.nextframe = FRAME_duck01;
	self->monsterinfo.currentmove = &gunner_move_duck;
	return;
}

// petunindan tad
void traitor_duck (edict_t *self, float eta)
{
	if ((self->monsterinfo.currentmove == &gunner_move_jump2) ||
		(self->monsterinfo.currentmove == &gunner_move_jump))
	{
		return;
	}

	if ((self->monsterinfo.currentmove == &traitor_move_fire_chain1) ||
		(self->monsterinfo.currentmove == &traitor_move_fire_chain1) ||
		(self->monsterinfo.currentmove == &traitor_move_fire_chain1)
		)
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->value)
		{
			self->monsterinfo.aiflags &= ~AI_DUCKED;
			return;
		}
	}

	if (skill->value == 0)
		// PMM - stupid dodge
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
	else
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));

	// has to be done immediately otherwise he can get stuck
	traitor_duck_down(self);

	self->monsterinfo.nextframe = 135;
	self->monsterinfo.currentmove = &traitor_move_duck;
	return;
}

void traitor_sidestep (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &traitor_move_jump2) ||
		(self->monsterinfo.currentmove == &traitor_move_jump))
	{
		return;
	}

	if ((self->monsterinfo.currentmove == &traitor_move_fire_chain1) ||
		(self->monsterinfo.currentmove == &traitor_run) ||
		(self->monsterinfo.currentmove == &traitor_move_fire_chain1)
		)
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->value)
		{
			self->monsterinfo.aiflags &= ~AI_DODGING;
			return;
		}
	}

	if (self->monsterinfo.currentmove != &traitor_move_run)
		self->monsterinfo.currentmove = &traitor_move_run;
}

//

void gunner_sidestep (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &gunner_move_jump2) ||
		(self->monsterinfo.currentmove == &gunner_move_jump))
	{
		return;
	}

	if ((self->monsterinfo.currentmove == &gunner_move_attack_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_fire_chain) ||
		(self->monsterinfo.currentmove == &gunner_move_attack_grenade)
		)
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->value)
		{
			self->monsterinfo.aiflags &= ~AI_DODGING;
			return;
		}
	}

	if (self->monsterinfo.currentmove != &gunner_move_run)
		self->monsterinfo.currentmove = &gunner_move_run;
}


/*QUAKED monster_gunner (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_gunner (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_death = gi.soundindex ("gunner/death1.wav");	
	sound_pain = gi.soundindex ("gunner/gunpain2.wav");	
	sound_pain2 = gi.soundindex ("gunner/gunpain1.wav");	
	sound_idle = gi.soundindex ("gunner/gunidle1.wav");	
	sound_open = gi.soundindex ("gunner/gunatck1.wav");	
	sound_search = gi.soundindex ("gunner/gunsrch1.wav");	
	sound_sight = gi.soundindex ("gunner/sight1.wav");	

	gi.soundindex ("gunner/gunatck2.wav");
	gi.soundindex ("gunner/gunatck3.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/gunner/tris.md2");
		self->s.skinnum = self->style * 2;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/gunner/tris.md2");

	{ // Coconut Monkey 2 sombrero
		cvar_t	*gamedir = gi.cvar("gamedir", "", 0);
		if (strlen(gamedir->string) && !strcmp(gamedir->string, "coconut2"))
			self->s.modelindex2 = gi.modelindex ("models/monsters/gunner/gear.md2");
	}

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	if(!self->health)
		self->health = 175;
	if(!self->gib_health)
		self->gib_health = -150;
	if(!self->mass)
		self->mass = 200;

	self->pain = gunner_pain;
	self->die = gunner_die;

	self->monsterinfo.stand = gunner_stand;
	self->monsterinfo.walk = gunner_walk;
	self->monsterinfo.run = gunner_run;
	// pmm
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.duck = gunner_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = gunner_sidestep;
//	self->monsterinfo.dodge = gunner_dodge;
	// pmm
	self->monsterinfo.attack = gunner_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = gunner_sight;
	self->monsterinfo.search = gunner_search;
	self->monsterinfo.blocked = gunner_blocked;		//PGM
	
	if (!self->blood_type)
		self->blood_type = 3; //sparks and blood

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}
	if(!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.30;
	self->common_name = "Gunner";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &gunner_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	// PMM
	self->monsterinfo.blindfire = true;

	walkmonster_start (self);
}

void SP_monster_traitor (edict_t *self)
{
	
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_death_tr = gi.soundindex ("player/male/death1.wav");	
	sound_pain_tr = gi.soundindex ("player/male/pain100_1.wav");	
	sound_pain2_tr = gi.soundindex ("player/male/pain100_2.wav");	
	sound_idle = gi.soundindex ("gunner/gunidle1.wav");	
	sound_open = gi.soundindex ("gunner/gunatck1.wav");	
	sound_search = gi.soundindex ("gunner/gunsrch1.wav");	
	sound_sight_tr = gi.soundindex ("infantry/infsght1.wav");	

	gi.soundindex ("infantry/infatck1.wav");
	gi.soundindex ("gunner/gunatck3.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/traitor/tris.md2");
		self->s.skinnum = self->style * 2;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/traitor/tris.md2");

	{ // Coconut Monkey 2 sombrero
		cvar_t	*gamedir = gi.cvar("gamedir", "", 0);
		if (strlen(gamedir->string) && !strcmp(gamedir->string, "coconut2"))
			self->s.modelindex2 = gi.modelindex ("models/monsters/traitor/gear.md2");
	}

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	if(!self->health)
		self->health = 175;
	if(!self->gib_health)
		self->gib_health = -150;
	if(!self->mass)
		self->mass = 200;
	
	//w_ weapon for monster
	self->s.modelindex2 = gi.modelindex ("players/male/w_chaingun.md2");

	self->pain = traitor_pain;
	self->die = traitor_die;

	self->monsterinfo.stand = traitor_stand;
	self->monsterinfo.walk = traitor_walk;
	self->monsterinfo.run = traitor_run;
	// pmm
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.duck = traitor_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = traitor_sidestep;
//	self->monsterinfo.dodge = gunner_dodge;
	// pmm
	self->monsterinfo.attack = traitor_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = traitor_sight;
	self->monsterinfo.search = traitor_search;
	self->monsterinfo.blocked = traitor_blocked;		//PGM
	
	if (!self->blood_type)
		self->blood_type = 4; //standard

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}
	if(!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.30;
	self->common_name = "Male Traitor";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &traitor_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	// PMM
	self->monsterinfo.blindfire = true;

	walkmonster_start (self);
}

void SP_monster_traitor_female (edict_t *self)
{
	
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_death_fetr = gi.soundindex ("player/female/death1.wav");	
	sound_pain_fetr = gi.soundindex ("player/female/pain100_1.wav");	
	sound_pain2_fetr = gi.soundindex ("player/female/pain100_2.wav");	
	sound_idle = gi.soundindex ("gunner/gunidle1.wav");	
	sound_open = gi.soundindex ("gunner/gunatck1.wav");	
	sound_search = gi.soundindex ("gunner/gunsrch1.wav");	
	sound_sight_fetr = gi.soundindex ("chick/chksght1.wav");	

	gi.soundindex ("infantry/infatck1.wav");
	gi.soundindex ("gunner/gunatck3.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/traitf/tris.md2");
		self->s.skinnum = self->style * 2;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/traitf/tris.md2");

	{ // Coconut Monkey 2 sombrero
		cvar_t	*gamedir = gi.cvar("gamedir", "", 0);
		if (strlen(gamedir->string) && !strcmp(gamedir->string, "coconut2"))
			self->s.modelindex2 = gi.modelindex ("models/monsters/traitor/gear.md2");
	}

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	if(!self->health)
		self->health = 175;
	if(!self->gib_health)
		self->gib_health = -150;
	if(!self->mass)
		self->mass = 200;
	
	//w_ weapon for monster
	self->s.modelindex2 = gi.modelindex ("players/female/w_chaingun.md2");

	self->pain = traitor_female_pain;
	self->die = traitor_female_die;

	self->monsterinfo.stand = traitor_stand;
	self->monsterinfo.walk = traitor_walk;
	self->monsterinfo.run = traitor_run;
	// pmm
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.duck = traitor_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = traitor_sidestep;
//	self->monsterinfo.dodge = gunner_dodge;
	// pmm
	self->monsterinfo.attack = traitor_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = traitor_female_sight;
	self->monsterinfo.search = traitor_search;
	self->monsterinfo.blocked = traitor_blocked;		//PGM
	
	if (!self->blood_type)
		self->blood_type = 4; //standard

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}
	if(!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.30;
	self->common_name = "Female Traitor";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &traitor_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	// PMM
	self->monsterinfo.blindfire = true;

	walkmonster_start (self);
}

void SP_monster_traitor_boss (edict_t *self)
{
	
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_death_fetr = gi.soundindex ("player/female/death1.wav");	
	sound_pain_fetr = gi.soundindex ("player/female/pain100_1.wav");	
	sound_pain2_fetr = gi.soundindex ("player/female/pain100_2.wav");	
	sound_idle = gi.soundindex ("gunner/gunidle1.wav");	
	sound_open = gi.soundindex ("gunner/gunatck1.wav");	
	sound_search = gi.soundindex ("gunner/gunsrch1.wav");	
	sound_sight_fetr = gi.soundindex ("chick/chksght1.wav");	

	gi.soundindex ("infantry/infatck1.wav");
	gi.soundindex ("gunner/gunatck3.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->s.skinnum = 2;

	self->s.modelindex = gi.modelindex ("models/monsters/traitf/tris.md2");

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	
	self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
	self->monsterinfo.power_armor_power = 800;

	if(!self->health)
		self->health = 2800;
	if(!self->gib_health)
		self->gib_health = -150;
	if(!self->mass)
		self->mass = 200;
	
	//w_ weapon for monster
	self->s.modelindex2 = gi.modelindex ("players/female/w_chaingun.md2");

	self->pain = traitor_female_pain;
	self->die = traitor_female_die;

	self->monsterinfo.stand = traitor_stand;
	self->monsterinfo.walk = traitor_walk;
	self->monsterinfo.run = traitor_run_boss;
	// pmm
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.duck = traitor_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = traitor_sidestep;
//	self->monsterinfo.dodge = gunner_dodge;
	// pmm
	self->monsterinfo.attack = traitor_attack_boss;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = traitor_female_sight;
	self->monsterinfo.search = traitor_search;
	self->monsterinfo.blocked = traitor_blocked;		//PGM
	
	if (!self->blood_type)
		self->blood_type = 4; //standard

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}
	if(!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.30;
	self->common_name = "Female Traitor Boss";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &traitor_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	// PMM
	self->monsterinfo.blindfire = true;

	walkmonster_start (self);
}

void traitor_cloakon(edict_t *self)
{
	gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/power1.wav"), 1, ATTN_NORM, 0);
	self->svflags |= SVF_NOCLIENT;
}

void traitor_cloakoff(edict_t *self)
{
	gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/power2.wav"), 1, ATTN_NORM, 0);
	self->svflags &= ~SVF_NOCLIENT;
}

void traitor_refire_allguns(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_endfire_chain;
}

void traitor_refire_boss(edict_t *self)
{
	self->monsterinfo.currentmove = &traitor_move_endfire_chain_cloakon;
}
