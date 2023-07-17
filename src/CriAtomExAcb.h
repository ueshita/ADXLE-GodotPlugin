#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExAcb : public RefCounted
{
    GDCLASS(CriAtomExAcb, RefCounted)
public:
    static void _bind_methods();

	CriAtomExAcb();
    ~CriAtomExAcb();

	void _init();

	bool load_acb_file(String acb_path, String awb_path);
	
	void release();

	Variant get_all_cue_infos();

	CriAtomExAcbHn get_handle() const { return this->handle; }

private:
	CriAtomExAcbHn handle = nullptr;
};

}
