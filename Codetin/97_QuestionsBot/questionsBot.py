import Tkinter as tk
import tkMessageBox
import random
import datetime
import os
import json

QUESTION_FOLDER = "D:\Nexteer\Codetin\97_QuestionsBot\questionBank"
LOG_FILE = os.path.join(QUESTION_FOLDER, "performance_log.json")  # store log inside questionBank

# Load questions from folder
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

class MockInterviewBot(object):
    def __init__(self, master):
        self.master = master
        self.master.title("Mock Interview Bot")
        
        tk.Label(master, text="Enter number of questions for each section:").pack(pady=5)

        self.section_entries = {}
        for section in questions.keys():
            frame = tk.Frame(master)
            frame.pack(pady=2)
            tk.Label(frame, text=section + ":").pack(side=tk.LEFT)
            entry = tk.Entry(frame, width=5)
            entry.pack(side=tk.LEFT)
            self.section_entries[section] = entry
        
        self.start_button = tk.Button(master, text="Start Interview", command=self.start_interview)
        self.start_button.pack(pady=10)
        
        self.question_label = tk.Label(master, text="", wraplength=400, font=("Arial", 14))
        self.question_label.pack(pady=20)
        
        self.known_button = tk.Button(master, text="I knew this", command=lambda: self.log_answer(True), state=tk.DISABLED)
        self.known_button.pack(side=tk.LEFT, padx=20)
        
        self.unknown_button = tk.Button(master, text="I didn't know", command=lambda: self.log_answer(False), state=tk.DISABLED)
        self.unknown_button.pack(side=tk.RIGHT, padx=20)
        
        self.questions_queue = []
        self.current_question = None

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

    def show_performance(self):
        result = "Performance Summary:\n\n"
        percentages = {}
        for section, stats in performance.items():
            total = stats["total"]
            known = stats["known"]
            percent = (known/float(total)*100) if total > 0 else 0
            percentages[section] = percent
            result += "%s: %d/%d known (%.1f%%)\n" % (section, known, total, percent)
        tkMessageBox.showinfo("Performance", result)
        self.save_to_json(percentages)

    def save_to_json(self, percentages):
        today = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_entry = {"date": today, "scores": percentages}

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
            json.dump(log_data, f, indent=4)

# Run GUI
root = tk.Tk()
app = MockInterviewBot(root)
root.mainloop()
