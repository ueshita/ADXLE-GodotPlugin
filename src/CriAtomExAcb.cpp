#include "GDLibrary.h"
#include "CriAtomExAcb.h"

namespace godot {

void CriAtomExAcb::_register_methods()
{
	register_method("_init", &CriAtomExAcb::_init);
	register_method("load_acb_file", &CriAtomExAcb::load_acb_file);
	register_method("release", &CriAtomExAcb::release);
	register_method("get_all_cue_infos", &CriAtomExAcb::get_all_cue_infos);
}

CriAtomExAcb::CriAtomExAcb()
{
}

CriAtomExAcb::~CriAtomExAcb()
{
	release();
}

void CriAtomExAcb::_init()
{
}

bool CriAtomExAcb::load_acb_file(String acb_path, String awb_path)
{
	release();

	this->handle = criAtomExAcb_LoadAcbFile(nullptr, FixedString<1024>(acb_path).str, 
		nullptr, FixedString<1024>(awb_path).str, nullptr, 0);
	return (this->handle != nullptr);
}

void CriAtomExAcb::release()
{
	if (!criAtomEx_IsInitialized()) {
		return;
	}

	if (this->handle) {
		criAtomExAcb_Release(this->handle);
		this->handle = nullptr;
	}
}

Variant CriAtomExAcb::get_all_cue_infos()
{
	if (!this->handle) {
		return Variant();
	}

	Array cue_list;
	int32_t num_cues = criAtomExAcb_GetNumCues(this->handle);
	for (int32_t index = 0; index < num_cues; index++) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoByIndex(this->handle, index, &info);
		
		Dictionary dic;
		dic["id"] = (int32_t)info.id;
		dic["type"] = (int32_t)info.type;
		dic["name"] = info.name;
		dic["user_data"] = info.user_data;
		dic["length"] = (int64_t)info.length;
		cue_list.append(dic);
	}

	return cue_list;
}

}
