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
	GDBIND_METHOD(CriAtomExVoicePool, set_additional_identifier, "identifier");
	GDBIND_METHOD(CriAtomExVoicePool, get_identifier);
	GDBIND_METHOD(CriAtomExVoicePool, detach_dsp);
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
	
	if (config.has("identifier")) {
		voicepool_config.identifier = (int)config["identifier"];
	}
	if (config.has("num_voices")) {
		voicepool_config.num_voices = (int)config["num_voices"];
	}
	if (config.has("max_channels")) {
		voicepool_config.player_config.max_channels = (int)config["max_channels"];
	}
	if (config.has("max_sampling_rate")) {
		voicepool_config.player_config.max_sampling_rate = (int)config["max_sampling_rate"];
	}
	if (config.has("streaming_flag")) {
		voicepool_config.player_config.streaming_flag = (bool)config["streaming_flag"];
	}
	if (config.has("decode_latency")) {
		voicepool_config.player_config.decode_latency = (int)config["decode_latency"];
	}
	if (config.has("sound_renderer_type")) {
		voicepool_config.player_config.sound_renderer_type = (CriAtomSoundRendererType)(int)config["sound_renderer_type"];
	}

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

	if (config.has("identifier")) {
		voicepool_config.identifier = (int)config["identifier"];
	}
	if (config.has("num_voices")) {
		voicepool_config.num_voices = (int)config["num_voices"];
	}
	if (config.has("max_channels")) {
		voicepool_config.player_config.max_channels = (int)config["max_channels"];
	}
	if (config.has("max_sampling_rate")) {
		voicepool_config.player_config.max_sampling_rate = (int)config["max_sampling_rate"];
	}
	if (config.has("streaming_flag")) {
		voicepool_config.player_config.streaming_flag = (bool)config["streaming_flag"];
	}

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
	if (handle) {
		criAtomExVoicePool_Free(handle);
		handle = nullptr;
	}
}

int CriAtomExVoicePool::get_num_used_voices()
{
	if (!handle) {
		return -1;
	}
	CriSint32 used_voices;
	criAtomExVoicePool_GetNumUsedVoices(handle, &used_voices, nullptr);
	return used_voices;
}

int CriAtomExVoicePool::get_num_limit_voices()
{
	if (!handle) {
		return -1;
	}
	CriSint32 limit_voices;
	criAtomExVoicePool_GetNumUsedVoices(handle, nullptr, &limit_voices);
	return limit_voices;
}

void CriAtomExVoicePool::set_additional_identifier(int64_t identifier)
{
	if (handle) {
		criAtomExVoicePool_SetAdditionalIdentifier(handle, (CriAtomExVoicePoolIdentifier)identifier);
	}
}

int64_t CriAtomExVoicePool::get_identifier() const
{
	if (!handle) {
		return -1;
	}
	CriUint64 identifier;
	if (criAtomExVoicePool_GetIdentifier(handle, &identifier) == CRI_FALSE) {
		return -1;
	}
	return (int64_t)identifier;
}

void CriAtomExVoicePool::detach_dsp()
{
	if (handle) {
		criAtomExVoicePool_DetachDsp(handle);
	}
}

}
