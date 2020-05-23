import os
import shutil

if os.path.isdir("cri-godot"):
    shutil.rmtree("cri-godot")
os.mkdir("cri-godot")
os.mkdir("cri-godot/include")
os.mkdir("cri-godot/libs")

shutil.copytree("cri/cocos2dx/include/android", "cri-godot/include/android")
shutil.copytree("cri/cocos2dx/include/ios", "cri-godot/include/ios")
shutil.copytree("cri/cocos2dx/include/macosx", "cri-godot/include/macosx")
shutil.copytree("cri/cocos2dx/include/pc", "cri-godot/include/pc")

shutil.copytree("cri/cocos2dx/libs/android", "cri-godot/libs/android")
shutil.copytree("cri/cocos2dx/libs/ios", "cri-godot/libs/ios")
shutil.copytree("cri/cocos2dx/libs/macosx", "cri-godot/libs/macosx")
shutil.copytree("cri/cocos2dx/libs/pc", "cri-godot/libs/pc")
shutil.copytree("cri/UE4/Engine/Plugins/Runtime/CriWare/CriWare/Source/ThirdParty/CriWare/cri/pc/libs/x64", "cri-godot/libs/pc/x64")

if not os.path.isdir("godot-proj/addons/adx2le/bin/win32/"):
    os.makedirs("godot-proj/addons/adx2le/bin/win32/")
shutil.copy("cri-godot/libs/pc/x86/cri_ware_pcx86_le.dll", "godot-proj/addons/adx2le/bin/win32/")

if not os.path.isdir("godot-proj/addons/adx2le/bin/win64/"):
    os.makedirs("godot-proj/addons/adx2le/bin/win64/")
shutil.copy("cri-godot/libs/pc/x64/cri_ware_pcx64_le.dll", "godot-proj/addons/adx2le/bin/win64/")
