#include "ObjectCharacterFrame.h"

#include "../../Game.h"
#include "../SceneTitle.h"
#include "ObjectPlayerFrame.h"

ObjectCharacterFrame::ObjectCharacterFrame(Scene *scene, Character *character) : ObjectImage(scene, "Data/Assets/.png/small_frame.png", nullptr, 0, 192, 96, 96, [&] (std::unique_ptr<Object *> &selector) {
	SceneTitle *title = static_cast<SceneTitle *>(this->get_scene());
	ObjectPlayerFrame *frame = static_cast<ObjectPlayerFrame *>(title->player_frame_from_selector(selector));
	frame->interact(selector);
	title->select(selector, nullptr);
}) {
	this->character = character;
	this->inner_sprite = sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(character->get_texture_path()),
		SDL_Rect { 0, 0, 64, 64 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	};
}
ObjectCharacterFrame::~ObjectCharacterFrame(void) {
	delete this->character;
}

void ObjectCharacterFrame::render(void) {
	ObjectImage::render();

	this->inner_sprite.dstrect.w = this->get_w_scaled() * 0.75;
	this->inner_sprite.dstrect.h = this->get_h_scaled() * 0.75;
	this->inner_sprite.dstrect.x = this->get_x_scaled() + (this->get_w_scaled() - this->inner_sprite.dstrect.w) / 2;
	this->inner_sprite.dstrect.y = this->get_y_scaled() + (this->get_h_scaled() - this->inner_sprite.dstrect.h) / 2;

	sprite_ex_f::render(this->inner_sprite);
}

void ObjectCharacterFrame::on_selected(std::unique_ptr<Object *> &selector) {
	SceneTitle *title = static_cast<SceneTitle *>(Game::get_instance()->get_scene());

	if(selector == title->selector_from_controller(Game::get_instance()->get_controller(0))) {
		this->get_sprite().srcrect = SDL_Rect {
			0, 0, 96, 96
		};
	} else if(selector == title->selector_from_controller(Game::get_instance()->get_controller(1))) {
		this->get_sprite().srcrect = SDL_Rect {
			96, 0, 96, 96
		};
	} else if(selector == title->selector_from_controller(Game::get_instance()->get_controller(2))) {
		this->get_sprite().srcrect = SDL_Rect {
			0, 96, 96, 96
		};
	} else if(selector == title->selector_from_controller(Game::get_instance()->get_controller(3))) {
		this->get_sprite().srcrect = SDL_Rect {
			96, 96, 96, 96
		};
	} else {
		this->get_sprite().srcrect = SDL_Rect {
			0, 192, 96, 96
		};
	}
	this->set_selected(true);

	static_cast<ObjectPlayerFrame *>(title->player_frame_from_selector(selector))->on_selected(selector);
}
void ObjectCharacterFrame::on_unselected(std::unique_ptr<Object *> &selector) {
	this->get_sprite().srcrect = SDL_Rect {
		0, 192, 96, 96
	};
	this->set_selected(false);

	for(controller_group *controller : Game::get_instance()->get_controllers()) {
		SceneTitle *title = static_cast<SceneTitle *>(this->get_scene());
		std::unique_ptr<Object *> &old_selector = title->selector_from_controller(controller);
		if(old_selector != selector && *old_selector == this) {
			this->on_selected(title->selector_from_controller(controller));
			this->set_selected(true);
		}
	}
}

Character *ObjectCharacterFrame::get_character(void) const {
	return this->character;
}
