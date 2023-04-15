/*
==============================================================================

SUPERTANK

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

void TreadSound (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, tread_sound, 1, ATTN_NORM, 0);
}

void supertank_search (edict_t *self)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, sound_search1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_search2, 1, ATTN_NORM, 0);
}


void supertank_dead (edict_t *self);
void hypertank_dead (edict_t *self);
void supertankRocket (edict_t *self);
void supertankMachineGun (edict_t *self);
void supertank_reattack1(edict_t *self);
// petunindan hypertank
void hypertankRocket (edict_t *self);
void hypertankMachineGun (edict_t *self);
void hypertank_reattack1(edict_t *self);
//


//
// stand
//

mframe_t supertank_frames_stand []=
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
mmove_t	supertank_move_stand = {FRAME_stand_1, FRAME_stand_60, supertank_frames_stand, NULL};
	
void supertank_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &supertank_move_stand;
}


mframe_t supertank_frames_run [] =
{
	ai_run, 12,	TreadSound,
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
mmove_t	supertank_move_run = {FRAME_forwrd_1, FRAME_forwrd_18, supertank_frames_run, NULL};

//
// walk
//


mframe_t supertank_frames_forward [] =
{
	ai_walk, 4,	TreadSound,
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
mmove_t	supertank_move_forward = {FRAME_forwrd_1, FRAME_forwrd_18, supertank_frames_forward, NULL};

void supertank_forward (edict_t *self)
{
		self->monsterinfo.currentmove = &supertank_move_forward;
}

void supertank_walk (edict_t *self)
{
		self->monsterinfo.currentmove = &supertank_move_forward;
}

void supertank_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &supertank_move_stand;
	else
		self->monsterinfo.currentmove = &supertank_move_run;
}

mframe_t supertank_frames_turn_right [] =
{
	ai_move,	0,	TreadSound,
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
mmove_t supertank_move_turn_right = {FRAME_right_1, FRAME_right_18, supertank_frames_turn_right, supertank_run};

mframe_t supertank_frames_turn_left [] =
{
	ai_move,	0,	TreadSound,
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
mmove_t supertank_move_turn_left = {FRAME_left_1, FRAME_left_18, supertank_frames_turn_left, supertank_run};


mframe_t supertank_frames_pain3 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t supertank_move_pain3 = {FRAME_pain3_9, FRAME_pain3_12, supertank_frames_pain3, supertank_run};

mframe_t supertank_frames_pain2 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t supertank_move_pain2 = {FRAME_pain2_5, FRAME_pain2_8, supertank_frames_pain2, supertank_run};

mframe_t supertank_frames_pain1 [] =
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t supertank_move_pain1 = {FRAME_pain1_1, FRAME_pain1_4, supertank_frames_pain1, supertank_run};

mframe_t supertank_frames_death1 [] =
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
	ai_move,	0,	supertank_dead //was BossExplode
};
mmove_t supertank_move_death = {FRAME_death_1, FRAME_death_24, supertank_frames_death1, NULL}; //was supertank_dead

// petunindan rose hypertank
mframe_t hypertank_frames_death1 [] =
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
	ai_move,	0,	hypertank_dead //was BossExplode
};
mmove_t hypertank_move_death = {FRAME_death_1, FRAME_death_24, hypertank_frames_death1, hypertank_dead}; //was supertank_dead

mframe_t supertank_frames_backward[] =
{
	ai_walk, 0,	TreadSound,
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
mmove_t	supertank_move_backward = {FRAME_backwd_1, FRAME_backwd_18, supertank_frames_backward, NULL};

mframe_t supertank_frames_attack4[]=
{
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL
};
mmove_t supertank_move_attack4 = {FRAME_attak4_1, FRAME_attak4_6, supertank_frames_attack4, supertank_run};

mframe_t supertank_frames_attack3[]=
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
mmove_t supertank_move_attack3 = {FRAME_attak3_1, FRAME_attak3_27, supertank_frames_attack3, supertank_run};

mframe_t supertank_frames_attack2[]=
{
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	supertankRocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	supertankRocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	supertankRocket,
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
mmove_t supertank_move_attack2 = {FRAME_attak2_1, FRAME_attak2_27, supertank_frames_attack2, supertank_run};

mframe_t hypertank_frames_attack2[]=
{
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	NULL,
	ai_charge,	0,	hypertankRocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	hypertankRocket,
	ai_move,	0,	NULL,
	ai_move,	0,	NULL,
	ai_move,	0,	hypertankRocket,
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
mmove_t hypertank_move_attack2 = {FRAME_attak2_1, FRAME_attak2_27, hypertank_frames_attack2, supertank_run};

mframe_t supertank_frames_attack1[]=
{
	ai_charge,	0,	supertankMachineGun,
	ai_charge,	0,	supertankMachineGun,
	ai_charge,	0,	supertankMachineGun,
	ai_charge,	0,	supertankMachineGun,
	ai_charge,	0,	supertankMachineGun,
	ai_charge,	0,	supertankMachineGun,

};
mmove_t supertank_move_attack1 = {FRAME_attak1_1, FRAME_attak1_6, supertank_frames_attack1, supertank_reattack1};

// petunindan hypertank chaingun frames
mframe_t hypertank_frames_attack1[]=
{
	ai_charge,	0,	hypertankMachineGun,
	ai_charge,	0,	hypertankMachineGun,
	ai_charge,	0,	hypertankMachineGun,
	ai_charge,	0,	hypertankMachineGun,
	ai_charge,	0,	hypertankMachineGun,
	ai_charge,	0,	hypertankMachineGun,

};
mmove_t hypertank_move_attack1 = {FRAME_attak1_1, FRAME_attak1_6, hypertank_frames_attack1, hypertank_reattack1};

mframe_t supertank_frames_end_attack1[]=
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
mmove_t supertank_move_end_attack1 = {FRAME_attak1_7, FRAME_attak1_20, supertank_frames_end_attack1, supertank_run};


void supertank_reattack1(edict_t *self)
{
	if (visible(self, self->enemy))
		if (random() < 0.9)
			self->monsterinfo.currentmove = &supertank_move_attack1;
		else
			self->monsterinfo.currentmove = &supertank_move_end_attack1;	
	else
		self->monsterinfo.currentmove = &supertank_move_end_attack1;
}

void hypertank_reattack1(edict_t *self)
{
	if (visible(self, self->enemy))
		if (random() < 0.9)
			self->monsterinfo.currentmove = &hypertank_move_attack1;
		else
			self->monsterinfo.currentmove = &supertank_move_end_attack1;	
	else
		self->monsterinfo.currentmove = &supertank_move_end_attack1;
}

void supertank_pain (edict_t *self, edict_t *other, float kick, int damage)
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

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if (damage <= 10)
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &supertank_move_pain1;
	}
	else if (damage <= 25)
	{
		gi.sound (self, CHAN_VOICE, sound_pain3, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &supertank_move_pain2;
	}
	else
	{
		gi.sound (self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM,0);
		self->monsterinfo.currentmove = &supertank_move_pain3;
	}
};


void supertankRocket (edict_t *self)
{
	vec3_t	forward, right;
	vec3_t	start;
	vec3_t	dir;
	vec3_t	vec;
	int		flash_number;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

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

// petunindan hypertank rocket code taken from stroggdm

void hypertankRocket (edict_t *self)
{
	vec3_t	forward, right;
	vec3_t	start;
	vec3_t	dir;
	vec3_t	vec;
	int		damage;
	float	damage_radius;
	int		radius_damage;
	int rnd = rndnum (0, 9);
	int		flash_number;
	
	damage = 100 + (int)(random() * 20.0);
	radius_damage = 50+20;
	damage_radius = 50+20;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

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
	
	if (rnd == 0 || rnd == 1 || rnd == 2)
	monster_fire_rocket (self, start, dir, 80, 500, flash_number,
		(self->spawnflags & SF_MONSTER_SPECIAL ? self->enemy : NULL) );
	else if (rnd == 3 || rnd == 4 || rnd == 5)
		monster_fire_grenade (self, start, dir, 50, 800, flash_number);
	else
		monster_fire_bfg (self, start, dir, 160, 500, 300, 200, MZ2_JORG_BFG_1);
}	

void supertankMachineGun (edict_t *self)
{
	vec3_t	dir;
	vec3_t	vec;
	vec3_t	start;
	vec3_t	forward, right;
	int		flash_number;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

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

// petunindan Hyper Chaingun code taken from stroggdm

void hypertankMachineGun (edict_t *self)
{
	vec3_t	dir;
	vec3_t	vec;
	vec3_t	start;
	vec3_t	forward, right;
	int		flash_number;
	int rnd = rndnum (0, 5);

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

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
	
	// Hyper chaingun
  
	if (rnd < 3)
		monster_fire_bullet (self, start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
	else
		monster_fire_blaster (self, start, forward, 9, 800, flash_number, EF_HYPERBLASTER, BLASTER_ORANGE);
	//
}

void supertank_attack(edict_t *self)
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
		self->monsterinfo.currentmove = &supertank_move_attack1;
	}
	else
	{	// fire rockets more often at distance
		if (random() < 0.3)
			self->monsterinfo.currentmove = &supertank_move_attack1;
		else
			self->monsterinfo.currentmove = &supertank_move_attack2;
	}
}

void hypertank_attack(edict_t *self)
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
		self->monsterinfo.currentmove = &hypertank_move_attack1;
	}
	else
	{	// fire rockets more often at distance
		if (random() < 0.3)
			self->monsterinfo.currentmove = &hypertank_move_attack1;
		else
			self->monsterinfo.currentmove = &hypertank_move_attack2;
	}
}


//
// death
//

void supertank_dead (edict_t *self)
{
	VectorSet (self->mins, -60, -60, 0);
	VectorSet (self->maxs, 60, 60, 72);
	self->movetype = MOVETYPE_TOSS;
//	self->svflags |= SVF_DEADMONSTER;
	self->s.frame = FRAME_death_24;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);
}

void hypertank_dead (edict_t *self)
{
	
	edict_t *bossdefeated;
	edict_t	*ent, *client;
	
	VectorSet (self->mins, -60, -60, 0);
	VectorSet (self->maxs, 60, 60, 72);
	self->movetype = MOVETYPE_TOSS;
//	self->svflags |= SVF_DEADMONSTER;
	self->s.frame = FRAME_death_24;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);
	
	bossdefeated = 1;
	
	// petunindan rose boss defeat message
	if (bossdefeated = 1)
	{
		
		// intermission after boss defeat
		
		//BeginIntermission (CreateTargetChangeLevel (level.mapname) );
		
		FinalMessage (self);
		
		//BeginIntermission (self);
	}
}


void BossExplode (edict_t *self)
{
	vec3_t	org;
	int		n;

	self->think = BossExplode;
	VectorCopy (self->s.origin, org);
	org[2] += 24 + (rand()&15);
	switch (self->count++)
	{
	case 1:
		org[0] -= 24;
		org[1] -= 24;
		break;
	case 2:
		org[0] += 24;
		org[1] += 24;
		break;
	case 3:
		org[0] += 24;
		org[1] -= 24;
		break;
	case 4:
		org[0] -= 24;
		org[1] += 24;
		break;
	case 5:
		org[0] -= 48;
		org[1] -= 48;
		break;
	case 6:
		org[0] += 48;
		org[1] += 48;
		break;
	case 7:
		org[0] -= 48;
		org[1] += 48;
		break;
	case 8:
		org[0] += 48;
		org[1] -= 48;
		break;
	case 9:
		self->s.sound = 0;

		//Knightmare- big explosion
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_EXPLOSION1_BIG);
		gi.WritePosition (org);
		gi.multicast (self->s.origin, MULTICAST_PVS);

		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", 500, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", 500, GIB_ORGANIC);
		for (n= 0; n < 8; n++)
			ThrowGib (self, "models/objects/gibs/gear/tris.md2", 500, GIB_METALLIC);
		for (n= 0; n < 8; n++)
			ThrowGib (self, "models/objects/gibs/sm_metal/tris.md2", 500, GIB_METALLIC);
		if (!strcmp(self->classname, "monster_jorg"))
		{
			for (n= 0; n < 4; n++)
				ThrowGib (self, "models/monsters/blackwidow/gib3/tris.md2", 500, GIB_METALLIC);
		}
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", 500, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/gear/tris.md2", 500, GIB_METALLIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_EXPLOSION1);
	gi.WritePosition (org);
	gi.multicast (self->s.origin, MULTICAST_PVS);

	self->nextthink = level.time + 0.1;
}


void supertank_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	
	self->s.skinnum |= 1;
	if (!(self->fogclip & 2)) //custom bloodtype flag check
		self->blood_type = 3; //sparks and blood
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

	self->activator = attacker; //Knightmare- save for explosion

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
	self->monsterinfo.currentmove = &supertank_move_death;
}

// petunindan rose

void hypertank_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	
	int		i, n;
	edict_t	*ent, *client;
	
	self->s.skinnum |= 1;
	if (!(self->fogclip & 2)) //custom bloodtype flag check
		self->blood_type = 3; //sparks and blood
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

	self->activator = attacker; //Knightmare- save for explosion

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
	self->monsterinfo.currentmove = &hypertank_move_death;
	
}

//===========
//PGM
qboolean supertank_blocked (edict_t *self, float dist)
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
// monster_supertank
//

/*QUAKED monster_supertank (1 .5 0) (-64 -64 0) (64 64 112) Ambush Trigger_Spawn Sight GoodGuy NoGib HomingRockets
*/
void SP_monster_supertank (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/boss1/tris.md2");
		self->s.skinnum = self->style * 2;
	//	self->style = 0; //clear for custom bloodtype flag
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
	self->s.modelindex = gi.modelindex ("models/monsters/boss1/tris.md2");
	VectorSet (self->mins, -64, -64, 0);
	VectorSet (self->maxs, 64, 64, 112);

	if(!self->health)
		self->health = 1500;
	if(!self->gib_health)
		self->gib_health = -999;
	if(!self->mass)
		self->mass = 800;

	self->pain = supertank_pain;
	self->die = supertank_die;
	self->monsterinfo.stand = supertank_stand;
	self->monsterinfo.walk = supertank_walk;
	self->monsterinfo.run = supertank_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.attack = supertank_attack;
	self->monsterinfo.search = supertank_search;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.blocked = supertank_blocked;		//PGM

	if (!self->blood_type)
		self->blood_type = 2; //sparks
	else
		self->fogclip |= 2; //custom bloodtype flag

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	self->common_name = "Supertank";

	gi.linkentity (self);
	
	self->monsterinfo.currentmove = &supertank_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start(self);

	//PMM
	//self->monsterinfo.aiflags |= AI_IGNORE_SHOTS;
	//PMM
}

void SP_monster_hypertank (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/boss1/tris.md2");
		self->s.skinnum = self->style * 2;
	//	self->style = 0; //clear for custom bloodtype flag
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
	self->s.modelindex = gi.modelindex ("models/monsters/boss1/tris.md2");
	VectorSet (self->mins, -64, -64, 0);
	VectorSet (self->maxs, 64, 64, 112);
	
	// Hypertank
	
	self->classname = "monster_hypertank";
	self->common_name = "Hypertank";
	
	self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
	//testing
	//self->monsterinfo.power_armor_power = 0;
	self->monsterinfo.power_armor_power = 2200;

	if(!self->health)
		self->health = 6500;
		//testing
		//self->health = 50;
	
	self->monsterinfo.attack = hypertank_attack;
	
	//
	
	if(!self->gib_health)
		self->gib_health = -999;
	if(!self->mass)
		self->mass = 800;

	self->pain = supertank_pain;
	self->die = hypertank_die;
	self->monsterinfo.stand = supertank_stand;
	self->monsterinfo.walk = supertank_walk;
	self->monsterinfo.run = supertank_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.search = supertank_search;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.blocked = supertank_blocked;		//PGM

	if (!self->blood_type)
		self->blood_type = 2; //sparks
	else
		self->fogclip |= 2; //custom bloodtype flag

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	self->common_name = "Supertank";

	gi.linkentity (self);
	
	self->monsterinfo.currentmove = &supertank_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start(self);

	//PMM
	//self->monsterinfo.aiflags |= AI_IGNORE_SHOTS;
	//PMM
}
