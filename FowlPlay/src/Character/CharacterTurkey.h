#ifndef CHARACTER_CHARACTERTURKEY_H_
#define CHARACTER_CHARACTERTURKEY_H_

#include "Character.h"

class CharacterTurkey : public Character {
	public:
		CharacterTurkey(void);
		virtual ~CharacterTurkey(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTER_CHARACTERTURKEY_H_ */
