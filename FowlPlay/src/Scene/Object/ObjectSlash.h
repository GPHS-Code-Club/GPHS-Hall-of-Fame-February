#ifndef OBJECT_OBJECTSLASH_H_
#define OBJECT_OBJECTSLASH_H_

#include "ObjectDamager.h"
#include "../../Animation/Animator.h"

class ObjectSlash : public ObjectDamager {
	Animator animator;
	animation *slashing;
	SDL_FPoint offset;

	public:
		ObjectSlash(Scene *scene, Object *owner, float off_x, float off_y);
		virtual ~ObjectSlash(void);

		virtual void update(void) override;
		virtual void render(void) override;
};

#endif /* OBJECT_OBJECTSLASH_H_ */
