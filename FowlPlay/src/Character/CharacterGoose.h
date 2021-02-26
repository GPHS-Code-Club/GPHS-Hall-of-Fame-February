#pragma once

#ifndef CHARACTER_CHARACTERGOOSE_H_
#define CHARACTER_CHARACTERGOOSE_H_

#include "Character.h"

class CharacterGoose : public Character {
	public:
		CharacterGoose(void);
		virtual ~CharacterGoose(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTERGOOSE_H_ */
