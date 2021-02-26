#include "ObjectWall.h"

ObjectWall::ObjectWall(Scene *scene, float x, float y, float w, float h, bool breaks_bullet) : Object(scene) {
	this->set_physics_type(Object::physics_type::solid);
	this->set_can_collide(true);
	this->set_pos_percent(x, y);
	this->set_size_percent(w, h);
	this->set_hitbox_percent(0, 0, w, h);
	this->set_breaks_bullet(breaks_bullet);
}

ObjectWall::~ObjectWall() {
	// TODO Auto-generated destructor stub
}

