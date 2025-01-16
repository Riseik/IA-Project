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

bool PlayerCondition_BallInEnemyTeam::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_HaveBall::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_BallPlayerFront::OnTest(Player* owner)
{
	return false;
}

bool PlayerCondition_BallPlayerBehind::OnTest(Player* owner)
{
	return false;
}
