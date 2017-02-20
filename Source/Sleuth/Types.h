// Copyright Adam Joyce 2017.

#pragma once

UENUM()
enum class EBotBehaviorType : uint8
{
	/* Does not move, remains in place until player is spotted. */
	Passive,

	/* Patrols a region until a player is spotted. */
	Patrolling,
};
