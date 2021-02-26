#include "ObjectParticle.h"

#include "SDL2/SDL_image.h"
#include "../../Game.h"
#include "../../TextureCache.h"

#include <iostream>

ObjectParticle::ObjectParticle(Scene *scene, const char *path, int max_life_time, float w, float h, int sprite_w, int sprite_h) : Object(scene), max_life_time(max_life_time), w(w), h(h) {
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(path),
		SDL_Rect { 0, 0, sprite_w, sprite_h },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->scale = 1.0;
	this->set_size_percent(this->w, this->h);
}
ObjectParticle::~ObjectParticle() {
	// TODO Auto-generated destructor stub
}

void ObjectParticle::update(void) {
	Object::update();

	this->scale = ((float) (this->max_life_time - this->get_frames_existed()) / (float) this->max_life_time);
	this->set_deltas_percent(this->get_dx_percent() * 0.99, this->get_dy_percent() * 0.99);

	if(this->get_frames_existed() >= this->max_life_time || (this->get_x_percent() <= -this->get_w_percent() || this->get_x_percent() >= 1.0) || (this->get_y_percent() <= -this->get_h_percent() || this->get_y_percent() >= 1.0)) {
		this->remove();
	}
}
void ObjectParticle::render(void) {
	if(this->is_active()) {
		this->get_sprite().dstrect.x = this->get_x_scaled();
		this->get_sprite().dstrect.y = this->get_y_scaled();
		this->get_sprite().dstrect.w = this->w * this->scale * Game::get_instance()->get_width();
		this->get_sprite().dstrect.h = this->h * this->scale * Game::get_instance()->get_width();
		this->get_sprite().center.x = this->get_w_scaled() / 2;
		this->get_sprite().center.y = this->get_h_scaled() / 2;

		Uint8 alpha = 255;
		SDL_GetTextureAlphaMod(this->get_sprite().texture, &alpha);
		SDL_SetTextureAlphaMod(this->get_sprite().texture, (this->scale * 255));

		sprite_ex_f::render(this->get_sprite());

		SDL_SetTextureAlphaMod(this->get_sprite().texture, alpha);
	}
}
