#ifndef SCENE_OBJECT_OBJECTPICKUP_H_
#define SCENE_OBJECT_OBJECTPICKUP_H_

#include "Object.h"
#include "../../Pickup/Pickup.h"

class ObjectPickup : public Object {
	float flip_scale;
	sprite_f shadow;
	Pickup *pickup;

	public:
		ObjectPickup(Scene *scene, Pickup *pickup);
		virtual ~ObjectPickup(void);

		virtual void update(void) override;
		virtual void render(void) override;

		Pickup *get_pickup(void) const;
};

#endif /* SCENE_OBJECT_OBJECTPICKUP_H_ */
