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
	Player* lastplayerWithBall;

	bool passPossible[PLAYER_PER_TEAM] = { false, false, false, false, false };
	bool passDangerous[PLAYER_PER_TEAM] = { false, false, false, false, false };

private:
	void TrySetSelectedEntity(Player* player, int x, int y);
	Player* GetClosestPlayer(Player* pTeam[], bool sortedByPossiblePass);


	float DotProduct(float v1x, float v2x, float v1y, float v2y);
	float Magnitude(float x, float y);
	float GetAngle(sf::Vector2f pToAnalyze, sf::Vector2f p1, sf::Vector2f p2);

	bool TryPassDangerous(Player* player);
	bool TryPassPossible(Player* player);
	bool CheckPassPossible();

	void OnGoal();
	void RepositionPlayers();
	void GiveRandomPlayerInTeamBall(Player* pTeam[]);
public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	float GetPlayerDistance(Player* p1, Player* p2);
	bool isInTeam(Player* player, Player* pTeam[]);
	Player** GetPlayerTeam(Player* player);
	void Pass();


};

