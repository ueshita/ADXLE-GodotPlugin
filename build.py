import sys
import os
import shutil
import subprocess

script_path = os.path.abspath(__file__)
sys.path.append(os.path.join(os.path.dirname(script_path), "godot-cpp"))

def import_generate_bindings(arch: str):
    bits = "32" if "32" in arch else "64"
    cwd = os.getcwd()
    os.chdir(os.path.join(os.path.dirname(script_path), "godot-cpp"))
    binding_generator = __import__("binding_generator")
    binding_generator.generate_bindings(
        api_filepath="gdextension/extension_api.json",
        interface_filepath="gdextension/gdextension_interface.json",
        use_template_get_node=False,
        bits=bits,
    )
    os.chdir(cwd)

os.chdir(os.path.dirname(script_path))

if "gen_bindings_only" in sys.argv:
    for arch in ["x86_64"]:
        import_generate_bindings(arch)

if "platform=windows" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/windows", exist_ok=True)
    shutil.copy2("cri/pc/libs/x64/cri_ware_pcx64_le.dll", "godot-proj/addons/adxle/bin/windows/cri_ware_pcx64_le.dll")

    import_generate_bindings("x86_64")
    subprocess.run("scons platform=windows arch=x86_64 target=template_release", shell=True)

elif "platform=macos" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/macos", exist_ok=True)

    import_generate_bindings("64")
    subprocess.run("scons platform=macos arch=universal target=template_release", shell=True)

    os.rename("godot-proj/addons/adxle/bin/macos/libadxle.universal.dylib", "godot-proj/addons/adxle/bin/macos/libadxle.dylib")

elif "platform=android" in sys.argv:
    os.makedirs(f"godot-proj/addons/adxle/bin/android/armeabi-v7a", exist_ok=True)
    shutil.copy2(f"cri/android/libs/armeabi-v7a/libcri_ware_android_LE.so", f"godot-proj/addons/adxle/bin/android/armeabi-v7a/libcri_ware_android_le.so")
    os.makedirs(f"godot-proj/addons/adxle/bin/android/arm64-v8a", exist_ok=True)
    shutil.copy2(f"cri/android/libs/arm64-v8a/libcri_ware_android_le.so", f"godot-proj/addons/adxle/bin/android/arm64-v8a/libcri_ware_android_le.so")
    os.makedirs(f"godot-proj/addons/adxle/bin/android/x86_64", exist_ok=True)
    shutil.copy2(f"cri/android/libs/x86_64/libcri_ware_android_le.so", f"godot-proj/addons/adxle/bin/android/x86_64/libcri_ware_android_le.so")
    
    for arch in ["arm32", "arm64", "x86_64"]:
        import_generate_bindings(arch)
        subprocess.run(f"scons platform=android arch={arch} target=template_release use_static_cpp=yes", shell=True)

elif "platform=ios" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/ios", exist_ok=True)

    import_generate_bindings("arm64")
    subprocess.run("scons platform=ios arch=universal target=template_release", shell=True)

    os.rename("godot-proj/addons/adxle/bin/ios/libadxle.universal.dylib", "godot-proj/addons/adxle/bin/ios/libadxle.dylib")
