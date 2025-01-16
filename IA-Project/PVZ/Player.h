#pragma once

#include "Entity.h"

template<typename T>
class StateMachine;

class Player : public Entity
{
	StateMachine<Player>* mpStateMachine;

	enum State
	{
		Idle,
		Moving,
		Pass,

		Count
	};

	float elapsedTime = 0.f;

public:
	const char* GetStateName(State state) const;

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pEntity) override;

	friend class PlayerAction_Attack;
	friend class PlayerAction_Support;
	friend class PlayerAction_Block;
	friend class PlayerAction_GetBack;
	friend class PlayerAction_Pass;

	friend class PlantCondition_NooEnemyInArea;
	friend class PlantCondition_CanPass;
	friend class PlantCondition_EnemyHaveTheBall;
};

