#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pEntity) override;
};


