#pragma once

#ifndef OBJECT_OBJECTBULLET_H_
#define OBJECT_OBJECTBULLET_H_

#include "ObjectDamager.h"

class ObjectBullet : public ObjectDamager {
	int delay;
	const int max_life_time;
	bool activate_near_miss;

	public:
		ObjectBullet(Scene *scene, Object *owner, int delay, int sprite_w, int sprite_h);
		virtual ~ObjectBullet(void);

		virtual void update(void) override;
		virtual void render(void) override;

		void set_activates_near_miss(bool activates_near_miss);
		bool get_activates_near_miss(void) const;

		void on_break(void);
};

#endif /* BULLETOBJECT_H_ */
