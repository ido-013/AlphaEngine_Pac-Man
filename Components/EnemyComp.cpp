#include "EnemyComp.h"
#include "AEEngine.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "../Event/CollisionEvent.h"

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner)
{

}

void EnemyComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;



	if (abs(targetX - t->GetPos().x) < 1 &&
		abs(targetY - t->GetPos().y) < 1 &&
		((dir == UP && wall[UP]) ||
			(dir == DOWN && wall[DOWN]) ||
			(dir == RIGHT && wall[RIGHT]) ||
			(dir == LEFT && wall[LEFT])))
		r->ClearVelocity();

	else
		r->SetVelocity(dx[dir] * speed, dy[dir] * speed);
}
