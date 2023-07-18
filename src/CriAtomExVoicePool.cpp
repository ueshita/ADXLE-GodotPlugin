#include "GDLibrary.h"
#include "CriAtomExVoicePool.h"

namespace godot {

void CriAtomExVoicePool::_bind_methods()
{
	GDBIND_STATIC_METHOD(CriAtomExVoicePool, allocate_standard_voice_pool, "config");
	GDBIND_STATIC_METHOD(CriAtomExVoicePool, allocate_hcamx_voice_pool, "config");
	GDBIND_METHOD(CriAtomExVoicePool, free_voice_pool);
	GDBIND_METHOD(CriAtomExVoicePool, get_num_used_voices);
	GDBIND_METHOD(CriAtomExVoicePool, get_num_limit_voices);
}

CriAtomExVoicePool::CriAtomExVoicePool()
{
}

CriAtomExVoicePool::~CriAtomExVoicePool()
{
	free_voice_pool();
}

Ref<CriAtomExVoicePool> CriAtomExVoicePool::allocate_standard_voice_pool(Dictionary config)
{
	CriAtomExStandardVoicePoolConfig voicepool_config;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&voicepool_config);
	
	if (config.has("identifier"))
		voicepool_config.identifier = (int)config["identifier"];
	if (config.has("num_voices"))
		voicepool_config.num_voices = (int)config["num_voices"];
	if (config.has("max_channels"))
		voicepool_config.player_config.max_channels = (int)config["max_channels"];
	if (config.has("max_sampling_rate"))
		voicepool_config.player_config.max_sampling_rate = (int)config["max_sampling_rate"];
	if (config.has("streaming_flag"))
		voicepool_config.player_config.streaming_flag = (bool)config["streaming_flag"];
	if (config.has("decode_latency"))
		voicepool_config.player_config.decode_latency = (int)config["decode_latency"];
	if (config.has("sound_renderer_type"))
		voicepool_config.player_config.sound_renderer_type = (CriAtomSoundRendererType)(int)config["sound_renderer_type"];

	auto handle = criAtomExVoicePool_AllocateStandardVoicePool(&voicepool_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	Ref<CriAtomExVoicePool> voicepool = memnew(CriAtomExVoicePool);
	voicepool->handle = handle;
	return voicepool;
}

Ref<CriAtomExVoicePool> CriAtomExVoicePool::allocate_hcamx_voice_pool(Dictionary config)
{
	CriAtomExHcaMxVoicePoolConfig voicepool_config;
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&voicepool_config);

	if (config.has("identifier"))
		voicepool_config.identifier = (int)config["identifier"];
	if (config.has("num_voices"))
		voicepool_config.num_voices = (int)config["num_voices"];
	if (config.has("max_channels"))
		voicepool_config.player_config.max_channels = (int)config["max_channels"];
	if (config.has("max_sampling_rate"))
		voicepool_config.player_config.max_sampling_rate = (int)config["max_sampling_rate"];
	if (config.has("streaming_flag"))
		voicepool_config.player_config.streaming_flag = (bool)config["streaming_flag"];

	auto handle = criAtomExVoicePool_AllocateHcaMxVoicePool(&voicepool_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	Ref<CriAtomExVoicePool> voicepool = memnew(CriAtomExVoicePool);
	voicepool->handle = handle;
	return voicepool;
}

void CriAtomExVoicePool::free_voice_pool()
{
	if (criAtomEx_IsInitialized() && this->handle) {
		criAtomExVoicePool_Free(this->handle);
		this->handle = nullptr;
	}
}

int CriAtomExVoicePool::get_num_used_voices()
{
	CriSint32 used_voices;
	criAtomExVoicePool_GetNumUsedVoices(this->handle, &used_voices, nullptr);
	return used_voices;
}

int CriAtomExVoicePool::get_num_limit_voices()
{
	CriSint32 limit_voices;
	criAtomExVoicePool_GetNumUsedVoices(this->handle, nullptr, &limit_voices);
	return limit_voices;
}

}
