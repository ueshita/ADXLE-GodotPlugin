#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>

namespace godot {

class CriAtomExVoicePool : public Reference
{
    GODOT_CLASS(CriAtomExVoicePool, Reference)
public:
    static void _register_methods();

	CriAtomExVoicePool();
    ~CriAtomExVoicePool();

	void _init();

	void allocate_standard_voice_pool(Dictionary config);

	void allocate_hcamx_voice_pool(Dictionary config);
	
	void free_voice_pool();

	int get_num_used_voices();
	
	int get_num_limit_voices();

	CriAtomExVoicePoolHn get_handle() const { return this->handle; }

private:
	CriAtomExVoicePoolHn handle = nullptr;
};

}
