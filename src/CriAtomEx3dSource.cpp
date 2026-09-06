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
	GDBIND_METHOD(CriAtomEx3dSource, get_position);
	GDBIND_METHOD(CriAtomEx3dSource, set_velocity);
	GDBIND_METHOD(CriAtomEx3dSource, set_orientation);
	GDBIND_METHOD(CriAtomEx3dSource, set_cone_parameter);
	GDBIND_METHOD(CriAtomEx3dSource, set_minmax_attenuation_distance);
	GDBIND_METHOD(CriAtomEx3dSource, set_interior_pan_field, "source_radius", "interior_distance");
	GDBIND_METHOD(CriAtomEx3dSource, set_doppler_factor, "doppler_factor");
	GDBIND_METHOD(CriAtomEx3dSource, set_volume, "volume");
	GDBIND_METHOD(CriAtomEx3dSource, set_max_angle_aisac_delta, "max_delta");
	GDBIND_METHOD(CriAtomEx3dSource, set_distance_aisac_control_id, "aisac_control_id");
	GDBIND_METHOD(CriAtomEx3dSource, set_listener_based_azimuth_angle_aisac_control_id, "aisac_control_id");
	GDBIND_METHOD(CriAtomEx3dSource, set_listener_based_elevation_angle_aisac_control_id, "aisac_control_id");
	GDBIND_METHOD(CriAtomEx3dSource, set_source_based_azimuth_angle_aisac_control_id, "aisac_control_id");
	GDBIND_METHOD(CriAtomEx3dSource, set_source_based_elevation_angle_aisac_control_id, "aisac_control_id");
	GDBIND_METHOD(CriAtomEx3dSource, set_attenuation_distance_setting, "enabled");
	GDBIND_METHOD(CriAtomEx3dSource, get_attenuation_distance_setting);
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
	if (handle) {
		criAtomEx3dSource_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomEx3dSource::update()
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_Update(handle);
}

void CriAtomEx3dSource::reset_parameters()
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_ResetParameters(handle);
}

void CriAtomEx3dSource::set_position(Vector3 position)
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_SetPosition(handle, (CriAtomExVector*)&position);
}

Vector3 CriAtomEx3dSource::get_position() const
{
	if (!handle) {
		return Vector3();
	}
	CriAtomExVector position = criAtomEx3dSource_GetPosition(handle);
	return Vector3(position.x, position.y, position.z);
}

void CriAtomEx3dSource::set_velocity(Vector3 velocity)
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_SetVelocity(handle, (CriAtomExVector*)&velocity);
}

void CriAtomEx3dSource::set_orientation(Vector3 front, Vector3 top)
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_SetOrientation(handle, (CriAtomExVector*)&front, (CriAtomExVector*)&top);
}

void CriAtomEx3dSource::set_cone_parameter(float inside_angle, float outside_angle, float outside_volume)
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_SetConeParameter(handle, inside_angle, outside_angle, outside_volume);
}

void CriAtomEx3dSource::set_minmax_attenuation_distance(float min_attenuation_distance, float max_attenuation_distance)
{
	if (!handle) {
		return;
	}
	criAtomEx3dSource_SetMinMaxAttenuationDistance(handle, min_attenuation_distance, max_attenuation_distance);
}

void CriAtomEx3dSource::set_interior_pan_field(float source_radius, float interior_distance)
{
	if (handle) {
		criAtomEx3dSource_SetInteriorPanField(handle, source_radius, interior_distance);
	}
}

void CriAtomEx3dSource::set_doppler_factor(float doppler_factor)
{
	if (handle) {
		criAtomEx3dSource_SetDopplerFactor(handle, doppler_factor);
	}
}

void CriAtomEx3dSource::set_volume(float volume)
{
	if (handle) {
		criAtomEx3dSource_SetVolume(handle, volume);
	}
}

void CriAtomEx3dSource::set_max_angle_aisac_delta(float max_delta)
{
	if (handle) {
		criAtomEx3dSource_SetMaxAngleAisacDelta(handle, max_delta);
	}
}

void CriAtomEx3dSource::set_distance_aisac_control_id(int64_t aisac_control_id)
{
	if (handle) {
		criAtomEx3dSource_SetDistanceAisacControlId(handle, (CriAtomExAisacControlId)aisac_control_id);
	}
}

void CriAtomEx3dSource::set_listener_based_azimuth_angle_aisac_control_id(int64_t aisac_control_id)
{
	if (handle) {
		criAtomEx3dSource_SetListenerBasedAzimuthAngleAisacControlId(handle, (CriAtomExAisacControlId)aisac_control_id);
	}
}

void CriAtomEx3dSource::set_listener_based_elevation_angle_aisac_control_id(int64_t aisac_control_id)
{
	if (handle) {
		criAtomEx3dSource_SetListenerBasedElevationAngleAisacControlId(handle, (CriAtomExAisacControlId)aisac_control_id);
	}
}

void CriAtomEx3dSource::set_source_based_azimuth_angle_aisac_control_id(int64_t aisac_control_id)
{
	if (handle) {
		criAtomEx3dSource_SetSourceBasedAzimuthAngleAisacControlId(handle, (CriAtomExAisacControlId)aisac_control_id);
	}
}

void CriAtomEx3dSource::set_source_based_elevation_angle_aisac_control_id(int64_t aisac_control_id)
{
	if (handle) {
		criAtomEx3dSource_SetSourceBasedElevationAngleAisacControlId(handle, (CriAtomExAisacControlId)aisac_control_id);
	}
}

void CriAtomEx3dSource::set_attenuation_distance_setting(bool enabled)
{
	if (handle) {
		criAtomEx3dSource_SetAttenuationDistanceSetting(handle, enabled ? CRI_TRUE : CRI_FALSE);
	}
}

bool CriAtomEx3dSource::get_attenuation_distance_setting() const
{
	if (!handle) {
		return false;
	}
	return criAtomEx3dSource_GetAttenuationDistanceSetting(handle) == CRI_TRUE;
}


}
