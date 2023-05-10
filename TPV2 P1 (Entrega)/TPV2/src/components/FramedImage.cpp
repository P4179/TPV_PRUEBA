#include "./FramedImage.h"

void FramedImage::initComponent() {
	// se guarda la referencia al Transform de la entidad
	transform = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(transform != nullptr);
}

void FramedImage::update(float frameTime) {
	elapsedTime += frameTime;

	if (elapsedTime > timer) {
		elapsedTime = 0;
		// se coge el frame de la siguiente columna
		++col;
		if (col >= texture->getCols()) {
			// si se han recorrido todas las columnas, se pasa a la siguiente fila
			++row;
			col = 0;

			// si se han recorrido todas las filas, se vuelve a la primera
			if (row >= texture->getRows()) {
				row = 0;
			}
		}
	}
}

void FramedImage::render() {
	SDL_Rect dest = transform->getRect();

	texture->renderFrame(dest, row, col);
}