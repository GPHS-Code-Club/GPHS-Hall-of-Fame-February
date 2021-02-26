#pragma once

#ifndef CHARACTER_CHARACTER_H_
#define CHARACTER_CHARACTER_H_

#include "../input.h"
#include "../Animation/Animator.h"

class Character {
	const char *texture_path;
	const char *bullet_path;
	const char *feather_path;
	const char *eggshell_path;
	command_map commands;
	int bullet_damage;
	int move_speed_divisor;

	public:
		Character(void);
		Character(const char *texture_path, const char *bullet_path, const char *feather_path, const char *eggshell_path, int bullet_damage, int move_speed_divisor);
		virtual ~Character(void);

		const char *get_texture_path(void) const;
		const char *get_bullet_path(void) const;
		const char *get_feather_path(void) const;

		BulletAttack get_attack(std::string command_input) const;

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) = 0;

		int get_bullet_damage(void) const;

		animation *get_moving_animation(void) const;

		int get_low_speed_divisor(void) const;
		int get_high_speed_divisor(void) const;

	protected:
		void map_command(std::string command_input, BulletAttack bullet_attack);
		animation *moving;
};

#endif /* CHARACTER_H_ */
