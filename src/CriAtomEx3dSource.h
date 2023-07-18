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

	static Ref<CriAtomEx3dSource> createSource(Dictionary config);

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
