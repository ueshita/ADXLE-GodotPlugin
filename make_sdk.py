import os
import shutil

os.makedirs("godot-proj/addons/adx2le/bin/windows", exist_ok=True)
shutil.copy2("cri/pc/libs/x64/cri_ware_pcx64_le.dll", "godot-proj/addons/adx2le/bin/windows/")

os.makedirs("godot-proj/addons/adx2le/bin/macos", exist_ok=True)
# shutil.copytree("cri/macosx/libs", "godot-proj/addons/adx2le/bin/macos", dirs_exist_ok=True)

os.makedirs("godot-proj/addons/adx2le/bin/android", exist_ok=True)
shutil.copytree("cri/android/libs", "godot-proj/addons/adx2le/bin/android", dirs_exist_ok=True)

os.makedirs("godot-proj/addons/adx2le/bin/ios", exist_ok=True)
# shutil.copytree("cri/ios/libs", "godot-proj/addons/adx2le/bin/ios", dirs_exist_ok=True)
