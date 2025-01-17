#pragma once

#include "Entity.h"
#include "RugbyScene.h"

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
	float speed = 100.f;
	sf::Vector2f yArea;

public:

	const char* GetStateName(State state) const;
	void IsImmune();
	void SetPlayerState(int a);
	void SetYArea(int index);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pEntity) override;

	RugbyScene* playerScene;

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

