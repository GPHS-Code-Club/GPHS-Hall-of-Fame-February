#include "Pickups.h"

#include "PickupCowtana.h"

Pickup *Pickups::cowtana = nullptr;

void Pickups::init(void) {
	Pickups::cowtana = new PickupCowtana();
}
