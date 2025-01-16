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

	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Pass;

	friend class PlayerCondition_NoEnemy;
	friend class PlayerCondition_EnemyArea;
	friend class PlayerCondition_EnemyContact;
};

