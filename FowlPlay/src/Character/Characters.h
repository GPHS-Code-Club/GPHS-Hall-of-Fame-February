#pragma once

#ifndef CHARACTER_CHARACTERS_H_
#define CHARACTER_CHARACTERS_H_

#include "Character.h"

class Characters {
	public:
		static Character *hen;
		static Character *goose;
		static Character *turkey;
		static Character *ostrich;
		static Character *crow;
		static Character *penguin;

		static void init(void);
		// TODO deinit?
};

#endif /* CHARACTERS_H_ */
