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

class PlayerCondition_BallInEnemyTeam : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_HaveBall : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_BallPlayerFront : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_BallPlayerBehind : public Condition<Player>
{

public:
	bool OnTest(Player* owner) override;
};
