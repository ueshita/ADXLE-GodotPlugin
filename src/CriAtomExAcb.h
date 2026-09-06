#pragma once

#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExAcb : public RefCounted
{
    GDCLASS(CriAtomExAcb, RefCounted)

public:
    static void _bind_methods();

public:
	CriAtomExAcb();
    ~CriAtomExAcb();

	static Ref<CriAtomExAcb> load_acb_file(String acb_path, Variant awb_path);

	static void release_all();
	
	void release();

	bool is_ready_to_release() const;
	int get_num_cues() const;
	bool exists_id(int cue_id) const;
	bool exists_name(String cue_name) const;
	bool exists_index(int cue_index) const;
	int get_cue_id_by_index(int cue_index) const;
	int get_cue_id_by_name(String cue_name) const;
	String get_cue_name_by_index(int cue_index) const;
	String get_cue_name_by_id(int cue_id) const;
	int get_cue_index_by_id(int cue_id) const;
	int get_cue_index_by_name(String cue_name) const;
	String get_user_data_by_id(int cue_id) const;
	String get_user_data_by_name(String cue_name) const;
	int64_t get_length_by_id(int cue_id) const;
	int64_t get_length_by_name(String cue_name) const;
	int get_num_usable_aisac_controls_by_id(int cue_id) const;
	int get_num_usable_aisac_controls_by_name(String cue_name) const;
	Dictionary get_usable_aisac_control_by_id(int cue_id, int index) const;
	Dictionary get_usable_aisac_control_by_name(String cue_name, int index) const;
	bool is_using_aisac_control_by_id(int cue_id, int64_t aisac_control_id) const;
	bool is_using_aisac_control_by_name(String cue_name, String aisac_control_name) const;
	int get_cue_priority_by_id(int cue_id) const;
	int get_cue_priority_by_name(String cue_name) const;
	Dictionary get_waveform_info_by_id(int cue_id) const;
	Dictionary get_waveform_info_by_name(String cue_name) const;
	Dictionary get_cue_info_by_name(String cue_name) const;
	Dictionary get_cue_info_by_id(int cue_id) const;
	Dictionary get_cue_info_by_index(int cue_index) const;
	Array get_all_cue_infos();
	int get_num_cue_playing_count_by_name(String cue_name) const;
	int get_num_cue_playing_count_by_id(int cue_id) const;
	int get_num_cue_playing_count_by_index(int cue_index) const;
	int get_block_index_by_index(int cue_index, String block_name) const;
	int get_block_index_by_id(int cue_id, String block_name) const;
	int get_block_index_by_name(String cue_name, String block_name) const;
	Dictionary get_acb_info() const;
	void reset_cue_type_state_by_name(String cue_name);
	void reset_cue_type_state_by_id(int cue_id);
	void reset_cue_type_state_by_index(int cue_index);
	int get_num_awb_file_slots() const;
	String get_awb_file_slot_name(int index) const;
	bool is_attached_awb_file(String awb_name) const;

	CriAtomExAcbHn get_handle() const { return handle; }

private:
	CriAtomExAcbHn handle = nullptr;
};

}
