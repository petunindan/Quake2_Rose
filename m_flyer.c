/*
==============================================================================

flyer

==============================================================================
*/

#include "g_local.h"
#include "m_flyer.h"

qboolean visible (edict_t *self, edict_t *other);
void SP_monster_kamikaze (edict_t *self);

static int	nextmove;			// Used for start/stop frames

static int	sound_sight;
static int	sound_idle;
static int	sound_pain1;
static int	sound_pain2;
static int	sound_slash;
static int	sound_sproing;
static int	sound_die;

int powerblow;


void flyer_check_melee(edict_t *self);
void flyer_loop_melee (edict_t *self);
void flyer_melee (edict_t *self);
void flyer_setstart (edict_t *self);
void flyer_stand (edict_t *self);
void flyer_nextmove (edict_t *self);

// ROGUE - kamikaze stuff
void flyer_kamikaze (edict_t *self);
void flyer_kamikaze_check (edict_t *self);
void flyer_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point);
/*
void showme1 (edict_t *self)
{
	if (!self->dmg)
	{
		gi.dprintf ("straight - %d\n", self->monsterinfo.lefty);
		self->dmg = 1;
	}
}

void showme2 (edict_t *self)
{
	if (!self->dmg)
	{
		gi.dprintf ("strafe - %d\n", self->monsterinfo.lefty);
		self->dmg = 1;
	}
}
*/

void flyer_sight (edict_t *self, edict_t *other)
{
	gi.sound (self, CHAN_VOICE, sound_sight, 1, ATTN_NORM, 0);
}

void flyer_idle (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

void flyer_pop_blades (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, sound_sproing, 1, ATTN_NORM, 0);
}


mframe_t flyer_frames_stand [] =
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
	ai_stand, 0, NULL
};
mmove_t	flyer_move_stand = {FRAME_stand01, FRAME_stand45, flyer_frames_stand, NULL};


mframe_t flyer_frames_walk [] =
{
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL,
	ai_walk, 5, NULL
};
mmove_t	flyer_move_walk = {FRAME_stand01, FRAME_stand45, flyer_frames_walk, NULL};

mframe_t flyer_frames_run [] =
{
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL,
	ai_run, 10, NULL
};
mmove_t	flyer_move_run = {FRAME_stand01, FRAME_stand45, flyer_frames_run, NULL};

mframe_t flyer_frames_kamizake [] =
{
	ai_charge, 40,	flyer_kamikaze_check,
	ai_charge, 40,	flyer_kamikaze_check,
	ai_charge, 40,	flyer_kamikaze_check,
	ai_charge, 40,	flyer_kamikaze_check,
	ai_charge, 40,	flyer_kamikaze_check
};
mmove_t flyer_move_kamikaze = {FRAME_rollr02, FRAME_rollr06, flyer_frames_kamizake, flyer_kamikaze};

void flyer_run (edict_t *self)
{
	if (!strcmp(self->classname, "monster_kamikaze"))
		self->monsterinfo.currentmove = &flyer_move_kamikaze;
	else
		if (self->monsterinfo.aiflags & AI_STAND_GROUND)
			self->monsterinfo.currentmove = &flyer_move_stand;
		else
			self->monsterinfo.currentmove = &flyer_move_run;
}

void flyer_walk (edict_t *self)
{
	if (!strcmp(self->classname, "monster_kamikaze"))
		flyer_run (self);
	else
		self->monsterinfo.currentmove = &flyer_move_walk;
}

void flyer_stand (edict_t *self)
{
	if (!strcmp(self->classname, "monster_kamikaze"))
		flyer_run (self);
	else
		self->monsterinfo.currentmove = &flyer_move_stand;
}

// ROGUE - kamikaze stuff

void flyer_kamikaze_explode (edict_t *self)
{
	vec3_t dir;

	if (self->monsterinfo.commander && self->monsterinfo.commander->inuse && 
		!strcmp(self->monsterinfo.commander->classname, "monster_carrier"))
	{
		self->monsterinfo.commander->monsterinfo.monster_slots++;
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("suicide hit!. %d slots left\n", self->monsterinfo.commander->monsterinfo.monster_slots);
	}

//	gi.dprintf ("boom!\n");
//	T_RadiusDamage(self, self->owner, 125, self, self->dmg_radius, MOD_NUKE);
//	T_RadiusDamage(self, self->owner, 125, self, 150, MOD_NUKE);
	if (self->enemy)
	{
		VectorSubtract (self->enemy->s.origin, self->s.origin, dir);
//void T_Damage (edict_t *targ, edict_t *inflictor, edict_t *attacker, vec3_t dir, vec3_t point, 
//			   vec3_t normal, int damage, int knockback, int dflags, int mod)
		T_Damage (self->enemy, self, self, dir, self->s.origin, vec3_origin, (int)50, (int)50, DAMAGE_RADIUS, MOD_UNKNOWN);
	}

	flyer_die (self, NULL, NULL, 0, dir);
/*	VectorMA (self->s.origin, -0.02, self->velocity, origin);
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_ROCKET_EXPLOSION);
	gi.WritePosition (origin);
	gi.multicast (self->s.origin, MULTICAST_PHS);

	G_FreeEdict (self);
*/
}

void flyer_kamikaze (edict_t *self)
{
	self->monsterinfo.currentmove = &flyer_move_kamikaze;
}

void flyer_kamikaze_check (edict_t *self)
{
	float	dist;

	// PMM - this needed because we could have gone away before we get here (blocked code)
	if (!self->inuse)
		return;

	if ((!self->enemy) || (!self->enemy->inuse))
	{
		flyer_kamikaze_explode (self);
		return;
	}

	self->goalentity = self->enemy;

	dist = realrange (self, self->enemy);

	if (dist < 90)
		flyer_kamikaze_explode (self);
}

// rogue - kamikaze

mframe_t flyer_frames_start [] =
{
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	flyer_nextmove
};
mmove_t flyer_move_start = {FRAME_start01, FRAME_start06, flyer_frames_start, NULL};

mframe_t flyer_frames_stop [] =
{
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	flyer_nextmove
};
mmove_t flyer_move_stop = {FRAME_stop01, FRAME_stop07, flyer_frames_stop, NULL};

void flyer_stop (edict_t *self)
{
		self->monsterinfo.currentmove = &flyer_move_stop;
}

void flyer_start (edict_t *self)
{
		self->monsterinfo.currentmove = &flyer_move_start;
}


mframe_t flyer_frames_rollright [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_rollright = {FRAME_rollr01, FRAME_rollr09, flyer_frames_rollright, NULL};

mframe_t flyer_frames_rollleft [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_rollleft = {FRAME_rollf01, FRAME_rollf09, flyer_frames_rollleft, NULL};

mframe_t flyer_frames_pain3 [] =
{	
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_pain3 = {FRAME_pain301, FRAME_pain304, flyer_frames_pain3, flyer_run};

mframe_t flyer_frames_pain2 [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_pain2 = {FRAME_pain201, FRAME_pain204, flyer_frames_pain2, flyer_run};

mframe_t flyer_frames_pain1 [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_pain1 = {FRAME_pain101, FRAME_pain109, flyer_frames_pain1, flyer_run};

mframe_t flyer_frames_defense [] = 
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,		// Hold this frame
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_defense = {FRAME_defens01, FRAME_defens06, flyer_frames_defense, NULL};

mframe_t flyer_frames_bankright [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_bankright = {FRAME_bankr01, FRAME_bankr07, flyer_frames_bankright, NULL};

mframe_t flyer_frames_bankleft [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_bankleft = {FRAME_bankl01, FRAME_bankl07, flyer_frames_bankleft, NULL};		


void flyer_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	end;
	vec3_t	dir;
	int		effect;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	if ((self->s.frame == FRAME_attak204) || (self->s.frame == FRAME_attak207) || (self->s.frame == FRAME_attak210))
		effect = EF_HYPERBLASTER;
	else
		effect = 0;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	VectorCopy (self->enemy->s.origin, end);
	end[2] += self->enemy->viewheight;

	// Lazarus fog reduction of accuracy
	if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
	{
		end[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		end[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		end[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
	}

	VectorSubtract (end, start, dir);
	monster_fire_blaster (self, start, dir, 1, 1000, flash_number, effect, BLASTER_ORANGE);
}

// petunindan Hornet attack fire and attack frames

void hornet_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	end;
	vec3_t	dir;
	int		effect;

	if(!self->enemy || !self->enemy->inuse)		//PGM
		return;									//PGM

	if ((self->s.frame == FRAME_attak204) || (self->s.frame == FRAME_attak207) || (self->s.frame == FRAME_attak210))
		effect = EF_HYPERBLASTER;
	else
		effect = 0;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	VectorCopy (self->enemy->s.origin, end);
	end[2] += self->enemy->viewheight;

	// Lazarus fog reduction of accuracy
	if(self->monsterinfo.visibility < FOG_CANSEEGOOD)
	{
		end[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		end[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		end[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
	}

	VectorSubtract (end, start, dir);
	monster_fire_railgun (self, start, dir, 50, 100, flash_number, effect, MZ2_GLADIATOR_RAILGUN_1);
}

void flyer_fireleft (edict_t *self)
{
	flyer_fire (self, MZ2_FLYER_BLASTER_1);
}

void flyer_fireright (edict_t *self)
{
	flyer_fire (self, MZ2_FLYER_BLASTER_2);
}

// petunindan Hornet fireleft fireright

void hornet_firerail (edict_t *self)
{
	hornet_fire (self, NULL);
}

void hornet_fireleft (edict_t *self)
{
	NULL;
}

void hornet_fireright (edict_t *self)
{
	NULL;
}


mframe_t flyer_frames_attack2 [] =
{
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, -10, flyer_fireleft,			// left gun
		ai_charge, -10, flyer_fireright,		// right gun
		ai_charge, -10, flyer_fireleft,			// left gun
		ai_charge, -10, flyer_fireright,		// right gun
		ai_charge, -10, flyer_fireleft,			// left gun
		ai_charge, -10, flyer_fireright,		// right gun
		ai_charge, -10, flyer_fireleft,			// left gun
		ai_charge, -10, flyer_fireright,		// right gun
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};

mframe_t hornet_frames_attack1 [] =
{
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, -10, hornet_firerail,			// fire rail
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};

mframe_t hornet_frames_attack2 [] =
{
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, -10, hornet_firerail,			// fire rail
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, -10, hornet_fireleft,			// left gun
		ai_charge, -10, hornet_fireright,		// right gun
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};
mmove_t flyer_move_attack2 = {FRAME_attak201, FRAME_attak217, flyer_frames_attack2, flyer_run};

// petunindan Hornet move_attack
mmove_t hornet_move_attack1 = {FRAME_attak201, FRAME_attak217, hornet_frames_attack1, flyer_run};

mmove_t hornet_move_attack2 = {FRAME_attak201, FRAME_attak217, hornet_frames_attack2, flyer_run};

// PMM
// circle strafe frames

mframe_t flyer_frames_attack3 [] =
{
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, flyer_fireleft,			// left gun
		ai_charge, 10, flyer_fireright,		// right gun
		ai_charge, 10, flyer_fireleft,			// left gun
		ai_charge, 10, flyer_fireright,		// right gun
		ai_charge, 10, flyer_fireleft,			// left gun
		ai_charge, 10, flyer_fireright,		// right gun
		ai_charge, 10, flyer_fireleft,			// left gun
		ai_charge, 10, flyer_fireright,		// right gun
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, NULL,
		ai_charge, 10, NULL
};
mmove_t flyer_move_attack3 = {FRAME_attak201, FRAME_attak217, flyer_frames_attack3, flyer_run};
// pmm

void flyer_slash_left (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, self->mins[0], 0);
	fire_hit (self, aim, 5, 0);
	gi.sound (self, CHAN_WEAPON, sound_slash, 1, ATTN_NORM, 0);
}

void flyer_slash_right (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, self->maxs[0], 0);
	fire_hit (self, aim, 5, 0);
	gi.sound (self, CHAN_WEAPON, sound_slash, 1, ATTN_NORM, 0);
}

mframe_t flyer_frames_start_melee [] =
{
		ai_charge, 0, flyer_pop_blades,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};
mmove_t flyer_move_start_melee = {FRAME_attak101, FRAME_attak106, flyer_frames_start_melee, flyer_loop_melee};

mframe_t flyer_frames_end_melee [] =
{
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};
mmove_t flyer_move_end_melee = {FRAME_attak119, FRAME_attak121, flyer_frames_end_melee, flyer_run};


mframe_t flyer_frames_loop_melee [] =
{
		ai_charge, 0, NULL,		// Loop Start
		ai_charge, 0, NULL,
		ai_charge, 0, flyer_slash_left,		// Left Wing Strike
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, flyer_slash_right,	// Right Wing Strike
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL		// Loop Ends
		
};
mmove_t flyer_move_loop_melee = {FRAME_attak107, FRAME_attak118, flyer_frames_loop_melee, flyer_check_melee};

void flyer_loop_melee (edict_t *self)
{
/*	if (random() <= 0.5)	
		self->monsterinfo.currentmove = &flyer_move_attack1;
	else */
	self->monsterinfo.currentmove = &flyer_move_loop_melee;
}



void flyer_attack (edict_t *self)
{
	float chance;
/*	if (random() <= 0.5)	
		self->monsterinfo.currentmove = &flyer_move_attack1;
	else */
	// 0% chance of circle in easy
	// 50% chance in normal
	// 75% chance in hard
	// 86.67% chance in nightmare

	if (!strcmp(self->classname, "monster_kamikaze"))
	{
		flyer_run (self);
		return;
	}

	if (!skill->value)
		chance = 0;
	else
		chance = 1.0 - (0.5/(float)(skill->value));

	if (random() > chance)
	{
		self->monsterinfo.attack_state = AS_STRAIGHT;
		self->monsterinfo.currentmove = &flyer_move_attack2;
	}
	else // circle strafe
	{
		if (random () <= 0.5) // switch directions
			self->monsterinfo.lefty = 1 - self->monsterinfo.lefty;
		self->monsterinfo.attack_state = AS_SLIDING;
		self->monsterinfo.currentmove = &flyer_move_attack3;
	}
}

void flyer_setstart (edict_t *self)
{
	nextmove = ACTION_run;
	self->monsterinfo.currentmove = &flyer_move_start;
}

void flyer_nextmove (edict_t *self)
{
	if (nextmove == ACTION_attack1)
		self->monsterinfo.currentmove = &flyer_move_start_melee;
	else if (nextmove == ACTION_attack2)
		self->monsterinfo.currentmove = &flyer_move_attack2;
	else if (nextmove == ACTION_run)
		self->monsterinfo.currentmove = &flyer_move_run;
}

void flyer_melee (edict_t *self)
{
//	flyer.nextmove = ACTION_attack1;
//	self->monsterinfo.currentmove = &flyer_move_stop;
	if (!strcmp(self->classname, "monster_kamikaze"))
		flyer_run (self);
	else
		self->monsterinfo.currentmove = &flyer_move_start_melee;
}

void flyer_check_melee(edict_t *self)
{
	if (range (self, self->enemy) == RANGE_MELEE)
		if (random() <= 0.8)
			self->monsterinfo.currentmove = &flyer_move_loop_melee;
		else
			self->monsterinfo.currentmove = &flyer_move_end_melee;
	else
		self->monsterinfo.currentmove = &flyer_move_end_melee;
}

void flyer_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	int		n;

	//	pmm	 - kamikaze's don't feel pain
	if (!strcmp(self->classname, "monster_kamikaze"))
		return;
	// pmm

	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;
	if (skill->value == 3)
		return;		// no pain anims in nightmare

	n = rand() % 3;
	if (n == 0)
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain1;
	}
	else if (n == 1)
	{
		gi.sound (self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain2;
	}
	else
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain3;
	}
}

// petunindan tad
void hornet_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	int		n;

	//	pmm	 - kamikaze's don't feel pain
	if (!strcmp(self->classname, "monster_kamikaze"))
		return;
	// pmm

	if (self->health < (self->max_health / 2))
	{
		self->s.skinnum |= 1;
		self->s.effects |= EF_ROCKET;
	}
	
	if ((self->monsterinfo.power_armor_power <= 0) && (powerblow == 1))
	{
		T_RadiusDamage (self, self, 5, NULL, 5, NULL);
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_BFG_EXPLOSION);
		gi.WritePosition(self -> s.origin);
		gi.multicast (self->s.origin, MULTICAST_PVS);
		powerblow = 0;
	}

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;
	if (skill->value == 3)
		return;		// no pain anims in nightmare

	n = rand() % 3;
	if (n == 0)
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain1;
	}
	else if (n == 1)
	{
		gi.sound (self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain2;
	}
	else
	{
		gi.sound (self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &flyer_move_pain3;
	}
}
//

void flyer_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int n; //Knightmare added

	for (n= 0; n < 4; n++)
		ThrowGib (self, "models/objects/gibs/sm_metal/tris.md2", damage, GIB_METALLIC);
	for (n= 0; n < 2; n++)
		ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
	gi.sound (self, CHAN_VOICE, sound_die, 1, ATTN_NORM, 0);
	BecomeExplosion1(self);
}

// PMM - kamikaze code .. blow up if blocked	
int flyer_blocked (edict_t *self, float dist)
{
	vec3_t origin;

	// kamikaze = 100, normal = 50
	if (!strcmp(self->classname, "monster_kamikaze"))
	{
		flyer_kamikaze_check(self);

		// if the above didn't blow us up (i.e. I got blocked by the player)
		if (self->inuse)
		{
			if (self->monsterinfo.commander && self->monsterinfo.commander->inuse && 
				!strcmp(self->monsterinfo.commander->classname, "monster_carrier"))
			{
				self->monsterinfo.commander->monsterinfo.monster_slots++;
//				if ((g_showlogic) && (g_showlogic->value))
//					gi.dprintf ("suicide blocked, exploding.  %d slots left\n", self->monsterinfo.commander->monsterinfo.monster_slots);
			}

			VectorMA (self->s.origin, -0.02, self->velocity, origin);
			gi.WriteByte (svc_temp_entity);
			gi.WriteByte (TE_ROCKET_EXPLOSION);
			gi.WritePosition (origin);
			gi.multicast (self->s.origin, MULTICAST_PHS);

			G_FreeEdict (self);
		}
		return true;
	}
	// we're a normal flyer
	if(blocked_checkshot (self, 0.25 + (0.05 * skill->value) ))
		return true;

	return false;
}

/*QUAKED monster_flyer (1 .5 0) (-16 -16 -24) (16 16 16) Ambush Trigger_Spawn Sight GoodGuy
*/
void SP_monster_flyer (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	// fix a map bug in jail5.bsp
	if (!Q_stricmp(level.mapname, "jail5") && (self->s.origin[2] == -104))
	{
		self->targetname = self->target;
		self->target = NULL;
	}

	//Knightmare- random replacement with kamikaze flyers
	if (kamikaze_flyer_replace->value > 0.0)
	{
		float r = random();
		if (r <= kamikaze_flyer_replace->value)
		{
			self->classname = "monster_kamikaze";
			SP_monster_kamikaze (self);
			return;
		}

	}

	sound_sight = gi.soundindex ("flyer/flysght1.wav");
	sound_idle = gi.soundindex ("flyer/flysrch1.wav");
	sound_pain1 = gi.soundindex ("flyer/flypain1.wav");
	sound_pain2 = gi.soundindex ("flyer/flypain2.wav");
	sound_slash = gi.soundindex ("flyer/flyatck2.wav");
	sound_sproing = gi.soundindex ("flyer/flyatck1.wav");
	sound_die = gi.soundindex ("flyer/flydeth1.wav");

	gi.soundindex ("flyer/flyatck3.wav");

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/flyer/tris.md2");
		self->s.skinnum = self->style * 2;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/flyer/tris.md2");
	VectorSet (self->mins, -16, -16, -24);
	// PMM - shortened to 16 from 32
	VectorSet (self->maxs, 16, 16, 16);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->s.sound = gi.soundindex ("flyer/flyidle1.wav");

	if(!self->health)
		self->health = 50;
	if(!self->mass)
		self->mass = 50;

	self->pain = flyer_pain;
	self->die = flyer_die;

	self->monsterinfo.stand = flyer_stand;
	self->monsterinfo.walk = flyer_walk;
	self->monsterinfo.run = flyer_run;
	self->monsterinfo.attack = flyer_attack;
	self->monsterinfo.melee = flyer_melee;
	self->monsterinfo.sight = flyer_sight;
	self->monsterinfo.idle = flyer_idle;
	self->monsterinfo.blocked = flyer_blocked;

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
	self->common_name = "Flyer";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &flyer_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	flymonster_start (self);
}

// PMM - suicide fliers
void SP_monster_kamikaze (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_sight = gi.soundindex ("flyer/flysght1.wav");
	sound_idle = gi.soundindex ("flyer/flysrch1.wav");
	sound_pain1 = gi.soundindex ("flyer/flypain1.wav");
	sound_pain2 = gi.soundindex ("flyer/flypain2.wav");
	sound_slash = gi.soundindex ("flyer/flyatck2.wav");
	sound_sproing = gi.soundindex ("flyer/flyatck1.wav");
	sound_die = gi.soundindex ("flyer/flydeth1.wav");

	gi.soundindex ("flyer/flyatck3.wav");

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/flyer/tris.md2");
		self->s.skinnum = self->style * 2;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/flyer/tris.md2");
	VectorSet (self->mins, -16, -16, -24);
	// used to be 32 tall .. was WAY too big
	VectorSet (self->maxs, 16, 16, 16);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->s.sound = gi.soundindex ("flyer/flyidle1.wav");
	
	self->s.effects |= EF_ROCKET;

	if(!self->health)
		self->health = 50;
	// PMM - normal flyer has mass of 50
	if(!self->mass)
		self->mass = 100;

	self->pain = flyer_pain;
	self->die = flyer_die;

	self->monsterinfo.stand = flyer_stand;
	self->monsterinfo.walk = flyer_walk;
	self->monsterinfo.run = flyer_run;
	self->monsterinfo.attack = flyer_attack;
	self->monsterinfo.melee = flyer_melee;
	self->monsterinfo.sight = flyer_sight;
	self->monsterinfo.idle = flyer_idle;
	self->monsterinfo.blocked = flyer_blocked;

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
	self->common_name = "Kamikaze Flyer";

	gi.linkentity (self);

	self->monsterinfo.currentmove = &flyer_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	flymonster_start (self);
}

// petunindan Hornet Railgun

void hornet_attack (edict_t *self)
{
	float chance;
/*	if (random() <= 0.5)	
		self->monsterinfo.currentmove = &flyer_move_attack1;
	else */
	// 0% chance of circle in easy
	// 50% chance in normal
	// 75% chance in hard
	// 86.67% chance in nightmare

	if (!strcmp(self->classname, "monster_kamikaze"))
	{
		flyer_run (self);
		return;
	}

	if (!skill->value)
		chance = 0;
	else
		chance = 1.0 - (0.5/(float)(skill->value));

	if (random() > chance)
	{
		self->monsterinfo.attack_state = AS_STRAIGHT;
		self->monsterinfo.currentmove = &hornet_move_attack1;
	}
	else // circle strafe
	{
		if (random () <= 0.5) // switch directions
			self->monsterinfo.lefty = 1 - self->monsterinfo.lefty;
		self->monsterinfo.attack_state = AS_SLIDING;
		self->monsterinfo.currentmove = &hornet_move_attack2;
	}
}

// petunindan Hornet

void SP_monster_flyer_hornet (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	// fix a map bug in jail5.bsp
	if (!Q_stricmp(level.mapname, "jail5") && (self->s.origin[2] == -104))
	{
		self->targetname = self->target;
		self->target = NULL;
	}

	//Knightmare- random replacement with kamikaze flyers
	if (kamikaze_flyer_replace->value > 0.0)
	{
		float r = random();
		if (r <= kamikaze_flyer_replace->value)
		{
			self->classname = "monster_kamikaze";
			SP_monster_kamikaze (self);
			return;
		}

	}

	sound_sight = gi.soundindex ("flyer/flysght1.wav");
	sound_idle = gi.soundindex ("flyer/flysrch1.wav");
	sound_pain1 = gi.soundindex ("flyer/flypain1.wav");
	sound_pain2 = gi.soundindex ("flyer/flypain2.wav");
	sound_slash = gi.soundindex ("flyer/flyatck2.wav");
	sound_sproing = gi.soundindex ("flyer/flyatck1.wav");
	sound_die = gi.soundindex ("flyer/flydeth1.wav");

	gi.soundindex ("flyer/flyatck3.wav");

	// Lazarus: special purpose skins
	if ( self->style )
	{
		PatchMonsterModel("models/monsters/flyer/tris.md2");
		self->s.skinnum = self->style * 4;
	}

	self->s.modelindex = gi.modelindex ("models/monsters/flyer/tris.md2");
	VectorSet (self->mins, -16, -16, -24);
	// PMM - shortened to 16 from 32
	VectorSet (self->maxs, 16, 16, 16);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->s.sound = gi.soundindex ("flyer/flyidle1.wav");
	
	// Hornet
	
	self->classname = "monster_flyer_hornet";
	self->common_name = "Hornet";
	
	if(!self->health)
		self->health = 300;
	if(!self->mass)
		self->mass = 50;
	
	self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
	self->monsterinfo.power_armor_power = 60;
	
	self->s.skinnum = 2 + 4*self->style;
	
	self->monsterinfo.attack = hornet_attack;
	
	//

	self->pain = hornet_pain;
	self->die = flyer_die;

	self->monsterinfo.stand = flyer_stand;
	self->monsterinfo.walk = flyer_walk;
	self->monsterinfo.run = flyer_run;
	self->monsterinfo.melee = flyer_melee;
	self->monsterinfo.sight = flyer_sight;
	self->monsterinfo.idle = flyer_idle;
	self->monsterinfo.blocked = flyer_blocked;

	if (!self->blood_type)
		self->blood_type = 3; //sparks and blood
	
	powerblow = 1;

	// Lazarus
	if(self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	gi.linkentity (self);

	self->monsterinfo.currentmove = &flyer_move_stand;	
	self->monsterinfo.scale = MODEL_SCALE;

	flymonster_start (self);
}
