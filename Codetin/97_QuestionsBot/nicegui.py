import Tkinter as tk
import tkMessageBox
import random
import datetime
import os
import json

QUESTION_FOLDER = "D:\Nexteer\Codetin\97_QuestionsBot\questionBank"
LOG_FILE = os.path.join(QUESTION_FOLDER, "performance_log.json")

# --- Load questions ---
def load_questions():
    questions = {}
    if not os.path.exists(QUESTION_FOLDER):
        print("Folder '%s' does not exist!" % QUESTION_FOLDER)
        return questions
    
    for filename in os.listdir(QUESTION_FOLDER):
        if filename.endswith(".txt"):
            section_name = os.path.splitext(filename)[0]
            path = os.path.join(QUESTION_FOLDER, filename)
            with open(path, "r") as f:
                content = f.read()
            qs = [q.strip() for q in content.split("##") if q.strip()]
            questions[section_name] = qs
    return questions

questions = load_questions()
if not questions:
    print("No questions loaded. Exiting.")
    exit(1)

performance = {section: {"known": 0, "total": 0} for section in questions.keys()}

# --- Scrollable frame class ---
class ScrollableFrame(tk.Frame):
    """A scrollable frame using Canvas"""
    def __init__(self, parent, width=500, height=200):
        tk.Frame.__init__(self, parent)
        self.canvas = tk.Canvas(self, borderwidth=0, background="#f1f3f4", width=width, height=height)
        self.frame = tk.Frame(self.canvas, background="#f1f3f4")
        self.vsb = tk.Scrollbar(self, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=self.vsb.set)

        self.vsb.pack(side="right", fill="y")
        self.canvas.pack(side="left", fill="both", expand=True)
        self.canvas.create_window((0,0), window=self.frame, anchor="nw", tags="self.frame")

        self.frame.bind("<Configure>", self.onFrameConfigure)
        self.canvas.bind_all("<MouseWheel>", self.onMouseWheel)

    def onFrameConfigure(self, event):
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))

    def onMouseWheel(self, event):
        self.canvas.yview_scroll(-1*(event.delta/120), "units")

# --- Main bot ---
class MockInterviewBot(object):
    def __init__(self, master):
        self.master = master
        self.master.title("Mock Interview Bot")
        self.master.geometry("600x600")
        self.master.configure(bg="#f1f3f4")  # Chrome-like gray

        # Header
        tk.Label(master, text="Mock Interview Bot", font=("Arial", 20, "bold"), bg="#f1f3f4", fg="#202124").pack(pady=10)

        # Instructions
        tk.Label(master, text="Enter number of questions for each section:", font=("Arial", 12), bg="#f1f3f4", fg="#5f6368").pack(pady=5)

        # Scrollable frame for section entries
        self.scroll_frame = ScrollableFrame(master, width=550, height=250)
        self.scroll_frame.pack(pady=5)

        self.section_entries = {}
        for section in questions.keys():
            frame = tk.Frame(self.scroll_frame.frame, bg="#f1f3f4")
            frame.pack(fill=tk.X, pady=2, padx=10)
            tk.Label(frame, text=section+":", width=25, anchor="w", font=("Arial", 11), bg="#f1f3f4", fg="#202124").pack(side=tk.LEFT)
            entry = tk.Entry(frame, width=5, font=("Arial", 11), relief=tk.FLAT, bg="white")
            entry.pack(side=tk.LEFT)
            self.section_entries[section] = entry

        # Start button
        self.start_button = tk.Button(master, text="Start Interview", font=("Arial", 12, "bold"), bg="#1a73e8", fg="white", relief=tk.FLAT, command=self.start_interview)
        self.start_button.pack(pady=10, ipadx=10, ipady=5)

        # Question display
        self.question_label = tk.Label(master, text="", wraplength=540, font=("Arial", 14), bg="white", relief=tk.GROOVE, bd=2, padx=10, pady=10, justify=tk.LEFT, fg="#202124")
        self.question_label.pack(padx=20, pady=15, fill=tk.BOTH, expand=True)

        # Buttons frame
        self.buttons_frame = tk.Frame(master, bg="#f1f3f4")
        self.buttons_frame.pack(pady=10)

        self.known_button = tk.Button(self.buttons_frame, text="I Knew This", font=("Arial", 12), bg="#1a73e8", fg="white", relief=tk.FLAT, width=15, command=lambda: self.log_answer(True), state=tk.DISABLED)
        self.known_button.pack(side=tk.LEFT, padx=15, ipadx=5, ipady=5)

        self.unknown_button = tk.Button(self.buttons_frame, text="I Didn't Know", font=("Arial", 12), bg="#d93025", fg="white", relief=tk.FLAT, width=15, command=lambda: self.log_answer(False), state=tk.DISABLED)
        self.unknown_button.pack(side=tk.RIGHT, padx=15, ipadx=5, ipady=5)

        # Interview state
        self.questions_queue = []
        self.current_question = None

    # --- Core functions ---
    def start_interview(self):
        self.questions_queue = []
        for section, entry in self.section_entries.items():
            try:
                num_q = int(entry.get())
            except ValueError:
                tkMessageBox.showerror("Error", "Please enter a valid number for section '%s'" % section)
                return
            if len(questions[section]) > 0:
                self.questions_queue += random.sample(questions[section], min(num_q, len(questions[section])))
        
        if not self.questions_queue:
            tkMessageBox.showerror("Error", "No questions selected to start.")
            return
        
        random.shuffle(self.questions_queue)
        self.next_question()

    def next_question(self):
        if not self.questions_queue:
            tkMessageBox.showinfo("Interview Completed", "You've completed all questions!")
            self.show_performance()
            self.question_label.config(text="")
            self.known_button.config(state=tk.DISABLED)
            self.unknown_button.config(state=tk.DISABLED)
            return
        
        self.current_question = self.questions_queue.pop(0)
        self.current_section = [sec for sec, qs in questions.items() if self.current_question in qs][0]
        self.question_label.config(text="%s:\n\n%s" % (self.current_section, self.current_question))
        self.known_button.config(state=tk.NORMAL)
        self.unknown_button.config(state=tk.NORMAL)

    def log_answer(self, knew):
        if knew:
            performance[self.current_section]["known"] += 1
        performance[self.current_section]["total"] += 1
        self.next_question()

    # --- Performance ---
    def show_performance(self):
        result = "Performance Summary:\n\n"
        percentages = {}
        for section, stats in performance.items():
            total = stats["total"]
            known = stats["known"]
            percent = (known/float(total)*100) if total > 0 else 0
            percentages[section] = percent
            if total > 0:
                result += "%s: %d/%d known (%.1f%%)\n" % (section, known, total, percent)
        tkMessageBox.showinfo("Performance", result)
        self.save_to_json(percentages)

    def save_to_json(self, percentages):
        today = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Only log attempted sections
        attempted_scores = {sec: pct for sec, pct in percentages.items() if performance[sec]["total"] > 0}
        if not attempted_scores:
            return

        log_entry = {"date": today, "scores": attempted_scores}

        if not os.path.exists(QUESTION_FOLDER):
            os.makedirs(QUESTION_FOLDER)

        if os.path.exists(LOG_FILE):
            with open(LOG_FILE, "r") as f:
                try:
                    log_data = json.load(f)
                except ValueError:
                    log_data = []
        else:
            log_data = []

        log_data.append(log_entry)

        with open(LOG_FILE, "w") as f:
            json.dump(log_data, f, indent=4, ensure_ascii=False)

# --- Run GUI ---
root = tk.Tk()
app = MockInterviewBot(root)
root.mainloop()
