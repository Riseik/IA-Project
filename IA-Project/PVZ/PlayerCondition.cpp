#include "PlayerCondition.h"
#include <iostream>
#pragma once

bool PlayerCondition_NoEnemyInArea::OnTest(Player* owner)
{


	return false;
}

bool PlayerCondition_CanPass::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;
	Player** team = scene->GetPlayerTeam(owner);

	if (owner == scene->playerWithBall && owner->IsTag(RugbyScene::Tag::PLAYER))
	{
		Player** team;
		if (scene->isInTeam(owner, scene->pTeam1))
			team = scene->pTeam2;
		else
			team = scene->pTeam1;

		for (int i = 0; i < PLAYER_PER_TEAM; i++)
		{
			float a = scene->GetPlayerDistance(owner, team[i]);
			if (team == scene->pTeam1)
			{
				if (std::sqrt(a) <= 100.f && team[i]->GetPosition().x < owner->GetPosition().x)
					return true;
			}
			else
			{
				if (std::sqrt(a) <= 100.f && team[i]->GetPosition().x > owner->GetPosition().x)
					return true;
			}

		}
	}

	return false;
}

bool PlayerCondition_BallInEnemyTeam::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;

	if (scene->GetPlayerTeam(owner) != scene->GetPlayerTeam(scene->playerWithBall))
		return true;

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
	Player** team = scene->GetPlayerTeam(owner);

	if (team == scene->GetPlayerTeam(scene->playerWithBall))
	{
		if(team == scene->pTeam1 && scene->playerWithBall->GetPosition().x + 100.f > owner->GetPosition().x)
			return true;
		else if (team == scene->pTeam2 && scene->playerWithBall->GetPosition().x - 100.f > owner->GetPosition().x)
			return true;
	}

	return false;
}

bool PlayerCondition_BallPlayerBehind::OnTest(Player* owner)
{
	RugbyScene* scene = owner->playerScene;
	Player** team = scene->GetPlayerTeam(owner);

	if (team == scene->GetPlayerTeam(scene->playerWithBall))
	{
		if (team == scene->pTeam1 && scene->playerWithBall->GetPosition().x - 50.f < owner->GetPosition().x)
		{
			std::cout << "a";
			return true;
		}

		else if (team == scene->pTeam2 && scene->playerWithBall->GetPosition().x + 50.f > owner->GetPosition().x)
			return true;
	}

	return false;
}
