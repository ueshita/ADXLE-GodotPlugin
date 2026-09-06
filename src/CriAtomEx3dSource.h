#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"
#include "CriAtomExAcb.h"

namespace godot {

class CriAtomEx3dSource : public RefCounted
{
    GDCLASS(CriAtomEx3dSource, RefCounted)
public:
    static void _bind_methods();

	CriAtomEx3dSource();

    ~CriAtomEx3dSource();

	static Ref<CriAtomEx3dSource> create_source(Dictionary config);

	void destroy();

	void update();

	void reset_parameters();

	void set_position(Vector3 position);
	Vector3 get_position() const;

	void set_velocity(Vector3 velocity);

	void set_orientation(Vector3 front, Vector3 top);

	void set_cone_parameter(float inside_angle, float outside_angle, float outside_volume);

	void set_minmax_attenuation_distance(float min_attenuation_distance, float max_attenuation_distance);
	void set_interior_pan_field(float source_radius, float interior_distance);
	void set_doppler_factor(float doppler_factor);
	void set_volume(float volume);
	void set_max_angle_aisac_delta(float max_delta);
	void set_distance_aisac_control_id(int64_t aisac_control_id);
	void set_listener_based_azimuth_angle_aisac_control_id(int64_t aisac_control_id);
	void set_listener_based_elevation_angle_aisac_control_id(int64_t aisac_control_id);
	void set_source_based_azimuth_angle_aisac_control_id(int64_t aisac_control_id);
	void set_source_based_elevation_angle_aisac_control_id(int64_t aisac_control_id);
	void set_attenuation_distance_setting(bool enabled);
	bool get_attenuation_distance_setting() const;

	CriAtomEx3dSourceHn get_handle() const { return handle; }

private:
	CriAtomEx3dSourceHn handle = nullptr;
};

}
