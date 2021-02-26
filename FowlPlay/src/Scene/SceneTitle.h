#pragma once

#ifndef SCENE_SCENETITLE_H_
#define SCENE_SCENETITLE_H_

#include "Scene.h"

#include "Object/ObjectImage.h"

#include <memory>

class SceneTitle : public Scene {
	Object *logo;
	Object *button_fight;
	Object *button_party;
	Object *button_story;
	Object *button_arcade;
	Object *connect_controller_text;
	Object *p1_frame;
	Object *p2_frame;
	Object *p3_frame;
	Object *p4_frame;
	Object *hen_frame;
	Object *goose_frame;
	Object *turkey_frame;
	Object *ostrich_frame;
	Object *crow_frame;
	Object *penguin_frame;
	Object *ready_text;

	std::unique_ptr<Object *> p1_selector;
	std::unique_ptr<Object *> p2_selector;
	std::unique_ptr<Object *> p3_selector;
	std::unique_ptr<Object *> p4_selector;

	public:
		SceneTitle(void);
		virtual ~SceneTitle(void);

		virtual void setup(void) override;
		virtual void update(void) override;
		virtual void render(void) override;
		virtual void destroy(void) override;

		virtual void on_button_press_a(controller_group *player) override;
		virtual void on_button_press_b(controller_group *player) override;

		void select(std::unique_ptr<Object *> &selector, Object *object) const;
		std::unique_ptr<Object *> &selector_from_controller(controller_group *controller);
		Object *player_frame_from_selector(std::unique_ptr<Object *> &selector) const;

		Object *get_first_character_frame_available(void) const;
};

#endif /* SCENE_SCENETITLE_H_ */
