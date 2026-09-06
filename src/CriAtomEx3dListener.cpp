#include "GDLibrary.h"
#include "CriAtomEx3dListener.h"

namespace godot {

void CriAtomEx3dListener::_bind_methods()
{
	ClassDB::bind_static_method("CriAtomEx3dListener", D_METHOD("create", "config"), &CriAtomEx3dListener::create_listener);
	GDBIND_METHOD(CriAtomEx3dListener, destroy);
	GDBIND_METHOD(CriAtomEx3dListener, update);
	GDBIND_METHOD(CriAtomEx3dListener, reset_parameters);
	GDBIND_METHOD(CriAtomEx3dListener, set_position);
	GDBIND_METHOD(CriAtomEx3dListener, get_position);
	GDBIND_METHOD(CriAtomEx3dListener, set_velocity);
	GDBIND_METHOD(CriAtomEx3dListener, set_orientation);
	GDBIND_METHOD(CriAtomEx3dListener, set_focus_point, "focus_point");
	GDBIND_METHOD(CriAtomEx3dListener, set_distance_focus_level, "distance_focus_level");
	GDBIND_METHOD(CriAtomEx3dListener, set_direction_focus_level, "direction_focus_level");
	GDBIND_METHOD(CriAtomEx3dListener, get_focus_point);
	GDBIND_METHOD(CriAtomEx3dListener, get_distance_focus_level);
	GDBIND_METHOD(CriAtomEx3dListener, get_direction_focus_level);
	GDBIND_METHOD(CriAtomEx3dListener, set_doppler_multiplier, "doppler_multiplier");
}

CriAtomEx3dListener::CriAtomEx3dListener()
{
}

CriAtomEx3dListener::~CriAtomEx3dListener()
{
	destroy();
}

Ref<CriAtomEx3dListener> CriAtomEx3dListener::create_listener(Dictionary config)
{
	CriAtomEx3dListenerConfig listener_config;
	criAtomEx3dListener_SetDefaultConfig(&listener_config);
	auto handle = criAtomEx3dListener_Create(&listener_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}

	Ref<CriAtomEx3dListener> listener = memnew(CriAtomEx3dListener);
	listener->handle = handle;
	return listener;
}

void CriAtomEx3dListener::destroy()
{
	if (handle) {
		criAtomEx3dListener_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomEx3dListener::update()
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_Update(handle);
}

void CriAtomEx3dListener::reset_parameters()
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_ResetParameters(handle);
}

void CriAtomEx3dListener::set_position(Vector3 position)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetPosition(handle, (CriAtomExVector*)&position);
}

Vector3 CriAtomEx3dListener::get_position() const
{
	if (!handle) {
		return Vector3();
	}
	CriAtomExVector position = criAtomEx3dListener_GetPosition(handle);
	return Vector3(position.x, position.y, position.z);
}

void CriAtomEx3dListener::set_velocity(Vector3 velocity)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetVelocity(handle, (CriAtomExVector*)&velocity);
}

void CriAtomEx3dListener::set_orientation(Vector3 front, Vector3 top)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetOrientation(handle, (CriAtomExVector*)&front, (CriAtomExVector*)&top);
}

void CriAtomEx3dListener::set_focus_point(Vector3 focus_point)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetFocusPoint(handle, (CriAtomExVector*)&focus_point);
}

void CriAtomEx3dListener::set_distance_focus_level(float distance_focus_level)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetDistanceFocusLevel(handle, distance_focus_level);
}

void CriAtomEx3dListener::set_direction_focus_level(float direction_focus_level)
{
	if (!handle) {
		return;
	}
	criAtomEx3dListener_SetDirectionFocusLevel(handle, direction_focus_level);
}

Vector3 CriAtomEx3dListener::get_focus_point() const
{
	if (!handle) {
		return Vector3();
	}
	CriAtomExVector focus_point;
	criAtomEx3dListener_GetFocusPoint(handle, &focus_point);
	return Vector3(focus_point.x, focus_point.y, focus_point.z);
}

float CriAtomEx3dListener::get_distance_focus_level() const
{
	if (!handle) {
		return 0.0f;
	}
	return criAtomEx3dListener_GetDistanceFocusLevel(handle);
}

float CriAtomEx3dListener::get_direction_focus_level() const
{
	if (!handle) {
		return 0.0f;
	}
	return criAtomEx3dListener_GetDirectionFocusLevel(handle);
}

void CriAtomEx3dListener::set_doppler_multiplier(float doppler_multiplier)
{
	if (handle) {
		criAtomEx3dListener_SetDopplerMultiplier(handle, doppler_multiplier);
	}
}


}
