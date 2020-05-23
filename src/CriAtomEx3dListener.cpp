#include "GDLibrary.h"
#include "CriAtomEx3dListener.h"

namespace godot {

void CriAtomEx3dListener::_register_methods()
{
	register_method("_init", &CriAtomEx3dListener::_init);
	register_method("create", &CriAtomEx3dListener::create);
	register_method("destroy", &CriAtomEx3dListener::destroy);
	register_method("update", &CriAtomEx3dListener::update);
	register_method("reset_parameters", &CriAtomEx3dListener::reset_parameters);
	register_method("set_position", &CriAtomEx3dListener::set_position);
	register_method("set_velocity", &CriAtomEx3dListener::set_velocity);
	register_method("set_orientation", &CriAtomEx3dListener::set_orientation);
}

CriAtomEx3dListener::CriAtomEx3dListener()
{
}

CriAtomEx3dListener::~CriAtomEx3dListener()
{
	destroy();
}

void CriAtomEx3dListener::_init()
{
}

void CriAtomEx3dListener::create(Dictionary config)
{
	destroy();

	CriAtomEx3dListenerConfig listener_config;
	criAtomEx3dListener_SetDefaultConfig(&listener_config);
	handle = criAtomEx3dListener_Create(&listener_config, nullptr, 0);
}

void CriAtomEx3dListener::destroy()
{
	if (!criAtomEx_IsInitialized()) {
		return;
	}

	if (handle) {
		criAtomEx3dListener_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomEx3dListener::update()
{
	criAtomEx3dListener_Update(handle);
}

void CriAtomEx3dListener::reset_parameters()
{
	criAtomEx3dListener_ResetParameters(handle);
}

void CriAtomEx3dListener::set_position(Vector3 position)
{
	criAtomEx3dListener_SetPosition(handle, (CriAtomExVector*)&position);
}

void CriAtomEx3dListener::set_velocity(Vector3 velocity)
{
	criAtomEx3dListener_SetVelocity(handle, (CriAtomExVector*)&velocity);
}

void CriAtomEx3dListener::set_orientation(Vector3 front, Vector3 top)
{
	criAtomEx3dListener_SetOrientation(handle, (CriAtomExVector*)&front, (CriAtomExVector*)&top);
}

}
