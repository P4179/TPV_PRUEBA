#pragma once

#include "../game/ecs_def.h"

namespace ecs {
	class Manager;

	class System {
	protected:
		ecs::Manager* mngr_;

	public:
		virtual ~System() {	}

		void setContext(ecs::Manager* mngr) {
			mngr_ = mngr;
		}

		// iniciar datos del sistema
		virtual void initSystem() {	}

		virtual void update(float frameTime) { }

		// método para recibir un mensaje y procesarlo
		virtual void receive(const ecs::Message& m) { }
	};
}