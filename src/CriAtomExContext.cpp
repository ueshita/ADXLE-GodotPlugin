#include <godot_cpp/variant/utility_functions.hpp>
#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriAtomExPlayer.h"
#include "CriWareFileIo.h"

namespace godot {

CriAtomExContext* CriAtomExContext::singleton = nullptr;

CriAtomExContext* CriAtomExContext::get_singleton()
{
	return singleton;
}

void CriAtomExContext::_bind_methods()
{
	GDBIND_METHOD(CriAtomExContext, initialize, "config");
	GDBIND_METHOD(CriAtomExContext, finalize);
	GDBIND_METHOD(CriAtomExContext, attach_dspbus_setting, "setting_name");
	GDBIND_METHOD(CriAtomExContext, detach_dspbus_setting);
	GDBIND_METHOD(CriAtomExContext, apply_dspbus_snapshot, "snapshot_name");
	GDBIND_METHOD(CriAtomExContext, get_applied_dspbus_snapshot_name);
}

CriAtomExContext::CriAtomExContext()
{
	if (singleton != nullptr) {
		UtilityFunctions::printerr("It is not possible to create a context twice");
		return;
	}
	singleton = this;

	// Set error callback
	criErr_SetCallback([](const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray){
		auto errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
		if (errmsg[0] == 'W') {
			UtilityFunctions::print(errmsg);
		} else {
			UtilityFunctions::printerr(errmsg);
		}
	});

}

CriAtomExContext::~CriAtomExContext()
{
	if (singleton != this) {
		return;
	}
	this->finalize();

	criErr_SetCallback(nullptr);

	singleton = nullptr;
}

void CriAtomExContext::_init()
{
}

void CriAtomExContext::initialize(String acf_file, Dictionary config)
{
	if (singleton != this) {
		return;
	}
	if (this->is_initialized) {
		return;
	}

	// Set Godot allocator
	criAtomEx_SetUserAllocator(
		[](void *obj, CriUint32 size){ return memalloc((int)size); },
		[](void *obj, void *mem){ memfree(mem); },
		nullptr);

	// Setup filesystem
	criFs_SetSelectIoCallback(CriWareFileIo::SelectIo);

	// Initialize AtomEx library
	CriAtomExConfig atom_ex_config;
	criAtomEx_SetDefaultConfig(&atom_ex_config);
	atom_ex_config.coordinate_system = CRIATOMEX_COORDINATE_SYSTEM_RIGHT_HANDED;
	if (config.has("max_virtual_voices")) {
		atom_ex_config.max_virtual_voices = (int)config["max_virtual_voices"];
	}

	CriAtomExHcaMxConfig hca_mx_config;
	criAtomExHcaMx_SetDefaultConfig(&hca_mx_config);
	if (config.has("hca_mx_sampling_rate")) {
		hca_mx_config.output_sampling_rate = (int)config["hca_mx_sampling_rate"];
	}

#if defined(XPT_TGT_PC)
	CriAtomExConfig_WASAPI lib_config;
	criAtomEx_SetDefaultConfig_WASAPI(&lib_config);
	lib_config.atom_ex = atom_ex_config;
	lib_config.hca_mx = hca_mx_config;
	criAtomEx_Initialize_WASAPI(&lib_config, nullptr, 0);
#elif defined(XPT_TGT_MACOSX)
	CriAtomExConfig_MACOSX lib_config;
	criAtomEx_SetDefaultConfig_MACOSX(&lib_config);
	lib_config.atom_ex = atom_ex_config;
	lib_config.hca_mx = hca_mx_config;
	criAtomEx_Initialize_MACOSX(&lib_config, nullptr, 0);
#elif defined(XPT_TGT_ANDROID)
	CriAtomExConfig_ANDROID lib_config;
	criAtomEx_SetDefaultConfig_ANDROID(&lib_config);
	lib_config.atom_ex = atom_ex_config;
	lib_config.hca_mx = hca_mx_config;
	criAtomEx_Initialize_ANDROID(&lib_config, nullptr, 0);
#elif defined(XPT_TGT_IOS)
	CriAtomExConfig_IOS lib_config;
	criAtomEx_SetDefaultConfig_IOS(&lib_config);
	lib_config.atom_ex = atom_ex_config;
	lib_config.hca_mx = hca_mx_config;
	criAtomEx_Initialize_IOS(&lib_config, nullptr, 0);
#endif
	this->is_initialized = true;

	// Register config file
	if (criAtomEx_RegisterAcfFile(nullptr, acf_file.utf8().get_data(), nullptr, 0) == CRI_FALSE) {
		return;
	}

	// Initialize stream buffer
	CriAtomExDbasConfig dbas_config;
	criAtomExDbas_SetDefaultConfig(&dbas_config);
	if (config.has("max_streams")) {
		dbas_config.max_streams = (int)config["max_streams"];
	}
	this->dbas_id = criAtomExDbas_Create(&dbas_config, nullptr, 0);

	criAtomExSequencer_SetEventCallback(&CriAtomExContext::sequence_event_callback, this);
	criAtomExBeatSync_SetCallback(&CriAtomExContext::beatsync_callback, this);
}

void CriAtomExContext::finalize()
{
	if (singleton != this) {
		return;
	}
	if (!this->is_initialized) {
		return;
	}
	this->is_initialized = false;

	// Finalize stream buffer
	if (this->dbas_id != CRIATOMDBAS_ILLEGAL_ID) {
		criAtomExDbas_Destroy(this->dbas_id)
		this->dbas_id = CRIATOMDBAS_ILLEGAL_ID;
	}

	// Finalize ADX2 library
#if defined(XPT_TGT_PC)
	criAtomEx_Finalize_WASAPI();
#elif defined(XPT_TGT_MACOSX)
	criAtomEx_Finalize_MACOSX();
#elif defined(XPT_TGT_ANDROID)
	criAtomEx_Finalize_ANDROID();
#elif defined(XPT_TGT_IOS)
	criAtomEx_Finalize_IOS();
#endif

	criAtomEx_SetUserAllocator(nullptr, nullptr, nullptr);
}

void CriAtomExContext::attach_dspbus_setting(String setting_name)
{
	criAtomEx_AttachDspBusSetting(setting_name.utf8().get_data(), nullptr, 0);
}

void CriAtomExContext::detach_dspbus_setting()
{
	criAtomEx_DetachDspBusSetting();
}

void CriAtomExContext::apply_dspbus_snapshot(String snapshot_name, float time_ms)
{
	criAtomEx_ApplyDspBusSnapshot(snapshot_name.utf8().get_data(), time_ms);
}

String CriAtomExContext::get_applied_dspbus_snapshot_name()
{
	return criAtomEx_GetAppliedDspBusSnapshotName();
}

CriSint32 CriAtomExContext::sequence_event_callback(void* obj, const CriAtomExSequenceEventInfo* info)
{
	CriAtomExContext* context = (CriAtomExContext*)obj;
	std::lock_guard<std::mutex> lock(context->mutex);

	for (size_t i = 0; i < context->player_list.size(); i++) {
		CriAtomExPlayer* player = context->player_list[i];
		if (player->get_handle() == info->player) {
			Dictionary dic;
			dic["id"] = (int32_t)info->id;
			dic["player"] = player;
			dic["position"] = (int64_t)info->position;
			dic["type"] = info->type;
			dic["value"] = (int32_t)info->value;
			dic["string"] = info->string;
			player->emit_signal<Dictionary>("sequence_event", dic);
			break;
		}
	}
	return 0;
}

CriSint32 CriAtomExContext::beatsync_callback(void* obj, const CriAtomExBeatSyncInfo* info)
{
	CriAtomExContext* context = (CriAtomExContext*)obj;
	std::lock_guard<std::mutex> lock(context->mutex);

	for (size_t i = 0; i < context->player_list.size(); i++) {
		CriAtomExPlayer* player = context->player_list[i];
		if (player->get_handle() == info->player) {
			Dictionary dic;
			dic["id"] = (int32_t)info->playback_id;
			dic["player"] = player;
			dic["bar_count"] = (int32_t)info->bar_count;
			dic["beat_count"] = (int32_t)info->beat_count;
			dic["beat_progress"] = info->beat_progress;
			dic["bpm"] = info->bpm;
			dic["offset"] = (int32_t)info->offset;
			dic["num_beats"] = (int32_t)info->num_beats;
			dic["label"] = info->label;
			player->emit_signal<Dictionary>("beatsync", dic);
			break;
		}
	}
	return 0;
}

void CriAtomExContext::add_player(CriAtomExPlayer* player)
{
	std::lock_guard<std::mutex> lock(mutex);
	player_list.push_back(player);
}

void CriAtomExContext::remove_player(CriAtomExPlayer* player)
{
	std::lock_guard<std::mutex> lock(mutex);
	auto it = std::find(player_list.begin(), player_list.end(), player);
	if (it != player_list.end()) {
		player_list.erase(it);
	}
}

}
