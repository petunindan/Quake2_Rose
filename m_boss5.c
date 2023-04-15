/*
==============================================================================

boss5

==============================================================================
*/

#include "g_local.h"
#include "m_supertank.h"

qboolean visible (edict_t *self, edict_t *other);

static int	sound_pain1;
static int	sound_pain2;
static int	sound_pain3;
static int	sound_death;
static int	sound_search1;
static int	sound_search2;

static	int	tread_sound;

void TreadSound2 (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, tread_sound, 1, ATTN_NORM, 0);
}

void boss5_search (edict_t *self)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, sound_search1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_search2, 1, ATTN_NORM, 0);
}


void boss5_dead (edict_t *self);
void boss5Rocket (edict_t *self);
void boss5MachineGun (edict_t *self);
void boss5_reattack1(edict_t *self);


//
// stand
//

mframe_t boss5_frames_stand []=
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
mmove_t	boss5_move_stand = {FRAME_stand_1, FRAME_stand_60, boss5_frames_stand, NULL};
	
void boss5_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &boss5_move_stand;
}


mframe_t boss5_frames_run [] =
{
	ai_run, 12,	TreadSound2,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL,
	ai_run, 12,	NULL
};
mmove_t	boss5_move_run = {FRAME_forwrd_1, FRAME_forwrd_18, boss5_frames_run, NULL};

//
// walk
//


mframe_t boss5_frames_forward [] =
{
	ai_walk, 4,	TreadSound2,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL,
	ai_walk, 4,	NULL
};
mmove_t	boss5_move_forward = {FRAME_forwrd_1, FRAME_forwrd_18, boss5_frames_forward, NULL};

void boss5_forward (edict_t *self)
{
		self->monsterinfo.currentmove = &boss5_move_forward;
}

void boss5_walk (edict_t *self)
{
		self->monsterinfo.currentmove = &boss5_move_forward;
}

void boss5_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &boss5_move_stand;
	else
		self->monsterinfo.currentmove = &boss5_move_run;
}

mframe_t boss5_frames_turn_right [] =
{
	ai_move,	0,	TreadSound2,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_turn_right = {FRAME_right_1, FRAME_right_18, boss5_frames_turn_right, boss5_run};

mframe_t boss5_frames_turn_left [] =
{
	ai_move,	0,	TreadSound2,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_turn_left = {FRAME_left_1, FRAME_left_18, boss5_frames_turn_left, boss5_run};


mframe_t boss5_frames_pain3 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_pain3 = {FRAME_pain3_9, FRAME_pain3_12, boss5_frames_pain3, boss5_run};

mframe_t boss5_frames_pain2 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_pain2 = {FRAME_pain2_5, FRAME_pain2_8, boss5_frames_pain2, boss5_run};

mframe_t boss5_frames_pain1 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_pain1 = {FRAME_pain1_1, FRAME_pain1_4, boss5_frames_pain1, boss5_run};

mframe_t boss5_frames_death1 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	boss5_dead //was BossExplode
};
mmove_t boss5_move_death = {FRAME_death_1, FRAME_death_24, boss5_frames_death1, NULL}; //was boss5_dead

mframe_t boss5_frames_backward[] =
{
	ai_walk, 0,	TreadSound2,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL,
	ai_walk, 0,	NULL
};
mmove_t	boss5_move_backward = {FRAME_backwd_1, FRAME_backwd_18, boss5_frames_backward, NULL};

mframe_t boss5_frames_attack4[]=
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_attack4 = {FRAME_attak4_1, FRAME_attak4_6, boss5_frames_attack4, boss5_run};

mframe_t boss5_frames_attack3[]=
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_attack3 = {FRAME_attak3_1, FRAME_attak3_27, boss5_frames_attack3, boss5_run};

mframe_t boss5_frames_attack2[]=
{
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	boss5Rocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	boss5Rocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	boss5Rocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_attack2 = {FRAME_attak2_1, FRAME_attak2_27, boss5_frames_attack2, boss5_run};

mframe_t boss5_frames_attack1[]=
{
	ai_charge,	0,	boss5MachineGun,
	ai_charge,	0,	boss5MachineGun,
	ai_charge,	0,	boss5MachineGun,
	ai_charge,	0,	boss5MachineGun,
	ai_charge,	0,	boss5MachineGun,
	ai_charge,	0,	boss5MachineGun,

};
mmove_t boss5_move_attack1 = {FRAME_attak1_1, FRAME_attak1_6, boss5_frames_attack1, boss5_reattack1};

mframe_t boss5_frames_end_attack1[]=
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t boss5_move_end_attack1 = {FRAME_attak1_7, FRAME_attak1_20, boss5_frames_end_attack1, boss5_run};


void boss5_reattack1(edict_t *self)
{
	if (visible(self, self->enemy))
		if (random() < 0.9)
			self->monsterinfo.currentmove = &boss5_move_attack1;
		else
			self->monsterinfo.currentmove = &boss5_move_end_attack1;	
	else
		self->monsterinfo.currentmove = &boss5_move_end_attack1;
}

void boss5_pain (edict_t *self, edict_t *other, float kick, int damage)
{

	if (self->health < (self->max_health / 2))
	{
		self->s.skinnum |= 1;
		if (!(self->fogclip & 2)) //custom bloodtype flag check
			self->blood_type = 3; //sparks and blood
	}

	if (level.time < self->pain_debounce_time)
			return;

	// Lessen the chance of him going into his pain frames
	if (damage <=25)
		if (random()<0.2)
			return;

	// Don't go into pain if he's firing his rockets
	if (skill->value >= 2)
		if ( (self->s.frame >= FRAME_attak2_1) && (self->s.frame <= FRAME_attak2_14) )
			return;

	self->pain_debounce_time = level.time + 3;

	if (damage <= 10)
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &boss5_move_pain1;
	}
	else if (damage <= 25)
	{
		gi.sound (self, CHAN_VOICE, sound_pain3, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &boss5_move_pain2;
	}
	else
	{
		gi.sound (self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &boss5_move_pain3;
	}
};


void boss5Rocket (edict_t *self)
{
	vec3_t	forward, right;
	vec3_t	start;
	vec3_t	dir;
	vec3_t	vec;
	int		flash_number;

	if (self->s.frame == FRAME_attak2_8)
		flash_number = MZ2_SUPERTANK_ROCKET_1;
	else if (self->s.frame == FRAME_attak2_11)
		flash_number = MZ2_SUPERTANK_ROCKET_2;
	else // (self->s.frame == FRAME_attak2_14)
		flash_number = MZ2_SUPERTANK_ROCKET_3;

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

	VectorCopy (self->enemy->s.origin, vec);
	vec[2] += self->enemy->viewheight;

	// Lazarus fog reduction of accuracy
	if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
	{
		vec[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		vec[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		vec[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
	}

	VectorSubtract (vec, start, dir);
	VectorNormalize (dir);

//	monster_fire_rocket (self, start, dir, 50, 500, flash_number);
	monster_fire_rocket (self, start, dir, 50, 500, flash_number,
		(self->spawnflags & SF_MONSTER_SPECIAL ? self->enemy : NULL) );
}	

void boss5MachineGun (edict_t *self)
{
	vec3_t	dir;
	vec3_t	vec;
	vec3_t	start;
	vec3_t	forward, right;
	int		flash_number;

	flash_number = MZ2_SUPERTANK_MACHINEGUN_1 + (self->s.frame - FRAME_attak1_1);

	//FIXME!!!
	dir[0] = 0;
	dir[1] = self->s.angles[1];
	dir[2] = 0;

	AngleVectors (dir, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

	if (self->enemy)
	{
		VectorCopy (self->enemy->s.origin, vec);
		VectorMA (vec, 0, self->enemy->velocity, vec);
		vec[2] += self->enemy->viewheight;

		// Lazarus fog reduction of accuracy
		if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
		{
			vec[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			vec[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			vec[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		}

		VectorSubtract (vec, start, forward);
		VectorNormalize (forward);
  }

	monster_fire_bullet (self, start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}	


void boss5_attack(edict_t *self)
{
	vec3_t	vec;
	float	range;
	//float	r;

	VectorSubtract (self->enemy->s.origin, self->s.origin, vec);
	range = VectorLength (vec);

	//r = random();

	// Attack 1 == Chaingun
	// Attack 2 == Rocket Launcher

	if (range <= 160)
	{
		self->monsterinfo.currentmove = &boss5_move_attack1;
	}
	else
	{	// fire rockets more often at distance
		if (random() < 0.3)
			self->monsterinfo.currentmove = &boss5_move_attack1;
		else
			self->monsterinfo.currentmove = &boss5_move_attack2;
	}
}


//
// death
//

void boss5_dead (edict_t *self)
{
	/*
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	*/
	VectorSet (self->mins, -60, -60, 0);
	VectorSet (self->maxs, 60, 60, 72);
	self->movetype = MOVETYPE_TOSS;
//	self->svflags |= SVF_DEADMONSTER;
	self->s.frame = FRAME_death_24;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);
}


void boss5_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{	
	self->s.skinnum |= 1;
	if (!(self->fogclip & 2)) //custom bloodtype flag check
		self->blood_type = 3; //sparks and blood
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

	//Knightmare-  check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
		BossExplode (self);

	if (self->deadflag == DEAD_DEAD)
		return;

	gi.sound (self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
	self->deadflag = DEAD_DEAD;
//	self->takedamage = DAMAGE_NO;
	self->takedamage = DAMAGE_YES;
	self->count = 0;
	self->monsterinfo.currentmove = &boss5_move_death;
}

//===========
//PGM
qboolean boss5_blocked (edict_t *self, float dist)
{
	if(blocked_checkshot (self, 0.25 + (0.05 * skill->value) ))
		return true;

	if(blocked_checkplat (self, dist))
		return true;

	return false;
}
//PGM
//===========

//
// monster_boss5
//

/*QUAKED monster_boss5 (1 .5 0) (-64 -64 0) (64 64 112) Ambush Trigger_Spawn Sight GoodGuy NoGib HomingRockets
*/
void SP_monster_boss5 (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain1 = gi.soundindex ("bosstank/btkpain1.wav");
	sound_pain2 = gi.soundindex ("bosstank/btkpain2.wav");
	sound_pain3 = gi.soundindex ("bosstank/btkpain3.wav");
	sound_death = gi.soundindex ("bosstank/btkdeth1.wav");
	sound_search1 = gi.soundindex ("bosstank/btkunqv1.wav");
	sound_search2 = gi.soundindex ("bosstank/btkunqv2.wav");

//	self->s.sound = gi.soundindex ("bosstank/btkengn1.wav");
	tread_sound = gi.soundindex ("bosstank/btkengn1.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/boss5/tris.md2");
		self->s.skinnum = self->style * 2;
	//	self->style = 0; //clear for custom bloodtype flag
	}

	self->s.modelindex = gi.modelindex ("models/monsters/boss5/tris.md2");
	VectorSet (self->mins, -64, -64, 0);
	VectorSet (self->maxs, 64, 64, 112);

	if(!self->health)
		self->health = 1500;
	if(!self->gib_health)
		self->gib_health = -999;
	if(!self->mass)
		self->mass = 800;

	self->pain = boss5_pain;
	self->die = boss5_die;
	self->monsterinfo.stand = boss5_stand;
	self->monsterinfo.walk = boss5_walk;
	self->monsterinfo.run = boss5_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.attack = boss5_attack;
	self->monsterinfo.search = boss5_search;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.blocked = boss5_blocked;		//PGM

	if (!self->blood_type)
		self->blood_type = 2; //sparks
	else
		self->fogclip |= 2; //custom bloodtype flag

	gi.linkentity (self);
	
	self->monsterinfo.currentmove = &boss5_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}
	else
	{	// RAFAEL
		self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = 400;
	}
	self->common_name = "Beta Class Supertank";

	walkmonster_start(self);

	//PMM
	//self->monsterinfo.aiflags |= AI_IGNORE_SHOTS;
	//PMM
}
