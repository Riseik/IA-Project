#pragma once

#include "Action.h"
#include "Player.h"

class PlayerCondition_NoEnemy : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {}
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerCondition_EnemyArea : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};
};

class PlayerCondition_EnemyContact : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};

	friend Player;
};