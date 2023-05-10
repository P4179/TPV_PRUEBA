#pragma once

#include <cstdint>
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLNetUtils.h"
#include "SDL_stdinc.h"

// se encuentra en un namespace
namespace ecs {
	class Entity;

	// uint8_t indica que se trata de un entero representado en 8 bits
	using cmpId_type = uint8_t;

	// los ítems del enum son enteros de 8 bits
	// se utiliza para seleccionar el componente adecuado en el array de componentes de una entidad
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,	// componente que controla la posición
		_IMAGE,	// componente que controla el render
		_CTRL,	// componente que controla el input
		_DE_ACCELERATION,
		_HEALTH,
		_SHOW_AT_OPPOSIDE_SIDE,
		_GUN,
		_DISABLE_ON_EXIT,
		_GENERATIONS,
		_FOLLOW,
		_ASTEROIDS_MANAGER,
		_COLLISIONS_MANAGER,
		_BUTTON,
		_SEPARATE_LETTERS,
		_NAME,

		// do not remove this
		_LAST_CMP_ID	// indica el número máximo de ítems que tiene el enum
	};

	// constante que se define en tiempo de compilación
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

	// grupos
	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		// grupo por defecto por si la entidad no pertenece a un grupo definido por el usuario
		_grp_GENERAL,
		_grp_FIGHTER,
		_grp_ASTEROIDS,
		_grp_BULLETS,
		_grp_BUTTONS,
		_grp_TEXT,
		_grp_ONLINE_TEXT,

		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	// handlers
	// se utilizan para acceder a una unidad específica del mismo manager 
	using hdlrId_type = uint8_t;
	enum hdlrId : hdlrId_type {
		FIGHTER,
		FIGHTER2,
		NAME,

		_LAST_HDLR_ID
	};
	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;

	using sysId_type = uint8_t;
	enum sysId : sysId_type {
		_sys_ASTEROIDS = 0,
		_sys_BULLET,
		_sys_BUTTON,
		_sys_ONLINE_BUTTON,
		_sys_COLLISIONS,
		_sys_FIGHTER,
		_sys_ONLINE_FIGHTER,
		_sys_GAME_CTRL,
		_sys_ONLINE,
		_sys_ONLINE_BULLET,
		_sys_ONLINE_COLLISIONS,
		_sys_RENDER,
		_sys_READ_INPUT,

		// do not remove this
		_LAST_SYS_ID
	};
	constexpr sysId_type maxSystemId = _LAST_SYS_ID;

	// mensajes
	using msgId_type = uint8_t;
	enum msgId : msgId_type {
		_m_ROUND_FINISHED,
		_m_COLLISION_FIGHTER_ASTEROID,
		_m_NO_ASTEROIDS,
		_m_ROUND_STARTED,
		_m_COLLISION_BULLET_ASTEROID,
		_m_SHOOT,
		_m_OPPONENT_SHOOT,
		_m_ADD_BULLET,
		_m_BUTTON_PRESSED,
		_m_ONLINE_MESSAGE,
		_m_FIGHTER_TRANSFORM,
		_m_COLLISION_BULLET_PLAYER,
		_m_CONNECTION_LOST,
		_m_SERVER_CHOSEN,
		_m_CLIENT_CHOSEN,
		_m_ONLINE_GAME_START,
		_m_OTHER_NAME,
		_m_GAMEOVER,
		_m_SUBSTRACT_OPPONENT_HP,
		_m_INVALID
	};

	// los mensajes son structs con el id del mensaje
	// y la información a pasar, que est?en un struct
	struct Message {
		msgId_type id;
		msgId_type nId;

		// _m_COLLISION_BULLET_ASTEROID
		struct {
			Entity* asteroid;
			Entity* bullet;
		} collision_bullet_asteroid_data;

		// _m_SHOOT
		struct {
			Vector2D pos;
			Vector2D vel;
			float width;
			float height;
		} shoot_data;

		// _m_BUTTON_PRESSED
		struct {
			void(*callback)();
		} button_pressed_data;

		// _m_FIGHTER_TRANSFORM
		struct {
			float posx;
			float posy;
			float rot;
			float velx;
			float vely;
		} fighter_transform_data;	
		
		// _m_GAMEOVER
		struct {
			Uint8 winner;
		} gameover_data;

		struct {
			char name[10];
			Uint8 size;
		} name_data;

	public:
		inline Uint8* serializeTransform(Uint8* buf) {
			buf = SDLNetUtils::serialize(nId, buf);
			buf = SDLNetUtils::serialize(fighter_transform_data.posx, buf);
			buf = SDLNetUtils::serialize(fighter_transform_data.posy, buf);
			buf = SDLNetUtils::serialize(fighter_transform_data.rot, buf);
			buf = SDLNetUtils::serialize(fighter_transform_data.velx, buf);
			buf = SDLNetUtils::serialize(fighter_transform_data.vely, buf);
			return buf;
		}

		inline Uint8* deserializeTransform(Uint8* buf) {
			buf = SDLNetUtils::deserialize(nId, buf);
			buf = SDLNetUtils::deserialize(fighter_transform_data.posx, buf);
			buf = SDLNetUtils::deserialize(fighter_transform_data.posy, buf);
			buf = SDLNetUtils::deserialize(fighter_transform_data.rot, buf);
			buf = SDLNetUtils::deserialize(fighter_transform_data.velx, buf);
			buf = SDLNetUtils::deserialize(fighter_transform_data.vely, buf);
			return buf;
		}

		inline Uint8* serializeBullet(Uint8* buf) {
			buf = SDLNetUtils::serialize(nId, buf);
			float temp = shoot_data.pos.getX();
			buf = SDLNetUtils::serialize(temp, buf);
			temp = shoot_data.pos.getY();
			buf = SDLNetUtils::serialize(temp, buf);
			temp = shoot_data.vel.getX();
			buf = SDLNetUtils::serialize(temp, buf);
			temp = shoot_data.vel.getY();
			buf = SDLNetUtils::serialize(temp, buf);
			buf = SDLNetUtils::serialize(shoot_data.width, buf);
			buf = SDLNetUtils::serialize(shoot_data.height, buf);
			return buf;
		}	

		inline Uint8* deserializeBullet(Uint8* buf) {
			buf = SDLNetUtils::deserialize(nId, buf);
			float temp;
			buf = SDLNetUtils::deserialize(temp, buf);
			shoot_data.pos.setX(temp);
			buf = SDLNetUtils::deserialize(temp, buf);
			shoot_data.pos.setY(temp);
			buf = SDLNetUtils::deserialize(temp, buf);
			shoot_data.vel.setX(temp);
			buf = SDLNetUtils::deserialize(temp, buf);
			shoot_data.vel.setY(temp);
			buf = SDLNetUtils::deserialize(shoot_data.width, buf);
			buf = SDLNetUtils::deserialize(shoot_data.height, buf);
			return buf;
		}

		inline Uint8* deserializeGameover(Uint8* buf) {
			buf = SDLNetUtils::deserialize(nId, buf);
			buf = SDLNetUtils::deserialize(gameover_data.winner, buf);
			return buf;
		}

		inline Uint8* serializeGameover(Uint8* buf) {
			buf = SDLNetUtils::serialize(nId, buf);
			buf = SDLNetUtils::serialize(gameover_data.winner, buf);
			return buf;
		}

		inline Uint8* serializeName(Uint8* buffer) {
			buffer = SDLNetUtils::serialize(nId, buffer);
			buffer = SDLNetUtils::serialize(name_data.size, buffer);
			for (int i = 0; i < name_data.size; ++i) {
				buffer = SDLNetUtils::serialize(name_data.name[i], buffer);
			}
			return buffer;
		}

		inline Uint8* deserializeName(Uint8* buffer) {
			buffer = SDLNetUtils::deserialize(nId, buffer);
			buffer = SDLNetUtils::deserialize(name_data.size, buffer);
			for (int i = 0; i < name_data.size; ++i) {
				buffer = SDLNetUtils::deserialize(name_data.name[i], buffer);
			}
			return buffer;
		}

		inline Uint8* serializePlayerBulletCollision(Uint8* buffer) {
			buffer = SDLNetUtils::serialize(nId, buffer);

			return buffer;
		}

		inline Uint8* deserializePlayerBulletCollision(Uint8* buffer) {
			buffer = SDLNetUtils::deserialize(nId, buffer);

			return buffer;
		}

		inline Uint8* serializeHP(Uint8* buffer) {
			buffer = SDLNetUtils::serialize(nId, buffer);

			return buffer;
		}

		inline Uint8* deserializeHP(Uint8* buffer) {
			buffer = SDLNetUtils::deserialize(nId, buffer);

			return buffer;
		}
	};

	using stateId_type = uint8_t;
	enum stateId : stateId_type {
		_s_MAIN_MENU,
		_s_PLAY,
		_s_NAME,
		_s_MULTIPLAYER,
		_s_CONNECT,
		_s_PAUSE,
		_s_GAMEOVER,
		_s_WIN
	};

	using gameState_type = uint8_t;
	enum gameStateId : gameState_type {
		_gs_CONNECTING,
		_gs_PLAYING,
		_gs_GAMEOVER
	};

}