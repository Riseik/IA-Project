#pragma once

#include "Entity.h"

template<typename T>
class StateMachine;

class Player : public Entity
{
	StateMachine<Player>* mpStateMachine;

	enum State
	{
		Attack,
		Support,
		Block,
		GetBack,
		Pass,

		Count
	};

	float elapsedTime = 0.f;

public:
	const char* GetStateName(State state) const;
	void IsImmune();

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pEntity) override;

	friend class PlayerAction_Attack;
	friend class PlayerAction_Support;
	friend class PlayerAction_Block;
	friend class PlayerAction_GetBack;
	friend class PlayerAction_Pass;

	friend class PlayerCondition_NoEnemyInArea;
	friend class PlayerCondition_CanPass;
	friend class PlayerCondition_BallInEnemyTeam;
	friend class PlayerCondition_HaveBall;
	friend class PlayerCondition_BallPlayerFront;
	friend class PlayerCondition_BallPlayerBehind;
};

