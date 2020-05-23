#pragma once

#include <Godot.hpp>
#include <cri_adx2le.h>

namespace godot {

class CriAtomExCategory : public Reference
{
    GODOT_CLASS(CriAtomExCategory, Reference)
public:
    static void _register_methods();

	CriAtomExCategory();
    ~CriAtomExCategory();

	void _init();

	void set_name(String category_name);

	String get_name() const;

	void set_id(int category_id);

	int get_id() const;

	void set_volume(float volume);

	float get_volume();

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
