#include "PlayerAction.h"
#include "Player.h"
#include "StateMachine.h"

#include "RugbyScene.h"
#include "GameManager.h"
#include <iostream>



void PlayerAction_Attack::OnStart(Player* pPlayer)
{

}

void PlayerAction_Attack::OnUpdate(Player* pPlayer)
{
	RugbyScene* scene = pPlayer->playerScene;
	if (scene->isInTeam(pPlayer, scene->pTeam1))
	{
		pPlayer->GoToDirection(scene->width, pPlayer->GetPosition().y, pPlayer->speed);
	}
	else
	{
		pPlayer->GoToDirection(0, pPlayer->GetPosition().y, pPlayer->speed);
	}
}


void PlayerAction_Support::OnStart(Player* pPlayer)
{
	pPlayer->speed = 50.f;
}

void PlayerAction_Support::OnUpdate(Player* pPlayer)
{
	RugbyScene* scene = pPlayer->playerScene;

	if (scene->GetPlayerTeam(pPlayer) == scene->GetPlayerTeam(scene->playerWithBall))
	{
		if (scene->isInTeam(pPlayer, scene->pTeam1))
		{
			pPlayer->GoToDirection(scene->width, pPlayer->GetPosition().y, pPlayer->speed);
		}
		else
		{
			pPlayer->GoToDirection(0, pPlayer->GetPosition().y, pPlayer->speed);
		}
	}
}

void PlayerAction_Block::OnStart(Player* pPlayer)
{
	pPlayer->speed = 50.f;
}

void PlayerAction_Block::OnUpdate(Player* pPlayer)
{
	sf::Vector2f pos = pPlayer->playerScene->playerWithBall->GetPosition();

	if(pos.y > pPlayer->yArea.x + 10.f && pos.y < pPlayer->yArea.y - 10.f)
		pPlayer->GoToDirection(pos.x, pos.y, pPlayer->speed);

	else
		pPlayer->GoToDirection(pos.x, pPlayer->GetPosition().y, pPlayer->speed);
}

void PlayerAction_GetBack::OnStart(Player* pPlayer)
{
	pPlayer->speed = 50.f;
}

void PlayerAction_GetBack::OnUpdate(Player* pPlayer)
{
	sf::Vector2f pos = pPlayer->playerScene->playerWithBall->GetPosition();
	RugbyScene* scene = pPlayer->playerScene;

	if(scene->GetPlayerTeam(pPlayer) == scene->pTeam1)
		pPlayer->GoToDirection(pos.x - 150.f, pPlayer->GetPosition().y, pPlayer->speed);
	else
		pPlayer->GoToDirection(pos.x + 150.f, pPlayer->GetPosition().y, pPlayer->speed);
}

void PlayerAction_Pass::OnStart(Player* pPlayer)
{
	pPlayer->playerScene->Pass();
	pPlayer->speed = 50.f;
}

void PlayerAction_Pass::OnUpdate(Player* pPlayer)
{
	//TODO
}

