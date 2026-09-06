#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExAcb;
class CriAtomEx3dSource;
class CriAtomEx3dListener;

class CriAtomExPlayer : public RefCounted
{
    GDCLASS(CriAtomExPlayer, RefCounted)

public:
    static void _bind_methods();

public:
	CriAtomExPlayer();

    ~CriAtomExPlayer();

	static Ref<CriAtomExPlayer> create_player(Dictionary config);

	static void stop_all_players();

	static void stop_all_players_without_release_time();

	void destroy();

	void set_cue_name(Ref<CriAtomExAcb> acb, String cue_name);

	void set_cue_id(Ref<CriAtomExAcb> acb, int cue_id);

	void set_cue_index(Ref<CriAtomExAcb> acb, int cue_index);

	uint32_t start();

	uint32_t prepare();

	void stop();

	void stop_without_release_time();

	void set_start_time(int64_t start_time);

	void pause(bool pause);
	void resume(int mode);

	bool is_paused();

	int32_t get_status();

	int64_t get_time();
	int get_num_playbacks() const;
	int64_t get_last_playback_id() const;
	void set_start_time_micro(int64_t start_time_micro);
	void set_sync_playback_id(int64_t playback_id);
	void set_playback_ratio(float ratio);
	void limit_loop_count(int count);
	void set_format(int format);
	void set_num_channels(int num_channels);
	void set_sampling_rate(int sampling_rate);
	void set_sound_renderer_type(int sound_renderer_type);
	void set_group_number(int group_number);
	void set_voice_control_method(int method);
	void set_voice_pool_identifier(int64_t identifier);
	void set_additional_voice_pool_identifier(int64_t identifier);
	void set_hcamx_mixer_id(int mixer_id);
	void set_asr_rack_id(int rack_id);

	void set_volume(float volume);

	void set_pitch(float pitch);
	void set_max_pitch(float pitch);
	void set_pan_type(int pan_type);

	void set_pan3d_angle(float pan3d_angle);

	void set_pan3d_elevation(float pan3d_elevation);

	void set_pan3d_interior_distance(float pan3d_interior_distance);

	void set_pan3d_volume(float pan3d_volume);

	void set_wideness(float wideness);

	void set_spread(float spread);

	void set_aisac_control_by_name(String control_name, float value);

	float get_aisac_control_by_name(String control_name);

	void set_aisac_control_by_id(int control_id, float value);

	float get_aisac_control_by_id(int control_id);

	void clear_aisac_controls();
	void attach_aisac(String global_aisac_name);
	void detach_aisac(String global_aisac_name);
	void detach_all_aisacs();
	int get_num_attached_aisacs() const;
	void set_bus_send_level(String bus_name, float level);
	float get_bus_send_level(String bus_name) const;
	void set_bus_send_level_offset(String bus_name, float level_offset);
	float get_bus_send_level_offset(String bus_name) const;
	void reset_bus_sends();
	void set_bandpass_filter_parameters(float low, float high);
	void set_biquad_filter_parameters(int type, float frequency, float gain, float q_value);
	void set_voice_priority(int priority);
	void set_category_by_id(int64_t category_id);
	void set_category_by_name(String category_name);
	void unset_category();
	int get_num_categories() const;
	Dictionary get_category_info(int index) const;
	void set_silent_mode(int silent_mode);
	void set_cue_priority(int cue_priority);
	void set_pre_delay_time(float time_ms);
	void set_random_seed(int64_t seed);

	void reset_parameters();

	void update(uint32_t playback_id);

	void update_all();

	void set_first_block_index(int32_t block_index);

	void set_selector_label(String selector, String label);
	void unset_selector_label(String selector);

	void clear_selector_labels();

	void attach_fader();

	void detach_fader();

	void set_fadein_time(int32_t fade_time);

	int32_t get_fadein_time();

	void set_fadeout_time(int32_t fade_time);

	int32_t get_fadeout_time();
	void set_fadein_start_offset(int32_t offset_ms);
	int32_t get_fadein_start_offset() const;
	void set_fadeout_end_delay(int32_t delay_ms);
	int32_t get_fadeout_end_delay() const;

	bool is_fading();

	void reset_fader_parameters();

	void set_3d_source(Ref<CriAtomEx3dSource> source);

	void set_3d_listener(Ref<CriAtomEx3dListener> listener);

	CriAtomExPlayerHn get_handle() const { return handle; }

private:
	CriAtomExPlayerHn handle = nullptr;
};

}
