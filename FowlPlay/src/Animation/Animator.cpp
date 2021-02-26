#include "Animator.h"

animation::~animation(void) {
	delete this->framerects;
}

Animator::Animator(void) {
	this->a = nullptr;
}
Animator::~Animator(void) {
	delete this->a;
}

void Animator::set_frame_delay(int frame_delay) {
	if(this->a != nullptr) {
		this->a->framedelay = frame_delay;
	}
}
void Animator::update(SDL_Rect *srcrect) {
	if(this->a != nullptr && this->a->animating) {
		++ this->a->frameat;
		if(this->a->framedelay != 0) {
			if(this->a->frameat % this->a->framedelay == 0) {
				++ this->a->framenum;
				if(this->a->framenum >= this->a->frames) {
					this->a->framenum = 0;
					if(!this->a->loop) {
						this->a->animating = false;
					}
				}
			}
			*srcrect = *this->a->framerects[this->a->framenum];
		}
	}
}
void Animator::set_animation(animation *a, bool animating) {
	this->a = a;
	this->a->animating = animating;
}
void Animator::set_animating(bool animating) {
	this->a->animating = animating;
}
bool Animator::animation_is(animation *a) const {
	return this->a == a;
}
bool Animator::is_animating(void) const {
	return this->a->animating;
}
