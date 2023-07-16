#include "GDLibrary.h"
#include "CriAtomExPlayer.h"
#include "CriAtomExAcb.h"
#include "CriAtomEx3dSource.h"
#include "CriAtomEx3dListener.h"

namespace godot {

void CriAtomExPlayer::_register_methods()
{
	register_method("_init", &CriAtomExPlayer::_init);
	register_method("create", &CriAtomExPlayer::create);
	register_method("destroy", &CriAtomExPlayer::destroy);
	register_method("set_cue_name", &CriAtomExPlayer::set_cue_name);
	register_method("set_cue_id", &CriAtomExPlayer::set_cue_id);
	register_method("set_cue_index", &CriAtomExPlayer::set_cue_index);
	register_method("start", &CriAtomExPlayer::start);
	register_method("stop", &CriAtomExPlayer::stop);
	register_method("stop_without_release_time", &CriAtomExPlayer::stop_without_release_time);
	register_method("set_start_time", &CriAtomExPlayer::set_start_time);
	register_method("pause", &CriAtomExPlayer::pause);
	register_method("is_paused", &CriAtomExPlayer::is_paused);
	register_method("get_status", &CriAtomExPlayer::get_status);
	register_method("get_time", &CriAtomExPlayer::get_time);
	register_method("set_volume", &CriAtomExPlayer::set_volume);
	register_method("set_pitch", &CriAtomExPlayer::set_pitch);
	register_method("set_pan3d_angle", &CriAtomExPlayer::set_pan3d_angle);
	register_method("set_pan3d_interior_distance", &CriAtomExPlayer::set_pan3d_interior_distance);
	register_method("set_aisac_control_by_name", &CriAtomExPlayer::set_aisac_control_by_name);
	register_method("set_aisac_control_by_id", &CriAtomExPlayer::set_aisac_control_by_id);
	register_method("reset_parameters", &CriAtomExPlayer::reset_parameters);
	register_method("update", &CriAtomExPlayer::update);
	register_method("update_all", &CriAtomExPlayer::update_all);
	register_method("set_first_block_index", &CriAtomExPlayer::set_first_block_index);
	register_method("set_selector_label", &CriAtomExPlayer::set_selector_label);
	register_method("clear_selector_labels", &CriAtomExPlayer::clear_selector_labels);
	register_method("attach_fader", &CriAtomExPlayer::attach_fader);
	register_method("detach_fader", &CriAtomExPlayer::detach_fader);
	register_method("set_fadein_time", &CriAtomExPlayer::set_fadein_time);
	register_method("set_fadeout_time", &CriAtomExPlayer::set_fadeout_time);
	register_method("is_fading", &CriAtomExPlayer::is_fading);
	register_method("reset_fader_parameters", &CriAtomExPlayer::reset_fader_parameters);
	register_method("set_3d_source", &CriAtomExPlayer::set_3d_source);
	register_method("set_3d_listener", &CriAtomExPlayer::set_3d_listener);
}

CriAtomExPlayer::CriAtomExPlayer()
{
}

CriAtomExPlayer::~CriAtomExPlayer()
{
	destroy();
}

void CriAtomExPlayer::_init()
{
}

void CriAtomExPlayer::create(Dictionary config)
{
	destroy();

	CriAtomExPlayerConfig player_config;
	criAtomExPlayer_SetDefaultConfig(&player_config);

	if (config.has("voice_allocation_method"))
		player_config.voice_allocation_method = (CriAtomExVoiceAllocationMethod)(int)config["voice_allocation_method"];
	if (config.has("max_path_strings"))
		player_config.max_path_strings = (int)config["max_path_strings"];
	if (config.has("max_path"))
		player_config.max_path = (int)config["max_path"];
	if (config.has("max_aisacs"))
		player_config.max_aisacs = (int)config["voice_allocation_method"];
	if (config.has("updates_time"))
		player_config.updates_time = (bool)config["updates_time"];
	if (config.has("enable_audio_synced_timer"))
		player_config.enable_audio_synced_timer = (bool)config["enable_audio_synced_timer"];

	handle = criAtomExPlayer_Create(&player_config, nullptr, 0);
}

void CriAtomExPlayer::destroy()
{
	if (!criAtomEx_IsInitialized()) {
		return;
	}

	if (handle) {
		criAtomExPlayer_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomExPlayer::set_cue_name(Ref<CriAtomExAcb> acb, String cue)
{
	criAtomExPlayer_SetCueName(handle, acb.is_valid() ? acb->get_handle() : nullptr, FixedString<256>(String(cue)).str);
}

void CriAtomExPlayer::set_cue_id(Ref<CriAtomExAcb> acb, int cue_id)
{
	criAtomExPlayer_SetCueId(handle, acb.is_valid() ? acb->get_handle() : nullptr, (CriAtomExCueId)cue_id);
}

void CriAtomExPlayer::set_cue_index(Ref<CriAtomExAcb> acb, int cue_index)
{
	criAtomExPlayer_SetCueIndex(handle, acb.is_valid() ? acb->get_handle() : nullptr, (CriAtomExCueId)cue_index);
}

uint32_t CriAtomExPlayer::start()
{
	return criAtomExPlayer_Start(handle);
}

void CriAtomExPlayer::stop()
{
	criAtomExPlayer_Stop(handle);
}

void CriAtomExPlayer::stop_without_release_time()
{
	criAtomExPlayer_StopWithoutReleaseTime(handle);
}

void CriAtomExPlayer::set_start_time(int64_t start_time)
{
	criAtomExPlayer_SetStartTime(handle, start_time);
}

void CriAtomExPlayer::pause(bool pause)
{
	criAtomExPlayer_Pause(handle, pause);
}

bool CriAtomExPlayer::is_paused()
{
	return criAtomExPlayer_IsPaused(handle);
}

int32_t CriAtomExPlayer::get_status()
{
	return (int32_t)criAtomExPlayer_GetStatus(handle);
}

int64_t CriAtomExPlayer::get_time()
{
	return criAtomExPlayer_GetTime(handle);
}

void CriAtomExPlayer::set_volume(float volume)
{
	criAtomExPlayer_SetVolume(handle, volume);
}

void CriAtomExPlayer::set_pitch(float pitch)
{
	criAtomExPlayer_SetPitch(handle, pitch);
}

void CriAtomExPlayer::set_pan3d_angle(float pan3d_angle)
{
	criAtomExPlayer_SetPan3dAngle(handle, pan3d_angle);
}

void CriAtomExPlayer::set_pan3d_interior_distance(float pan3d_interior_distance)
{
	criAtomExPlayer_SetPan3dInteriorDistance(handle, pan3d_interior_distance);
}

void CriAtomExPlayer::set_aisac_control_by_name(String control_name, float value)
{
	criAtomExPlayer_SetAisacControlByName(handle, FixedString<256>(String(control_name)).str, value);
}

void CriAtomExPlayer::set_aisac_control_by_id(int control_id, float value)
{
	criAtomExPlayer_SetAisacControlById(handle, (CriAtomExAisacControlId)control_id, value);
}

void CriAtomExPlayer::reset_parameters()
{
	criAtomExPlayer_ResetParameters(handle);
}

void CriAtomExPlayer::update(uint32_t playback_id)
{
	criAtomExPlayer_Update(handle, playback_id);
}

void CriAtomExPlayer::update_all()
{
	criAtomExPlayer_UpdateAll(handle);
}

void CriAtomExPlayer::set_first_block_index(int32_t block_index)
{
	criAtomExPlayer_SetFirstBlockIndex(handle, block_index);
}

void CriAtomExPlayer::set_selector_label(String selector, String label)
{
	criAtomExPlayer_SetSelectorLabel(handle, FixedString<128>(selector).str, FixedString<128>(label).str);
}

void CriAtomExPlayer::clear_selector_labels()
{
	criAtomExPlayer_ClearSelectorLabels(handle);
}

void CriAtomExPlayer::attach_fader()
{
	criAtomExPlayer_AttachFader(handle, nullptr, nullptr, 0);
}

void CriAtomExPlayer::detach_fader()
{
	criAtomExPlayer_DetachFader(handle);
}

void CriAtomExPlayer::set_fadein_time(int32_t fade_time)
{
	criAtomExPlayer_SetFadeInTime(handle, fade_time);
}

int32_t CriAtomExPlayer::get_fadein_time()
{
	return criAtomExPlayer_GetFadeInTime(handle);
}

void CriAtomExPlayer::set_fadeout_time(int32_t fade_time)
{
	criAtomExPlayer_SetFadeOutTime(handle, fade_time);
}

int32_t CriAtomExPlayer::get_fadeout_time()
{
	return criAtomExPlayer_GetFadeOutTime(handle);
}

bool CriAtomExPlayer::is_fading()
{
	return criAtomExPlayer_IsFading(handle);
}

void CriAtomExPlayer::reset_fader_parameters()
{
	criAtomExPlayer_ResetFaderParameters(handle);
}

void CriAtomExPlayer::set_3d_source(Ref<CriAtomEx3dSource> source)
{
	criAtomExPlayer_Set3dSourceHn(handle, source.is_valid() ? source->get_handle() : nullptr);
}

void CriAtomExPlayer::set_3d_listener(Ref<CriAtomEx3dListener> listener)
{
	criAtomExPlayer_Set3dListenerHn(handle, listener.is_valid() ? listener->get_handle() : nullptr);
}

}
