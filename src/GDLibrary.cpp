#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriAtomExVoicePool.h"
#include "CriAtomExAcb.h"
#include "CriAtomExCategory.h"
#include "CriAtomExPlayer.h"
#include "CriAtomEx3dSource.h"
#include "CriAtomEx3dListener.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *option)
{
	Godot::gdnative_init(option);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *option)
{
	Godot::gdnative_terminate(option);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
	Godot::nativescript_init(handle);

	register_class<CriAtomExContext>();
	register_class<CriAtomExVoicePool>();
	register_class<CriAtomExAcb>();
	register_class<CriAtomExCategory>();
	register_class<CriAtomExPlayer>();
	register_class<CriAtomEx3dSource>();
	register_class<CriAtomEx3dListener>();
}
