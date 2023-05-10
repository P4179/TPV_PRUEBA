#pragma once

#include <vector>
#include <array>
#include "../game/ecs_def.h"
#include "../utils/checkML.h"

using namespace std;

namespace ecs {
	class Entity;

	class Manager {
	private:
		// entidades que gestiona el manager
		// lista con los grupos de entidades
		array<vector<Entity*>, ecs::maxGroupId> entsByGroup_;
		// handlers
		// se establece solo para los objetos que interesen
		array<Entity*, ecs::maxHdlrId> hdlrs_;

	public:
		// constructora
		Manager();

		// destructora
		virtual ~Manager();

		// llama al update de todas entidades
		void update(float frameTime);

		// llama al render de todas entidades
		void render();

		void handleInput();

		// se crea la entidad dentro de addEntity para tener más control de la gestión de memoria
		Entity* addEntity(ecs::grpId_type gId = ecs::_grp_GENERAL);

		void refresh();

		// se devuelve la lista de entidades de un grupo
		const vector<Entity*>& getEntities(grpId_type gId = ecs::_grp_GENERAL) {
			return entsByGroup_[gId];
		}

		// se setea el handler de una unidad concreta
		inline void setHandler(hdlrId_type hId, Entity* e) {
			hdlrs_[hId] = e;
		}

		// se obtiene una unidad a partir de su handler
		inline Entity* getHandler(hdlrId_type hId) {
			return hdlrs_[hId];
		}
	};
}