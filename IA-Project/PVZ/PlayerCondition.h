#pragma once
#include "Player.h"
#include "Condition.h"

class PlantCondition_NoEnemyInArea : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlantCondition_CanPass : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlantCondition_EnemyHaveTheBall : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

