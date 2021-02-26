#include "Pickup.h"

Pickup::Pickup(const char *texture_path, use_type type) {
	this->texture_path = texture_path;
	this->type = type;
}
Pickup::~Pickup() {
	delete this->texture_path;
}

const char *Pickup::get_texture_path(void) const {
	return this->texture_path;
}
Pickup::use_type Pickup::get_use_type(void) const {
	return this->type;
}
