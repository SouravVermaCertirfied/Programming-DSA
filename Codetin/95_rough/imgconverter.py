import os
from PIL import Image
from pillow_heif import register_heif_opener

# 1. Register the HEIC opener with Pillow
register_heif_opener()

# 2. Define your paths
source_dir = r"C:\Users\Sourav\Downloads\drive-download-20260516T163131Z-3-001"
target_dir = os.path.join(source_dir, "converted")

# 3. Create the 'converted' folder if it doesn't exist
if not os.path.exists(target_dir):
    os.makedirs(target_dir)
    print(f"Created folder: {target_dir}")

# 4. Get all .heic files (case-insensitive)
files = [f for f in os.listdir(source_dir) if f.lower().endswith('.heic')]

if not files:
    print("No .heic files found in the source directory.")
else:
    print(f"Found {len(files)} HEIC files. Starting conversion...\n")
    
    for filename in files:
        # Construct full input and output paths
        input_path = os.path.join(source_dir, filename)
        
        # Change extension to .jpg
        base_name = os.path.splitext(filename)[0]
        output_path = os.path.join(target_dir, f"{base_name}.jpg")
        
        print(f"Converting: {filename} -> {base_name}.jpg")
        
        try:
            # Open the HEIC image and save it as JPEG
            image = Image.open(input_path)
            # 'RGB' conversion ensures transparency channels (if any) don't crash the JPEG saver
            image.convert("RGB").save(output_path, "JPEG", quality=90)
        except Exception as e:
            print(f"❌ Failed to convert {filename}. Error: {e}")

    print("\nDone! All files successfully converted and put inside the 'converted' folder.")