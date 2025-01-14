#include "Player.h"
#include "StateMachine.h"
#include "RugbyScene.h"

#include "PlayerCondition.h"
#include "PlayerAction.h"

#include "Debug.h"

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Moving: return "Shooting";
	case Pass: return "Reloading";
	default: return "Unknown";
	}
	return nullptr;
}

void Player::OnInitialize()
{

}

void Player::OnUpdate()
{
	mpStateMachine = new StateMachine<Player>(this, State::Count);
}