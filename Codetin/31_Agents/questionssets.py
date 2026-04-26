import os
import random
import ollama

# --- CONFIGURATION ---
NOTES_FOLDER = r"D:\Github\Programming-DSA\Codetin" 
OUTPUT_FOLDER = "./qualcomm_prep_sets"
MODEL = "gemma4:e4b"
NUM_SETS = 5
FILES_PER_SET = 5

def get_all_md_files(root_folder):
    """Recursively finds all .md files in the folder and sub-folders."""
    md_files = []
    for root, dirs, files in os.walk(root_folder):
        for file in files:
            if file.endswith('.md'):
                # Store the full path so we can read it later
                md_files.append(os.path.join(root, file))
    return md_files

def generate_set(set_index, selected_file_paths):
    """Generates a Qualcomm-style interview set with Answers at the bottom."""
    questions = []
    answers = []
    
    print(f"--- Generating Set {set_index} ---")

    # Shuffle to ensure grounded/probabilistic split is randomized across file topics
    random.shuffle(selected_file_paths)

    for i, file_path in enumerate(selected_file_paths):
        file_name = os.path.basename(file_path)
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            print(f"Error reading {file_name}: {e}")
            continue

        # 70% Grounded (3 questions), 30% Probabilistic (2 questions)
        is_grounded = i < 3 
        
        if is_grounded:
            prompt = (
                f"CONTEXT FROM NOTES ({file_name}):\n{content[:3000]}\n\n"
                "TASK: Create a technical interview question that tests DEPTH of understanding of the notes above. "
                "The answer must be present in the notes. Do not ask for definitions; ask for 'why' or 'how' "
                "based on the logic provided. Format: 'Question: ... Answer: ...'"
            )
        else:
            prompt = (
                f"TOPIC: {file_name}\n\n"
                "TASK: Ignore the provided notes. Based on your knowledge as a Qualcomm Principal Engineer, "
                "ask a high-level question related to this topic that tests system optimization, "
                "memory constraints, or hardware-software interaction. Format: 'Question: ... Answer: ...'"
            )

        response = ollama.generate(
            model=MODEL,
            system="You are an expert Qualcomm Interviewer. You focus on efficiency, C++ internals, and DSA optimization.",
            prompt=prompt
        )
        
        text = response['response']
        q_label = "GROUNDED" if is_grounded else "STRETCH"
        
        # Split Question and Answer for the requested layout
        if "Answer:" in text:
            parts = text.split("Answer:", 1)
            q_text = parts[0].replace("Question:", "").strip()
            a_text = parts[1].strip()
        else:
            q_text = text
            a_text = "See model response for details (formatting split failed)."

        questions.append(f"### Q{i+1} [{q_label}] - Topic: {file_name}\n{q_text}")
        answers.append(f"### A{i+1} (Ref: {file_name})\n{a_text}")

    # Write to File
    if not os.path.exists(OUTPUT_FOLDER):
        os.makedirs(OUTPUT_FOLDER)

    output_path = os.path.join(OUTPUT_FOLDER, f"Qualcomm_Set_{set_index}.md")
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(f"# Qualcomm Interview Prep: Set {set_index}\n\n")
        f.write("## 📝 THE QUESTIONS\n\n")
        f.write("\n\n---\n\n".join(questions))
        f.write("\n\n\n---\n## 🔑 THE ANSWER KEY\n\n")
        f.write("\n\n---\n\n".join(answers))
    
    print(f"Successfully saved Set {set_index} to {output_path}")

def main():
    all_md_paths = get_all_md_files(NOTES_FOLDER)
    
    if len(all_md_paths) < FILES_PER_SET:
        print(f"Error: Only found {len(all_md_paths)} .md files in the entire tree.")
        return

    for i in range(1, NUM_SETS + 1):
        # random.sample picks from the full recursive list
        selected = random.sample(all_md_paths, FILES_PER_SET)
        generate_set(i, selected)

if __name__ == "__main__":
    main()