#include "Object.h"

#include "../../SDLHelpers.h"
#include "../../Game.h"
#include "ObjectBullet.h"

#include <iostream>
#include <algorithm>

Object::Object(Scene *scene) {
	this->scene = scene;

	this->s = { };

	this->pos_percent = { 0, 0 };
	this->deltas_percent = { 0 , 0 };
	this->size_percent = { 0, 0 };
	this->hitbox_percent = { 0, 0, 0, 0 };
	this->hitbox_offset_percent = { 0, 0 };

	this->mark_for_removal = false;
	this->can_be_collided_with = false;
	this->can_collide = false;
	this->active = true;
	this->frames_existed = 0;
	this->controllable = true;
	this->wait_timer = 0;
	this->z = 0;
	this->angle_delta = 0;
	this->pushing = nullptr;

	this->type = Object::physics_type::none;
	this->being_pushed = false;
	this->breaks_bullet = false;

	this->visible = true;
}
Object::Object(void) : Object(nullptr) { }
Object::~Object(void) {
	delete this->pushing;
	this->scene = nullptr;
}

void Object::set_pos_percent(float x, float y) {
	this->pos_percent = SDL_FPoint {
		x, y
	};
}
SDL_FPoint &Object::get_pos_percent(void) {
	return this->pos_percent;
}
float Object::get_x_percent(void) const {
	return this->pos_percent.x;
}
float Object::get_y_percent(void) const {
	return this->pos_percent.y;
}
float Object::get_x_scaled(void) const {
	return this->get_x_percent() * Game::get_instance()->get_width();
}
float Object::get_y_scaled(void) const {
	return this->get_y_percent() * Game::get_instance()->get_height();
}

void Object::set_deltas_percent(float x, float y) {
	this->deltas_percent = SDL_FPoint {
		x, y
	};
}
float Object::get_dx_percent(void) const {
	return this->deltas_percent.x;
}
float Object::get_dy_percent(void) const {
	return this->deltas_percent.y;
}
float Object::get_dx_scaled(void) const {
	return this->get_dx_percent() * Game::get_instance()->get_height();
}
float Object::get_dy_scaled(void) const {
	return this->get_dy_percent() * Game::get_instance()->get_height();
}

void Object::set_size_percent(float w, float h) {
	this->size_percent = SDL_FPoint {
		w, h
	};
}
float Object::get_w_percent(void) const {
	return this->size_percent.x;
}
float Object::get_h_percent(void) const {
	return this->size_percent.y;
}
void Object::set_size_scaled(float w, float h) {
	this->size_percent = SDL_FPoint {
		w / Game::get_instance()->get_width(),
		h / Game::get_instance()->get_height()
	};
}
float Object::get_w_scaled(void) const {
	return this->get_w_percent() * Game::get_instance()->get_width();
}
float Object::get_h_scaled(void) const {
	return this->get_h_percent() * Game::get_instance()->get_height();
}

void Object::set_hitbox_percent(float x, float y, float w, float h) {
	this->hitbox_offset_percent = SDL_FPoint {
		x, y
	};
	this->hitbox_percent = SDL_FRect {
		x, y, w, h
	};
}
float Object::get_hitbox_x_percent(void) const {
	return this->hitbox_percent.x;
}
float Object::get_hitbox_y_percent(void) const {
	return this->hitbox_percent.y;
}
float Object::get_hitbox_w_percent(void) const {
	return this->hitbox_percent.w;
}
float Object::get_hitbox_h_percent(void) const {
	return this->hitbox_percent.h;
}
float Object::get_hitbox_offx_percent(void) const {
	return this->hitbox_offset_percent.x;
}
float Object::get_hitbox_offy_percent(void) const {
	return this->hitbox_offset_percent.y;
}
float Object::get_hitbox_x_scaled(void) const {
	return this->get_hitbox_x_percent() * Game::get_instance()->get_width();
}
float Object::get_hitbox_y_scaled(void) const {
	return this->get_hitbox_y_percent() * Game::get_instance()->get_height();
}
float Object::get_hitbox_w_scaled(void) const {
	return this->get_hitbox_w_percent() * Game::get_instance()->get_width();
}
float Object::get_hitbox_h_scaled(void) const {
	return this->get_hitbox_h_percent() * Game::get_instance()->get_height();
}

void Object::set_z(int z) {
	this->z = z;
}
int Object::get_z(void) const {
	return this->z;
}


int Object::get_frames_existed(void) const {
	return this->frames_existed;
}

void Object::remove() {
	this->on_remove();
	this->mark_for_removal = true;
}
bool Object::marked_for_removal(void) const {
	return this->mark_for_removal;
}
void Object::on_remove(void) { }

void Object::update(void) {
	if(this->active) {
		this->pos_percent = sum(this->pos_percent, this->deltas_percent);
		if(this->can_be_collided_with || this->can_collide) {
			this->hitbox_percent.x = this->get_x_percent() + this->get_hitbox_offx_percent();
			this->hitbox_percent.y = this->get_y_percent() + this->get_hitbox_offy_percent();
		}
		++ this->frames_existed;
		if(this->wait_timer > 0) {
			-- this->wait_timer;
			if(this->wait_timer == 0) {
				this->wait_action();
			}
		}
		this->s.angle += this->angle_delta;

//		if(this->pushing != nullptr && std::find(this->get_collisions().begin(), this->get_collisions().end(), this->pushing) == this->get_collisions().end()) {
//			this->pushing->set_being_pushed(false);
//			this->pushing = nullptr;
//		}

		for(Object *object : this->get_collisions()) {
			if((this->is_solid() || this->is_pushable()) && object->is_solid()) {
				float dif_top_bottom = (object->get_hitbox_y_scaled() + object->get_hitbox_h_scaled()) - this->get_hitbox_y_scaled();
				float dif_right_left = (object->get_hitbox_x_scaled() + object->get_hitbox_w_scaled()) - this->get_hitbox_x_scaled();
				float dif_bottom_top = (this->get_hitbox_y_scaled() + this->get_hitbox_h_scaled()) - object->get_hitbox_y_scaled();
				float dif_left_right = (this->get_hitbox_x_scaled() + this->get_hitbox_w_scaled()) - object->get_hitbox_x_scaled();

				std::vector<float *> distances;
				distances.push_back(&dif_top_bottom);
				distances.push_back(&dif_right_left);
				distances.push_back(&dif_bottom_top);
				distances.push_back(&dif_left_right);
				std::sort(distances.begin(), distances.end(), [] (float *l, float *r) -> bool {
					return *r > *l;
				});
				if(distances[0] == &dif_top_bottom) {
					this->pos_percent = sum(this->pos_percent, {
						0, std::abs(this->get_dy_percent())
					});
				} else if(distances[0] == &dif_right_left) {
					this->pos_percent = sum(this->pos_percent, {
						std::abs(this->get_dx_percent()), 0
					});
				} else if(distances[0] == &dif_bottom_top) {
					this->pos_percent = sum(this->pos_percent, {
						0, -std::abs(this->get_dy_percent())
					});
				} else if(distances[0] == &dif_left_right) {
					this->pos_percent = sum(this->pos_percent, {
						-std::abs(this->get_dx_percent()), 0
					});
				}
			} //else if(object->is_pushable()) {
//				this->pos_percent = difference(this->pos_percent, new SDL_FPoint {
//					this->deltas_percent->x / 2, this->deltas_percent->y / 2
//				});
//				object->set_being_pushed(true);
//				object->set_deltas_percent(this->deltas_percent->x * 2, this->deltas_percent->y * 2);
//				this->pushing = object;
//			} // TODO
		}
	}
}
void Object::render(void) {
	if(this->active) {
		this->s.dstrect.x = this->get_x_scaled();
		this->s.dstrect.y = this->get_y_scaled();
		this->s.dstrect.w = this->get_w_scaled();
		this->s.dstrect.h = this->get_h_scaled();

		this->s.center.x = this->s.dstrect.w / 2;
		this->s.center.y = this->s.dstrect.h / 2;

		if(this->is_visible()) {
			sprite_ex_f::render(this->s);
		}

		if(Game::get_instance()->is_in_debug_mode()) {
			if(this->can_be_collided_with || this->can_collide) {
				SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 255, 0, 0, 255);
				SDL_FRect hb = this->get_hitbox_scaled();
				SDL_RenderDrawRectF(Game::get_instance()->get_renderer(), &hb);
			}
		}
	}
}

bool Object::get_can_be_collided_with(void) const {
	return this->can_be_collided_with && this->active;
}
bool Object::get_can_collide(void) const {
	return this->can_collide && this->active;
}
void Object::set_can_be_collided_with(bool can_be_collided_with) {
	this->can_be_collided_with = can_be_collided_with;
}
void Object::set_can_collide(bool can_collide) {
	this->can_collide = can_collide;
}
std::vector<Object *> Object::get_collisions(void) const {
	std::vector<Object *> collisions;
	if(this->get_can_be_collided_with() && this->is_active()) {
		for(Object *object : *this->get_scene()->get_objects()) {
			if(object != this && object->get_can_collide() && object->is_active()) {
				SDL_Rect this_hitbox = f_rect_to_rect(this->get_hitbox_scaled());
				SDL_Rect object_hitbox = f_rect_to_rect(object->get_hitbox_scaled());
				if(SDL_HasIntersection(&this_hitbox, &object_hitbox) == SDL_TRUE) {
					collisions.push_back(object);
				}
			}
		}
	}
	return collisions;
}
SDL_FRect Object::get_hitbox_scaled(void) const {
	return SDL_FRect {
		this->hitbox_percent.x * Game::get_instance()->get_width(),
		this->hitbox_percent.y * Game::get_instance()->get_height(),
		this->hitbox_percent.w * Game::get_instance()->get_width(),
		this->hitbox_percent.h * Game::get_instance()->get_height()
	};
}
bool Object::has_collision_with(Object *collider) const {
	for(Object *object : this->get_collisions()) {
		if(object->get_can_be_collided_with() && object == collider) {
			return true;
		}
	}
	return false;
}

sprite_ex_f &Object::get_sprite(void) {
	return this->s;
}
void Object::set_sprite(sprite_ex_f s) {
	this->s = s;
}

void Object::set_rotation(int degrees) {
	this->s.angle = degrees;
}
void Object::set_angle_delta(float angle_delta) {
	this->angle_delta = angle_delta;
}

Scene *Object::get_scene(void) const {
	return this->scene;
}

bool Object::is_controllable(void) const {
	return this->controllable;
}
void Object::set_controllable(bool controllable) {
	this->controllable = controllable;
}

void Object::after_n_frames(int n, std::function<void(void)> action) {
	this->wait_timer = n;
	this->wait_action = action;
}

bool Object::is_solid(void) const {
	return this->type == Object::physics_type::solid;
}
bool Object::is_pushable(void) const {
	return this->type == Object::physics_type::pushable;
}
bool Object::is_being_pushed(void) const {
	return this->being_pushed;
}
void Object::set_being_pushed(bool being_pushed) {
	this->being_pushed = being_pushed;
}
void Object::set_physics_type(physics_type type) {
	this->type = type;
}

void Object::set_breaks_bullet(bool breaks_bullet) {
	this->breaks_bullet = breaks_bullet;
}
bool Object::does_break_bullet(void) const {
	return this->breaks_bullet;
}

bool Object::is_active(void) const {
	return this->active;
}
void Object::set_active(bool active) {
	this->active = active;
}

void Object::set_visible(bool visible) {
	this->visible = visible;
}
bool Object::is_visible(void) const {
	return this->visible;
}
