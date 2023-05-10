#pragma once

#include <vector>
#include <array>
#include "../game/ecs_def.h"
#include "../utils/checkML.h"
#include "System.h"
#include "Entity.h"

using namespace std;

namespace ecs {
	class Manager {
	private:
		// entidades que gestiona el manager
		// lista con los grupos de entidades
		array<vector<Entity*>, ecs::maxGroupId> entsByGroup_;
		// handlers
		// se establece solo para los objetos que interesen
		array<Entity*, ecs::maxHdlrId> hdlrs_;
		// array con los sistemas
		// cada sistema tiene un identificador, de modo que cada posición del array
		// es para un sistema distinto
		array<System*, maxSystemId> sys_;
		// vector con los mensajes pendientes
		// de esta forma, se asegura que los mensajes se procesan en el orden correcto
		// ej: sistemas A, B y C
		// el sistema A envía un mensaje m1 y cuando llega a B envía un mensaje m2
		// sin los mensajes pendientes, C recibiría primero m2 y luego, m1
		std::vector<ecs::Message> msgs_;
		std::vector<Message> aux_msgs_;

	public:
		// constructora
		Manager();

		// destructora
		virtual ~Manager();

		// COMPONENTES
		template<typename T, typename ...Ts>
		inline T* addComponent(Entity* e, Ts&& ...args) {
			T* c = new T(std::forward<Ts>(args)...);

			constexpr cmpId_type cId = T::id;
			removeComponent<T>(e);

			// se puede acceder a los atributos privados porque manager es amigo de entity
			e->currCmps_.push_back(c);
			e->cmps_[cId] = c;

			// no harían falta
			c->setContext(e, this);
			c->initComponent();

			return c;
		}

		template<typename T>
		inline void removeComponent(Entity* e) {
			constexpr cmpId_type cId = T::id;
			if (e->cmps_[cId] != nullptr) {
				auto iter = std::find(e->currCmps_.begin(), e->currCmps_.end(), e->cmps_[cId]);

				e->currCmps_.erase(iter);
				// eliminar
				delete e->cmps_[cId];
				e->cmps_[cId] = nullptr;
			}
		}

		template<typename T>
		inline bool hasComponent(Entity* e) {
			constexpr cmpId_type cId = T::id;
			return e->cmps_[cId] != nullptr;
		}

		template<typename T>
		inline T* getComponent(Entity* e) {
			constexpr cmpId_type cId = T::id;
			return static_cast<T*>(e->cmps_[cId]);
		}

		inline void setAlive(Entity* e, bool alive) {
			e->alive_ = alive;
		}

		inline bool isAlive(Entity* e) {
			return e->alive_;
		}

		inline void setActive(Entity* e, bool active) {
			e->active_ = active;
		}

		inline bool isActive(Entity* e) {
			return e->active_;
		}

		inline grpId_type groupId(Entity* e) {
			return e->gId_;
		}

		inline std::vector<Entity*>* getGroup(grpId grp) { return &entsByGroup_[grp]; }

		// ENTIDADES
		// se crea la entidad dentro de addEntity para tener más control de la gestión de memoria
		Entity* addEntity(ecs::grpId_type gId = ecs::_grp_GENERAL);

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

		// SISTEMAS
		// añadir un sistema al manager
		template<typename T, typename ...Ts>
		inline T* addSystem(Ts &&... args) {
			// se coge el id del sistema
			constexpr sysId_type sId = T::id;

			// se elimina que pudiera haber en ese mismo hueco
			removeSystem<T>();

			// se crea el sistema
			System* s = new T(std::forward<Ts>(args)...);

			s->setContext(this);
			s->initSystem();

			// se guardad en el lugar correspondiente en el array de sistemas
			sys_[sId] = s;

			return static_cast<T*>(s);
		}

		template<typename T>
		inline void removeSystem() {
			// se coge el id del sistema
			// si hay alguno en el array en esa posición, se elimina
			constexpr sysId_type sId = T::id;
			if (sys_[sId] != nullptr) {
				delete sys_[sId];
				sys_[sId] = nullptr;
			}
		}

		// coger un sistema del manager
		// se puede utilizar para pasarle un mensaje a un sistema concreto
		template<typename T>
		inline T* getSystem() {
			// se coge el id del sistema
			constexpr sysId_type sId = T::id;
			// se devuelve el sisteam
			return static_cast<T*>(sys_[sId]);
		}

		// enviar un mensaje a todos los sistemas con retardo o no
		inline void send(const ecs::Message& m, bool delay = false) {
			if (!delay) {
				for (System* s : sys_) {
					if (s != nullptr)
						s->receive(m);
				}
			}
			else {
				// colocarlo en el vector de mensajes pendientes de procesar
				// la diferencia entre emplace_back y push_back
				// es que en el primero se pueden meter varios datos juntos
				// y en el segundo, solo uno
				msgs_.emplace_back(m);
			}
		}

		// procesar los mensajes pendientes de procesar
		inline void flushMessages() {
			// se intercambian los vectores
			std::swap(msgs_, aux_msgs_);

			// se procesan los mensajes pendientes, que ahora están en el vector auxiliar
			for (auto& m : aux_msgs_) {
				for (System* s : sys_) {
					if (s != nullptr)
						s->receive(m);
				}
			}

			// se borran los mensajes procesados
			aux_msgs_.clear();
		}

		// MODELO GAMEOBJECTS - COMPONENTS
		// llama al update de todas entidades
		void update(float frameTime);
		// llama al render de todas entidades
		void render();
		void handleInput();
		void refresh();
	};
}