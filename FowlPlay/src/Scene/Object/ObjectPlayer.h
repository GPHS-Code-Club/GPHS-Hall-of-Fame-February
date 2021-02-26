#pragma once

#ifndef OBJECT_OBJECTPLAYER_H_
#define OBJECT_OBJECTPLAYER_H_

#include "Object.h"
#include "../../Character/Character.h"
#include "../../Animation/Animator.h"
#include "ObjectBullet.h"
#include "../../controller_group.h"
#include "../../input.h"
#include "../../Pickup/Pickup.h"

class ObjectPlayer : public Object {
	Character *character;
	int max_health;
	int current_health;
	int max_near_miss;
	int current_near_miss;
	int invulnerability_frames;
	Animator animator;
	SDL_FRect near_miss_hitbox_percent;
	float flip_scale;
	bool flip_left;
	bool attacking;
	bool stationary;
	sprite_f shadow;
	sprite_ex_f reticle;
	sprite_ex_f pickup_sprite;
	int player_index;
	controller_group *player;
	int damaged_frames;
	input direction;
	std::vector<input> inputs;
	std::stringstream attack;
	bool trigger_shooting;
	SDL_Texture *inputs_texture;
	SDL_Rect up_rect, left_rect, down_rect, right_rect;
	bool near_missing;
	ObjectBullet *near_missing_bullet;
	SDL_Color nm_color;
	Pickup *pickup;

	static std::map<controller_group *, ObjectPlayer *> controller_player_map;

	public:
		ObjectPlayer(Scene *scene, Character *character, int player_index);
		virtual ~ObjectPlayer(void);

		void hurt(ObjectDamager *bullet);
		Character *get_character(void) const;

		virtual void update(void) override;
		virtual void render(void) override;

		void set_attacking(bool attacking);
		bool is_attacking(void) const;

		void set_stationary(bool stationary);
		bool is_stationary(void) const;

		controller_group *get_controller_group(void) const;

		void slash(void);
		void shoot(void);

		void set_near_missing(bool near_missing);
		bool is_near_missing(void) const;

		void set_nm_hitbox_percent(float x, float y, float w, float h);
		float get_nm_hitbox_x_percent(void) const;
		float get_nm_hitbox_y_percent(void) const;
		float get_nm_hitbox_w_percent(void) const;
		float get_nm_hitbox_h_percent(void) const;
		float get_nm_hitbox_x_scaled(void) const;
		float get_nm_hitbox_y_scaled(void) const;
		float get_nm_hitbox_w_scaled(void) const;
		float get_nm_hitbox_h_scaled(void) const;
		SDL_FRect get_nm_hitbox_scaled(void) const;

		void set_pickup(Pickup *pickup);
		Pickup *get_pickup(void) const;

		static ObjectPlayer *get_player_from_controller(controller_group *controller);
};

#endif /* PLAYEROBJECT_H_ */
