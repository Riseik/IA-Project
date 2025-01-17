#include "RugbyScene.h"

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

		pTeam2[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
		pTeam2[i]->SetPosition(width - playerStartX, playerStartY, 0.f, 0.5f);

		playerStartY += playerGapY;
		playerStartX += playerGapX;
		playerGapX = -playerGapX;
	}

	float ballRadius = height * 0.020f;

	ball = CreateEntity<Ball>(ballRadius, { 255, 128, 0 });
	ball->SetPosition(pTeam1[2]->GetPosition().x, pTeam1[2]->GetPosition().y, 0.f, 0.5f);
	
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

	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		float angle = GetAngle(playerWithBall->GetPosition(), pTeam1[1]->GetPosition(), pTeam1[3]->GetPosition());
		Debug::DrawText(200, 200, std::to_string(angle), 1.f, 1.f, sf::Color::Red);
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
		if (passPossible[i])
			passDangerous[i] = TryPassDangerous(pTeam[i]);
		else
			passDangerous[i] = false;

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
		else if (passDangerous[i])
			Debug::DrawLine(playerWithBall->GetPosition().x, playerWithBall->GetPosition().y, pTeam[i]->GetPosition().x, pTeam[i]->GetPosition().y, {255, 128, 0});
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
	int indexClosestNotDangerous = -1;
	float closestDistanceNotDangerous = 100000.f;
	int indexClosest = 0;
	float closestDistance = 100000.f;

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		if (sortedByPossiblePass && !passPossible[i])
			continue;

		if (pTeam[i] == playerWithBall)
			continue;

		float distance = GetPlayerDistance(playerWithBall, pTeam[i]);

		if (distance < closestDistanceNotDangerous && !passDangerous[i])
		{
			indexClosestNotDangerous = i;
			closestDistanceNotDangerous = distance;
		}
		if (distance < closestDistance)
		{
			indexClosest = i;
			closestDistance = distance;
		}
	}
	if (indexClosestNotDangerous != -1)
		return pTeam[indexClosestNotDangerous];
	else
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

float RugbyScene::DotProduct(float v1x, float v2x, float v1y, float v2y)
{
	return v1x * v2x + v1y * v2y;
}

float RugbyScene::Magnitude(float x, float y)
{
	return std::sqrt(x * x + y * y);
}

float RugbyScene::GetAngle(sf::Vector2f pToAnalyze, sf::Vector2f p1, sf::Vector2f p2)
{
	float v1x = pToAnalyze.x - p1.x;
	float v1y = pToAnalyze.y - p1.y;
	float v2x = pToAnalyze.x - p2.x;
	float v2y = pToAnalyze.y - p2.y;

	float dot = DotProduct(v1x, v2x, v1y, v2y);

	float magv1 = Magnitude(v1x, v1y);
	float magv2 = Magnitude(v2x, v2y);

	float cos = dot / (magv1 * magv2);
	float radAngle = std::acos(cos);

	return radAngle * (180.f / 3.14f);
}

bool RugbyScene::TryPassDangerous(Player* player)
{
	Player** pTeam;

	if (isInTeam(player, pTeam1))
		pTeam = pTeam2;
	else
		pTeam = pTeam1;

	float playerDistance = GetPlayerDistance(playerWithBall, player);

	for (int i = 0; i < PLAYER_PER_TEAM; i++)
	{
		float enemyDistance = GetPlayerDistance(playerWithBall, pTeam[i]);

		if (enemyDistance > playerDistance) continue;

		float angle = GetAngle(playerWithBall->GetPosition(), player->GetPosition(), pTeam[i]->GetPosition());

		if (angle < 10.f + height * 0.035f) return true;
	}

	return false;
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
	Player* closestPlayer = GetClosestPlayer(pTeam1, true);
	/*playerWithBall = nullptr;*/
	/*ball->GoToPosition(closestPlayer->GetPosition().x, closestPlayer->GetPosition().y, 500.f);*/
	playerWithBall = closestPlayer;
}
