#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>
#include "CriAtomExAcb.h"

namespace godot {

class CriAtomEx3dSource : public Reference
{
    GODOT_CLASS(CriAtomEx3dSource, Reference)
public:
    static void _register_methods();

	CriAtomEx3dSource();

    ~CriAtomEx3dSource();

	void _init();

	void create(Dictionary config);

	void destroy();

	void update();

	void reset_parameters();

	void set_position(Vector3 position);

	void set_velocity(Vector3 velocity);

	void set_orientation(Vector3 front, Vector3 top);

	void set_cone_parameter(float inside_angle, float outside_angle, float outside_volume);

	void set_minmax_attenuation_distance(float min_attenuation_distance, float max_attenuation_distance);

	CriAtomEx3dSourceHn get_handle() const { return this->handle; }

private:
	CriAtomEx3dSourceHn handle = nullptr;
};

}
