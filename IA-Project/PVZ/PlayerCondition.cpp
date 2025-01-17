#include "PlayerCondition.h"
#pragma once

bool PlayerCondition_NoEnemyInArea::OnTest(Player* owner)
{


	return false;
}

bool PlayerCondition_CanPass::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;
	if (owner = scene->playerWithBall)
	{
		Player** team;
		if (scene->isInTeam(owner, scene->pTeam1))
			team = scene->pTeam2;
		else
			team = scene->pTeam1;

		for (int i = 0; i < PLAYER_PER_TEAM; i++)
		{
			if(scene->GetPlayerDistance(owner, team[i]) <= 1000.f)
				return true;
		}
	}

	return false;
}

bool PlayerCondition_BallInEnemyTeam::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;
	Player** team;

	if (scene->isInTeam(owner, scene->pTeam1))
		team = scene->pTeam1;
	else
		team = scene->pTeam2;

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		if (team[i] == scene->playerWithBall)
			return true;
	}

	return false;
}

bool PlayerCondition_HaveBall::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;

	if (owner == scene->playerWithBall)
		return true;

	return false;
}

bool PlayerCondition_BallPlayerFront::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;

	if (scene->playerWithBall->GetPosition().x > owner->GetPosition().x)
		return true;

	return false;
}

bool PlayerCondition_BallPlayerBehind::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;

	if (scene->playerWithBall->GetPosition().x < owner->GetPosition().x)
		return true;

	return false;
}
