#ifndef SCENE_OBJECT_OBJECTCHARACTERFRAME_H_
#define SCENE_OBJECT_OBJECTCHARACTERFRAME_H_

#include "ObjectImage.h"
#include "../../Character/Character.h"

class ObjectCharacterFrame : public ObjectImage {
	Character *character;
	sprite_ex_f inner_sprite;

	public:
		ObjectCharacterFrame(Scene *scene, Character *character);
		virtual ~ObjectCharacterFrame(void);

		virtual void render(void) override;

		virtual void on_selected(std::unique_ptr<Object *> &selector) override;
		virtual void on_unselected(std::unique_ptr<Object *> &selector) override;

		Character *get_character(void) const;
};

#endif /* SCENE_OBJECT_OBJECTCHARACTERFRAME_H_ */
