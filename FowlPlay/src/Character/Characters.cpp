#include "Characters.h"

#include "CharacterHen.h"
#include "CharacterGoose.h"
#include "CharacterTurkey.h"
#include "CharacterOstrich.h"
#include "CharacterCrow.h"
#include "CharacterPenguin.h"

Character *Characters::hen = nullptr;
Character *Characters::goose = nullptr;
Character *Characters::turkey = nullptr;
Character *Characters::ostrich = nullptr;
Character *Characters::crow = nullptr;
Character *Characters::penguin = nullptr;

void Characters::init(void) {
	Characters::hen = new CharacterHen();
	Characters::goose = new CharacterGoose();
	Characters::turkey = new CharacterTurkey();
	Characters::ostrich = new CharacterOstrich();
	Characters::crow = new CharacterCrow();
	Characters::penguin = new CharacterPenguin();
}
