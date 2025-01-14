#pragma once

#include "GameManager.h"

#define PLAYER_PER_TEAM 5

class Player;

namespace sf 
{
	class Event;
}

class RugbyScene : public Scene
{
	Player* playerSelected;
	Player* playerWithBall;

public:
	enum Tag {
		PLAYER,
		GOAL
	};

	int width;
	int height;

	Player* pTeam1[PLAYER_PER_TEAM];
	Player* pTeam2[PLAYER_PER_TEAM];

private:
	void TrySetSelectedEntity(Player* player, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	void OnGoal(Player* player);
};

