#include <stdio.h>
#include "GDLibrary.h"
#include "CriAtomExCategory.h"

namespace godot {

void CriAtomExCategory::_bind_methods()
{
	GDBIND_METHOD(CriAtomExCategory, set_name, "name");
	GDBIND_METHOD(CriAtomExCategory, get_name);
	GDBIND_METHOD(CriAtomExCategory, set_id, "id");
	GDBIND_METHOD(CriAtomExCategory, get_id);
	GDBIND_METHOD(CriAtomExCategory, set_volume, "volume");
	GDBIND_METHOD(CriAtomExCategory, get_volume);
	GDBIND_METHOD(CriAtomExCategory, get_total_volume);
	GDBIND_METHOD(CriAtomExCategory, set_fade_in_time, "time_ms");
	GDBIND_METHOD(CriAtomExCategory, set_fade_out_time, "time_ms");
	GDBIND_METHOD(CriAtomExCategory, set_aisac_control_by_id, "control_id", "value");
	GDBIND_METHOD(CriAtomExCategory, reset_all_aisac_controls);
	GDBIND_METHOD(CriAtomExCategory, attach_aisac, "global_aisac_name");
	GDBIND_METHOD(CriAtomExCategory, detach_aisac, "global_aisac_name");
	GDBIND_METHOD(CriAtomExCategory, detach_all_aisacs);
	GDBIND_METHOD(CriAtomExCategory, get_num_attached_aisacs);
	GDBIND_METHOD(CriAtomExCategory, get_current_aisac_control_value, "control_id");
	GDBIND_METHOD(CriAtomExCategory, get_num_cue_playing_count);
	GDBIND_METHOD(CriAtomExCategory, override_cue_limit, "num_limit");
	GDBIND_METHOD(CriAtomExCategory, stop);
	GDBIND_METHOD(CriAtomExCategory, stop_without_release_time);
	GDBIND_METHOD(CriAtomExCategory, pause, "paused");
	GDBIND_METHOD(CriAtomExCategory, is_paused);
	GDBIND_METHOD(CriAtomExCategory, solo, "soloed");
	GDBIND_METHOD(CriAtomExCategory, is_soloed);
	GDBIND_METHOD(CriAtomExCategory, mute, "muted");
	GDBIND_METHOD(CriAtomExCategory, is_muted);
}

CriAtomExCategory::CriAtomExCategory()
{
}

CriAtomExCategory::~CriAtomExCategory()
{
}

void CriAtomExCategory::set_name(String category_name)
{
	CriAtomExCategoryInfo info;

	if (criAtomExAcf_GetCategoryInfoByName(category_name.utf8().get_data(), &info)) {
		id = info.id;
	} else {
		char message[256];
		snprintf(message, sizeof(message), "Specified category not found: %s", category_name.utf8().get_data());
		godot::_err_print_error("CriAtomExCategory::set_name", "CriAtomExCategory.cpp", __LINE__, message, false, false);
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
		godot::_err_print_error("CriAtomExCategory::get_name", "CriAtomExCategory.cpp", __LINE__, message, false, false);
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

float CriAtomExCategory::get_total_volume()
{
	return criAtomExCategory_GetTotalVolumeById(id);
}

void CriAtomExCategory::set_fade_in_time(int time_ms)
{
	if (time_ms >= 0 && time_ms <= UINT16_MAX) {
		criAtomExCategory_SetFadeInTimeById(id, (CriUint16)time_ms);
	}
}

void CriAtomExCategory::set_fade_out_time(int time_ms)
{
	if (time_ms >= 0 && time_ms <= UINT16_MAX) {
		criAtomExCategory_SetFadeOutTimeById(id, (CriUint16)time_ms);
	}
}

void CriAtomExCategory::set_aisac_control_by_id(int64_t control_id, float value)
{
	criAtomExCategory_SetAisacControlById(id, (CriAtomExAisacControlId)control_id, value);
}

bool CriAtomExCategory::reset_all_aisac_controls()
{
	return criAtomExCategory_ResetAllAisacControlById(id) == CRI_TRUE;
}

void CriAtomExCategory::attach_aisac(String global_aisac_name)
{
	CharString name = global_aisac_name.utf8();
	criAtomExCategory_AttachAisacById(id, name.get_data());
}

void CriAtomExCategory::detach_aisac(String global_aisac_name)
{
	CharString name = global_aisac_name.utf8();
	criAtomExCategory_DetachAisacById(id, name.get_data());
}

void CriAtomExCategory::detach_all_aisacs()
{
	criAtomExCategory_DetachAisacAllById(id);
}

int CriAtomExCategory::get_num_attached_aisacs()
{
	return criAtomExCategory_GetNumAttachedAisacsById(id);
}

float CriAtomExCategory::get_current_aisac_control_value(int64_t control_id)
{
	CriFloat32 value;
	if (criAtomExCategory_GetCurrentAisacControlValueById(id, (CriAtomExAisacControlId)control_id, &value) == CRI_FALSE) {
		return 0.0f;
	}
	return value;
}

int CriAtomExCategory::get_num_cue_playing_count()
{
	return criAtomExCategory_GetNumCuePlayingCountById(id);
}

void CriAtomExCategory::override_cue_limit(int num_limit)
{
	criAtomExCategory_OverrideCueLimitById(id, num_limit);
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
