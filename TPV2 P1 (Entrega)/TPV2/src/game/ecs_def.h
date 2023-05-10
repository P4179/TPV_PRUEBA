#pragma once

#include <cstdint>

// se encuentra en un namespace
namespace ecs {
	// uint8_t indica que se trata de un entero representado en 8 bits
	using cmpId_type = uint8_t;

	// los �tems del enum son enteros de 8 bits
	// se utiliza para seleccionar el componente adecuado en el array de componentes de una entidad
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,	// componente que controla la posici�n
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

		// do not remove this
		_LAST_CMP_ID	// indica el n�mero m�ximo de �tems que tiene el enum
	};

	// constante que se define en tiempo de compilaci�n
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

	// grupos
	using grpId_type = uint8_t;
	enum grpId : grpId_type {
		// grupo por defecto por si la entidad no pertenece a un grupo definido por el usuario
		_grp_GENERAL,
		_grp_ASTEROIDS,
		_grp_BULLETS,

		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	// handlers
	// se utilizan para acceder a una unidad espec�fica del mismo manager 
	using hdlrId_type = uint8_t;
	enum hdlrId : hdlrId_type {
		FIGHTER,
		_LAST_HDLR_ID
	};
	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;
}