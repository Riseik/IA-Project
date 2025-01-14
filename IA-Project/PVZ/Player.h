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

public:
	const char* GetStateName(State state) const;

protected:
	void OnInitialize() override;
	void OnUpdate() override;

	friend class PlantAction_Idle;
	friend class PlantAction_Moving;
	friend class PlantAction_Pass;

	friend class PlantCondition_NoEnemy;
	friend class PlantCondition_EnemyArea;
	friend class PlantCondition_EnemyContact;
};

