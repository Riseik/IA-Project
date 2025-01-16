#include "PlayerCondition.h"

bool PlantCondition_NoEnemyInArea::OnTest(Player* player)
{
	return false;
}

bool PlantCondition_CanPass::OnTest(Player* player)
{
	return false;
}

bool PlantCondition_EnemyHaveTheBall::OnTest(Player* player)
{
	return false;
}
