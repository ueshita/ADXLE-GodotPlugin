#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>

namespace godot {

class CriAtomExAcb : public Reference
{
    GODOT_CLASS(CriAtomExAcb, Reference)
public:
    static void _register_methods();

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
