#include "RugbyScene.h"

#include "Player.h"
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

		pTeam2[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
		pTeam2[i]->SetPosition(width - playerStartX, playerStartY, 0.f, 0.5f);

		playerStartY += playerGapY;
		playerStartX += playerGapX;
		playerGapX = -playerGapX;
	}
	
	playerWithBall = pTeam1[2];
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
		sf::Vector2f position = playerWithBall->GetPosition();
		Debug::DrawCircle(position.x, position.y, 15, { 255, 128, 0 });
	}

	if (playerSelected != nullptr)
	{
		sf::Vector2f position = playerSelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
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

		if (passPossible[i])
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
	}
	else
	{
		Debug::DrawText(100, 100, "GOAL", 1.f, 1.f, sf::Color::Red);
	}
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

Player* RugbyScene::GetClosestPlayer(Player* pTeam[])
{
	int indexClosest = 0;
	float closestDistance = 100000.f;

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
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

bool RugbyScene::TryPassPossible(Player* player)
{
	if (sqrt(GetPlayerDistance(playerWithBall, player)) > 200)
		return false;

	if (isInTeam(playerWithBall, pTeam1) && playerWithBall->GetPosition().x < player->GetPosition().x)
		return false;

	if (isInTeam(playerWithBall, pTeam2) && playerWithBall->GetPosition().x > player->GetPosition().x)
		return false;

	return true;
}

void RugbyScene::Pass()
{
	Player* closestPlayer = GetClosestPlayer(pTeam1);
	playerWithBall = closestPlayer;
}
