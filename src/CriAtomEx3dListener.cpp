#include "GDLibrary.h"
#include "CriAtomEx3dListener.h"

namespace godot {

void CriAtomEx3dListener::_bind_methods()
{
	ClassDB::bind_static_method("CriAtomEx3dListener", D_METHOD("create", "config"), &CriAtomEx3dListener::createListener);
	GDBIND_METHOD(CriAtomEx3dListener, destroy);
	GDBIND_METHOD(CriAtomEx3dListener, update);
	GDBIND_METHOD(CriAtomEx3dListener, reset_parameters);
	GDBIND_METHOD(CriAtomEx3dListener, set_position);
	GDBIND_METHOD(CriAtomEx3dListener, set_velocity);
	GDBIND_METHOD(CriAtomEx3dListener, set_orientation);
}

CriAtomEx3dListener::CriAtomEx3dListener()
{
}

CriAtomEx3dListener::~CriAtomEx3dListener()
{
	destroy();
}

Ref<CriAtomEx3dListener> CriAtomEx3dListener::createListener(Dictionary config)
{
	CriAtomEx3dListenerConfig listener_config;
	criAtomEx3dListener_SetDefaultConfig(&listener_config);
	auto handle = criAtomEx3dListener_Create(&listener_config, nullptr, 0);

	Ref<CriAtomEx3dListener> listener = memnew(CriAtomEx3dListener);
	listener->handle = handle;
	return listener;
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
