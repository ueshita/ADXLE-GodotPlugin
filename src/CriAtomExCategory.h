#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExCategory : public RefCounted
{
    GDCLASS(CriAtomExCategory, RefCounted)
public:
    static void _bind_methods();

	CriAtomExCategory();
    ~CriAtomExCategory();

	void set_name(String category_name);

	String get_name() const;

	void set_id(int category_id);

	int get_id() const;

	void set_volume(float volume);

	float get_volume();
	float get_total_volume();
	void set_fade_in_time(int time_ms);
	void set_fade_out_time(int time_ms);
	void set_aisac_control_by_id(int64_t control_id, float value);
	bool reset_all_aisac_controls();
	void attach_aisac(String global_aisac_name);
	void detach_aisac(String global_aisac_name);
	void detach_all_aisacs();
	int get_num_attached_aisacs();
	float get_current_aisac_control_value(int64_t control_id);
	int get_num_cue_playing_count();
	void override_cue_limit(int num_limit);

	void stop();

	void stop_without_release_time();

	void pause(bool pause);

	bool is_paused();

	void solo(bool solo, float mute_volume);

	bool is_soloed();

	void mute(bool mute);

	bool is_muted();

private:
	CriAtomExCategoryId id = UINT32_MAX;
};

}
