#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExVoicePool : public RefCounted
{
    GDCLASS(CriAtomExVoicePool, RefCounted)

public:
    static void _bind_methods();

public:
	CriAtomExVoicePool();
    ~CriAtomExVoicePool();

	static Ref<CriAtomExVoicePool> allocate_standard_voice_pool(Dictionary config);

	static Ref<CriAtomExVoicePool> allocate_hcamx_voice_pool(Dictionary config);
	
	void free_voice_pool();

	int get_num_used_voices();
	
	int get_num_limit_voices();

	CriAtomExVoicePoolHn get_handle() const { return this->handle; }

private:
	CriAtomExVoicePoolHn handle = nullptr;
};

}
