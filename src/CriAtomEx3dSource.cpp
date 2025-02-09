#include "GDLibrary.h"
#include "CriAtomEx3dSource.h"

namespace godot {

void CriAtomEx3dSource::_bind_methods()
{
	ClassDB::bind_static_method("CriAtomEx3dSource", D_METHOD("create", "config"), &CriAtomEx3dSource::create_source);
	GDBIND_METHOD(CriAtomEx3dSource, destroy);
	GDBIND_METHOD(CriAtomEx3dSource, update);
	GDBIND_METHOD(CriAtomEx3dSource, reset_parameters);
	GDBIND_METHOD(CriAtomEx3dSource, set_position);
	GDBIND_METHOD(CriAtomEx3dSource, set_velocity);
	GDBIND_METHOD(CriAtomEx3dSource, set_orientation);
	GDBIND_METHOD(CriAtomEx3dSource, set_cone_parameter);
	GDBIND_METHOD(CriAtomEx3dSource, set_minmax_attenuation_distance);
}

CriAtomEx3dSource::CriAtomEx3dSource()
{
}

CriAtomEx3dSource::~CriAtomEx3dSource()
{
	destroy();
}

Ref<CriAtomEx3dSource> CriAtomEx3dSource::create_source(Dictionary config)
{
	CriAtomEx3dSourceConfig source_config;
	criAtomEx3dSource_SetDefaultConfig(&source_config);

	auto handle = criAtomEx3dSource_Create(&source_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	
	Ref<CriAtomEx3dSource> source = memnew(CriAtomEx3dSource);
	source->handle = handle;
	return source;
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
