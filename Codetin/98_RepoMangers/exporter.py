import os
import zlib
import struct

# ------------------ CONFIGURATION ------------------ #

MODE = "export"  # "export" or "import"
# MODE = "import"  # "export" or "import"

EXPORT_REPO_PATH = r"D:\Nexteer\Codetin"
EXPORT_OUTPUT_FILE = r"D:\Breifcase\export.bin"

IMPORT_TXT_FILE_PATH = r"D:\Breifcase\export.pdf"
IMPORT_OUTPUT_REPO = r"D:\Breifcase\import"

XOR_KEY = 123  # simple fixed key (0–255)

# ------------------ HELPERS ------------------ #

def xor_bytes(data: bytes, key: int) -> bytes:
    return bytes(b ^ key for b in data)

def ensure_dir(path: str):
    os.makedirs(os.path.dirname(path), exist_ok=True)

# ------------------ EXPORT ------------------ #

def export_repo():
    container = bytearray()

    for root, _, files in os.walk(EXPORT_REPO_PATH):
        for name in files:
            full_path = os.path.join(root, name)
            rel_path = os.path.relpath(full_path, EXPORT_REPO_PATH).replace("\\", "/")

            with open(full_path, "rb") as f:
                raw = f.read()

            path_bytes = rel_path.encode("utf-8")

            # Pack: [path_len][path][data_len][data]
            container += struct.pack(">I", len(path_bytes))
            container += path_bytes
            container += struct.pack(">Q", len(raw))
            container += raw

    # Compress the whole container once
    compressed = zlib.compress(container, level=9)
    # XOR encrypt for casual obfuscation
    final_blob = xor_bytes(compressed, XOR_KEY)

    ensure_dir(EXPORT_OUTPUT_FILE)
    with open(EXPORT_OUTPUT_FILE, "wb") as f:
        f.write(final_blob)

    print(f"Export complete → {EXPORT_OUTPUT_FILE}")

# ------------------ IMPORT ------------------ #

def import_repo():
    with open(IMPORT_TXT_FILE_PATH, "rb") as f:
        encrypted = f.read()

    compressed = xor_bytes(encrypted, XOR_KEY)
    data = zlib.decompress(compressed)

    offset = 0
    total = len(data)

    while offset < total:
        path_len = struct.unpack(">I", data[offset:offset+4])[0]
        offset += 4

        path = data[offset:offset+path_len].decode("utf-8")
        offset += path_len

        data_len = struct.unpack(">Q", data[offset:offset+8])[0]
        offset += 8

        file_data = data[offset:offset+data_len]
        offset += data_len

        out_path = os.path.join(IMPORT_OUTPUT_REPO, path)
        ensure_dir(out_path)

        with open(out_path, "wb") as f:
            f.write(file_data)

    print(f"Import complete → {IMPORT_OUTPUT_REPO}")

# ------------------ MAIN ------------------ #

if __name__ == "__main__":
    if MODE == "export":
        export_repo()
    elif MODE == "import":
        import_repo()
    else:
        print("Invalid MODE")

"""
# 1. Modes:
#    - The script should have two hardcoded modes: export and import.

# 2. Paths:
#    - Hardcoded paths for source repo, backup file, and restore folder.
#    - Example:
#        EXPORT_REPO_PATH = r"D:\Repo\Source"
#        EXPORT_OUTPUT_FILE = r"D:\Repo\Backup\export.bin"
#        IMPORT_TXT_FILE_PATH = r"D:\Repo\Backup\export.bin"
#        IMPORT_OUTPUT_REPO = r"D:\Repo\Restore"

# 3. Functionality:

#    **Export mode:**
#    - Traverse the source repo recursively.
#    - Preserve full folder structure.
#    - Store file contents **exactly** (text, code, images, binaries).
#    - Make the backup file **opaque** (unauthorized user should not see filenames or content).
#    - Compress the backup to minimize size without losing information.
#    - Apply a simple XOR encryption for casual obfuscation.
#    - Save everything as a single binary file (`export.bin`), no JSON, no readable structure.

#    **Import mode:**
#    - Read the backup file.
#    - Decrypt, decompress, and restore all files to the output folder.
#    - Recreate the original folder structure.
#    - Ensure all file contents are exactly the same as the original.

# 4. Requirements:
#    - Python 3.9 compatible.
#    - No external libraries.
#    - Handle any file type safely.
#    - Backup file should look like random/corrupt data to an unauthorized observer.
#    - Optimize for smaller file size (do not increase size with unnecessary steps like base64 for the whole container).

# Please provide the **full Python script** with comments explaining each step.
"""
