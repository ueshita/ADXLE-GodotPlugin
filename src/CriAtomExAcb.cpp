#include "GDLibrary.h"
#include "CriAtomExAcb.h"

namespace godot {

namespace {

String string_or_empty(const CriChar8 *value)
{
	if (!value) {
		return String();
	}
	return String(value);
}

Dictionary cue_info_to_dictionary(const CriAtomExCueInfo &info)
{
	Dictionary result;
	result["id"] = (int32_t)info.id;
	result["type"] = (int32_t)info.type;
	result["name"] = info.name ? String(info.name) : String();
	result["user_data"] = info.user_data ? String(info.user_data) : String();
	result["length"] = (int64_t)info.length;
	result["num_limits"] = (int32_t)info.num_limits;
	result["num_blocks"] = (int32_t)info.num_blocks;
	result["num_tracks"] = (int32_t)info.num_tracks;
	result["num_related_waveforms"] = (int32_t)info.num_related_waveforms;
	result["priority"] = (int32_t)info.priority;
	result["header_visibility"] = info.header_visibility != 0;
	result["ignore_player_parameter"] = info.ignore_player_parameter != 0;
	result["probability"] = (int32_t)info.probability;
	result["pan_type"] = (int32_t)info.pan_type;
	result["volume"] = info.volume;
	result["silent_mode"] = (int32_t)info.silent_mode;
	result["pitch"] = info.pitch;
	result["selector_index"] = (int32_t)info.selector_index;
	return result;
}

Dictionary waveform_info_to_dictionary(const CriAtomExWaveformInfo &info)
{
	Dictionary result;
	result["wave_id"] = (int32_t)info.wave_id;
	result["format"] = (int32_t)info.format;
	result["sampling_rate"] = (int32_t)info.sampling_rate;
	result["num_channels"] = (int32_t)info.num_channels;
	result["num_samples"] = (int64_t)info.num_samples;
	result["streaming"] = info.streaming_flag == CRI_TRUE;
	return result;
}

Dictionary aisac_control_info_to_dictionary(const CriAtomExAisacControlInfo &info)
{
	Dictionary result;
	result["name"] = info.name ? String(info.name) : String();
	result["id"] = (int64_t)info.id;
	return result;
}

}

void CriAtomExAcb::_bind_methods()
{
	GDBIND_STATIC_METHOD(CriAtomExAcb, load_acb_file, "acb_path", "awb_path");
	GDBIND_STATIC_METHOD(CriAtomExAcb, release_all);
	GDBIND_METHOD(CriAtomExAcb, release);
	GDBIND_METHOD(CriAtomExAcb, is_ready_to_release);
	GDBIND_METHOD(CriAtomExAcb, get_num_cues);
	GDBIND_METHOD(CriAtomExAcb, exists_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, exists_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, exists_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_cue_id_by_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_cue_id_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_cue_name_by_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_cue_name_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_cue_index_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_cue_index_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_user_data_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_user_data_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_length_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_length_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_num_usable_aisac_controls_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_num_usable_aisac_controls_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_usable_aisac_control_by_id, "cue_id", "index");
	GDBIND_METHOD(CriAtomExAcb, get_usable_aisac_control_by_name, "cue_name", "index");
	GDBIND_METHOD(CriAtomExAcb, is_using_aisac_control_by_id, "cue_id", "aisac_control_id");
	GDBIND_METHOD(CriAtomExAcb, is_using_aisac_control_by_name, "cue_name", "aisac_control_name");
	GDBIND_METHOD(CriAtomExAcb, get_cue_priority_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_cue_priority_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_waveform_info_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_waveform_info_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_cue_info_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_cue_info_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_cue_info_by_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_all_cue_infos);
	GDBIND_METHOD(CriAtomExAcb, get_num_cue_playing_count_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, get_num_cue_playing_count_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, get_num_cue_playing_count_by_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_block_index_by_index, "cue_index", "block_name");
	GDBIND_METHOD(CriAtomExAcb, get_block_index_by_id, "cue_id", "block_name");
	GDBIND_METHOD(CriAtomExAcb, get_block_index_by_name, "cue_name", "block_name");
	GDBIND_METHOD(CriAtomExAcb, get_acb_info);
	GDBIND_METHOD(CriAtomExAcb, reset_cue_type_state_by_name, "cue_name");
	GDBIND_METHOD(CriAtomExAcb, reset_cue_type_state_by_id, "cue_id");
	GDBIND_METHOD(CriAtomExAcb, reset_cue_type_state_by_index, "cue_index");
	GDBIND_METHOD(CriAtomExAcb, get_num_awb_file_slots);
	GDBIND_METHOD(CriAtomExAcb, get_awb_file_slot_name, "index");
	GDBIND_METHOD(CriAtomExAcb, is_attached_awb_file, "awb_name");
}

CriAtomExAcb::CriAtomExAcb()
{
}

CriAtomExAcb::~CriAtomExAcb()
{
	release();
}

Ref<CriAtomExAcb> CriAtomExAcb::load_acb_file(String acb_path, Variant awb_path)
{
	auto handle = criAtomExAcb_LoadAcbFile(
		nullptr, acb_path.utf8().get_data(), 
		nullptr, (awb_path.get_type() == Variant::STRING) ? ((String)awb_path).utf8().get_data() : nullptr, 
		nullptr, 0);
	if (handle == nullptr) {
		return nullptr;
	}

	Ref<CriAtomExAcb> acb = memnew(CriAtomExAcb);
	acb->handle = handle;
	return acb;
}

void CriAtomExAcb::release_all()
{
	criAtomExAcb_ReleaseAll();
}

void CriAtomExAcb::release()
{
	if (handle) {
		criAtomExAcb_Release(handle);
		handle = nullptr;
	}
}

bool CriAtomExAcb::is_ready_to_release() const
{
	if (!handle) {
		return false;
	}
	return criAtomExAcb_IsReadyToRelease(handle) == CRI_TRUE;
}

int CriAtomExAcb::get_num_cues() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetNumCues(handle);
}

bool CriAtomExAcb::exists_id(int cue_id) const
{
	if (!handle) {
		return false;
	}
	return criAtomExAcb_ExistsId(handle, cue_id) == CRI_TRUE;
}

bool CriAtomExAcb::exists_name(String cue_name) const
{
	if (!handle) {
		return false;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_ExistsName(handle, name.get_data()) == CRI_TRUE;
}

bool CriAtomExAcb::exists_index(int cue_index) const
{
	if (!handle) {
		return false;
	}
	return criAtomExAcb_ExistsIndex(handle, cue_index) == CRI_TRUE;
}

int CriAtomExAcb::get_cue_id_by_index(int cue_index) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetCueIdByIndex(handle, cue_index);
}

int CriAtomExAcb::get_cue_id_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetCueIdByName(handle, name.get_data());
}

String CriAtomExAcb::get_cue_name_by_index(int cue_index) const
{
	if (!handle) {
		return String();
	}
	return string_or_empty(criAtomExAcb_GetCueNameByIndex(handle, cue_index));
}

String CriAtomExAcb::get_cue_name_by_id(int cue_id) const
{
	if (!handle) {
		return String();
	}
	return string_or_empty(criAtomExAcb_GetCueNameById(handle, cue_id));
}

int CriAtomExAcb::get_cue_index_by_id(int cue_id) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetCueIndexById(handle, cue_id);
}

int CriAtomExAcb::get_cue_index_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetCueIndexByName(handle, name.get_data());
}

String CriAtomExAcb::get_user_data_by_id(int cue_id) const
{
	if (!handle) {
		return String();
	}
	return string_or_empty(criAtomExAcb_GetUserDataById(handle, cue_id));
}

String CriAtomExAcb::get_user_data_by_name(String cue_name) const
{
	if (!handle) {
		return String();
	}
	CharString name = cue_name.utf8();
	return string_or_empty(criAtomExAcb_GetUserDataByName(handle, name.get_data()));
}

int64_t CriAtomExAcb::get_length_by_id(int cue_id) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetLengthById(handle, cue_id);
}

int64_t CriAtomExAcb::get_length_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetLengthByName(handle, name.get_data());
}

int CriAtomExAcb::get_num_usable_aisac_controls_by_id(int cue_id) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetNumUsableAisacControlsById(handle, cue_id);
}

int CriAtomExAcb::get_num_usable_aisac_controls_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetNumUsableAisacControlsByName(handle, name.get_data());
}

Dictionary CriAtomExAcb::get_usable_aisac_control_by_id(int cue_id, int index) const
{
	if (!handle || index < 0 || index > UINT16_MAX) {
		return Dictionary();
	}
	CriAtomExAisacControlInfo info;
	if (criAtomExAcb_GetUsableAisacControlById(handle, cue_id, (CriUint16)index, &info) == CRI_FALSE) {
		return Dictionary();
	}
	return aisac_control_info_to_dictionary(info);
}

Dictionary CriAtomExAcb::get_usable_aisac_control_by_name(String cue_name, int index) const
{
	if (!handle || index < 0 || index > UINT16_MAX) {
		return Dictionary();
	}
	CharString name = cue_name.utf8();
	CriAtomExAisacControlInfo info;
	if (criAtomExAcb_GetUsableAisacControlByName(handle, name.get_data(), (CriUint16)index, &info) == CRI_FALSE) {
		return Dictionary();
	}
	return aisac_control_info_to_dictionary(info);
}

bool CriAtomExAcb::is_using_aisac_control_by_id(int cue_id, int64_t aisac_control_id) const
{
	if (!handle) {
		return false;
	}
	return criAtomExAcb_IsUsingAisacControlById(handle, cue_id, (CriAtomExAisacControlId)aisac_control_id) == CRI_TRUE;
}

bool CriAtomExAcb::is_using_aisac_control_by_name(String cue_name, String aisac_control_name) const
{
	if (!handle) {
		return false;
	}
	CharString name = cue_name.utf8();
	CharString aisac_name = aisac_control_name.utf8();
	return criAtomExAcb_IsUsingAisacControlByName(handle, name.get_data(), aisac_name.get_data()) == CRI_TRUE;
}

int CriAtomExAcb::get_cue_priority_by_id(int cue_id) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetCuePriorityById(handle, cue_id);
}

int CriAtomExAcb::get_cue_priority_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetCuePriorityByName(handle, name.get_data());
}

Dictionary CriAtomExAcb::get_waveform_info_by_id(int cue_id) const
{
	if (!handle) {
		return Dictionary();
	}
	CriAtomExWaveformInfo info;
	if (criAtomExAcb_GetWaveformInfoById(handle, cue_id, &info) == CRI_FALSE) {
		return Dictionary();
	}
	return waveform_info_to_dictionary(info);
}

Dictionary CriAtomExAcb::get_waveform_info_by_name(String cue_name) const
{
	if (!handle) {
		return Dictionary();
	}
	CharString name = cue_name.utf8();
	CriAtomExWaveformInfo info;
	if (criAtomExAcb_GetWaveformInfoByName(handle, name.get_data(), &info) == CRI_FALSE) {
		return Dictionary();
	}
	return waveform_info_to_dictionary(info);
}

Dictionary CriAtomExAcb::get_cue_info_by_name(String cue_name) const
{
	if (!handle) {
		return Dictionary();
	}
	CharString name = cue_name.utf8();
	CriAtomExCueInfo info;
	if (criAtomExAcb_GetCueInfoByName(handle, name.get_data(), &info) == CRI_FALSE) {
		return Dictionary();
	}
	return cue_info_to_dictionary(info);
}

Dictionary CriAtomExAcb::get_cue_info_by_id(int cue_id) const
{
	if (!handle) {
		return Dictionary();
	}
	CriAtomExCueInfo info;
	if (criAtomExAcb_GetCueInfoById(handle, cue_id, &info) == CRI_FALSE) {
		return Dictionary();
	}
	return cue_info_to_dictionary(info);
}

Dictionary CriAtomExAcb::get_cue_info_by_index(int cue_index) const
{
	if (!handle) {
		return Dictionary();
	}
	CriAtomExCueInfo info;
	if (criAtomExAcb_GetCueInfoByIndex(handle, cue_index, &info) == CRI_FALSE) {
		return Dictionary();
	}
	return cue_info_to_dictionary(info);
}

Array CriAtomExAcb::get_all_cue_infos()
{
	if (!handle) {
		return Array();
	}

	Array cue_list;
	int32_t num_cues = criAtomExAcb_GetNumCues(handle);
	for (int32_t index = 0; index < num_cues; index++) {
		CriAtomExCueInfo info;
		if (criAtomExAcb_GetCueInfoByIndex(handle, index, &info) == CRI_TRUE) {
			cue_list.append(cue_info_to_dictionary(info));
		}
	}

	return cue_list;
}

int CriAtomExAcb::get_num_cue_playing_count_by_name(String cue_name) const
{
	if (!handle) {
		return -1;
	}
	CharString name = cue_name.utf8();
	return criAtomExAcb_GetNumCuePlayingCountByName(handle, name.get_data());
}

int CriAtomExAcb::get_num_cue_playing_count_by_id(int cue_id) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetNumCuePlayingCountById(handle, cue_id);
}

int CriAtomExAcb::get_num_cue_playing_count_by_index(int cue_index) const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetNumCuePlayingCountByIndex(handle, cue_index);
}

int CriAtomExAcb::get_block_index_by_index(int cue_index, String block_name) const
{
	if (!handle) {
		return CRIATOMEX_INVALID_BLOCK_INDEX;
	}
	CharString name = block_name.utf8();
	return criAtomExAcb_GetBlockIndexByIndex(handle, cue_index, name.get_data());
}

int CriAtomExAcb::get_block_index_by_id(int cue_id, String block_name) const
{
	if (!handle) {
		return CRIATOMEX_INVALID_BLOCK_INDEX;
	}
	CharString name = block_name.utf8();
	return criAtomExAcb_GetBlockIndexById(handle, cue_id, name.get_data());
}

int CriAtomExAcb::get_block_index_by_name(String cue_name, String block_name) const
{
	if (!handle) {
		return CRIATOMEX_INVALID_BLOCK_INDEX;
	}
	CharString name = cue_name.utf8();
	CharString block = block_name.utf8();
	return criAtomExAcb_GetBlockIndexByName(handle, name.get_data(), block.get_data());
}

Dictionary CriAtomExAcb::get_acb_info() const
{
	if (!handle) {
		return Dictionary();
	}
	CriAtomExAcbInfo info;
	if (criAtomExAcb_GetAcbInfo(handle, &info) == CRI_FALSE) {
		return Dictionary();
	}
	Dictionary result;
	result["name"] = info.name ? String(info.name) : String();
	result["size"] = (int64_t)info.size;
	result["version"] = (int64_t)info.version;
	result["user_data"] = info.user_data ? String(info.user_data) : String();
	result["language"] = info.language ? String(info.language) : String();
	result["character_encoding"] = (int32_t)info.character_encoding;
	result["volume"] = info.volume;
	result["num_cues"] = (int32_t)info.num_cues;
	return result;
}

void CriAtomExAcb::reset_cue_type_state_by_name(String cue_name)
{
	if (!handle) {
		return;
	}
	CharString name = cue_name.utf8();
	criAtomExAcb_ResetCueTypeStateByName(handle, name.get_data());
}

void CriAtomExAcb::reset_cue_type_state_by_id(int cue_id)
{
	if (handle) {
		criAtomExAcb_ResetCueTypeStateById(handle, cue_id);
	}
}

void CriAtomExAcb::reset_cue_type_state_by_index(int cue_index)
{
	if (handle) {
		criAtomExAcb_ResetCueTypeStateByIndex(handle, cue_index);
	}
}

int CriAtomExAcb::get_num_awb_file_slots() const
{
	if (!handle) {
		return -1;
	}
	return criAtomExAcb_GetNumAwbFileSlots(handle);
}

String CriAtomExAcb::get_awb_file_slot_name(int index) const
{
	if (!handle || index < 0 || index > UINT16_MAX) {
		return String();
	}
	return string_or_empty(criAtomExAcb_GetAwbFileSlotName(handle, (CriUint16)index));
}

bool CriAtomExAcb::is_attached_awb_file(String awb_name) const
{
	if (!handle) {
		return false;
	}
	CharString name = awb_name.utf8();
	return criAtomExAcb_IsAttachedAwbFile(handle, name.get_data()) == CRI_TRUE;
}

}
