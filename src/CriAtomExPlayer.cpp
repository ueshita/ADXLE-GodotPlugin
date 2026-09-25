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
	GDBIND_METHOD(CriAtomExPlayer, resume, "mode");
	GDBIND_METHOD(CriAtomExPlayer, is_paused);
	GDBIND_METHOD(CriAtomExPlayer, get_status);
	GDBIND_METHOD(CriAtomExPlayer, get_time);
	GDBIND_METHOD(CriAtomExPlayer, get_num_playbacks);
	GDBIND_METHOD(CriAtomExPlayer, get_last_playback_id);
	GDBIND_METHOD(CriAtomExPlayer, set_start_time_micro, "start_time_micro");
	GDBIND_METHOD(CriAtomExPlayer, set_sync_playback_id, "playback_id");
	GDBIND_METHOD(CriAtomExPlayer, set_playback_ratio, "ratio");
	GDBIND_METHOD(CriAtomExPlayer, limit_loop_count, "count");
	GDBIND_METHOD(CriAtomExPlayer, set_format, "format");
	GDBIND_METHOD(CriAtomExPlayer, set_num_channels, "num_channels");
	GDBIND_METHOD(CriAtomExPlayer, set_sampling_rate, "sampling_rate");
	GDBIND_METHOD(CriAtomExPlayer, set_sound_renderer_type, "sound_renderer_type");
	GDBIND_METHOD(CriAtomExPlayer, set_group_number, "group_number");
	GDBIND_METHOD(CriAtomExPlayer, set_voice_control_method, "method");
	GDBIND_METHOD(CriAtomExPlayer, set_voice_pool_identifier, "identifier");
	GDBIND_METHOD(CriAtomExPlayer, set_additional_voice_pool_identifier, "identifier");
	GDBIND_METHOD(CriAtomExPlayer, set_hcamx_mixer_id, "mixer_id");
	GDBIND_METHOD(CriAtomExPlayer, set_asr_rack_id, "rack_id");
	GDBIND_METHOD(CriAtomExPlayer, set_volume, "volume");
	GDBIND_METHOD(CriAtomExPlayer, set_pitch, "pitch");
	GDBIND_METHOD(CriAtomExPlayer, set_max_pitch, "pitch");
	GDBIND_METHOD(CriAtomExPlayer, set_pan_type, "pan_type");
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
	GDBIND_METHOD(CriAtomExPlayer, attach_aisac, "global_aisac_name");
	GDBIND_METHOD(CriAtomExPlayer, detach_aisac, "global_aisac_name");
	GDBIND_METHOD(CriAtomExPlayer, detach_all_aisacs);
	GDBIND_METHOD(CriAtomExPlayer, get_num_attached_aisacs);
	GDBIND_METHOD(CriAtomExPlayer, set_bus_send_level, "bus_name", "level");
	GDBIND_METHOD(CriAtomExPlayer, get_bus_send_level, "bus_name");
	GDBIND_METHOD(CriAtomExPlayer, set_bus_send_level_offset, "bus_name", "level_offset");
	GDBIND_METHOD(CriAtomExPlayer, get_bus_send_level_offset, "bus_name");
	GDBIND_METHOD(CriAtomExPlayer, reset_bus_sends);
	GDBIND_METHOD(CriAtomExPlayer, set_bandpass_filter_parameters, "low", "high");
	GDBIND_METHOD(CriAtomExPlayer, set_biquad_filter_parameters, "type", "frequency", "gain", "q_value");
	GDBIND_METHOD(CriAtomExPlayer, set_voice_priority, "priority");
	GDBIND_METHOD(CriAtomExPlayer, set_category_by_id, "category_id");
	GDBIND_METHOD(CriAtomExPlayer, set_category_by_name, "category_name");
	GDBIND_METHOD(CriAtomExPlayer, unset_category);
	GDBIND_METHOD(CriAtomExPlayer, get_num_categories);
	GDBIND_METHOD(CriAtomExPlayer, get_category_info, "index");
	GDBIND_METHOD(CriAtomExPlayer, set_silent_mode, "silent_mode");
	GDBIND_METHOD(CriAtomExPlayer, set_cue_priority, "cue_priority");
	GDBIND_METHOD(CriAtomExPlayer, set_pre_delay_time, "time_ms");
	GDBIND_METHOD(CriAtomExPlayer, set_random_seed, "seed");
	GDBIND_METHOD(CriAtomExPlayer, reset_parameters);
	GDBIND_METHOD(CriAtomExPlayer, update);
	GDBIND_METHOD(CriAtomExPlayer, update_all);
	GDBIND_METHOD(CriAtomExPlayer, set_first_block_index, "block_index");
	GDBIND_METHOD(CriAtomExPlayer, set_selector_label, "selector", "label");
	GDBIND_METHOD(CriAtomExPlayer, unset_selector_label, "selector");
	GDBIND_METHOD(CriAtomExPlayer, clear_selector_labels);
	GDBIND_METHOD(CriAtomExPlayer, attach_fader);
	GDBIND_METHOD(CriAtomExPlayer, detach_fader);
	GDBIND_METHOD(CriAtomExPlayer, set_fadein_time, "fade_time");
	GDBIND_METHOD(CriAtomExPlayer, get_fadein_time);
	GDBIND_METHOD(CriAtomExPlayer, set_fadeout_time, "fade_time");
	GDBIND_METHOD(CriAtomExPlayer, get_fadeout_time);
	GDBIND_METHOD(CriAtomExPlayer, set_fadein_start_offset, "offset_ms");
	GDBIND_METHOD(CriAtomExPlayer, get_fadein_start_offset);
	GDBIND_METHOD(CriAtomExPlayer, set_fadeout_end_delay, "delay_ms");
	GDBIND_METHOD(CriAtomExPlayer, get_fadeout_end_delay);
	GDBIND_METHOD(CriAtomExPlayer, is_fading);
	GDBIND_METHOD(CriAtomExPlayer, reset_fader_parameters);
	GDBIND_METHOD(CriAtomExPlayer, set_3d_source, "source");
	GDBIND_METHOD(CriAtomExPlayer, set_3d_listener, "listener");

	GDBIND_SIGNAL("sequence_event", GDBIND_SIGNAL_ARG(info, Variant::DICTIONARY));
	GDBIND_SIGNAL("beatsync", GDBIND_SIGNAL_ARG(info, Variant::DICTIONARY));
	GDBIND_SIGNAL("finished", GDBIND_SIGNAL_ARG(playback_id, Variant::INT));
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

	if (config.has("voice_allocation_method")) {
		player_config.voice_allocation_method = (CriAtomExVoiceAllocationMethod)(int)config["voice_allocation_method"];
	}
	if (config.has("max_path_strings")) {
		player_config.max_path_strings = (int)config["max_path_strings"];
	}
	if (config.has("max_path")) {
		player_config.max_path = (int)config["max_path"];
	}
	if (config.has("max_aisacs")) {
		player_config.max_aisacs = (int)config["max_aisacs"];
	}
	if (config.has("updates_time")) {
		player_config.updates_time = (bool)config["updates_time"];
	}
	if (config.has("enable_audio_synced_timer")) {
		player_config.enable_audio_synced_timer = (bool)config["enable_audio_synced_timer"];
	}

	auto handle = criAtomExPlayer_Create(&player_config, nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	
	Ref<CriAtomExPlayer> player = memnew(CriAtomExPlayer);
	player->handle = handle;
	criAtomExPlayer_SetPlaybackEventCallback(handle, &CriAtomExPlayer::_playback_event_callback, player.ptr());
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
	if (handle) {
		// Wait for any server callback before detaching its pointer to this object.
		criAtomExPlayer_Destroy(handle);
		handle = nullptr;
	}
}

void CriAtomExPlayer::set_cue_name(Ref<CriAtomExAcb> acb, String cue_name)
{
	if (!handle) {
		return;
	}
	CriAtomExAcbHn acb_handle = nullptr;
	if (acb.is_valid()) {
		acb_handle = acb->get_handle();
	}
	CharString name = cue_name.utf8();
	criAtomExPlayer_SetCueName(handle, acb_handle, name.get_data());
}

void CriAtomExPlayer::set_cue_id(Ref<CriAtomExAcb> acb, int cue_id)
{
	if (!handle) {
		return;
	}
	CriAtomExAcbHn acb_handle = nullptr;
	if (acb.is_valid()) {
		acb_handle = acb->get_handle();
	}
	criAtomExPlayer_SetCueId(handle, acb_handle, (CriAtomExCueId)cue_id);
}

void CriAtomExPlayer::set_cue_index(Ref<CriAtomExAcb> acb, int cue_index)
{
	if (!handle) {
		return;
	}
	CriAtomExAcbHn acb_handle = nullptr;
	if (acb.is_valid()) {
		acb_handle = acb->get_handle();
	}
	criAtomExPlayer_SetCueIndex(handle, acb_handle, (CriAtomExCueId)cue_index);
}

uint32_t CriAtomExPlayer::start()
{
	if (!handle) {
		return CRIATOMEX_INVALID_PLAYBACK_ID;
	}
	return criAtomExPlayer_Start(handle);
}

uint32_t CriAtomExPlayer::prepare()
{
	if (!handle) {
		return CRIATOMEX_INVALID_PLAYBACK_ID;
	}
	return criAtomExPlayer_Prepare(handle);
}

void CRIAPI CriAtomExPlayer::_playback_event_callback(void* obj, CriAtomExPlaybackEvent event, const CriAtomExPlaybackInfoDetail* info)
{
	if (event == CRIATOMEX_PLAYBACK_EVENT_REMOVE) {
		// Receivers that need the main thread must connect with CONNECT_DEFERRED.
		auto player = static_cast<CriAtomExPlayer*>(obj);
		player->emit_signal("finished", (int64_t)info->id);
	}
}

void CriAtomExPlayer::stop()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_Stop(handle);
}

void CriAtomExPlayer::stop_without_release_time()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_StopWithoutReleaseTime(handle);
}

void CriAtomExPlayer::set_start_time(int64_t start_time)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetStartTime(handle, start_time);
}

void CriAtomExPlayer::pause(bool pause)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_Pause(handle, pause);
}

void CriAtomExPlayer::resume(int mode)
{
	if (handle) {
		criAtomExPlayer_Resume(handle, (CriAtomExResumeMode)mode);
	}
}

bool CriAtomExPlayer::is_paused()
{
	if (!handle) {
		return false;
	}
	return criAtomExPlayer_IsPaused(handle);
}

int32_t CriAtomExPlayer::get_status()
{
	if (!handle) {
		return (int32_t)CRIATOMEXPLAYER_STATUS_ERROR;
	}
	return (int32_t)criAtomExPlayer_GetStatus(handle);
}

int64_t CriAtomExPlayer::get_time()
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetTime(handle);
}

int CriAtomExPlayer::get_num_playbacks() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetNumPlaybacks(handle);
}

int64_t CriAtomExPlayer::get_last_playback_id() const
{
	if (!handle) {
		return (int64_t)CRIATOMEX_INVALID_PLAYBACK_ID;
	}
	return (int64_t)criAtomExPlayer_GetLastPlaybackId(handle);
}

void CriAtomExPlayer::set_start_time_micro(int64_t start_time_micro)
{
	if (handle) {
		criAtomExPlayer_SetStartTimeMicro(handle, start_time_micro);
	}
}

void CriAtomExPlayer::set_sync_playback_id(int64_t playback_id)
{
	if (handle) {
		criAtomExPlayer_SetSyncPlaybackId(handle, (CriAtomExPlaybackId)playback_id);
	}
}

void CriAtomExPlayer::set_playback_ratio(float ratio)
{
	if (handle) {
		criAtomExPlayer_SetPlaybackRatio(handle, ratio);
	}
}

void CriAtomExPlayer::limit_loop_count(int count)
{
	if (handle) {
		criAtomExPlayer_LimitLoopCount(handle, count);
	}
}

void CriAtomExPlayer::set_format(int format)
{
	if (handle) {
		criAtomExPlayer_SetFormat(handle, (CriAtomExFormat)format);
	}
}

void CriAtomExPlayer::set_num_channels(int num_channels)
{
	if (handle) {
		criAtomExPlayer_SetNumChannels(handle, num_channels);
	}
}

void CriAtomExPlayer::set_sampling_rate(int sampling_rate)
{
	if (handle) {
		criAtomExPlayer_SetSamplingRate(handle, sampling_rate);
	}
}

void CriAtomExPlayer::set_sound_renderer_type(int sound_renderer_type)
{
	if (handle) {
		criAtomExPlayer_SetSoundRendererType(handle, (CriAtomSoundRendererType)sound_renderer_type);
	}
}

void CriAtomExPlayer::set_group_number(int group_number)
{
	if (handle) {
		criAtomExPlayer_SetGroupNumber(handle, group_number);
	}
}

void CriAtomExPlayer::set_voice_control_method(int method)
{
	if (handle) {
		criAtomExPlayer_SetVoiceControlMethod(handle, (CriAtomExVoiceControlMethod)method);
	}
}

void CriAtomExPlayer::set_voice_pool_identifier(int64_t identifier)
{
	if (handle) {
		criAtomExPlayer_SetVoicePoolIdentifier(handle, (CriAtomExVoicePoolIdentifier)identifier);
	}
}

void CriAtomExPlayer::set_additional_voice_pool_identifier(int64_t identifier)
{
	if (handle) {
		criAtomExPlayer_SetAdditionalVoicePoolIdentifier(handle, (CriAtomExVoicePoolIdentifier)identifier);
	}
}

void CriAtomExPlayer::set_hcamx_mixer_id(int mixer_id)
{
	if (handle) {
		criAtomExPlayer_SetHcaMxMixerId(handle, mixer_id);
	}
}

void CriAtomExPlayer::set_asr_rack_id(int rack_id)
{
	if (handle) {
		criAtomExPlayer_SetAsrRackId(handle, rack_id);
	}
}

void CriAtomExPlayer::set_volume(float volume)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetVolume(handle, volume);
}

void CriAtomExPlayer::set_pitch(float pitch)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetPitch(handle, pitch);
}

void CriAtomExPlayer::set_max_pitch(float pitch)
{
	if (handle) {
		criAtomExPlayer_SetMaxPitch(handle, pitch);
	}
}

void CriAtomExPlayer::set_pan_type(int pan_type)
{
	if (handle) {
		criAtomExPlayer_SetPanType(handle, (CriAtomExPanType)pan_type);
	}
}

void CriAtomExPlayer::set_pan3d_angle(float pan3d_angle)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetPan3dAngle(handle, pan3d_angle);
}

void CriAtomExPlayer::set_pan3d_elevation(float pan3d_elevation)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetPan3dElevation(handle, pan3d_elevation);
}

void CriAtomExPlayer::set_pan3d_interior_distance(float pan3d_interior_distance)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetPan3dInteriorDistance(handle, pan3d_interior_distance);
}

void CriAtomExPlayer::set_pan3d_volume(float pan3d_volume)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetPan3dVolume(handle, pan3d_volume);
}

void CriAtomExPlayer::set_wideness(float wideness)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetWideness(handle, wideness);
}

void CriAtomExPlayer::set_spread(float spread)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetSpread(handle, spread);
}

void CriAtomExPlayer::set_aisac_control_by_name(String control_name, float value)
{
	if (!handle) {
		return;
	}
	CharString name = control_name.utf8();
	criAtomExPlayer_SetAisacControlByName(handle, name.get_data(), value);
}

float CriAtomExPlayer::get_aisac_control_by_name(String control_name)
{
	if (!handle) {
		return 0.0f;
	}
	CharString name = control_name.utf8();
	return criAtomExPlayer_GetAisacControlByName(handle, name.get_data());
}

void CriAtomExPlayer::set_aisac_control_by_id(int control_id, float value)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetAisacControlById(handle, (CriAtomExAisacControlId)control_id, value);
}

float CriAtomExPlayer::get_aisac_control_by_id(int control_id)
{
	if (!handle) {
		return 0.0f;
	}
	return criAtomExPlayer_GetAisacControlById(handle, (CriAtomExAisacControlId)control_id);
}

void CriAtomExPlayer::clear_aisac_controls()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_ClearAisacControls(handle);
}

void CriAtomExPlayer::attach_aisac(String global_aisac_name)
{
	if (!handle) {
		return;
	}
	CharString name = global_aisac_name.utf8();
	criAtomExPlayer_AttachAisac(handle, name.get_data());
}

void CriAtomExPlayer::detach_aisac(String global_aisac_name)
{
	if (!handle) {
		return;
	}
	CharString name = global_aisac_name.utf8();
	criAtomExPlayer_DetachAisac(handle, name.get_data());
}

void CriAtomExPlayer::detach_all_aisacs()
{
	if (handle) {
		criAtomExPlayer_DetachAisacAll(handle);
	}
}

int CriAtomExPlayer::get_num_attached_aisacs() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetNumAttachedAisacs(handle);
}

void CriAtomExPlayer::set_bus_send_level(String bus_name, float level)
{
	if (!handle) {
		return;
	}
	CharString name = bus_name.utf8();
	criAtomExPlayer_SetBusSendLevelByName(handle, name.get_data(), level);
}

float CriAtomExPlayer::get_bus_send_level(String bus_name) const
{
	if (!handle) {
		return 0.0f;
	}
	CharString name = bus_name.utf8();
	CriFloat32 level;
	if (criAtomExPlayer_GetBusSendLevelByName(handle, name.get_data(), &level) == CRI_FALSE) {
		return 0.0f;
	}
	return level;
}

void CriAtomExPlayer::set_bus_send_level_offset(String bus_name, float level_offset)
{
	if (!handle) {
		return;
	}
	CharString name = bus_name.utf8();
	criAtomExPlayer_SetBusSendLevelOffsetByName(handle, name.get_data(), level_offset);
}

float CriAtomExPlayer::get_bus_send_level_offset(String bus_name) const
{
	if (!handle) {
		return 0.0f;
	}
	CharString name = bus_name.utf8();
	CriFloat32 offset;
	if (criAtomExPlayer_GetBusSendLevelOffsetByName(handle, name.get_data(), &offset) == CRI_FALSE) {
		return 0.0f;
	}
	return offset;
}

void CriAtomExPlayer::reset_bus_sends()
{
	if (handle) {
		criAtomExPlayer_ResetBusSends(handle);
	}
}

void CriAtomExPlayer::set_bandpass_filter_parameters(float low, float high)
{
	if (handle) {
		criAtomExPlayer_SetBandpassFilterParameters(handle, low, high);
	}
}

void CriAtomExPlayer::set_biquad_filter_parameters(int type, float frequency, float gain, float q_value)
{
	if (handle) {
		criAtomExPlayer_SetBiquadFilterParameters(handle, (CriAtomExBiquadFilterType)type, frequency, gain, q_value);
	}
}

void CriAtomExPlayer::set_voice_priority(int priority)
{
	if (handle) {
		criAtomExPlayer_SetVoicePriority(handle, priority);
	}
}

void CriAtomExPlayer::set_category_by_id(int64_t category_id)
{
	if (handle) {
		criAtomExPlayer_SetCategoryById(handle, (CriAtomExCategoryId)category_id);
	}
}

void CriAtomExPlayer::set_category_by_name(String category_name)
{
	if (!handle) {
		return;
	}
	CharString name = category_name.utf8();
	criAtomExPlayer_SetCategoryByName(handle, name.get_data());
}

void CriAtomExPlayer::unset_category()
{
	if (handle) {
		criAtomExPlayer_UnsetCategory(handle);
	}
}

int CriAtomExPlayer::get_num_categories() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetNumCategories(handle);
}

Dictionary CriAtomExPlayer::get_category_info(int index) const
{
	if (!handle || index < 0 || index > UINT16_MAX) {
		return Dictionary();
	}
	CriAtomExCategoryInfo info;
	if (criAtomExPlayer_GetCategoryInfo(handle, (CriUint16)index, &info) == CRI_FALSE) {
		return Dictionary();
	}
	Dictionary result;
	result["group_no"] = (int64_t)info.group_no;
	result["id"] = (int64_t)info.id;
	result["name"] = info.name ? String(info.name) : String();
	result["num_cue_limits"] = (int64_t)info.num_cue_limits;
	result["volume"] = info.volume;
	return result;
}

void CriAtomExPlayer::set_silent_mode(int silent_mode)
{
	if (handle) {
		criAtomExPlayer_SetSilentMode(handle, (CriAtomExSilentMode)silent_mode);
	}
}

void CriAtomExPlayer::set_cue_priority(int cue_priority)
{
	if (handle) {
		criAtomExPlayer_SetCuePriority(handle, cue_priority);
	}
}

void CriAtomExPlayer::set_pre_delay_time(float time_ms)
{
	if (handle) {
		criAtomExPlayer_SetPreDelayTime(handle, time_ms);
	}
}

void CriAtomExPlayer::set_random_seed(int64_t seed)
{
	if (handle) {
		criAtomExPlayer_SetRandomSeed(handle, (CriUint32)seed);
	}
}

void CriAtomExPlayer::reset_parameters()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_ResetParameters(handle);
}

void CriAtomExPlayer::update(uint32_t playback_id)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_Update(handle, playback_id);
}

void CriAtomExPlayer::update_all()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_UpdateAll(handle);
}

void CriAtomExPlayer::set_first_block_index(int32_t block_index)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetFirstBlockIndex(handle, block_index);
}

void CriAtomExPlayer::set_selector_label(String selector, String label)
{
	if (!handle) {
		return;
	}
	CharString selector_name = selector.utf8();
	CharString label_name = label.utf8();
	criAtomExPlayer_SetSelectorLabel(handle, selector_name.get_data(), label_name.get_data());
}

void CriAtomExPlayer::unset_selector_label(String selector)
{
	if (!handle) {
		return;
	}
	CharString name = selector.utf8();
	criAtomExPlayer_UnsetSelectorLabel(handle, name.get_data());
}

void CriAtomExPlayer::clear_selector_labels()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_ClearSelectorLabels(handle);
}

void CriAtomExPlayer::attach_fader()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_AttachFader(handle, nullptr, nullptr, 0);
}

void CriAtomExPlayer::detach_fader()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_DetachFader(handle);
}

void CriAtomExPlayer::set_fadein_time(int32_t fade_time)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetFadeInTime(handle, fade_time);
}

int32_t CriAtomExPlayer::get_fadein_time()
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetFadeInTime(handle);
}

void CriAtomExPlayer::set_fadeout_time(int32_t fade_time)
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_SetFadeOutTime(handle, fade_time);
}

int32_t CriAtomExPlayer::get_fadeout_time()
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetFadeOutTime(handle);
}

void CriAtomExPlayer::set_fadein_start_offset(int32_t offset_ms)
{
	if (handle) {
		criAtomExPlayer_SetFadeInStartOffset(handle, offset_ms);
	}
}

int32_t CriAtomExPlayer::get_fadein_start_offset() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetFadeInStartOffset(handle);
}

void CriAtomExPlayer::set_fadeout_end_delay(int32_t delay_ms)
{
	if (handle) {
		criAtomExPlayer_SetFadeOutEndDelay(handle, delay_ms);
	}
}

int32_t CriAtomExPlayer::get_fadeout_end_delay() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExPlayer_GetFadeOutEndDelay(handle);
}

bool CriAtomExPlayer::is_fading()
{
	if (!handle) {
		return false;
	}
	return criAtomExPlayer_IsFading(handle);
}

void CriAtomExPlayer::reset_fader_parameters()
{
	if (!handle) {
		return;
	}
	criAtomExPlayer_ResetFaderParameters(handle);
}

void CriAtomExPlayer::set_3d_source(Ref<CriAtomEx3dSource> source)
{
	if (!handle) {
		return;
	}
	CriAtomEx3dSourceHn source_handle = nullptr;
	if (source.is_valid()) {
		source_handle = source->get_handle();
	}
	criAtomExPlayer_Set3dSourceHn(handle, source_handle);
}

void CriAtomExPlayer::set_3d_listener(Ref<CriAtomEx3dListener> listener)
{
	if (!handle) {
		return;
	}
	CriAtomEx3dListenerHn listener_handle = nullptr;
	if (listener.is_valid()) {
		listener_handle = listener->get_handle();
	}
	criAtomExPlayer_Set3dListenerHn(handle, listener_handle);
}

}
