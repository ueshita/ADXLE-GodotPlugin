#include "GDLibrary.h"
#include "CriAtomEx3dSource.h"

namespace godot {

void CriAtomEx3dSource::_register_methods()
{
	register_method("_init", &CriAtomEx3dSource::_init);
	register_method("create", &CriAtomEx3dSource::create);
	register_method("destroy", &CriAtomEx3dSource::destroy);
	register_method("update", &CriAtomEx3dSource::update);
	register_method("reset_parameters", &CriAtomEx3dSource::reset_parameters);
	register_method("set_position", &CriAtomEx3dSource::set_position);
	register_method("set_velocity", &CriAtomEx3dSource::set_velocity);
	register_method("set_orientation", &CriAtomEx3dSource::set_orientation);
	register_method("set_cone_parameter", &CriAtomEx3dSource::set_cone_parameter);
	register_method("set_minmax_attenuation_distance", &CriAtomEx3dSource::set_minmax_attenuation_distance);
}

CriAtomEx3dSource::CriAtomEx3dSource()
{
}

CriAtomEx3dSource::~CriAtomEx3dSource()
{
	destroy();
}

void CriAtomEx3dSource::_init()
{
}

void CriAtomEx3dSource::create(Dictionary config)
{
	destroy();

	CriAtomEx3dSourceConfig source_config;
	criAtomEx3dSource_SetDefaultConfig(&source_config);
	handle = criAtomEx3dSource_Create(&source_config, nullptr, 0);
}

void CriAtomEx3dSource::destroy()
{
	if (!criAtomEx_IsInitialized()) {
		return;
	}

	if (handle) {
		criAtomEx3dSource_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomEx3dSource::update()
{
	criAtomEx3dSource_Update(handle);
}

void CriAtomEx3dSource::reset_parameters()
{
	criAtomEx3dSource_ResetParameters(handle);
}

void CriAtomEx3dSource::set_position(Vector3 position)
{
	criAtomEx3dSource_SetPosition(handle, (CriAtomExVector*)&position);
}

void CriAtomEx3dSource::set_velocity(Vector3 velocity)
{
	criAtomEx3dSource_SetVelocity(handle, (CriAtomExVector*)&velocity);
}

void CriAtomEx3dSource::set_orientation(Vector3 front, Vector3 top)
{
	criAtomEx3dSource_SetOrientation(handle, (CriAtomExVector*)&front, (CriAtomExVector*)&top);
}

void CriAtomEx3dSource::set_cone_parameter(float inside_angle, float outside_angle, float outside_volume)
{
	criAtomEx3dSource_SetConeParameter(handle, inside_angle, outside_angle, outside_volume);
}

void CriAtomEx3dSource::set_minmax_attenuation_distance(float min_attenuation_distance, float max_attenuation_distance)
{
	criAtomEx3dSource_SetMinMaxAttenuationDistance(handle, min_attenuation_distance, max_attenuation_distance);
}

}
