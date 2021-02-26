#include "ObjectPickup.h"

#include "../../Game.h"
#include "ObjectPlayer.h"

#include <cmath>
#include <iostream>

ObjectPickup::ObjectPickup(Scene *scene, Pickup *pickup) : Object(scene){
	this->set_can_be_collided_with(true);
	this->set_size_percent(0.05, 0.1);
	this->set_hitbox_percent(0, 0, 0.05, 0.1);
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(pickup->get_texture_path()),
		SDL_Rect { 0, 0, 64, 64 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->shadow = sprite_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/shadow.png"),
		SDL_Rect { 0, 0, 64, 32 },
		SDL_FRect { 0, 0, 32, 16 },
	};
	this->flip_scale = 1;
	this->pickup = pickup;
}
ObjectPickup::~ObjectPickup() {
	delete this->pickup;
}

void ObjectPickup::update(void) {
	this->flip_scale = std::sin((float) this->get_frames_existed() / 500.0);
	if(this->flip_scale > 0) {
		this->get_sprite().flip = SDL_FLIP_NONE;
	} else if(this->flip_scale < 0) {
		this->get_sprite().flip = SDL_FLIP_HORIZONTAL;
	}
	float old_width = this->get_w_percent();
	this->set_size_percent(0.05 * std::abs(this->flip_scale), 0.1);
	float new_width = this->get_w_percent();
	this->set_pos_percent(this->get_x_percent() - (new_width - old_width) / 2.0, this->get_y_percent());
	this->set_hitbox_percent(this->get_hitbox_offx_percent() + (new_width - old_width) / 2.0, this->get_hitbox_offy_percent(), this->get_hitbox_w_percent(), this->get_hitbox_h_percent());

	// TODO fix on other objects

	Object::update();

	for(Object *object : this->get_collisions()) {
		if(ObjectPlayer *player = dynamic_cast<ObjectPlayer *>(object)) {
			player->set_pickup(this->get_pickup());
			this->remove();
		}
	}
}

void ObjectPickup::render(void) {
	this->shadow.dstrect.x = this->get_hitbox_x_scaled() + this->get_hitbox_w_scaled() / 2 - (float) (Game::get_instance()->get_width() * 0.05 / 2);
	this->shadow.dstrect.y = this->get_y_scaled() + (float) (Game::get_instance()->get_height() * 0.05 * 1.5);
	this->shadow.dstrect.w = (float) (Game::get_instance()->get_width() * 0.05);
	this->shadow.dstrect.h = (float) (Game::get_instance()->get_height() * 0.05);

	sprite_f::render(this->shadow);

	if(this->is_active()) {
		this->get_sprite().dstrect.x = this->get_x_scaled();
		this->get_sprite().dstrect.y = this->get_y_scaled() + 5 * std::sin(this->get_frames_existed() / 250.0);
		this->get_sprite().dstrect.w = this->get_w_scaled();
		this->get_sprite().dstrect.h = this->get_h_scaled();

		this->get_sprite().center.x = this->get_sprite().dstrect.w / 2;
		this->get_sprite().center.y = this->get_sprite().dstrect.h / 2;

		if(this->is_visible()) {
			sprite_ex_f::render(this->get_sprite());
		}

		if(Game::get_instance()->is_in_debug_mode()) {
			if(this->get_can_be_collided_with() || this->get_can_collide()) {
				SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 255, 0, 0, 255);
				SDL_FRect hb = this->get_hitbox_scaled();
				SDL_RenderDrawRectF(Game::get_instance()->get_renderer(), &hb);
			}
		}
	}
}

Pickup *ObjectPickup::get_pickup(void) const {
	return this->pickup;
}
