#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>

namespace godot {

class CriAtomExAcb;
class CriAtomEx3dSource;
class CriAtomEx3dListener;

class CriAtomExPlayer : public Reference
{
    GODOT_CLASS(CriAtomExPlayer, Reference)
public:
    static void _register_methods();

	CriAtomExPlayer();

    ~CriAtomExPlayer();

	void _init();

	void create(Dictionary config);

	void destroy();

	void set_cue_name(Ref<CriAtomExAcb> acb, String cue_name);

	void set_cue_id(Ref<CriAtomExAcb> acb, int cue_id);

	void set_cue_index(Ref<CriAtomExAcb> acb, int cue_index);

	uint32_t start();

	void stop();

	void stop_without_release_time();

	void set_start_time(int64_t start_time);

	void pause(bool pause);

	bool is_paused();

	int32_t get_status();

	int64_t get_time();

	void set_volume(float volume);

	void set_pitch(float pitch);

	void set_pan3d_angle(float pan3d_angle);

	void set_pan3d_interior_distance(float pan3d_interior_distance);

	void set_aisac_control_by_name(String control_name, float value);

	void set_aisac_control_by_id(int control_id, float value);

	void reset_parameters();

	void update(uint32_t playback_id);

	void update_all();

	void set_first_block_index(int32_t block_index);

	void set_selector_label(String selector, String label);

	void clear_selector_labels();

	void attach_fader();

	void detach_fader();

	void set_fadein_time(int32_t fade_time);

	int32_t get_fadein_time();

	void set_fadeout_time(int32_t fade_time);

	int32_t get_fadeout_time();

	bool is_fading();

	void reset_fader_parameters();

	void set_3d_source(Ref<CriAtomEx3dSource> source);

	void set_3d_listener(Ref<CriAtomEx3dListener> listener);

	CriAtomExPlayerHn get_handle() const { return this->handle; }

private:
	CriAtomExPlayerHn handle = nullptr;
};

}
