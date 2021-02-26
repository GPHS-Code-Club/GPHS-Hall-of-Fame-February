#include "ObjectPlayerFrame.h"

#include "../../Game.h"
#include "../SceneTitle.h"
#include "ObjectCharacterFrame.h"

ObjectPlayerFrame::ObjectPlayerFrame(Scene *scene, int controller_index, animation *a) : ObjectImage(scene, "Data/Assets/.png/frame.png", a, 0, 192, 96, 96, [&] (std::unique_ptr<Object *> &selector) {
	this->play_animation();
	this->animated = true;
}) {
	this->controller_index = controller_index;
	this->controller = Game::get_instance()->get_controller(this->controller_index);
	this->character_sprite = sprite_ex_f {
		Game::get_instance()->get_renderer(),
		nullptr,
		SDL_Rect { 0, 0, 64, 64 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	};
	this->animated = false;
	this->character = nullptr;
}
ObjectPlayerFrame::~ObjectPlayerFrame(void) {
	delete this->controller;
}

void ObjectPlayerFrame::interact(std::unique_ptr<Object *> &selector) {
	ObjectImage::interact(selector);
}

void ObjectPlayerFrame::update(void) {
	if(this->controller == nullptr) { // TODO remove if statement once removing controllers works, and always test
		this->controller = Game::get_instance()->get_controller(this->controller_index);
		if(this->controller != nullptr) {
			SceneTitle *title = static_cast<SceneTitle *>(Game::get_instance()->get_scene());
			title->select(title->selector_from_controller(this->controller), title->get_first_character_frame_available());
		}
	}

	ObjectImage::update();
}
void ObjectPlayerFrame::render(void) {
	this->character_sprite.dstrect.w = this->get_w_scaled() * 0.5;
	this->character_sprite.dstrect.h = this->get_h_scaled() * 0.5;
	this->character_sprite.dstrect.x = this->get_x_scaled() + (this->get_w_scaled() - this->character_sprite.dstrect.w) / 2;
	this->character_sprite.dstrect.y = this->get_y_scaled() + (this->get_h_scaled() - this->character_sprite.dstrect.h) / 2;

	if(this->controller == nullptr) {
		this->get_sprite().srcrect = {
			0, 384, 96, 96
		};
	} else {
		if(!this->get_animator().is_animating()) {
			if(this->animated) {
				this->get_sprite().srcrect = *this->get_animation()->framerects[11];
			} else {
				if(this->get_animation()->framerects != nullptr && this->get_animation()->framerects[0] != nullptr) {
					this->get_sprite().srcrect = *this->get_animation()->framerects[0];
				} else {
					this->get_sprite().srcrect = { 0, 0, 0, 0 };
				}
			}
		}
	}

	SceneTitle *title = static_cast<SceneTitle *>(this->get_scene());
	std::unique_ptr<Object *> &selector = title->selector_from_controller(this->controller);
	if(selector.get() != nullptr) {
		if(ObjectCharacterFrame *frame = dynamic_cast<ObjectCharacterFrame *>(*selector)) {
			this->character_sprite.texture = Game::get_instance()->get_cache()->load_texture(frame->get_character()->get_texture_path());
			this->character = frame->get_character();
		}
	}

	ObjectImage::render();

	if(this->character_sprite.texture != nullptr) {
		sprite_ex_f::render(this->character_sprite);
	}
}

void ObjectPlayerFrame::on_selected(std::unique_ptr<Object *> &selector) {
	this->set_selected(true);
}
void ObjectPlayerFrame::on_unselected(std::unique_ptr<Object *> &selector) {
	this->set_selected(false);
}

bool ObjectPlayerFrame::ready(void) const {
	return this->animated;
}

Character *ObjectPlayerFrame::get_character(void) const {
	return this->character;
}
