"""
offline_mock_interviewer.py
Fully offline mock interviewer using your study folder at /content/
"""

import os
from transformers import pipeline
from gpt4all import GPT4All

# ---------- CONFIG ----------
FOLDER_PATH = "/content/"  # Your folder path
MODEL_PATH = "/content/models/ggml-gpt4all-j-v1.3-groovy.bin"  # Local GPT4All model
SUMMARIZER_MODEL = "sshleifer/distilbart-cnn-12-6"  # Small offline summarization model

# ---------- LOAD FILES ----------
def load_files(folder_path):
    files_data = {}
    for filename in os.listdir(folder_path):
        filepath = os.path.join(folder_path, filename)
        if os.path.isfile(filepath) and filename.endswith(('.md','.txt','.c','.cpp')):
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                files_data[filename] = f.read()
    return files_data

# ---------- SUMMARIZE NOTES ----------
def summarize_text(text, summarizer):
    summary = summarizer(text, max_length=150, min_length=50, do_sample=False)
    return summary[0]['summary_text']

# ---------- GENERATE QUESTIONS ----------
def generate_questions(summary, model):
    prompt = f"Create 3 interview questions from this summary:\n{summary}"
    questions = model.generate(prompt, max_tokens=500)
    return questions

# ---------- INTERACTIVE INTERVIEW ----------
def interview_loop(questions_dict, model):
    for file, questions in questions_dict.items():
        print(f"\n--- Interview from {file} ---")
        question_list = questions.split('\n')
        for q in question_list:
            if not q.strip():
                continue
            print("\nQuestion:", q)
            answer = input("Your answer: ")
            eval_prompt = f"Question: {q}\nAnswer: {answer}\nEvaluate this answer and provide constructive feedback."
            feedback = model.generate(eval_prompt, max_tokens=500)
            print("Feedback:", feedback)

# ---------- MAIN ----------
def main():
    print("Loading files...")
    files_data = load_files(FOLDER_PATH)
    print(f"Loaded {len(files_data)} files.")

    print("Loading summarizer...")
    summarizer = pipeline("summarization", model=SUMMARIZER_MODEL)

    print("Loading offline GPT4All model...")
    gpt_model = GPT4All(MODEL_PATH, model_type="llama")  # Fully offline

    # Summarize notes and generate questions
    questions_dict = {}
    for filename, content in files_data.items():
        if filename.endswith(('.md', '.txt')):
            print(f"Summarizing {filename}...")
            summary = summarize_text(content, summarizer)
            questions = generate_questions(summary, gpt_model)
            questions_dict[filename] = questions
        elif filename.endswith(('.c','.cpp')):
            questions_dict[filename] = f"Explain what this code does:\n{content}\nAlso mention any potential bugs or improvements."

    # Start interactive interview
    interview_loop(questions_dict, gpt_model)

if __name__ == "__main__":
    main()
