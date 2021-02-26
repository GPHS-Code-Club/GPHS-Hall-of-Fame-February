#pragma once

#ifndef OBJECT_OBJECTDAMAGER_H_
#define OBJECT_OBJECTDAMAGER_H_

#include "Object.h"

class ObjectDamager : public Object {
	Object *owner;
	SDL_FPoint knockback;
	int iframes;
	int damage;
	bool disappears;

	public:
		ObjectDamager(Scene *scene, Object *owner, int damage, bool disappears);
		virtual ~ObjectDamager(void);

		virtual void update(void) override;

		int get_damage(void) const;
		float get_knockback_x(void) const;
		float get_knockback_y(void) const;
		void set_knockback(float x, float y);
		Object *get_owner(void) const;
		bool disappear_on_collision(void) const;
		void set_iframes(int iframes);
		int get_iframes(void) const;
};

#endif /* OBJECT_OBJECTDAMAGER_H_ */
