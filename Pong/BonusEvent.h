#pragma once
#include "Entity.h"

enum class BonusType
{
	None = 0,
	AddSpeed,
	SmallBall,
	DecreaseSize,
	IncreaseSize,
};


class BonusEvent
{
public:
	virtual void handle(Entity caller, BonusType bonusType) = 0;
};