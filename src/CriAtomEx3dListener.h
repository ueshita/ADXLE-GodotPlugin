#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"
#include "CriAtomExAcb.h"

namespace godot {

class CriAtomEx3dListener : public RefCounted
{
    GDCLASS(CriAtomEx3dListener, RefCounted)
public:
    static void _bind_methods();

	CriAtomEx3dListener();

    ~CriAtomEx3dListener();

	static Ref<CriAtomEx3dListener> createListener(Dictionary config);

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
