#include "./Health.h"

void Health::render() {
	SDL_Rect dest;
	dest.w = dest.h = 50;
	dest.y = 0;

	// renderiza cada coraz�n uno detr�s de otro
	for (int i = 0; i < lifes; ++i) {
		dest.x = 0 + dest.w * i;

		texture->render(dest);
	}
}