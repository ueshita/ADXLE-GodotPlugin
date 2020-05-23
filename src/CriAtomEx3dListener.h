#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>
#include "CriAtomExAcb.h"

namespace godot {

class CriAtomEx3dListener : public Reference
{
    GODOT_CLASS(CriAtomEx3dListener, Reference)
public:
    static void _register_methods();

	CriAtomEx3dListener();

    ~CriAtomEx3dListener();

	void _init();

	void create(Dictionary config);

	void destroy();

	void update();

	void reset_parameters();

	void set_position(Vector3 position);

	void set_velocity(Vector3 velocity);

	void set_orientation(Vector3 front, Vector3 top);

	CriAtomEx3dListenerHn get_handle() const { return this->handle; }

private:
	CriAtomEx3dListenerHn handle = nullptr;
};

}
