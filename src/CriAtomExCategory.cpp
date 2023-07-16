#include <stdio.h>
#include "GDLibrary.h"
#include "CriAtomExCategory.h"

namespace godot {

void CriAtomExCategory::_register_methods()
{
	register_method("_init", &CriAtomExCategory::_init);
	register_method("set_name", &CriAtomExCategory::set_name);
	register_method("get_name", &CriAtomExCategory::get_name);
	register_method("set_id", &CriAtomExCategory::set_id);
	register_method("get_id", &CriAtomExCategory::get_id);
	register_method("set_volume", &CriAtomExCategory::set_volume);
	register_method("get_volume", &CriAtomExCategory::get_volume);
	register_method("stop", &CriAtomExCategory::stop);
	register_method("stop_without_release_time", &CriAtomExCategory::stop_without_release_time);
	register_method("pause", &CriAtomExCategory::pause);
	register_method("is_paused", &CriAtomExCategory::is_paused);
	register_method("solo", &CriAtomExCategory::solo);
	register_method("is_soloed", &CriAtomExCategory::is_soloed);
	register_method("mute", &CriAtomExCategory::mute);
	register_method("is_muted", &CriAtomExCategory::is_muted);
}

CriAtomExCategory::CriAtomExCategory()
{
}

CriAtomExCategory::~CriAtomExCategory()
{
}

void CriAtomExCategory::_init()
{
}

void CriAtomExCategory::set_name(String category_name)
{
	CriAtomExCategoryInfo info;

	if (criAtomExAcf_GetCategoryInfoByName(FixedString<256>(category_name).str, &info)) {
		id = info.id;
	} else {
		char message[256];
		snprintf(message, sizeof(message), "Specified category not found: %s", FixedString<256>(category_name).str);
		api->godot_print_error(message, "CriAtomExCategory::set_name", "CriAtomExCategory.cpp", __LINE__);
	}
}

String CriAtomExCategory::get_name() const
{
	CriAtomExCategoryInfo info;

	if (criAtomExAcf_GetCategoryInfoById(id, &info)) {
		return info.name;
	} else {
		char message[256];
		snprintf(message, sizeof(message), "Specified category not found: %d", id);
		api->godot_print_error(message, "CriAtomExCategory::get_name", "CriAtomExCategory.cpp", __LINE__);
		return "";
	}
}

void CriAtomExCategory::set_id(int category_id)
{
	id = category_id;
}

int CriAtomExCategory::get_id() const
{
	return id;
}

void CriAtomExCategory::set_volume(float volume)
{
	criAtomExCategory_SetVolumeById(id, volume);
}

float CriAtomExCategory::get_volume()
{
	return criAtomExCategory_GetVolumeById(id);
}

void CriAtomExCategory::stop()
{
	criAtomExCategory_StopById(id);
}

void CriAtomExCategory::stop_without_release_time()
{
	criAtomExCategory_StopWithoutReleaseTimeById(id);
}

void CriAtomExCategory::pause(bool pause)
{
	criAtomExCategory_PauseById(id, pause);
}

bool CriAtomExCategory::is_paused()
{
	return criAtomExCategory_IsPausedById(id);
}

void CriAtomExCategory::solo(bool solo, float mute_volume)
{
	criAtomExCategory_SoloById(id, solo, mute_volume);
}

bool CriAtomExCategory::is_soloed()
{
	return criAtomExCategory_IsSoloedById(id);
}

void CriAtomExCategory::mute(bool mute)
{
	criAtomExCategory_MuteById(id, mute);
}

bool CriAtomExCategory::is_muted()
{
	return criAtomExCategory_IsMutedById(id);
}

}
