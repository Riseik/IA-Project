#pragma once

#include "Action.h"
#include "Player.h"

class PlayerCondition_NoEnemyInArea : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_CanPass : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_EnemyHaveTheBall : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;

	friend Player;
};
