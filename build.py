import sys
import os
import shutil
import subprocess
import multiprocessing
import glob

script_path = os.path.abspath(__file__)

def import_generate_bindings():
    binding_generator = __import__("godot-cpp.binding_generator").binding_generator
    cwd = os.getcwd()
    os.chdir(os.path.join(os.path.dirname(script_path), "godot-cpp"))
    binding_generator.generate_bindings("gdextension/extension_api.json", False)
    os.chdir(cwd)

import_generate_bindings()

os.chdir(os.path.dirname(script_path))

if "platform=windows" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/windows", exist_ok=True)
    shutil.copy2("cri/pc/libs/x64/cri_ware_pcx64_le.dll", "godot-proj/addons/adxle/bin/windows/cri_ware_pcx64_le.dll")

    # subprocess.run("scons platform=windows arch=x86_32 target=template_release", shell = True)
    subprocess.run("scons platform=windows arch=x86_64 target=template_release", shell = True)

elif "platform=macos" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/macos", exist_ok=True)

    subprocess.run("scons platform=macos arch=universal target=template_release", shell = True)

    os.rename("godot-proj/addons/adxle/bin/macos/libadxle.universal.dylib", "godot-proj/addons/adxle/bin/macos/libadxle.dylib")

elif "platform=android" in sys.argv:
    os.makedirs(f"godot-proj/addons/adxle/bin/android/armeabi-v7a", exist_ok=True)
    shutil.copy2(f"cri/android/libs/armeabi-v7a/libcri_ware_android_LE.so", f"godot-proj/addons/adxle/bin/android/armeabi-v7a/libcri_ware_android_le.so")
    os.makedirs(f"godot-proj/addons/adxle/bin/android/arm64-v8a", exist_ok=True)
    shutil.copy2(f"cri/android/libs/arm64-v8a/libcri_ware_android_le.so", f"godot-proj/addons/adxle/bin/android/arm64-v8a/libcri_ware_android_le.so")
    os.makedirs(f"godot-proj/addons/adxle/bin/android/x86_64", exist_ok=True)
    shutil.copy2(f"cri/android/libs/x86_64/libcri_ware_android_le.so", f"godot-proj/addons/adxle/bin/android/x86_64/libcri_ware_android_le.so")

    subprocess.run("scons platform=android arch=arm32 target=template_release", shell = True)
    subprocess.run("scons platform=android arch=arm64 target=template_release", shell = True)
    subprocess.run("scons platform=android arch=x86_64 target=template_release", shell = True)

elif "platform=ios" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/ios", exist_ok=True)

    subprocess.run("scons platform=ios arch=universal target=template_release", shell = True)

    os.rename("godot-proj/addons/adxle/bin/ios/libadxle.universal.dylib", "godot-proj/addons/adxle/bin/ios/libadxle.dylib")
