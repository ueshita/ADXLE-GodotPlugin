#include "GDLibrary.h"
#include "CriAtomExContext.h"
#include "CriAtomExVoicePool.h"
#include "CriAtomExAcb.h"
#include "CriAtomExCategory.h"
#include "CriAtomExPlayer.h"
#include "CriAtomEx3dSource.h"
#include "CriAtomEx3dListener.h"

using namespace godot;

void initialize_adxle_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<CriAtomExContext>();
	ClassDB::register_class<CriAtomExVoicePool>();
	ClassDB::register_class<CriAtomExAcb>();
	ClassDB::register_class<CriAtomExCategory>();
	ClassDB::register_class<CriAtomExPlayer>();
	ClassDB::register_class<CriAtomEx3dSource>();
	ClassDB::register_class<CriAtomEx3dListener>();
}

void uninitialize_adxle_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" 
GDExtensionBool GDE_EXPORT adxle_library_init(
	GDExtensionInterfaceGetProcAddress p_get_proc_address,
	GDExtensionClassLibraryPtr p_library,
	GDExtensionInitialization *r_initialization)
{
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_adxle_module);
	init_obj.register_terminator(uninitialize_adxle_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
