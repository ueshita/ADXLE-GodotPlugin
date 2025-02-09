#pragma once

#include <vector>
#include <cri_adx2le.h>
#include "GDLibrary.h"

namespace godot {

class CriAtomExPlayer;

class CriAtomExContext : public RefCounted
{
    GDCLASS(CriAtomExContext, RefCounted)
		
	static CriAtomExContext* singleton;

public:
	static CriAtomExContext* get_singleton();

    static void _bind_methods();

	CriAtomExContext();

    ~CriAtomExContext();

	void _init();

	void initialize(String acf_file, Dictionary config);

	void finalize();

	void attach_dspbus_setting(String setting_name);

	void detach_dspbus_setting();

	void apply_dspbus_snapshot(String snapshot_name, float duration);

	String get_applied_dspbus_snapshot_name();

	static CriSint32 sequence_event_callback(void* obj, const CriAtomExSequenceEventInfo* info);

	static CriSint32 beatsync_callback(void* obj, const CriAtomExBeatSyncInfo* info);

	void add_player(CriAtomExPlayer* player);

	void remove_player(CriAtomExPlayer* player);

private:
	bool is_initialized = false;
	std::mutex mutex;
	std::vector<CriAtomExPlayer*> player_list;
	CriAtomExDbasId dbas_id = CRIATOMDBAS_ILLEGAL_ID;
};

}
