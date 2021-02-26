#pragma once

#ifndef OBJECT_OBJECT_H_
#define OBJECT_OBJECT_H_

#include "../../sprite.h"
#include "../Scene.h"

#include <vector>
#include <functional>

class Scene;

class Object {
	SDL_FPoint pos_percent;
	SDL_FPoint deltas_percent;
	SDL_FPoint size_percent;
	SDL_FRect hitbox_percent;
	SDL_FPoint hitbox_offset_percent;
	bool mark_for_removal;
	int frames_existed;
	Scene *scene;
	bool controllable;
	int wait_timer;
	std::function<void(void)> wait_action;
	int z;
	float angle_delta;
	bool being_pushed;
	Object *pushing;
	bool breaks_bullet;
	sprite_ex_f s;
	bool can_collide;
	bool can_be_collided_with;
	bool active;
	bool visible;

	public:
	 	enum physics_type {
	 		solid, pushable, none
	 	};

		Object(Scene *scene);
		Object(void);
		virtual ~Object(void);

		void set_pos_percent(float x, float y);
		SDL_FPoint &get_pos_percent(void);
		float get_x_percent(void) const;
		float get_y_percent(void) const;
		float get_x_scaled(void) const;
		float get_y_scaled(void) const;

		void set_deltas_percent(float dx, float dy);
		float get_dx_percent(void) const;
		float get_dy_percent(void) const;
		float get_dx_scaled(void) const;
		float get_dy_scaled(void) const;

		void set_size_percent(float w, float h);
		float get_w_percent(void) const;
		float get_h_percent(void) const;
		void set_size_scaled(float w, float h);
		float get_w_scaled(void) const;
		float get_h_scaled(void) const;

		void set_hitbox_percent(float x, float y, float w, float h);
		float get_hitbox_x_percent(void) const;
		float get_hitbox_y_percent(void) const;
		float get_hitbox_w_percent(void) const;
		float get_hitbox_h_percent(void) const;
		float get_hitbox_offx_percent(void) const;
		float get_hitbox_offy_percent(void) const;
		float get_hitbox_x_scaled(void) const;
		float get_hitbox_y_scaled(void) const;
		float get_hitbox_w_scaled(void) const;
		float get_hitbox_h_scaled(void) const;
		SDL_FRect get_hitbox_scaled(void) const;

		void set_z(int z);
		int get_z(void) const;

		int get_frames_existed(void) const;

		void remove(void);
		bool marked_for_removal(void) const;
		virtual void on_remove(void);

		virtual void update(void);
		virtual void render(void);

		bool get_can_be_collided_with(void) const;
		bool get_can_collide(void) const;
		void set_can_be_collided_with(bool can_be_collided_with);
		void set_can_collide(bool can_collide);
		std::vector<Object *> get_collisions(void) const;
		bool has_collision_with(Object *collider) const;

		sprite_ex_f &get_sprite(void);
		void set_sprite(sprite_ex_f s);

		void set_rotation(int degrees);
		void set_angle_delta(float angle_delta);

		Scene *get_scene(void) const;

		bool is_controllable(void) const;
		void set_controllable(bool controllable);

		void after_n_frames(int n, std::function<void(void)> action);

		bool is_solid(void) const;
		bool is_pushable(void) const;
		bool is_being_pushed(void) const;
		void set_being_pushed(bool being_pushed);
		void set_physics_type(physics_type type);

		void set_breaks_bullet(bool breaks_bullet);
		bool does_break_bullet(void) const;

		bool is_active(void) const;
		void set_active(bool active);

		void set_visible(bool visible);
		bool is_visible(void) const;

	private:
		physics_type type;
};

#endif /* OBJECT_H_ */
