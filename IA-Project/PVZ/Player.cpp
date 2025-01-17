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
	playerScene = GetScene<RugbyScene>();

	
	//Attack
	{
		Action<Player>* pAttack = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Attack);

		//-> Pass
		{
			auto transition = pAttack->CreateTransition(State::Pass);
			auto condition = transition->AddCondition<PlayerCondition_CanPass>();
		}
		//-> Block
		{
			auto transition = pAttack->CreateTransition(State::Block);
			auto condition = transition->AddCondition<PlayerCondition_BallInEnemyTeam>();
		}
	}
	

	//Support
	{
		Action<Player>* pSupport = mpStateMachine->CreateAction<PlayerAction_Support>(State::Support);

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
		Action<Player>* pBlock = mpStateMachine->CreateAction<PlayerAction_Block>(State::Block);

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
		Action<Player>* pGetBack = mpStateMachine->CreateAction<PlayerAction_GetBack>(State::GetBack);

		//-> Attack
		{
			auto transition = pGetBack->CreateTransition(State::Attack);
			auto condition = transition->AddCondition<PlayerCondition_HaveBall>();
		}
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
		Action<Player>* pPass = mpStateMachine->CreateAction<PlayerAction_Pass>(State::Pass);

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
	IsImmune();
	mpStateMachine->Update();
}


void Player::OnCollision(Entity* pEntity)
{
	if (pEntity->IsTag(RugbyScene::Tag::PLAYER))
	{
		if (playerScene->playerWithBall == pEntity)
		{
			playerScene->playerWithBall = this;
			playerScene->playerWithBall->speed = 100.f;
			SetTag(RugbyScene::Tag::IMMUNE);
		}
	}
}



void Player::IsImmune()
{
	if (IsTag(RugbyScene::Tag::IMMUNE))
	{
		elapsedTime += GameManager::Get()->GetDeltaTime();
		if (elapsedTime > 1.f)
		{
			playerScene->playerWithBall->speed = 50.f;
			SetTag(RugbyScene::Tag::PLAYER);
			elapsedTime = 0.f;
		}
	}
}

void Player::SetPlayerState(int state)
{
	switch (state)
	{
	case 0:
		mpStateMachine->SetState(State::Attack);
		break;
	case 1:
		mpStateMachine->SetState(State::Support);
		break;
	case 2:
		mpStateMachine->SetState(State::Block);
		break;
	case 3:
		mpStateMachine->SetState(State::GetBack);
		break;
	case 4:
		mpStateMachine->SetState(State::Pass);
		break;
	default:
		break;
	}



}

void Player::SetYArea(int index)
{
	switch (index)
	{
	case 0:
		yArea = { 0.f, playerScene->height / 2.f};
		break;
	case 1:
		yArea = { playerScene->height / 4.f , (playerScene->height / 4.f) * 3.f};
		break;
	case 2:
		yArea = { (playerScene->height / 2.f), (float)(playerScene->height)};
		break;
	default:
		break;
	}
}
