#include "./Image.h"

void Image::initComponent() {
	// se guarda la referencia al Transform de la entidad
	tr_ = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(tr_ != nullptr);
}

void Image::render() {
	SDL_Rect dest = tr_->getRect();

	// renderiza la textura
	tex_->render(dest, tr_->getRot());
}