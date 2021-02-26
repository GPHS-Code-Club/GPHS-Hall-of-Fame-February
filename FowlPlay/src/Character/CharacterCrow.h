#ifndef CHARACTER_CHARACTERCROW_H_
#define CHARACTER_CHARACTERCROW_H_

#include "Character.h"

class CharacterCrow : public Character {
	public:
		CharacterCrow(void);
		virtual ~CharacterCrow(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTER_CHARACTEROSTRICH_H_ */
