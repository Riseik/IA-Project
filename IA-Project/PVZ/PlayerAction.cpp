#include "PlayerAction.h"
#include "Player.h"
#include "StateMachine.h"

#include "RugbyScene.h"
#include "GameManager.h"



void PlayerAction_Attack::OnStart(Player* pPlayer)
{
	pPlayer->speed = 20.f;
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
	pPlayer->speed = 20.f;
}

void PlayerAction_Support::OnUpdate(Player* pPlayer)
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

void PlayerAction_Block::OnStart(Player* pPlayer)
{
	pPlayer->speed = 20.f;
}

void PlayerAction_Block::OnUpdate(Player* pPlayer)
{
	sf::Vector2f pos = pPlayer->playerScene->playerWithBall->GetPosition();
	pPlayer->GoToPosition(pos.x, pos.y, pPlayer->speed);
}

void PlayerAction_GetBack::OnStart(Player* pPlayer)
{
	pPlayer->speed = 20.f;
}

void PlayerAction_GetBack::OnUpdate(Player* pPlayer)
{
	sf::Vector2f pos = pPlayer->playerScene->playerWithBall->GetPosition();
	pPlayer->GoToDirection(pos.x - 50.f, pPlayer->GetPosition().y, pPlayer->speed);
}

void PlayerAction_Pass::OnStart(Player* pPlayer)
{
	pPlayer->playerScene->Pass();
	pPlayer->speed = 20.f;
}

void PlayerAction_Pass::OnUpdate(Player* pPlayer)
{
	//TODO
}

