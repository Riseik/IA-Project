#include <list>

#include "RugbyScene.h"

#include "StateMachine.h"
#include "Player.h"
#include "Ball.h"
#include "Debug.h"

void RugbyScene::OnInitialize()
{
	width = GetWindowWidth();
	height = GetWindowHeight();

	float playerRadius = height * 0.035f;

	float playerStartY = height / (PLAYER_PER_TEAM * 2.f);
	float playerGapY = height / (float)PLAYER_PER_TEAM;

	float playerStartX = width * 0.35f;
	float playerGapX = -(width * 0.05f);

	for (int i = 0; i < PLAYER_PER_TEAM; i++) {
		pTeam1[i] = CreateEntity<Player>(playerRadius, sf::Color::Green);
		pTeam1[i]->SetPosition(playerStartX, playerStartY, 0.f, 0.5f);
		pTeam1[i]->SetPlayerState(1);
	

		pTeam2[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
		pTeam2[i]->SetPosition(width - playerStartX, playerStartY, 0.f, 0.5f);
		pTeam2[i]->SetPlayerState(2);

		playerStartY += playerGapY;
		playerStartX += playerGapX;
		playerGapX = -playerGapX;

		if (i == 0 || i == 1)
		{
			pTeam1[i]->SetYArea(0);
			pTeam2[i]->SetYArea(0);
		}
		else if (i == 2)
		{
			pTeam1[i]->SetYArea(1);
			pTeam2[i]->SetYArea(1);
		}
		else
		{
			pTeam1[i]->SetYArea(2);
			pTeam2[i]->SetYArea(2);
		}
	}

	float ballRadius = height * 0.020f;

	ball = CreateEntity<Ball>(ballRadius, { 255, 128, 0 });
	ball->SetPosition(pTeam1[2]->GetPosition().x, pTeam1[2]->GetPosition().y, 0.f, 0.5f);
	
	playerWithBall = pTeam1[2];
	playerWithBall->SetPlayerState(0);
}

void RugbyScene::OnEvent(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		for (Player* player : pTeam1) {
			TrySetSelectedEntity(player, event.mouseButton.x, event.mouseButton.y);
		}
		for (Player* player : pTeam2) {
			TrySetSelectedEntity(player, event.mouseButton.x, event.mouseButton.y);
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		if (playerSelected != nullptr)
		{
			playerSelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}

	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Debug::DrawText(100, 100, "PASS", 1.f, 1.f, sf::Color::Red);
		Pass();
	}
}

void RugbyScene::OnUpdate()
{
	Debug::DrawLine(width / 10, 0, width / 10, height, {255, 255, 255});
	Debug::DrawLine(width - width / 10, 0, width - width / 10, height, { 255, 255, 255 });

	if (playerWithBall != nullptr)
	{
		ball->SetPosition(playerWithBall->GetPosition().x, playerWithBall->GetPosition().y, 0.5f, 0.5f);
	}

	if (playerSelected != nullptr)
	{
		sf::Vector2f position = playerSelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		if (playerWithBall == nullptr)
			break;

		Player** pTeam;

		if (isInTeam(playerWithBall, pTeam1))
			pTeam = pTeam1;
		else
			pTeam = pTeam2;

		if (pTeam[i] == playerWithBall)
		{
			passPossible[i] = false;
			continue;
		}
		passPossible[i] = TryPassPossible(pTeam[i]);

		int indexOptimalPass = -1;
		if (!CheckPassPossible()) indexOptimalPass = -1;
		else
		{
			Player* closestPlayer = GetClosestPlayer(pTeam, true);
			for (int i = 0; i < PLAYER_PER_TEAM; ++i) {
				if (pTeam[i] == closestPlayer) {
					indexOptimalPass = i;
					break;
				}
			}
		}

		if (i == indexOptimalPass)
			Debug::DrawLine(playerWithBall->GetPosition().x, playerWithBall->GetPosition().y, pTeam[i]->GetPosition().x, pTeam[i]->GetPosition().y, sf::Color::Blue);
		else if (passPossible[i])
			Debug::DrawLine(playerWithBall->GetPosition().x, playerWithBall->GetPosition().y, pTeam[i]->GetPosition().x, pTeam[i]->GetPosition().y, sf::Color::Green);
		else
			Debug::DrawLine(playerWithBall->GetPosition().x, playerWithBall->GetPosition().y, pTeam[i]->GetPosition().x, pTeam[i]->GetPosition().y, sf::Color::Red);

	}

	if (playerWithBall->GetPosition().x > width - width / 10 || playerWithBall->GetPosition().x < width / 10)
	{
		OnGoal();
	}
}

void RugbyScene::OnGoal()
{
	if (isInTeam(playerWithBall, pTeam1))
	{
		Debug::DrawText(100, 100, "GOAL", 1.f, 1.f, sf::Color::Green);
		GiveRandomPlayerInTeamBall(pTeam2);
	}
	else
	{
		Debug::DrawText(100, 100, "GOAL", 1.f, 1.f, sf::Color::Red);
		GiveRandomPlayerInTeamBall(pTeam1);
	}
	RepositionPlayers();
}

void RugbyScene::RepositionPlayers()
{
	float playerStartY = height / (PLAYER_PER_TEAM * 2.f);
	float playerGapY = height / (float)PLAYER_PER_TEAM;

	float playerStartX = width * 0.35f;
	float playerGapX = -(width * 0.05f);

	for (int i = 0; i < PLAYER_PER_TEAM; i++) {
		pTeam1[i]->SetPosition(playerStartX, playerStartY, 0.f, 0.5f);
		pTeam2[i]->SetPosition(width - playerStartX, playerStartY, 0.f, 0.5f);

		playerStartY += playerGapY;
		playerStartX += playerGapX;
		playerGapX = -playerGapX;
	}
}

void RugbyScene::GiveRandomPlayerInTeamBall(Player* pTeam[])
{
	playerWithBall = pTeam[std::rand() % 5];
}

void RugbyScene::TrySetSelectedEntity(Player* player, int x, int y)
{
	if (player->IsInside(x, y) == false)
		return;

	playerSelected = player;
}

float RugbyScene::GetPlayerDistance(Player* p1, Player* p2)
{
	int x1 = p1->GetPosition().x;
	int y1 = p1->GetPosition().y;
	int x2 = p2->GetPosition().x;
	int y2 = p2->GetPosition().y;

	float distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

	return distance;
}

Player* RugbyScene::GetClosestPlayer(Player* pTeam[], bool sortedByPossiblePass)
{
	int indexClosest = 0;
	float closestDistance = 100000.f;

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		if (sortedByPossiblePass && !passPossible[i])
			continue;

		if (pTeam[i] == playerWithBall)
			continue;

		float distance = GetPlayerDistance(playerWithBall, pTeam[i]);

		if (distance < closestDistance)
		{
			indexClosest = i;
			closestDistance = distance;
		}
	}

	return pTeam[indexClosest];
}

bool RugbyScene::isInTeam(Player* player, Player* pTeam[])
{
	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		if (player == pTeam[i])
		{
			return true;
		}
	}
	return false;
}

Player** RugbyScene::GetPlayerTeam(Player* player)
{
	if (isInTeam(player, pTeam1))
		return pTeam1;
	else
		return pTeam2;
}

bool RugbyScene::TryPassPossible(Player* player)
{
	if (sqrt(GetPlayerDistance(playerWithBall, player)) > 300)
		return false;

	if (isInTeam(playerWithBall, pTeam1) && playerWithBall->GetPosition().x < player->GetPosition().x)
		return false;

	if (isInTeam(playerWithBall, pTeam2) && playerWithBall->GetPosition().x > player->GetPosition().x)
		return false;

	return true;
}

bool RugbyScene::CheckPassPossible()
{
	bool possible = false;
	for (bool playerAvailable : passPossible)
	{
		if (playerAvailable) possible = true;
	}
	return possible;
}

void RugbyScene::Pass()
{
	if (!CheckPassPossible()) return;

	Player* closestPlayer;

	if (GetPlayerTeam(playerWithBall) == pTeam1)
	{
		closestPlayer = GetClosestPlayer(pTeam1, true);
	}
	else
		closestPlayer = GetClosestPlayer(pTeam2, true);

	playerWithBall = closestPlayer;
	/*ball->GoToPosition(closestPlayer->GetPosition().x, closestPlayer->GetPosition().y, 300.f);*/
}
