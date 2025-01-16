#include "PlayerCondition.h"
#pragma once

bool PlayerCondition_NoEnemyInArea::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_CanPass::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_EnemyHaveTheBall::OnTest(Player* owner)
{
	return false;
}
