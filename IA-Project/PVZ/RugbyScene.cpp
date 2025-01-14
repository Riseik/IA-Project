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

}

void RugbyScene::OnGoal(Player* player)
{
	if (player = playerWithBall) {
		Debug::DrawText(100, 100, "GOAL", 1.f, 1.f, sf::Color::Red);
	}
}

void RugbyScene::TrySetSelectedEntity(Player* player, int x, int y)
{
	if (player->IsInside(x, y) == false)
		return;

	playerSelected = player;
}