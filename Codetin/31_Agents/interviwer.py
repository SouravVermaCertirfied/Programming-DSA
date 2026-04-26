import ollama
import os
import time

# Configuration
DIRECTORY_PATH = r"D:\Github\Programming-DSA\Codetin"  # Change to your folder
EXTENSIONS = {'.c', '.cpp', '.md'}
MODEL = 'gemma4:e4b'

# High-fidelity prompt to prevent information loss
REVISION_PROMPT_TEMPLATE = """
Act as an expert technical archivist. Your task is to transform the provided file into detailed interview revision notes.

CRITICAL INSTRUCTION: DO NOT OMIT technical details. Ensure zero information loss regarding logic, edge cases, and specific syntax mentioned.

Structure your response as follows:
1. **Comprehensive Topic Overview**: What is this file teaching?
2. **Technical Deep-Dive**: Break down every function, logic block, or note entry found in the file. Explain the 'how' and 'why'.
3. **Memory & Performance**: Mention time/space complexity or memory management details present.
4. **Interview Criticals**: Based on the content, what are the most likely questions an interviewer would ask?
5. **Exact Syntax/Snippet**: Keep the most crucial code logic for quick memorization.

FILE CONTENT:
{content}
"""

def generate_revision_notes(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        # Checking if file is empty to save time/VRAM
        if not content.strip():
            return "File is empty."

        response = ollama.chat(model=MODEL, messages=[
            {'role': 'system', 'content': 'You are a technical expert that provides exhaustive, high-fidelity technical notes with no information loss.'},
            {'role': 'user', 'content': REVISION_PROMPT_TEMPLATE.format(content=content)},
        ])
        return response['message']['content']
    except Exception as e:
        return f"Error processing {file_path}: {e}"

def main():
    start_time = time.time()
    file_count = 0
    output_filename = "Full_Detail_Interview_Guide.md"

    if not os.path.exists(DIRECTORY_PATH):
        print("Error: Root directory not found.")
        return

    with open(output_filename, "w", encoding='utf-8') as output_file:
        output_file.write(f"# MASTER INTERVIEW REVISION GUIDE (Full Fidelity)\n")
        output_file.write(f"Created: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        output_file.write(f"Model used: {MODEL}\n\n")

        for root, dirs, files in os.walk(DIRECTORY_PATH):
            valid_files = [f for f in files if os.path.splitext(f)[1].lower() in EXTENSIONS]
            
            if valid_files:
                folder_name = os.path.basename(root)
                output_file.write(f"\n# CHAPTER: {folder_name.upper()}\n")
                output_file.write(f"Source Folder: `{root}`\n")
                output_file.write("-" * 40 + "\n\n")

                for filename in sorted(valid_files):
                    print(f"Analyzing [{folder_name}] -> {filename}...")
                    file_path = os.path.join(root, filename)
                    
                    notes = generate_revision_notes(file_path)
                    
                    output_file.write(f"## SECTION: {filename}\n")
                    output_file.write(notes + "\n\n")
                    output_file.write("---" * 10 + "\n\n")
                    file_count += 1

    duration = time.time() - start_time
    
    print("\n" + "="*40)
    print("REVISION GUIDE GENERATED")
    print(f"Total Execution Time: {duration:.2f} seconds")
    print(f"Total Files Processed: {file_count}")
    print(f"Average Speed: {duration/max(1, file_count):.2f} sec/file")
    print(f"File Saved: {output_filename}")
    print("="*40)

if __name__ == "__main__":
    main()