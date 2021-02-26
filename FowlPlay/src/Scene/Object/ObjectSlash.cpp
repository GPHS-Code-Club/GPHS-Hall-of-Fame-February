#include "ObjectSlash.h"

#include "../../Game.h"
#include "SDL2/SDL_image.h"
#include "ObjectPlayer.h"
#include "../../TextureCache.h"

#include <cmath>

ObjectSlash::ObjectSlash(Scene *scene, Object *owner, float off_x, float off_y) : ObjectDamager(scene, owner, 10, false) {
	this->set_size_percent(0.05, 0.1);
	this->set_hitbox_percent(0, 0, 0.05, 0.1);
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/slash.png"),
		SDL_Rect { 0, 0, 64, 64},
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->set_deltas_percent(0, 0);
	this->offset = SDL_FPoint { off_x, off_y };
	this->slashing = animation::create<16>(12, "Data/Assets/.anim/slashing.anim", 32, 32, false);
	this->slashing->framerects = animation::load<16>("Data/Assets/.anim/slashing.anim", 32, 32);
	this->set_knockback(off_x, off_y);
//	this->set_iframes(1000);
	this->set_iframes(1);
	this->set_z(2);
	this->set_rotation(std::atan(off_y / off_x) * 57.296 + (off_x > 0 ? 180 : 0));
	this->set_breaks_bullet(true);
}

ObjectSlash::~ObjectSlash(void) {
	delete this->slashing;
}

void ObjectSlash::update(void) {
	ObjectDamager::update();

	this->set_pos_percent(this->get_owner()->get_hitbox_x_percent() + this->get_owner()->get_hitbox_w_percent() / 2 + this->offset.x - 0.05 / 2, this->get_owner()->get_hitbox_y_percent() + this->get_owner()->get_hitbox_w_percent() / 2 + this->offset.y - 0.1 / 2);

	if(this->animator.animation_is(nullptr)) {
		this->animator.set_animation(this->slashing, true);
	}

	if(this->get_can_collide()) {
		if(this->get_frames_existed() > 50) {
			this->set_can_collide(false);
		} else {
//			for(Object *object : this->get_collisions()) {
//				if(ObjectBullet *bullet = dynamic_cast<ObjectBullet *>(object)) {
//					if(bullet->get_owner() != this->get_owner()) {
//						bullet->remove();
//					}
//				}
//			} // TODO put on bullet
		}
	}

	if(!this->animator.is_animating()) {
		this->remove();
		static_cast<ObjectPlayer *>(this->get_owner())->set_attacking(false);
	}
}
void ObjectSlash::render(void) {
	this->animator.update(&this->get_sprite().srcrect);

	Object::render();
}
