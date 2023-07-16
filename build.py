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
    binding_generator.generate_bindings("godot-headers/api.json", False)
    os.chdir(cwd)

import_generate_bindings()

os.chdir(os.path.dirname(script_path))

job_opt = " -j" + str(multiprocessing.cpu_count())

if "platform=windows" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/windows", exist_ok=True)
    shutil.copy2("cri/pc/libs/x64/cri_ware_pcx64_le.dll", "godot-proj/addons/adxle/bin/windows/cri_ware_pcx64_le.dll")

    # subprocess.run("scons platform=windows bits=32 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=windows bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adxle/bin/windows", exist_ok = True)

    # shutil.copy2("bin/libadxle.win32.dll", "godot-proj/addons/adxle/bin/windows/")
    shutil.copy2("bin/libadxle.win64.dll", "godot-proj/addons/adxle/bin/windows/")

elif "platform=macos" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/macos", exist_ok=True)
    # shutil.copytree("cri/macosx/libs", "godot-proj/addons/adxle/bin/macos", dirs_exist_ok=True)

    subprocess.run("scons platform=macos bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adxle/bin/macos", exist_ok = True)

    shutil.copy2("bin/libadxle.macos.dylib", "godot-proj/addons/adxle/bin/macos/")

elif "platform=android" in sys.argv:
    for arch in ["arm64-v8a", "armeabi-v7a", "x86_64"]:
        os.makedirs(f"godot-proj/addons/adxle/bin/android/{arch}", exist_ok=True)
        shutil.copy2(f"cri/android/libs/{arch}/libcri_ware_android_LE.so", f"godot-proj/addons/adxle/bin/android/{arch}/libcri_ware_android_le.so")

    subprocess.run("scons platform=android android_arch=armeabi-v7a target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=arm64-v8a target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=x86_64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adxle/bin/android", exist_ok = True)

    shutil.copy2("bin/libadxle.android.armeabi-v7a.so", "godot-proj/addons/adxle/bin/android/armeabi-v7a/libadxle.android.so")
    shutil.copy2("bin/libadxle.android.arm64-v8a.so", "godot-proj/addons/adxle/bin/android/arm64-v8a/libadxle.android.so")
    shutil.copy2("bin/libadxle.android.x86_64.so", "godot-proj/addons/adxle/bin/android/x86_64/libadxle.android.so")

elif "platform=ios" in sys.argv:
    os.makedirs("godot-proj/addons/adxle/bin/ios", exist_ok=True)
    # shutil.copytree("cri/ios/libs", "godot-proj/addons/adxle/bin/ios", dirs_exist_ok=True)

    subprocess.run("scons platform=ios ios_arch=arm64 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=ios ios_arch=x86_64 target=release" + job_opt, shell = True)

    subprocess.run("lipo -create bin/libadxle.ios.arm64.dylib -output bin/libadxle.ios.dylib", shell = True)
    subprocess.run("lipo -create bin/libadxle.ios.x86_64.dylib -output bin/libadxle.ios-sim.dylib", shell = True)

    os.makedirs("godot-proj/addons/adxle/bin/ios", exist_ok = True)
    
    shutil.copy2("bin/libadxle.ios.dylib", "godot-proj/addons/adxle/bin/ios/")
    shutil.copy2("bin/libadxle.ios-sim.dylib", "godot-proj/addons/adxle/bin/ios/")
