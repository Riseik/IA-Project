#include "Ball.h"

#include "RugbyScene.h"

void Ball::OnInitialize()
{
	SetTag(RugbyScene::Tag::BALL);
}

void Ball::OnUpdate()
{

}

void Ball::OnCollision(Entity* pEntity)
{
	if (GetScene<RugbyScene>()->playerWithBall != nullptr)
		return;

	if (pEntity->IsTag(RugbyScene::Tag::PLAYER)) 
	{
		GetScene<RugbyScene>()->playerWithBall = (Player*)pEntity;
	}
}
