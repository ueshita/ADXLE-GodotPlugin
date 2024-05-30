#include "GDLibrary.h"
#include "CriAtomExAcb.h"

namespace godot {

void CriAtomExAcb::_bind_methods()
{
	GDBIND_STATIC_METHOD(CriAtomExAcb, load_acb_file, "acb_path", "awb_path");
	GDBIND_STATIC_METHOD(CriAtomExAcb, release_all);
	GDBIND_METHOD(CriAtomExAcb, release);
	GDBIND_METHOD(CriAtomExAcb, get_all_cue_infos);
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
	if (!criAtomEx_IsInitialized()) {
		return;
	}

	criAtomExAcb_ReleaseAll();
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
