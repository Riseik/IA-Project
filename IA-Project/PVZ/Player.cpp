#include "Player.h"
#include "RugbyScene.h"

#include "StateMachine.h"
#include "PlayerCondition.h"
#include "PlayerAction.h"

#include "Debug.h"

void Player::OnInitialize()
{
	SetTag(RugbyScene::Tag::PLAYER);
	mpStateMachine = new StateMachine<Player>(this, State::Count);

	{
		Action<Player>* pAttack = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Attack);
	}
}

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


void Player::OnUpdate()
{

	mpStateMachine->Update();
}

void Player::OnCollision(Entity* pEntity)
{
	if (pEntity->IsTag(RugbyScene::Tag::PLAYER))
	{
		if (GetScene<RugbyScene>()->playerWithBall == pEntity)
		{
			GetScene<RugbyScene>()->playerWithBall = this;
			SetTag(RugbyScene::Tag::IMMUNE);
		}
	}
}

void Player::IsImmune()
{
	if (IsTag(RugbyScene::Tag::IMMUNE))
	{
		elapsedTime += GameManager::Get()->GetDeltaTime();
		if (elapsedTime > 2.f)
		{
			SetTag(RugbyScene::Tag::PLAYER);
			elapsedTime = 0.f;
		}
	}
}
