import tkinter as tk
from tkinter import ttk, messagebox
import os
import random
import json
from datetime import datetime

# ---------------- Constants ---------------- #
QUESTION_FOLDER = r"D:\Nexteer\Codetin\97_QuestionsBot\questionBank"
LOG_FILE = "performance_log.json"
QUESTION_TIME_LIMIT = 60  # seconds per question
BG_COLOR = "#ffffff"
CARD_COLOR = "#f5f5f5"
BUTTON_COLOR = "#007bff"
BUTTON_HOVER = "#0056b3"
TEXT_COLOR = "#333333"
FONT = ("Helvetica", 12)
CARD_PADDING = 10

# ---------------- Helper Functions ---------------- #
def load_questions():
    """Load questions from questionBank folder."""
    sections = {}
    for file in os.listdir(QUESTION_FOLDER):
        if file.endswith(".txt"):
            section_name = os.path.splitext(file)[0]
            with open(os.path.join(QUESTION_FOLDER, file), "r", encoding="utf-8") as f:
                content = f.read()
                questions = [q.strip() for q in content.split("##") if q.strip()]
                sections[section_name] = questions
    return sections

def save_performance(log_data):
    """Save performance to JSON file."""
    if os.path.exists(LOG_FILE):
        with open(LOG_FILE, "r", encoding="utf-8") as f:
            data = json.load(f)
    else:
        data = []
    data.append(log_data)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=4)

# ---------------- Main Application ---------------- #
class QuizBotApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Quiz Bot")
        self.geometry("700x500")
        self.configure(bg=BG_COLOR)
        self.sections = load_questions()
        self.quiz_data = {}  # {section: [questions]}
        self.user_inputs = {}  # {section: num_questions}
        self.performance = {}
        self.current_section = None
        self.current_question_index = 0
        self.total_questions = 0
        self.master_time = 0
        self.question_time_left = QUESTION_TIME_LIMIT
        self.create_setup_screen()

    # ---------------- Setup Screen ---------------- #
    def create_setup_screen(self):
        self.clear_screen()
        tk.Label(self, text="Select Number of Questions per Section", font=("Helvetica", 16, "bold"), bg=BG_COLOR).pack(pady=10)

        # Scrollable Frame
        container = ttk.Frame(self)
        canvas = tk.Canvas(container, bg=BG_COLOR, highlightthickness=0)
        scrollbar = ttk.Scrollbar(container, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)

        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )

        canvas.create_window((0,0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        container.pack(fill="both", expand=True)
        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

        self.section_entries = {}

        for section, questions in self.sections.items():
            card = tk.Frame(scrollable_frame, bg=CARD_COLOR, padx=CARD_PADDING, pady=CARD_PADDING)
            tk.Label(card, text=section, font=("Helvetica", 14, "bold"), bg=CARD_COLOR).pack(side="left", padx=5)
            entry_var = tk.StringVar(value=str(len(questions)))
            entry = tk.Entry(card, textvariable=entry_var, width=5, font=FONT)
            entry.pack(side="right", padx=5)
            card.pack(pady=5, fill="x", padx=20)
            self.section_entries[section] = entry_var

        start_btn = tk.Button(self, text="Start Quiz", bg=BUTTON_COLOR, fg="white", font=FONT, command=self.start_quiz)
        start_btn.pack(pady=10)

    # ---------------- Start Quiz ---------------- #
    def start_quiz(self):
        # Validate input and prepare quiz data
        self.user_inputs = {}
        for section, var in self.section_entries.items():
            try:
                num = int(var.get())
                if num < 1 or num > len(self.sections[section]):
                    raise ValueError
                self.user_inputs[section] = num
            except ValueError:
                messagebox.showerror("Invalid Input", f"Enter a valid number of questions for {section}")
                return

        # Prepare quiz questions
        self.quiz_data = {}
        self.total_questions = 0
        for section, num in self.user_inputs.items():
            questions = random.sample(self.sections[section], num)
            self.quiz_data[section] = questions
            self.total_questions += num

        self.performance = {section: {"known":0, "total":len(qs), "questions":[]} for section, qs in self.quiz_data.items()}

        # Initialize quiz state
        self.master_time = 0
        self.section_list = list(self.quiz_data.keys())
        self.current_section_index = 0
        self.current_question_index = 0

        self.create_quiz_screen()

    # ---------------- Quiz Screen ---------------- #
    def create_quiz_screen(self):
        self.clear_screen()
        self.current_section = self.section_list[self.current_section_index]
        self.current_question = self.quiz_data[self.current_section][self.current_question_index]

        # Section Label
        tk.Label(self, text=f"Section: {self.current_section}", font=("Helvetica", 16, "bold"), bg=BG_COLOR).pack(pady=10)

        # Question Card
        card = tk.Frame(self, bg=CARD_COLOR, padx=CARD_PADDING, pady=CARD_PADDING)
        tk.Label(card, text=self.current_question, wraplength=600, font=FONT, bg=CARD_COLOR).pack()
        card.pack(pady=20, padx=20, fill="both", expand=True)

        # Timer
        self.timer_label = tk.Label(self, text=f"Time Left: {self.question_time_left} s", font=FONT, bg=BG_COLOR, fg="red")
        self.timer_label.pack()

        # Buttons
        btn_frame = tk.Frame(self, bg=BG_COLOR)
        btn_frame.pack(pady=10)
        knew_btn = tk.Button(btn_frame, text="I knew this", bg=BUTTON_COLOR, fg="white", font=FONT, command=lambda: self.answer(True))
        didnt_btn = tk.Button(btn_frame, text="I didn’t know", bg=BUTTON_COLOR, fg="white", font=FONT, command=lambda: self.answer(False))
        knew_btn.pack(side="left", padx=10)
        didnt_btn.pack(side="left", padx=10)

        # Start timers
        self.question_time_left = QUESTION_TIME_LIMIT
        self.update_timer()
        self.update_master_timer()

    # ---------------- Timer Updates ---------------- #
    def update_timer(self):
        if self.question_time_left > 0:
            self.timer_label.config(text=f"Time Left: {self.question_time_left} s")
            self.question_time_left -= 1
            self.after(1000, self.update_timer)
        else:
            self.answer(False)  # Auto move to next if time expires

    def update_master_timer(self):
        self.master_time += 1
        self.after(1000, self.update_master_timer)

    # ---------------- Handle Answer ---------------- #
    def answer(self, knew):
        section_perf = self.performance[self.current_section]
        section_perf["questions"].append({
            "question": self.current_question,
            "knew": knew,
            "time_taken": QUESTION_TIME_LIMIT - self.question_time_left
        })
        if knew:
            section_perf["known"] += 1

        # Move to next question
        if self.current_question_index + 1 < len(self.quiz_data[self.current_section]):
            self.current_question_index += 1
        else:
            if self.current_section_index + 1 < len(self.section_list):
                self.current_section_index += 1
                self.current_section = self.section_list[self.current_section_index]
                self.current_question_index = 0
            else:
                self.show_summary()
                return
        self.create_quiz_screen()

    # ---------------- Summary Screen ---------------- #
    def show_summary(self):
        self.clear_screen()
        tk.Label(self, text="Quiz Summary", font=("Helvetica", 18, "bold"), bg=BG_COLOR).pack(pady=10)

        for section, data in self.performance.items():
            tk.Label(self, text=f"{section}: {data['known']}/{data['total']} known ({data['known']/data['total']*100:.1f}%)", font=("Helvetica", 14), bg=BG_COLOR).pack(pady=5)
            for q in data["questions"]:
                tk.Label(self, text=f"- {q['question']} | Knew: {q['knew']} | Time: {q['time_taken']}s", font=("Helvetica", 10), bg=BG_COLOR, wraplength=650, anchor="w", justify="left").pack(padx=20, anchor="w")

        # Save performance
        log_data = {
            "timestamp": datetime.now().isoformat(),
            "performance": self.performance,
            "total_time": self.master_time
        }
        save_performance(log_data)

        tk.Button(self, text="Close", bg=BUTTON_COLOR, fg="white", font=FONT, command=self.destroy).pack(pady=10)

    # ---------------- Utility ---------------- #
    def clear_screen(self):
        for widget in self.winfo_children():
            widget.destroy()

# ---------------- Run Application ---------------- #
if __name__ == "__main__":
    app = QuizBotApp()
    app.mainloop()
