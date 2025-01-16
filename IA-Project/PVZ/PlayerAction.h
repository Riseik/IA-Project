#pragma once

#include "Action.h"
#include "Player.h"

class PlayerCondition_Attack : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {}
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerCondition_Support : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};
};

class PlayerCondition_Block : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};

	friend Player;
};

class PlayerCondition_GetBack : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};

	friend Player;
};

class PlayerCondition_Pass : public Action<Player>
{

public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {};

	friend Player;
};