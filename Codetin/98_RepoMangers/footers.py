import os
import re

# ==============================================================================
# HARDCODED CONFIGURATION
# ==============================================================================
TARGET_DIR = r"D:\Github\Programming-DSA\Codetin"
# ==============================================================================

def natural_sort_key(s):
    """
    Breaks a string into parts of text and numbers.
    e.g., "a05_QuestionBank" -> ["a", 5, "_QuestionBank"]
    This ensures '05_...' and 'a05_...' resolve logically.
    """
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', s)]

def clean_existing_footer(content):
    """Removes any previously generated footer to avoid duplicates."""
    pattern = r'\n+---\n+<div style="display: flex; justify-content: space-between;">[\s\S]*?</div>\n*$'
    return re.sub(pattern, '', content).strip()

def generate_footers(root_path):
    if not os.path.exists(root_path):
        print(f"❌ Error: The path '{root_path}' does not exist.")
        return
    
    print(f"🔄 Processing notes with Natural Sorting in: {root_path}\n")
    processed_folders = 0

    for folder_name in os.listdir(root_path):
        folder_path = os.path.join(root_path, folder_name)
        
        if os.path.isdir(folder_path) and not folder_name.startswith('.'):
            # --- THE FIX IS HERE ---
            # We use key=natural_sort_key to ensure intelligent file ordering
            md_files = sorted(
                [f for f in os.listdir(folder_path) if f.endswith('.md') and f.lower() != 'readme.md'],
                key=natural_sort_key
            )
            
            if not md_files:
                continue
                
            processed_folders += 1
            
            for i, file_name in enumerate(md_files):
                file_path = os.path.join(folder_path, file_name)
                
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                base_content = clean_existing_footer(content)
                
                prev_link = ""
                next_link = ""
                
                if i > 0:
                    prev_file = md_files[i - 1]
                    prev_link = f'<a href="{prev_file}">← {prev_file}</a>'
                else:
                    prev_link = '<span></span>' 
                
                if i < len(md_files) - 1:
                    next_file = md_files[i + 1]
                    next_link = f'<a href="{next_file}">{next_file} →</a>'
                
                if i > 0 or i < len(md_files) - 1:
                    footer = f'\n\n---\n<div style="display: flex; justify-content: space-between;">\n    {prev_link}\n    {next_link}\n</div>'
                    new_content = base_content + footer
                else:
                    new_content = base_content

                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                    
            print(f"  ✅ Processed {len(md_files)} files in: {folder_name}")
            
    if processed_folders == 0:
        print("⚠️ No subfolders containing markdown files were found.")
    else:
        print("\n🎉 All done! Your natural-order navigation footers are updated.")

if __name__ == "__main__":
    generate_footers(TARGET_DIR)