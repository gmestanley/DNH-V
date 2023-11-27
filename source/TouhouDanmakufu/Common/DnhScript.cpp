#include "DnhScript.hpp"
#include "DnhCommon.hpp"
#include "DnhGcLibImpl.hpp"

/**********************************************************
//DnhScript
**********************************************************/
const static function dnhFunction[] = {
	{ "KEY_INVALID", constant<ESimpleInput::KEY_INVALID>::func, 0 },

	{ "VK_LEFT", constant<ESimpleInput::KEY_LEFT>::func, 0 },
	{ "VK_RIGHT", constant<ESimpleInput::KEY_RIGHT>::func, 0 },
	{ "VK_UP", constant<ESimpleInput::KEY_UP>::func, 0 },
	{ "VK_DOWN", constant<ESimpleInput::KEY_DOWN>::func, 0 },
	{ "VK_SHOT", constant<ESimpleInput::KEY_SHOT>::func, 0 },
	{ "VK_BOMB", constant<ESimpleInput::KEY_BOMB>::func, 0 },
	{ "VK_SPELL", constant<ESimpleInput::KEY_BOMB>::func, 0 },
	{ "VK_SLOWMOVE", constant<ESimpleInput::KEY_SLOWMOVE>::func, 0 },
	{ "VK_USER1", constant<ESimpleInput::KEY_USER1>::func, 0 },
	{ "VK_USER2", constant<ESimpleInput::KEY_USER2>::func, 0 },
	{ "VK_OK", constant<ESimpleInput::KEY_OK>::func, 0 },
	{ "VK_CANCEL", constant<ESimpleInput::KEY_CANCEL>::func, 0 },
	{ "VK_PAUSE", constant<ESimpleInput::KEY_PAUSE>::func, 0 },

	{ "VK_USER_ID_STAGE", constant<ESimpleInput::VK_USER_ID_STAGE>::func, 0 },
	{ "VK_USER_ID_PLAYER", constant<ESimpleInput::VK_USER_ID_PLAYER>::func, 0 },
};
DnhScript::DnhScript()
{
	_AddFunction(dnhFunction, sizeof(dnhFunction) / sizeof(function));
}
