import sys
import os
import shutil
import subprocess
import multiprocessing

script_path = os.path.abspath(__file__)

def replace_word(file_name, target_str, replace_str):
    text = ""
    with open(file_name, "r") as file:
        text = file.read()

    text = text.replace(target_str, replace_str)

    with open(file_name, "w") as file:
        file.write(text)

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
    replace_word("godot-cpp/Sconstruct", "/MD", "/MT")

    # subprocess.run("scons platform=windows bits=32 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=windows bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adx2le/bin/windows", exist_ok = True)

    # shutil.copy2("bin/libadx2le.win32.dll", "godot-proj/addons/adx2le/bin/windows/")
    shutil.copy2("bin/libadx2le.win64.dll", "godot-proj/addons/adx2le/bin/windows/")

elif "platform=macos" in sys.argv:
    subprocess.run("scons platform=macos bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adx2le/bin/macos", exist_ok = True)

    shutil.copy2("bin/libadx2le.macos.dylib", "godot-proj/addons/adx2le/bin/macos/")

elif "platform=android" in sys.argv:
    subprocess.run("scons platform=android android_arch=armv7 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=arm64v8 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=x86_64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/addons/adx2le/bin/android", exist_ok = True)

    shutil.copy2("bin/libadx2le.android.armv7.so", "godot-proj/addons/adx2le/bin/android/armeabi-v7a/")
    shutil.copy2("bin/libadx2le.android.arm64v8.so", "godot-proj/addons/adx2le/bin/android/arm64-v8a/")
    shutil.copy2("bin/libadx2le.android.x86_64.so", "godot-proj/addons/adx2le/bin/android/x86_64/")

elif "platform=ios" in sys.argv:
    replace_word("godot-cpp/Sconstruct", "-version-min=10.0", "-version-min=9.0")

    subprocess.run("scons platform=ios ios_arch=arm64 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=ios ios_arch=x86_64 target=release" + job_opt, shell = True)

    subprocess.run("lipo -create bin/libadx2le.ios.arm64.dylib -output bin/libadx2le.ios.dylib", shell = True)
    subprocess.run("lipo -create bin/libadx2le.ios.x86_64.dylib -output bin/libadx2le.ios-sim.dylib", shell = True)

    os.makedirs("godot-proj/addons/adx2le/bin/ios", exist_ok = True)
    
    shutil.copy2("bin/libadx2le.ios.dylib", "godot-proj/addons/adx2le/bin/ios/")
    shutil.copy2("bin/libadx2le.ios-sim.dylib", "godot-proj/addons/adx2le/bin/ios/")
