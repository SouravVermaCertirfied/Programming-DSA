# Point to your local Ollama server
$env:ANTHROPIC_BASE_URL="http://localhost:11434/v1"

# Use 'ollama' as a dummy key (required to bypass the login check)
$env:ANTHROPIC_AUTH_TOKEN="ollama"

---

This is a great blueprint for a high-performance, local AI workstation that keeps your SSD (C: Drive) lean. 

Here is how to replicate this setup on any Windows machine.

### Phase 1: Prepare the D: Drive (The "Do's")
**DO:** Set these up **before** installing anything to prevent files from ever touching your C: drive.
* Create these folders: `D:\npm_global` and `D:\OllamaModels`.
* Open PowerShell as **Administrator** and run these to set permanent system-wide paths:

```powershell
# 1. Force NPM to install tools on D:
npm config set prefix "D:\npm_global"

# 2. Force Ollama to store models on D:
[System.Environment]::SetEnvironmentVariable('OLLAMA_MODELS', 'D:\OllamaModels', 'User')

# 3. Add the new NPM folder to your Windows PATH (so 'claude' command works)
$oldPath = [System.Environment]::GetEnvironmentVariable('Path', 'User')
[System.Environment]::SetEnvironmentVariable('Path', "$oldPath;D:\npm_global", 'User')
```

---

### Phase 2: Installation
**DO:** Restart your terminal after Phase 1 so the new paths take effect.

```powershell
# 1. Install Claude Code globally (now goes to D:)
npm install -g @anthropic-ai/claude-code

# 2. Pull the optimized local model
ollama pull gemma4:e4b
```

---

### Phase 3: The "Local Mode" Bridge
**DO:** Set these variables so Claude Code talks to your PC instead of the cloud. Use the Windows "Environment Variables" UI to make these permanent, or run these in your session:

```powershell
# Tell Claude Code to use your local Ollama server
$env:ANTHROPIC_BASE_URL="http://localhost:11434/v1"

# Use 'ollama' as a placeholder key (bypass login)
$env:ANTHROPIC_AUTH_TOKEN="ollama"
```

---

### Phase 4: Launching
**DO:** Always `cd` into your project folder first so Claude has context!

```powershell
# Navigate to project
cd "D:\Your\Coding\Project"

# Launch the agent
claude --model gemma4:e4b
```

### 💡 Quick Summary Checklist for New PCs:
* **Storage:** HDD is fine for models, but expect a **20-second "warm-up"** when the model first loads into your RAM/GPU.
* **GPU:** Ensure you have **NVIDIA drivers** installed so Ollama can use your GPU (like your GTX 1650) instead of your CPU.
* **Shell:** **DO** install Git for Windows. Claude Code needs `bash.exe` (usually in `C:\Program Files\Git\bin\bash.exe`) to run its internal tools properly.