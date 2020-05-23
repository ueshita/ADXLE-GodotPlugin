#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriWareFileIo.h"

namespace godot {

void CriAtomExContext::_register_methods()
{
	register_method("_init", &CriAtomExContext::_init);
	register_method("initialize", &CriAtomExContext::initialize);
	register_method("finalize", &CriAtomExContext::finalize);
	register_method("attach_dspbus_setting", &CriAtomExContext::attach_dspbus_setting);
	register_method("detach_dspbus_setting", &CriAtomExContext::detach_dspbus_setting);
	register_method("apply_dspbus_snapshot", &CriAtomExContext::apply_dspbus_snapshot);
	register_method("get_applied_dspbus_snapshot_name", &CriAtomExContext::get_applied_dspbus_snapshot_name);

	//register_signal("sequence_event", );
	//register_signal("beatsync_position", );
}

CriAtomExContext::CriAtomExContext()
{
	// Set error callback
	criErr_SetCallback([](const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray){
		auto errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
		if (errmsg[0] == 'W') {
			api->godot_print_warning(errmsg, "CRIERR", "Internal", 0);
		} else {
			api->godot_print_error(errmsg, "CRIERR", "Internal", 0);
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
		[](void *obj, CriUint32 size){ return godot::api->godot_alloc((int)size); },
		[](void *obj, void *mem){ godot::api->godot_free(mem); }, nullptr);

	// Setup filesystem
	criFs_SetSelectIoCallback(CriWareFileIo::SelectIo);

	// Initialize AtomEx library
	CriAtomExConfig_WASAPI lib_config;
	criAtomEx_SetDefaultConfig_WASAPI(&lib_config);
	if (config.has("max_virtual_voices"))
		lib_config.atom_ex.max_virtual_voices = (int)config["max_virtual_voices"];
	criAtomEx_Initialize_WASAPI(&lib_config, nullptr, 0);
	this->is_initialized = true;

	// Register config file
	if (criAtomEx_RegisterAcfFile(nullptr, FixedString<1024>(acf_file).str, nullptr, 0) == CRI_FALSE) {
		return;
	}

	// Initialize stream buffer
	CriAtomExDbasConfig dbas_config;
	criAtomExDbas_SetDefaultConfig(&dbas_config);
	if (config.has("max_streams"))
		dbas_config.max_streams = (int)config["max_streams"];
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
	criAtomEx_Finalize_WASAPI();

	criAtomEx_SetUserAllocator(nullptr, nullptr, nullptr);
}

void CriAtomExContext::attach_dspbus_setting(String setting_name)
{
	criAtomEx_AttachDspBusSetting(FixedString<256>(setting_name).str, nullptr, 0);
}

void CriAtomExContext::detach_dspbus_setting()
{
	criAtomEx_DetachDspBusSetting();
}

void CriAtomExContext::apply_dspbus_snapshot(String snapshot_name, float time_ms)
{
	criAtomEx_ApplyDspBusSnapshot(FixedString<256>(snapshot_name).str, time_ms);
}

String CriAtomExContext::get_applied_dspbus_snapshot_name()
{
	return criAtomEx_GetAppliedDspBusSnapshotName();
}

}
