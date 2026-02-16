import os
import re
from html import escape

# =====================================================
# HARDCODED PATHS
# =====================================================
SRC_DIR = r"D:\Nexteer\Codetin\01_C"
DEST_HTML = r"D:\Nexteer\Codetin\98_RepoMangers\out.html"

# =====================================================
# HELPERS
# =====================================================
def slugify(text):
    return re.sub(r"[^a-zA-Z0-9]+", "-", text.lower()).strip("-")

def parse_markdown(md_text, file_slug):
    html = []
    nav = []
    in_code = False
    in_list = False
    in_table = False
    table_rows = []

    for line in md_text.splitlines():
        line_strip = line.strip()

        # Fenced code blocks
        if line_strip.startswith("```"):
            if not in_code:
                html.append("<pre><code>")
                in_code = True
            else:
                html.append("</code></pre>")
                in_code = False
            continue

        if in_code:
            html.append(escape(line))
            continue

        # Tables: simple pipe | table
        if "|" in line_strip and not line_strip.startswith("#"):
            cells = [c.strip() for c in line_strip.split("|")]
            if not in_table:
                in_table = True
                table_rows.append("<table>")
            table_rows.append("<tr>" + "".join(f"<td>{escape(c)}</td>" for c in cells if c) + "</tr>")
            continue
        else:
            if in_table:
                table_rows.append("</table>")
                html.extend(table_rows)
                table_rows = []
                in_table = False

        # Headings
        m = re.match(r"(#{1,6})\s+(.*)", line)
        if m:
            level = len(m.group(1))
            text = m.group(2).strip()
            hid = f"{file_slug}-{slugify(text)}"
            html.append(f'<h{level} id="{hid}">{escape(text)}</h{level}>')
            nav.append((level, text, hid))
            continue

        # Lists
        if line_strip.startswith("- "):
            if not in_list:
                html.append("<ul>")
                in_list = True
            html.append(f"<li>{escape(line_strip[2:])}</li>")
            continue
        else:
            if in_list:
                html.append("</ul>")
                in_list = False

        # Inline formatting
        line = escape(line)
        line = re.sub(r"\*\*(.+?)\*\*", r"<strong>\1</strong>", line)
        line = re.sub(r"\*(.+?)\*", r"<em>\1</em>", line)
        line = re.sub(r"`(.+?)`", r"<code>\1</code>", line)
        line = re.sub(r"\[(.+?)\]\((.+?)\)", r'<a href="\2">\1</a>', line)

        if line_strip:
            html.append(f"<p>{line}</p>")

    # Close open lists/tables
    if in_list:
        html.append("</ul>")
    if in_table:
        table_rows.append("</table>")
        html.extend(table_rows)

    return "\n".join(html), nav

# =====================================================
# PROCESS FILES
# =====================================================
sections_html = []
nav_html = []

md_files = sorted(f for f in os.listdir(SRC_DIR) if f.endswith(".md"))

for idx, filename in enumerate(md_files):
    file_path = os.path.join(SRC_DIR, filename)
    file_title = os.path.splitext(filename)[0].replace("_", " ").title()
    file_slug = f"file-{idx}"

    with open(file_path, "r", encoding="utf-8") as f:
        md_text = f.read()

    content_html, headings = parse_markdown(md_text, file_slug)

    nav_html.append(f'<li class="file-title">{escape(file_title)}</li>')
    for level, text, hid in headings:
        indent = (level - 1) * 12
        nav_html.append(f'<li style="margin-left:{indent}px"><a href="#{hid}">{escape(text)}</a></li>')

    sections_html.append(f'<section class="content-section"><h1>{escape(file_title)}</h1>{content_html}</section>')

# =====================================================
# HTML TEMPLATE (LIGHT THEME, TABLES & CODE FIX)
# =====================================================
html_template = """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>My Notes</title>
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
:root {{
  --bg: #fefefe;
  --panel: #f0f0f0;
  --text: #111111;
  --muted: #555555;
  --accent: #1a73e8;
  --border: #cccccc;
  --code-bg: #eaeaea;
}}

body {{
  margin: 0;
  background: var(--bg);
  color: var(--text);
  font-family: system-ui, sans-serif;
}}

.layout {{
  display: grid;
  grid-template-columns: 20% 80%;
  height: 100vh;
}}

nav {{
  background: var(--panel);
  border-right: 1px solid var(--border);
  padding: 1rem;
  overflow-y: auto;
}}

nav ul {{
  list-style: none;
  padding: 0;
}}

nav li {{
  margin: 0.3rem 0;
}}

nav a {{
  color: var(--muted);
  text-decoration: none;
}}

nav a.active {{
  color: var(--accent);
  font-weight: 600;
}}

.file-title {{
  margin-top: 1rem;
  font-size: 0.85rem;
  text-transform: uppercase;
  color: var(--accent);
}}

main {{
  padding: 2rem 3rem;
  overflow-y: auto;
}}

h1, h2, h3, h4 {{
  border-bottom: 1px solid var(--border);
}}

pre {{
  background: var(--code-bg);
  padding: 1rem;
  border-radius: 6px;
  overflow-x: auto;
}}

code {{
  font-family: ui-monospace, monospace;
  background: var(--code-bg);
  padding: 0 3px;
  border-radius: 3px;
}}

table {{
  border-collapse: collapse;
  width: 100%;
  margin: 1rem 0;
}}

table, th, td {{
  border: 1px solid var(--border);
}}

th, td {{
  padding: 0.5rem;
  text-align: left;
}}

</style>
</head>

<body>
<div class="layout">
  <nav>
    <ul>
      {nav}
    </ul>
  </nav>

  <main id="main">
    {content}
  </main>
</div>

<script>
const links = document.querySelectorAll("nav a");
const headings = document.querySelectorAll("h1, h2, h3, h4, h5");

const observer = new IntersectionObserver(entries => {{
  entries.forEach(e => {{
    if (e.isIntersecting) {{
      links.forEach(l => l.classList.remove("active"));
      const a = document.querySelector('nav a[href="#' + e.target.id + '"]');
      if (a) a.classList.add("active");
    }}
  }});
}}, {{
  root: document.querySelector("main"),
  threshold: 0.3
}});

headings.forEach(h => observer.observe(h));
</script>
</body>
</html>
"""

# =====================================================
# WRITE OUTPUT
# =====================================================
os.makedirs(os.path.dirname(DEST_HTML), exist_ok=True)
with open(DEST_HTML, "w", encoding="utf-8") as f:
    f.write(html_template.format(nav="".join(nav_html), content="".join(sections_html)))

print("✅ Light theme website generated with proper code blocks and tables:", DEST_HTML)
