#ifndef MSKILL_H
#define MSKILL_H


/// 스킬 타입
enum MSkillType{
	MST_PASSIVE_COMBAT = 0,		///<	패시브 스킬은 액티베이션이 필요없다.
	MST_ACTIVE_COMBAT = 1,		///<	액티브스킬 중 전투에 관련된 스킬이다. 이 타입의 스킬은 버프 윈도우에 표시되지 않으며, DURATION도 가질 수 있다.
	MST_ACTIVE_SPELL = 2,		///<	액티브스킬 중 마법의 형태를 가지는 스킬이다. 이 타입의 스킬은 Duration이 0보다 큰 경우 버프 윈도우에 표시되어진다.
};

/// 스킬 공식 종류
enum MSkillFomulaType{
	MSFT_NORMAL = 0,
	MSFT_COMPLEX_BENEFIT = 1,
	MSFT_COMPLEX_DETRIMENT = 2,
};

enum MPrimaSkill{
	MSK_NA = 0,
	MSK_OCS = 1,
	MSK_DCS = 2,
	MSK_RCS = 3,
	MSK_ECS = 4,
	MSK_OMS = 5,
	MSK_DMS = 6,
	MSK_EMS = 7,
};

enum MTargetType{
	MTT_NONE = 0,
	MTT_FRIENDLY_TARGET = 1,
	MTT_UNFRIENDLY_TARGET = 2,
	MTT_FRIENDLY_GROUP = 3,
	MTT_SPECIFIED = 255
};

enum MSpecies{
	MSPC_NA = 0,
	MSPC_HUMANOID = 1,
	MSPC_ABERRATION = 2,
	MSPC_ANIMAL = 3,
	MSPC_CONSTRUCT = 4,
	MSPC_DRAGON = 5,
	MSPC_ELEMENTAL = 6,
	MSPC_FEY = 7,
	MSPC_GIANT = 8,
	MSPC_PLANT = 9,
	MSPC_DEVIL = 10,
	MSPC_UNDEAD = 11,
	MSPC_VAMPIRE = 12,
	MSPC_VERMIN = 13,
};

enum MWeaponType{
	MWT_NA = 0,
	MWT_ONE_HANDED_SLASH = 1,
	MWT_TWO_HANDED_SLASH = 2,
	MWT_ONE_HANDED_BLUNT = 3,
	MWT_TWO_HANDED_BLUNT = 4,
	MWT_ONE_HANDED_PIERCING = 5,
	MWT_TWO_HANDED_PIERCING = 6,
	MWT_ONE_HANDED_RANGE_WEAPONT = 7,
	MWT_TWO_HANDED_RANGE_WEAPONT = 8,
	MWT_ONE_HANDED_HAND_TO_HAND = 9,
};

enum MSF_MOD {
	MSF_MOD_HEALTH,
	MSF_MOD_STAT,
	MSF_MOD_RESIST,
	MSF_MOD_DEFENSE,
	MSF_MOD_OFFENSE,
	MSF_MOD_NORMAL,
	MSF_MOD_STATUS,
	MSF_MOD_PRIMA,
	MSF_MOD_KEY
};



#endif
