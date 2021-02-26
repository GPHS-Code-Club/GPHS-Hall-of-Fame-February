#include "SceneTitle.h"

#include "../Game.h"
#include "../Animation/Detail.h"
#include "../Character/Characters.h"
#include "Scenes.h"
#include "Object/ObjectText.h"
#include "Object/ObjectCharacterFrame.h"
#include "Object/ObjectPlayerFrame.h"
#include "Object/ObjectPlayer.h"

SceneTitle::SceneTitle(void) : Scene(128, 128, 255) {
	this->logo = nullptr;
	this->button_fight = nullptr;
	this->button_party = nullptr;
	this->button_story = nullptr;
	this->button_arcade = nullptr;
	this->connect_controller_text = nullptr;
	this->p1_frame = nullptr;
	this->p2_frame = nullptr;
	this->p3_frame = nullptr;
	this->p4_frame = nullptr;
	this->hen_frame = nullptr;
	this->goose_frame = nullptr;
	this->turkey_frame = nullptr;
	this->ostrich_frame = nullptr;
	this->crow_frame = nullptr;
	this->penguin_frame = nullptr;
	this->ready_text = nullptr;
}
SceneTitle::~SceneTitle(void) {
	delete this->logo;
	delete this->button_fight;
	delete this->button_party;
	delete this->button_story;
	delete this->button_arcade;
	delete this->connect_controller_text;
	delete this->p1_frame;
	delete this->p2_frame;
	delete this->p3_frame;
	delete this->p4_frame;
	delete this->hen_frame;
	delete this->goose_frame;
	delete this->turkey_frame;
	delete this->ostrich_frame;
	delete this->crow_frame;
	delete this->penguin_frame;
	delete this->ready_text;
}

void SceneTitle::setup(void) {
	Scene::setup();

	animation *logo_anim = animation::create<2>(75, "Data/Assets/.anim/logo.anim", 512, 512, true);
	logo_anim->framerects = animation::load<2>("Data/Assets/.anim/logo.anim", 512, 512);
	this->logo = new ObjectImage(this, "Data/Assets/.png/logo.png", logo_anim, 0, 0, 512, 512, [this] (std::unique_ptr<Object *> &selector) {
		static_cast<ObjectImage *>(this->logo)->play_animation();
		this->logo->after_n_frames(500, [&] () {
			static_cast<ObjectImage *>(this->logo)->move_to(this->logo->get_x_percent(), -this->logo->get_h_percent());
			static_cast<ObjectImage *>(this->button_fight)->move_to(this->button_fight->get_x_percent(), 0.25 - this->button_fight->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->button_party)->move_to(this->button_party->get_x_percent(), 0.25 - this->button_party->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->button_story)->move_to(this->button_story->get_x_percent(), 0.75 - this->button_story->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->button_arcade)->move_to(this->button_arcade->get_x_percent(), 0.75 - this->button_arcade->get_h_percent() / 2);
			this->logo->after_n_frames(1000, [&] {
				this->logo->remove();
				this->select(this->p1_selector, this->button_fight); // TODO see why it doesn't work if i put it before after_n_frames
			});
		});
	});
	this->logo->set_size_percent(0.5, 0.9);
	this->logo->set_pos_percent(0.5 - this->logo->get_w_percent() / 2, 0.5 - this->logo->get_h_percent() / 2);
	this->push_back(this->logo);

	this->button_fight = new ObjectImage(this, "Data/Assets/.png/button_fight.png", nullptr, 0, 0, 256, 128, [this] (std::unique_ptr<Object *> &selector) {
		this->button_fight->after_n_frames(100, [&] () {
			static_cast<ObjectImage *>(this->button_fight)->move_to(this->button_fight->get_x_percent(), 1.25);
			static_cast<ObjectImage *>(this->button_party)->move_to(this->button_party->get_x_percent(), 1.25);
			static_cast<ObjectImage *>(this->button_story)->move_to(this->button_story->get_x_percent(), 1.75);
			static_cast<ObjectImage *>(this->button_arcade)->move_to(this->button_arcade->get_x_percent(), 1.75);

			static_cast<ObjectImage *>(this->p1_frame)->move_to(this->p1_frame->get_x_percent(), 0.05);
			static_cast<ObjectImage *>(this->p2_frame)->move_to(this->p2_frame->get_x_percent(), 0.05);
			static_cast<ObjectImage *>(this->p3_frame)->move_to(this->p3_frame->get_x_percent(), 0.05);
			static_cast<ObjectImage *>(this->p4_frame)->move_to(this->p4_frame->get_x_percent(), 0.05);

			static_cast<ObjectImage *>(this->hen_frame)->move_to(this->hen_frame->get_x_percent(), 0.6 - this->hen_frame->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->goose_frame)->move_to(this->goose_frame->get_x_percent(), 0.6 - this->goose_frame->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->turkey_frame)->move_to(this->turkey_frame->get_x_percent(), 0.6 - this->turkey_frame->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->ostrich_frame)->move_to(this->ostrich_frame->get_x_percent(), 0.6 - this->ostrich_frame->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->crow_frame)->move_to(this->crow_frame->get_x_percent(), 0.6 - this->crow_frame->get_h_percent() / 2);
			static_cast<ObjectImage *>(this->penguin_frame)->move_to(this->penguin_frame->get_x_percent(), 0.6 - this->penguin_frame->get_h_percent() / 2);

			if(Game::get_instance()->get_controller(0) != nullptr) {
				this->select(this->p1_selector, this->hen_frame);
			}
			if(Game::get_instance()->get_controller(1) != nullptr) {
				this->select(this->p2_selector, this->goose_frame);
			}
			if(Game::get_instance()->get_controller(2) != nullptr) {
				this->select(this->p3_selector, this->turkey_frame);
			}
			if(Game::get_instance()->get_controller(3) != nullptr) {
				this->select(this->p4_selector, this->ostrich_frame);
			}
		});
	});
	this->button_fight->set_size_percent(0.5, 0.5);
	this->button_fight->set_pos_percent(0.25 - this->button_fight->get_w_percent() / 2, 1.25);
	this->push_back(this->button_fight);

	this->button_party = new ObjectImage(this, "Data/Assets/.png/button_party.png", nullptr, 0, 0, 256, 128, [] (std::unique_ptr<Object *> &selector) { });
	this->button_party->set_size_percent(0.5, 0.5);
	this->button_party->set_pos_percent(0.75 - this->button_party->get_w_percent() / 2, 1.25);
	this->push_back(this->button_party);

	this->button_story = new ObjectImage(this, "Data/Assets/.png/button_story.png", nullptr, 0, 0, 256, 128, [] (std::unique_ptr<Object *> &selector) { });
	this->button_story->set_size_percent(0.5, 0.5);
	this->button_story->set_pos_percent(0.25 - this->button_story->get_w_percent() / 2, 1.75);
	this->push_back(this->button_story);

	this->button_arcade = new ObjectImage(this, "Data/Assets/.png/button_arcade.png", nullptr, 0, 0, 256, 128, [] (std::unique_ptr<Object *> &selector) { });
	this->button_arcade->set_size_percent(0.5, 0.5);
	this->button_arcade->set_pos_percent(0.75 - this->button_arcade->get_w_percent() / 2, 1.75);
	this->push_back(this->button_arcade);

	this->connect_controller_text = new ObjectText(this, "Data/Assets/.ttf/agent-red.regular.ttf", "PLEASE CONNECT A CONTROLLER TO CONTINUE", 64, 255, 255, 255);
	this->connect_controller_text->set_size_percent(0.75, 0.05);
	this->connect_controller_text->set_pos_percent(0.5 - this->connect_controller_text->get_w_percent() / 2, 0.9 - this->connect_controller_text->get_h_percent() / 2);
	this->push_back(this->connect_controller_text);

	animation *p1_select = animation::create<12>(30, "Data/Assets/.anim/p1_select.anim", 96, 96, false);
	p1_select->framerects = animation::load<12>("Data/Assets/.anim/p1_select.anim", 96, 96);

	this->p1_frame = new ObjectPlayerFrame(this, 0, p1_select);
	this->p1_frame->set_size_percent(0.2, 0.4);
	this->p1_frame->set_pos_percent(0.125 - this->p1_frame->get_w_percent() / 2, -0.95);
	this->push_back(this->p1_frame);

	animation *p2_select = animation::create<12>(30, "Data/Assets/.anim/p2_select.anim", 96, 96, false);
	p2_select->framerects = animation::load<12>("Data/Assets/.anim/p2_select.anim", 96, 96);

	this->p2_frame = new ObjectPlayerFrame(this, 1, p2_select);
	this->p2_frame->set_size_percent(0.2, 0.4);
	this->p2_frame->set_pos_percent(0.375 - this->p2_frame->get_w_percent() / 2, -0.95);
	this->push_back(this->p2_frame);

	animation *p3_select = animation::create<12>(30, "Data/Assets/.anim/p3_select.anim", 96, 96, false);
	p3_select->framerects = animation::load<12>("Data/Assets/.anim/p3_select.anim", 96, 96);

	this->p3_frame = new ObjectPlayerFrame(this, 2, p3_select);
	this->p3_frame->set_size_percent(0.2, 0.4);
	this->p3_frame->set_pos_percent(0.625 - this->p3_frame->get_w_percent() / 2, -0.95);
	this->push_back(this->p3_frame);

	animation *p4_select = animation::create<12>(30, "Data/Assets/.anim/p4_select.anim", 96, 96, false);
	p4_select->framerects = animation::load<12>("Data/Assets/.anim/p4_select.anim", 96, 96);

	this->p4_frame = new ObjectPlayerFrame(this, 3, p4_select);
	this->p4_frame->set_size_percent(0.2, 0.4);
	this->p4_frame->set_pos_percent(0.875 - this->p4_frame->get_w_percent() / 2, -0.95);
	this->push_back(this->p4_frame);

	this->hen_frame = new ObjectCharacterFrame(this, Characters::hen);
	this->hen_frame->set_size_percent(0.1, 0.2);
	this->hen_frame->set_pos_percent(0.5 - this->hen_frame->get_w_percent() * 3, -(0.6 - this->hen_frame->get_h_percent() / 2));
	this->push_back(this->hen_frame);

	this->goose_frame = new ObjectCharacterFrame(this, Characters::goose);
	this->goose_frame->set_size_percent(0.1, 0.2);
	this->goose_frame->set_pos_percent(0.5 - this->goose_frame->get_w_percent() * 2, -(0.6 - this->goose_frame->get_h_percent() / 2));
	this->push_back(this->goose_frame);

	this->turkey_frame = new ObjectCharacterFrame(this, Characters::turkey);
	this->turkey_frame->set_size_percent(0.1, 0.2);
	this->turkey_frame->set_pos_percent(0.5 - this->turkey_frame->get_w_percent(), -(0.6 - this->turkey_frame->get_h_percent() / 2));
	this->push_back(this->turkey_frame);

	this->ostrich_frame = new ObjectCharacterFrame(this, Characters::ostrich);
	this->ostrich_frame->set_size_percent(0.1, 0.2);
	this->ostrich_frame->set_pos_percent(0.5, -(0.6 - this->ostrich_frame->get_h_percent() / 2));
	this->push_back(this->ostrich_frame);

	this->crow_frame = new ObjectCharacterFrame(this, Characters::crow);
	this->crow_frame->set_size_percent(0.1, 0.2);
	this->crow_frame->set_pos_percent(0.5 + this->crow_frame->get_w_percent(), -(0.6 - this->crow_frame->get_h_percent() / 2));
	this->push_back(this->crow_frame);

	this->penguin_frame = new ObjectCharacterFrame(this, Characters::penguin);
	this->penguin_frame->set_size_percent(0.1, 0.2);
	this->penguin_frame->set_pos_percent(0.5 + this->penguin_frame->get_w_percent() * 2, -(0.6 - this->penguin_frame->get_h_percent() / 2));
	this->push_back(this->penguin_frame);

	this->ready_text = new ObjectText(this, "Data/Assets/.ttf/agent-red.regular.ttf", "READY? PRESS A", 128, 0, 0, 0);
	this->ready_text->set_size_percent(0.5, 0.075);
	this->ready_text->set_pos_percent(0.5 - this->ready_text->get_w_percent() / 2, 0.8125 - this->ready_text->get_h_percent() / 2);
	this->ready_text->set_visible(false);
	this->push_back(this->ready_text);
}
void SceneTitle::update(void) {
	Scene::update();

	if(Game::get_instance()->get_controllers().empty()) {
		this->connect_controller_text->set_visible(true);
	} else {
		this->connect_controller_text->set_visible(false);
	}

	bool all_ready = true;

	for(controller_group *controller : Game::get_instance()->get_controllers()) {
		if(!static_cast<ObjectPlayerFrame *>(this->player_frame_from_selector(this->selector_from_controller(controller)))->ready()) {
			all_ready = false;
		}
		if(controller->input_wait == 0) {
			if(controller->left_x > 20000) {
				controller->input_wait = 75;
				if(*this->selector_from_controller(controller) == this->button_fight) {
					this->select(this->selector_from_controller(controller), this->button_party);
				} else if(*this->selector_from_controller(controller) == this->button_story) {
					this->select(this->selector_from_controller(controller), this->button_arcade);
				} else if(*this->selector_from_controller(controller) == this->hen_frame) {
					this->select(this->selector_from_controller(controller), this->goose_frame);
				} else if(*this->selector_from_controller(controller) == this->goose_frame) {
					this->select(this->selector_from_controller(controller), this->turkey_frame);
				} else if(*this->selector_from_controller(controller) == this->turkey_frame) {
					this->select(this->selector_from_controller(controller), this->ostrich_frame);
				} else if(*this->selector_from_controller(controller) == this->ostrich_frame) {
					this->select(this->selector_from_controller(controller), this->crow_frame);
				} else if(*this->selector_from_controller(controller) == this->crow_frame) {
					this->select(this->selector_from_controller(controller), this->penguin_frame);
				} else if(*this->selector_from_controller(controller) == this->penguin_frame) {
					this->select(this->selector_from_controller(controller), this->hen_frame);
				}
			} else if(controller->left_x < -20000) {
				controller->input_wait = 75;
				if(*this->selector_from_controller(controller) == this->button_party) {
					this->select(this->selector_from_controller(controller), this->button_fight);
				} else if(*this->selector_from_controller(controller) == this->button_arcade) {
					this->select(this->selector_from_controller(controller), this->button_story);
				} else if(*this->selector_from_controller(controller) == this->goose_frame) {
					this->select(this->selector_from_controller(controller), this->hen_frame);
				} else if(*this->selector_from_controller(controller) == this->turkey_frame) {
					this->select(this->selector_from_controller(controller), this->goose_frame);
				} else if(*this->selector_from_controller(controller) == this->ostrich_frame) {
					this->select(this->selector_from_controller(controller), this->turkey_frame);
				} else if(*this->selector_from_controller(controller) == this->crow_frame) {
					this->select(this->selector_from_controller(controller), this->ostrich_frame);
				} else if(*this->selector_from_controller(controller) == this->penguin_frame) {
					this->select(this->selector_from_controller(controller), this->crow_frame);
				} else if(*this->selector_from_controller(controller) == this->hen_frame) {
					this->select(this->selector_from_controller(controller), this->penguin_frame);
				}
			} else if(controller->left_y > 20000) {
				controller->input_wait = 75;
				if(*this->selector_from_controller(controller) == this->button_fight) {
					this->select(this->selector_from_controller(controller), this->button_story);
				} else if(*this->selector_from_controller(controller) == this->button_party) {
					this->select(this->selector_from_controller(controller), this->button_arcade);
				}
			} else if(controller->left_y < -20000) {
				controller->input_wait = 75;
				if(*this->selector_from_controller(controller) == this->button_story) {
					this->select(this->selector_from_controller(controller), this->button_fight);
				} else if(*this->selector_from_controller(controller) == this->button_arcade) {
					this->select(this->selector_from_controller(controller), this->button_party);
				}
			}
		} else if(controller->input_wait > 0) {
			-- controller->input_wait;
		}
	}

	if(all_ready && Game::get_instance()->get_controllers().size() > 0) {
		this->ready_text->set_visible(true);
	} else {
		this->ready_text->set_visible(false);
	}

	// TODO un hardcode later
}
void SceneTitle::render(void) {
	Scene::render();
}
void SceneTitle::destroy(void) {
	Scene::destroy();
}

void SceneTitle::on_button_press_a(controller_group *player) {
	if(this->ready_text->is_visible()) {
		Game::get_instance()->set_scene(Scenes::gameplay);

		unsigned int index = 0;
		for(controller_group *controller : Game::get_instance()->get_controllers()) {
			Object *player = new ObjectPlayer(
				Game::get_instance()->get_scene(),
				static_cast<ObjectPlayerFrame *>(this->player_frame_from_selector(this->selector_from_controller(controller)))->get_character(),
				index
			);
			if(Game::get_instance()->get_controllers().size() > 2) {
				player->set_pos_percent(index == 0 || index == 2 ? 0.1 : 0.9 - 0.05, index == 0 || index == 1 ? 0.25 - 0.1 / 2 : 0.75 - 0.1 / 2);
			} else {
				player->set_pos_percent(index == 0 ? 0.1 : 0.9 - 0.05, 0.5 - 0.1 / 2);
			}

			Game::get_instance()->get_scene()->push_back(player);

			++ index;
		}
	} else {
		if(std::find(this->get_objects()->begin(), this->get_objects()->end(), this->logo) != this->get_objects()->end()) {
			static_cast<ObjectImage *>(this->logo)->interact(this->p1_selector);
		} else {
			if(this->selector_from_controller(player) != nullptr) {
				static_cast<ObjectImage *>(*this->selector_from_controller(player))->interact(this->selector_from_controller(player));
			}
		}
	}
}
void SceneTitle::on_button_press_b(controller_group *player) {

}

void SceneTitle::select(std::unique_ptr<Object *> &selector, Object *object) const {
	if(selector != nullptr && *selector != nullptr) {
		if(ObjectImage *button = dynamic_cast<ObjectImage *>(*selector)) {
			button->on_unselected(selector);
		}
		selector.release();
	}
	selector = std::make_unique<Object *>(object);
	if(ObjectImage *button = dynamic_cast<ObjectImage *>(*selector)) {
		if(*selector != nullptr) {
			button->on_selected(selector);
		}
	}
}
std::unique_ptr<Object *> &SceneTitle::selector_from_controller(controller_group *controller) {
	if(controller == Game::get_instance()->get_controller(0)) {
		return this->p1_selector;
	} else if(controller == Game::get_instance()->get_controller(1)) {
		return this->p2_selector;
	} else if(controller == Game::get_instance()->get_controller(2)) {
		return this->p3_selector;
	} else if(controller == Game::get_instance()->get_controller(3)) {
		return this->p4_selector;
	} else {
		return this->p1_selector;
	}
}
Object *SceneTitle::player_frame_from_selector(std::unique_ptr<Object *> &selector) const {
	if(selector == this->p1_selector) {
		return this->p1_frame;
	} else if(selector == this->p2_selector) {
		return this->p2_frame;
	} else if(selector == this->p3_selector) {
		return this->p3_frame;
	} else if(selector == this->p4_selector) {
		return this->p4_frame;
	} else {
		return nullptr;
	}
}

Object *SceneTitle::get_first_character_frame_available(void) const {
	if(!static_cast<ObjectImage *>(this->hen_frame)->is_selected()) {
		return this->hen_frame;
	} else if(!static_cast<ObjectImage *>(this->goose_frame)->is_selected()) {
		return this->goose_frame;
	} else {
		return this->penguin_frame;
	}
}
