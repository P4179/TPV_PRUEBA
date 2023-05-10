#include "Manager.h"
#include "Entity.h"

ecs::Manager::Manager() : entsByGroup_() {
	// se reserva memoria para cada grupo de la lista de grupos
	for (auto& groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}

	for (auto& system : sys_) {
		system = nullptr;
	}
}

ecs::Manager::~Manager() {
	// borrar todas las entidades de todos los grupos
	for (auto& ents : entsByGroup_) {
		for (auto e : ents) {
			delete e;
		}
	}

	for (auto system : sys_) {
		delete system;
	}
}

// se crea la entidad dentro de addEntity para tener más control de la gestión de memoria
ecs::Entity* ecs::Manager::addEntity(ecs::grpId_type gId) {
	// crea la entidad
	ecs::Entity* e = new ecs::Entity(gId);
	// se establece la entidad est?viva
	setAlive(e, true);

	setActive(e, true);
	// establece el contexto de la entidad con el propio manager
	e->setContext(this);
	// se añade la entidad a la lista
	entsByGroup_[gId].push_back(e);

	return e;
}

// llama al update de todas entidades
void ecs::Manager::update(float frameTime) {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++) {
			ents[i]->update(frameTime);
		}
	}
}

// llama al render de todas entidades
void ecs::Manager::render() {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++) {
			ents[i]->render();
		}
	}
}

void ecs::Manager::handleInput() {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++) {
			ents[i]->handleInput();
		}
	}
}

void ecs::Manager::refresh() {
	// recorre la lista de grupos
	for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
		// para cada grupo quita del vector las entidades que no están vivas
		// además, aprovecha para eliminar memoria
		vector<Entity*>& grpEnts = entsByGroup_[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* e) {
					if (e->isAlive()) {
						return false;
					}
					else {
						delete e;
						return true;
					}
				}),
			grpEnts.end());
	}
}