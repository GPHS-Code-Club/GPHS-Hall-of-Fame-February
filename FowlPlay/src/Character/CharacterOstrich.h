#ifndef CHARACTER_CHARACTEROSTRICH_H_
#define CHARACTER_CHARACTEROSTRICH_H_

#include "Character.h"

class CharacterOstrich : public Character {
	public:
		CharacterOstrich(void);
		virtual ~CharacterOstrich(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTER_CHARACTEROSTRICH_H_ */
