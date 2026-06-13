import os
import re

# ==============================================================================
# HARDCODED CONFIGURATION
# ==============================================================================
TARGET_DIR = r"D:\Github\Programming-DSA\Codetin"
# ==============================================================================

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', s)]

def clean_existing_footer(content):
    """Wipes out any previously generated footers (flexbox, tables, or p-tags)."""
    pattern = r'\n+---\n+(?:<div style="display: flex; justify-content: space-between;">[\s\S]*?</div>|<table width="100%">[\s\S]*?</table>|<p align="left">[\s\S]*?</p>)\n*$'
    return re.sub(pattern, '', content).strip()

def generate_footers(root_path):
    if not os.path.exists(root_path):
        print(f"❌ Error: The path '{root_path}' does not exist.")
        return
    
    print(f"🔄 Processing clean website footers in: {root_path}\n")
    processed_folders = 0

    for folder_name in os.listdir(root_path):
        folder_path = os.path.join(root_path, folder_name)
        
        if os.path.isdir(folder_path) and not folder_name.startswith('.'):
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
                
                if i < len(md_files) - 1:
                    next_file = md_files[i + 1]
                    next_link = f'<a href="{next_file}">{next_file} →</a>'
                
                if i > 0 or i < len(md_files) - 1:
                    # Pure HTML alignment attributes. No CSS style strings to get blocked,
                    # and no table tags to force ugly borders.
                    # Setting next_link to float right cleanly splits them on the line.
                    footer = (
                        f'\n\n---\n'
                        f'<p align="right">\n'
                        f'  <span style="float: left;">{prev_link}</span>\n'
                        f'  {next_link}\n'
                        f'</p>'
                    )
                    
                    # Alternative absolute fallback if GitHub strips the float:
                    # Separate block paragraphs that force alignment natively
                    footer = f'\n\n---\n<p align="left">{prev_link}</p>\n<p align="right" style="margin-top: -30px;">{next_link}</p>'
                    
                    # Let's use the most bulletproof native approach that bypasses all CSS sanitizers:
                    footer = (
                        f'\n\n---\n'
                        f'<p align="left">{prev_link}</p>\n'
                        f'<p align="right" style="margin-top:-2.4em;">{next_link}</p>'
                    )
                else:
                    new_content = base_content

                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(base_content + footer if (i > 0 or i < len(md_files) - 1) else base_content)
                    
            print(f"  ✅ Processed {len(md_files)} files in: {folder_name}")
            
    if processed_folders == 0:
        print("⚠️ No subfolders containing markdown files were found.")
    else:
        print("\n🎉 Footers updated successfully! Push to GitHub to view the clean design.")

if __name__ == "__main__":
    generate_footers(TARGET_DIR)