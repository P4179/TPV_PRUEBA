#pragma once

#include <vector>
#include <array>
#include "../game/ecs_def.h"
#include "Component.h"
#include "../utils/checkML.h"

using namespace std;

namespace ecs {
	class Manager;

	class Entity {
	private:
		bool alive_;
		Manager* mngr_;
		// vector con todos los componentes que tiene una entidad para recorrerlos fácilmente
		vector<Component*> currCmps_;
		// array con los componentes que tiene una entidad
		// se utiliza para acceder a cada uno de ellos fácilmente, por identificador
		// Por ejemplo, el componente físico está en todas las entidades en la primera posición
		array<Component*, ecs::maxComponentId> cmps_;

	public:

		Entity() : mngr_(nullptr), cmps_(), currCmps_(), alive_() {
			// se reserva suficiente memoria en el vector para que no haga falta redimensionarlo
			// mejora el rendimiento
			currCmps_.reserve(ecs::maxComponentId);
		}

		// borra todos los componentes
		virtual ~Entity() {
			for (auto c : currCmps_) {
				delete c;
			}
		}

		// se le pasa el manager para que se le pueda pasar a sus componentes
		inline void setContext(Manager* mngr) {
			mngr_ = mngr;
		}

		// consultar si la entidad está viva o no
		// que una entidad no esté viva significa que se puede cuando se haya recorrido
		// toda la lista de entidades
		inline bool isAlive() {
			return alive_;
		}

		inline void setAlive(bool alive) {
			alive_ = alive;
		}

		// ejecuta update de todos los componentes
		inline void update(float frameTime) {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->update(frameTime);
			}
		}

		// ejecuta el render de todos los componentes
		inline void render() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->render();
			}
		}

		inline void handleInput() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; ++i) {
				currCmps_[i]->handleInput();
			}
		}

		// T es el tipo de componente
		// Ts son los tipos de los argumentos que recibe el componente
		// se utiliza && porque es lo que recibe de argumento forward
		template<typename T, typename ...Ts>
		inline T* addComponent(Ts&& ...args) {
			// crea el componente
			// forward asegura que el tipo con el que se cree el objeto
			// sea el mismo que ha recibido la función para un template T
			// Por ejemplo, asegura que el tipo es string y no string&
			T* c = new T(forward<Ts>(args)...);

			// a partir de la clase del componente se haya su identficador
			constexpr cmpId cId = T::id;

			// elimina cualquier componente que pudiera haber de ese tipo
			ecs::Entity::removeComponent<T>();

			// añade el componente al vector
			currCmps_.push_back(c);
			// añade el componente al array en su correspondiente posición
			cmps_[cId] = c;

			// setea el contexto del componente
			// la propia entidad y pasar el manager para que él pueda añadirlo
			c->setContext(this, mngr_);

			// inicializa el componente
			c->initComponent();

			return c;
		}

		// eliminar un componente de una entidad
		template<typename T>
		inline void removeComponent() {
			constexpr cmpId cId = T::id;

			// existe un componente de ese tipo
			if (cmps_[cId] != nullptr) {
				// se busca un componente en el vector
				auto iter = std::find(currCmps_.begin(), currCmps_.end(), cmps_[cId]);
				// se elimina del vector
				currCmps_.erase(iter);

				// se libera memoria del array
				delete cmps_[cId];
				// apunta a nullptr
				cmps_[cId] = nullptr;
			}
		}

		// siempre se utiliza typename
		template<typename T>
		inline T* getComponent() {
			constexpr cmpId cId = T::id;

			// se devuelve el componente haciendo casting
			// Por ejemplo, no se devuelve Component, sino Transform
			return static_cast<T*>(cmps_[cId]);
		}

		// se comprueba si existe ese componente
		template<typename T>
		inline bool hasComponent() {
			constexpr cmpId cId = T::id;

			return cmps_[cId] != nullptr;
		}

	};
}