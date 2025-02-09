#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriAtomExPlayer.h"
#include "CriAtomExAcb.h"
#include "CriAtomEx3dSource.h"
#include "CriAtomEx3dListener.h"

namespace godot {

void CriAtomExPlayer::_bind_methods()
{
	ClassDB::bind_static_method("CriAtomExPlayer", D_METHOD("create", "config"), &CriAtomExPlayer::create_player);
	GDBIND_STATIC_METHOD(CriAtomExPlayer, stop_all_players);
	GDBIND_STATIC_METHOD(CriAtomExPlayer, stop_all_players_without_release_time);
	GDBIND_METHOD(CriAtomExPlayer, destroy);
	GDBIND_METHOD(CriAtomExPlayer, set_cue_name, "acb", "cue_name");
	GDBIND_METHOD(CriAtomExPlayer, set_cue_id, "acb", "cue_id");
	GDBIND_METHOD(CriAtomExPlayer, set_cue_index, "acb", "cue_index");
	GDBIND_METHOD(CriAtomExPlayer, start);
	GDBIND_METHOD(CriAtomExPlayer, prepare);
	GDBIND_METHOD(CriAtomExPlayer, stop);
	GDBIND_METHOD(CriAtomExPlayer, stop_without_release_time);
	GDBIND_METHOD(CriAtomExPlayer, set_start_time, "start_time");
	GDBIND_METHOD(CriAtomExPlayer, pause, "paused");
	GDBIND_METHOD(CriAtomExPlayer, is_paused);
	GDBIND_METHOD(CriAtomExPlayer, get_status);
	GDBIND_METHOD(CriAtomExPlayer, get_time);
	GDBIND_METHOD(CriAtomExPlayer, set_volume, "volume");
	GDBIND_METHOD(CriAtomExPlayer, set_pitch, "pitch");
	GDBIND_METHOD(CriAtomExPlayer, set_pan3d_angle, "pan3d_angle");
	GDBIND_METHOD(CriAtomExPlayer, set_pan3d_elevation, "pan3d_elevation");
	GDBIND_METHOD(CriAtomExPlayer, set_pan3d_interior_distance, "pan3d_distance");
	GDBIND_METHOD(CriAtomExPlayer, set_pan3d_volume, "pan3d_volume");
	GDBIND_METHOD(CriAtomExPlayer, set_wideness, "wideness");
	GDBIND_METHOD(CriAtomExPlayer, set_spread, "spread");
	GDBIND_METHOD(CriAtomExPlayer, set_aisac_control_by_name, "aisac_name", "aisac_value");
	GDBIND_METHOD(CriAtomExPlayer, get_aisac_control_by_name, "aisac_name");
	GDBIND_METHOD(CriAtomExPlayer, set_aisac_control_by_id, "aisac_id", "aisac_value");
	GDBIND_METHOD(CriAtomExPlayer, get_aisac_control_by_id, "aisac_id");
	GDBIND_METHOD(CriAtomExPlayer, clear_aisac_controls);
	GDBIND_METHOD(CriAtomExPlayer, reset_parameters);
	GDBIND_METHOD(CriAtomExPlayer, update);
	GDBIND_METHOD(CriAtomExPlayer, update_all);
	GDBIND_METHOD(CriAtomExPlayer, set_first_block_index, "block_index");
	GDBIND_METHOD(CriAtomExPlayer, set_selector_label, "selector", "label");
	GDBIND_METHOD(CriAtomExPlayer, clear_selector_labels);
	GDBIND_METHOD(CriAtomExPlayer, attach_fader);
	GDBIND_METHOD(CriAtomExPlayer, detach_fader);
	GDBIND_METHOD(CriAtomExPlayer, set_fadein_time, "fade_time");
	GDBIND_METHOD(CriAtomExPlayer, set_fadeout_time, "fade_time");
	GDBIND_METHOD(CriAtomExPlayer, is_fading);
	GDBIND_METHOD(CriAtomExPlayer, reset_fader_parameters);
	GDBIND_METHOD(CriAtomExPlayer, set_3d_source, "source");
	GDBIND_METHOD(CriAtomExPlayer, set_3d_listener, "listener");

	GDBIND_SIGNAL(CriAtomExPlayer, "sequence_event");
	GDBIND_SIGNAL(CriAtomExPlayer, "beatsync");
}

CriAtomExPlayer::CriAtomExPlayer()
{
	if (auto context = CriAtomExContext::get_singleton()) {
		context->add_player(this);
	}
}

CriAtomExPlayer::~CriAtomExPlayer()
{
	destroy();
	if (auto context = CriAtomExContext::get_singleton()) {
		context->remove_player(this);
	}
}

Ref<CriAtomExPlayer> CriAtomExPlayer::create_player(Dictionary config)
{
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

	auto handle = criAtomExPlayer_Create(&player_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	
	Ref<CriAtomExPlayer> player = memnew(CriAtomExPlayer);
	player->handle = handle;
	return player;
}

void CriAtomExPlayer::stop_all_players()
{
	criAtomExPlayer_StopAllPlayers();
}

void CriAtomExPlayer::stop_all_players_without_release_time()
{
	criAtomExPlayer_StopAllPlayersWithoutReleaseTime();
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

void CriAtomExPlayer::set_cue_name(Ref<CriAtomExAcb> acb, String cue_name)
{
	criAtomExPlayer_SetCueName(handle, acb.is_valid() ? acb->get_handle() : nullptr, cue_name.utf8().get_data());
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

uint32_t CriAtomExPlayer::prepare()
{
	return criAtomExPlayer_Prepare(handle);
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

void CriAtomExPlayer::set_pan3d_elevation(float pan3d_elevation)
{
	criAtomExPlayer_SetPan3dElevation(handle, pan3d_elevation);
}

void CriAtomExPlayer::set_pan3d_interior_distance(float pan3d_interior_distance)
{
	criAtomExPlayer_SetPan3dInteriorDistance(handle, pan3d_interior_distance);
}

void CriAtomExPlayer::set_pan3d_volume(float pan3d_volume)
{
	criAtomExPlayer_SetPan3dVolume(handle, pan3d_volume);
}

void CriAtomExPlayer::set_wideness(float wideness)
{
	criAtomExPlayer_SetWideness(handle, wideness);
}

void CriAtomExPlayer::set_spread(float spread)
{
	criAtomExPlayer_SetSpread(handle, spread);
}

void CriAtomExPlayer::set_aisac_control_by_name(String control_name, float value)
{
	criAtomExPlayer_SetAisacControlByName(handle, control_name.utf8().get_data(), value);
}

float CriAtomExPlayer::get_aisac_control_by_name(String control_name)
{
	return criAtomExPlayer_GetAisacControlByName(handle, control_name.utf8().get_data());
}

void CriAtomExPlayer::set_aisac_control_by_id(int control_id, float value)
{
	criAtomExPlayer_SetAisacControlById(handle, (CriAtomExAisacControlId)control_id, value);
}

float CriAtomExPlayer::get_aisac_control_by_id(int control_id)
{
	return criAtomExPlayer_GetAisacControlById(handle, (CriAtomExAisacControlId)control_id);
}

void CriAtomExPlayer::clear_aisac_controls()
{
	criAtomExPlayer_ClearAisacControls(handle);
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
	criAtomExPlayer_SetSelectorLabel(handle, selector.utf8().get_data(), label.utf8().get_data());
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
