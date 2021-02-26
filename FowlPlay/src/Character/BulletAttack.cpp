#include "BulletAttack.h"

BulletAttack::BulletAttack(std::function<void(Object *)> action) {
	this->action = action;
}
BulletAttack::~BulletAttack(void) {
	// TODO Auto-generated destructor stub
}

void BulletAttack::activate(Object *object) const {
	this->action(object);
}
