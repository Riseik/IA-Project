#pragma once

#include "GameManager.h"

#define PLAYER_PER_TEAM 5

class Player;
class Ball;

namespace sf 
{
	class Event;
}

class RugbyScene : public Scene
{

public:
	enum Tag {
		PLAYER,
		IMMUNE,
		BALL
	};

	int width;
	int height;
	
	Ball* ball;

	Player* pTeam1[PLAYER_PER_TEAM];
	Player* pTeam2[PLAYER_PER_TEAM];
	
	Player* playerSelected;
	Player* playerWithBall;

	bool passPossible[5] = {false, false, false, false, false};

private:
	void TrySetSelectedEntity(Player* player, int x, int y);
	float GetPlayerDistance(Player* p1, Player* p2);
	Player* GetClosestPlayer(Player* pTeam[], bool sortedByPossiblePass);


	bool TryPassPossible(Player* player);
	bool CheckPassPossible();

	void OnGoal();
	void RepositionPlayers();
	void GiveRandomPlayerInTeamBall(Player* pTeam[]);
public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	bool isInTeam(Player* player, Player* pTeam[]);
	void Pass();


};

