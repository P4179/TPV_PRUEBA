#include "./KeyToContinue.h"

void KeyToContinue::handleInput() {
	if (ih->isKeyDown(key)) {
		callback();
	}
}