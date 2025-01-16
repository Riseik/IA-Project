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

	//Attack
	{
		Action<Player>* pAttack = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Attack);

		//-> Pass
		{
			auto transition = pAttack->CreateTransition(State::Pass);
			auto condition = transition->AddCondition<PlayerCondition_CanPass>();
		}
	}

	//Support
	{
		Action<Player>* pSupport = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Support);

		//-> Attack
		{
			auto transition = pSupport->CreateTransition(State::Attack);
			auto condition = transition->AddCondition<PlayerCondition_HaveBall>();
		}
		//-> Block
		{
			auto transition = pSupport->CreateTransition(State::Block);
			auto condition = transition->AddCondition<PlayerCondition_BallInEnemyTeam>();
		}
		//-> GetBack
		{
			auto transition = pSupport->CreateTransition(State::GetBack);
			auto condition = transition->AddCondition<PlayerCondition_BallPlayerBehind>();
		}
	}

	//Block
	{
		Action<Player>* pBlock = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Block);

		//-> Attack
		{
			auto transition = pBlock->CreateTransition(State::Attack);
			auto condition = transition->AddCondition<PlayerCondition_HaveBall>();
		}
		//-> Support
		{
			auto transition = pBlock->CreateTransition(State::Support);
			auto condition = transition->AddCondition<PlayerCondition_BallPlayerFront>();
		}
		//-> GetBack
		{
			auto transition = pBlock->CreateTransition(State::GetBack);
			auto condition = transition->AddCondition<PlayerCondition_BallPlayerBehind>();
		}
	}

	//GetBack
	{
		Action<Player>* pGetBack = mpStateMachine->CreateAction<PlayerAction_Attack>(State::GetBack);

		//-> Support
		{
			auto transition = pGetBack->CreateTransition(State::Support);
			auto condition = transition->AddCondition<PlayerCondition_BallPlayerFront>();
		}
		//-> Block
		{
			auto transition = pGetBack->CreateTransition(State::Block);
			auto condition = transition->AddCondition<PlayerCondition_BallInEnemyTeam>();
		}
	}

	//Pass
	{
		Action<Player>* pPass = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Pass);

		//-> GetBack
		{
			auto transition = pPass->CreateTransition(State::GetBack);
			auto condition = transition->AddCondition<PlayerCondition_BallPlayerBehind>();
		}
		//-> Block
		{
			auto transition = pPass->CreateTransition(State::Block);
			auto condition = transition->AddCondition<PlayerCondition_BallInEnemyTeam>();
		}
	}
}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Attack: return "Attack";
	case Support: return "Support";
	case Block: return "Block";
	case GetBack: return "GetBack";
	case Pass: return "Pass";
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
