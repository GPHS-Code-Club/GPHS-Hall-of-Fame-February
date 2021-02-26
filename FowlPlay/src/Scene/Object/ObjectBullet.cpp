#include "ObjectBullet.h"

#include "SDL2/SDL_image.h"

#include "ObjectPlayer.h"
#include "../../TextureCache.h"
#include "../../Game.h"
#include "ObjectParticle.h"

#include <cmath>

ObjectBullet::ObjectBullet(Scene *scene, Object *owner, int delay, int sprite_w, int sprite_h) : ObjectDamager(scene, owner, static_cast<ObjectPlayer *>(owner)->get_character()->get_bullet_damage(), true), max_life_time(5000) {
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(static_cast<ObjectPlayer *>(owner)->get_character()->get_bullet_path()),
		SDL_Rect { 0, 0, sprite_w, sprite_h },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->delay = delay;
	this->set_active(false);
	this->set_iframes(1);
	this->set_z(1);
	this->activate_near_miss = true;
}
ObjectBullet::~ObjectBullet() {

}

void ObjectBullet::update(void) {
	ObjectDamager::update();

	if(this->is_active()) {
		if(this->get_frames_existed() >= this->max_life_time || (this->get_x_scaled() <= -this->get_w_scaled() || this->get_x_scaled() >= Game::get_instance()->get_width()) || (this->get_y_scaled() <= -this->get_h_scaled() || this->get_y_scaled() >= Game::get_instance()->get_height())) {
			this->remove();
		}
	} else {
		if(this->delay == 0) {
			this->set_active(true);
		} else {
			-- this->delay;
		}

		this->set_pos_percent(this->get_owner()->get_hitbox_x_percent() + this->get_owner()->get_hitbox_w_percent() / 2 - this->get_hitbox_w_percent() / 2, this->get_owner()->get_hitbox_y_percent() + this->get_owner()->get_hitbox_h_percent() / 2 - this->get_hitbox_h_percent() / 2); // hmm. do we lock the player to the spot until the bullets shoot? do we move them with the player? or do we leave them behind? TODO
	}
}
void ObjectBullet::render(void) {
	float life_time = ((float) (this->max_life_time - this->get_frames_existed()) / (float) this->max_life_time);

	Uint8 alpha = 255;
	if(life_time <= 0.25) {
		SDL_GetTextureAlphaMod(this->get_sprite().texture, &alpha);
		SDL_SetTextureAlphaMod(this->get_sprite().texture, (this->get_frames_existed() / 50) % 2 == 0 ? 128 : 0);
	}

	Object::render();

	if(life_time <= 0.25) {
		SDL_SetTextureAlphaMod(this->get_sprite().texture, alpha);
	}
}

void ObjectBullet::set_activates_near_miss(bool activates_near_miss) {
	this->activate_near_miss = activates_near_miss;
}
bool ObjectBullet::get_activates_near_miss(void) const {
	return this->activate_near_miss;
}

void ObjectBullet::on_break(void) {
	for(int i = 0; i < 8; ++ i) { // TODO eggshell particles
		Object *particle = new ObjectParticle(this->get_scene(), "Data/Assets/.png/eggshell.png", 750, 32, 32, 32, 32);
//		particle->set_pos(this->get_x() + this->get_w() / 2.0 - 16, this->get_y() + this->get_h() / 2.0 - 16);
//		particle->set_deltas((float) std::cos(0.01745329252 * (45 * i)) / 2.0, (float) std::sin(0.01745329252 * (45 * i)) / 2.0);
		particle->set_angle_delta(1);
		particle->set_rotation(rand() % 360);
//		this->get_scene()->push_back(particle);
	} // TODO what the fuck
	this->remove();
}
