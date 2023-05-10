#pragma once

#include "../utils/checkML.h"

namespace ecs {
	class Entity;
	class Manager;

	// es un struct porque solo tiene datos, no comportamientos
	struct Component {
	protected:
		ecs::Entity* ent_;
		ecs::Manager* mngr_;

	public:
		Component() : ent_(nullptr), mngr_(nullptr) {}

		virtual ~Component() { }

		// Se utiliza para pasarle al componente un puntero a su entidad y al manager
		// INLINE significa que al llamar el método no se cambia el contador de programa,
		// sino que se copia el cuerpo del método. Por lo que se consigue mejor rendimiento
		// Se utiliza para método pequeños
		inline void setContext(ecs::Entity* ent, ecs::Manager* mngr) {
			ent_ = ent;
			mngr_ = mngr;
		}

		// se invoca al añadir un componente a una entidad
		// Se inicializa el componente si es necesario
		virtual void initComponent() { }


		// SE DEJAN ESTOS MÉTODOS POR SI SE QUIERE SEGUIR USANDO EL MODELO GAMEOBJECTS - COMPONENTS
		
		// para actualizar el estado
		virtual void update(float frameTime) { }
		// para manejar el pintado
		virtual void render() { }
		// manejar el input del jugador
		virtual void handleInput() { }
	};
}