#include "Character.h"

Character::Character(void) : Character(nullptr, nullptr, nullptr, nullptr, 0, 1) { }
Character::Character(const char *texture_path, const char *bullet_path, const char *feather_path, const char *eggshell_path, int bullet_damage, int move_speed_divisor) {
	this->texture_path = texture_path;
	this->bullet_path = bullet_path;
	this->feather_path = feather_path;
	this->eggshell_path = eggshell_path;
	this->bullet_damage = bullet_damage;
	this->moving = animation::create<8>(0, "Data/Assets/.anim/moving.anim", 64, 64, true);
	this->moving->framerects = animation::load<8>("Data/Assets/.anim/moving.anim", 64, 64);
	this->move_speed_divisor = move_speed_divisor;
}
Character::~Character(void) {
	delete this->texture_path;
	delete this->bullet_path;
	delete this->feather_path;
	delete this->eggshell_path;
}

const char *Character::get_texture_path(void) const {
	return this->texture_path;
}
const char *Character::get_bullet_path(void) const {
	return this->bullet_path;
}
const char *Character::get_feather_path(void) const {
	return this->feather_path;
}

BulletAttack Character::get_attack(std::string command_input) const {
	return this->commands.at(command_input);
}

int Character::get_bullet_damage(void) const {
	return this->bullet_damage;
}

animation *Character::get_moving_animation(void) const {
	return this->moving;
}

void Character::map_command(std::string command_input, BulletAttack bullet_attack) {
	this->commands.insert(std::make_pair(command_input, bullet_attack));
}

int Character::get_low_speed_divisor(void) const {
	return this->move_speed_divisor;
}
int Character::get_high_speed_divisor(void) const {
	return this->move_speed_divisor * 2;
}
