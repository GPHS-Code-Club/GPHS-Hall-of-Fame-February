#ifndef CHARACTER_CHARACTERPENGUIN_H_
#define CHARACTER_CHARACTERPENGUIN_H_

#include "Character.h"

class CharacterPenguin : public Character {
	public:
		CharacterPenguin(void);
		virtual ~CharacterPenguin(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTER_CHARACTEROSTRICH_H_ */
