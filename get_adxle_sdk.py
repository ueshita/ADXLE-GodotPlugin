import os
import shutil
import urllib.request
import glob


def convert_encoding(filepath: str):
    try:
        with open(filepath, "r", encoding="shift_jis") as f:
            text = f.read()
        with open(filepath, "w", encoding="utf8") as f:
            f.write(text)
    except UnicodeDecodeError:
        pass


def main():
    with open("./sdk_url.txt") as f:
        sdk_package_url = f.read()
    print(f"SDK package URL: {sdk_package_url}")

    local_package_name = "sdk.zip"
    _, message = urllib.request.urlretrieve(sdk_package_url, local_package_name)
    print(message)

    if os.path.exists(local_package_name):
        shutil.unpack_archive(local_package_name, extract_dir="./")
        os.remove(local_package_name)

        for filepath in glob.glob("cri/**/*.h", recursive=True):
            convert_encoding(filepath)

        print("SDK package installation succeeded.")
    else:
        print("SDK package installation failed.")


if __name__ == "__main__":
    main()
