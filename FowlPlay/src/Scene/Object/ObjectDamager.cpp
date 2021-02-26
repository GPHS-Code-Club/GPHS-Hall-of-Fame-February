#include "ObjectDamager.h"

#include "ObjectPlayer.h"

ObjectDamager::ObjectDamager(Scene *scene, Object *owner, int damage, bool disappears) : Object(scene) {
	this->owner = owner;
	this->set_can_be_collided_with(true);
	this->set_can_collide(true);
	this->knockback = { 0, 0 };
	this->iframes = 0;
	this->damage = damage;
	this->disappears = disappears;
}
ObjectDamager::~ObjectDamager(void) {
	this->owner = nullptr;
}

void ObjectDamager::update(void) {
	Object::update();

	for(Object *object : this->get_collisions()) {
		if(ObjectBullet *bullet = dynamic_cast<ObjectBullet *>(this)) {
			if(/*bullet->get_owner() != this->get_owner() && */object->does_break_bullet()) {
				bullet->on_break();
			}
		} // TODO
		if(ObjectPlayer *player = dynamic_cast<ObjectPlayer *>(object)) {
			if(player != this->owner) {
				player->hurt(this);
				if(ObjectBullet *bullet = dynamic_cast<ObjectBullet *>(this)) {
					player->set_near_missing(false);
					bullet->set_activates_near_miss(false);
				}
			}
		}
	}
}

int ObjectDamager::get_damage(void) const {
	return this->damage;
}
float ObjectDamager::get_knockback_x(void) const {
	return this->knockback.x;
}
float ObjectDamager::get_knockback_y(void) const {
	return this->knockback.y;
}
void ObjectDamager::set_knockback(float x, float y) {
	this->knockback.x = x, this->knockback.y = y;
}
Object *ObjectDamager::get_owner(void) const {
	return this->owner;
}
bool ObjectDamager::disappear_on_collision(void) const {
	return this->disappears;
}
void ObjectDamager::set_iframes(int iframes) {
	this->iframes = iframes;
}
int ObjectDamager::get_iframes(void) const {
	return this->iframes;
}
