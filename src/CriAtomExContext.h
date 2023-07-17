#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExContext : public RefCounted
{
    GDCLASS(CriAtomExContext, RefCounted)
public:
    static void _bind_methods();

	CriAtomExContext();

    ~CriAtomExContext();

	void _init();

	void initialize(String acf_file, Dictionary config);

	void finalize();

	void attach_dspbus_setting(String setting_name);

	void detach_dspbus_setting();

	void apply_dspbus_snapshot(String snapshot_name, float duration);

	String get_applied_dspbus_snapshot_name();

private:
	bool is_initialized = false;
	CriAtomExDbasId dbas_id = CRIATOMDBAS_ILLEGAL_ID;
};

}
