#include <godot_cpp/variant/utility_functions.hpp>
#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriWareFileIo.h"

namespace godot {

void CriAtomExContext::_bind_methods()
{
	GDBIND_METHOD(CriAtomExContext, initialize, "config");
	GDBIND_METHOD(CriAtomExContext, finalize);
	GDBIND_METHOD(CriAtomExContext, attach_dspbus_setting, "setting_name");
	GDBIND_METHOD(CriAtomExContext, detach_dspbus_setting);
	GDBIND_METHOD(CriAtomExContext, apply_dspbus_snapshot, "snapshot_name");
	GDBIND_METHOD(CriAtomExContext, get_applied_dspbus_snapshot_name);

	//register_signal("sequence_event", );
	//register_signal("beatsync_position", );
}

CriAtomExContext::CriAtomExContext()
{
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
	this->finalize();

	criErr_SetCallback(nullptr);
}

void CriAtomExContext::_init()
{
}

void CriAtomExContext::initialize(String acf_file, Dictionary config)
{
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

	//criAtomExSequencer_SetEventCallback();
	//criAtomExBeatSync_SetCallback();
}

void CriAtomExContext::finalize()
{
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

}
