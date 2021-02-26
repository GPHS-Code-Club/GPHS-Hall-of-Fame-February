#ifndef SCENE_OBJECT_OBJECTPLAYERFRAME_H_
#define SCENE_OBJECT_OBJECTPLAYERFRAME_H_

#include "ObjectImage.h"
#include "../../Character/Character.h"

class ObjectPlayerFrame : public ObjectImage {
	int controller_index;
	controller_group *controller;
	sprite_ex_f character_sprite;
	bool animated;
	Character *character;

	public:
		ObjectPlayerFrame(Scene *scene, int controller_index, animation *a);
		virtual ~ObjectPlayerFrame(void);

		void interact(std::unique_ptr<Object *> &selector) override;

		virtual void update(void) override;
		virtual void render(void) override;

		virtual void on_selected(std::unique_ptr<Object *> &selector) override;
		virtual void on_unselected(std::unique_ptr<Object *> &selector) override;

		bool ready(void) const;

		Character *get_character(void) const;
};

#endif /* SCENE_OBJECT_OBJECTPLAYERFRAME_H_ */
