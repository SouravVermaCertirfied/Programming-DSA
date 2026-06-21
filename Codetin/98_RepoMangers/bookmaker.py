import os
import re
import markdown2
from reportlab.lib.pagesizes import letter
from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.enums import TA_LEFT
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle, PageBreak

# --- ABSOLUTE PATH CONFIGURATION ---
NOTES_DIR = r"D:\Github\Programming-DSA\Codetin"
OUTPUT_DIR = r"D:\Github\Programming-DSA\Codetin\95_rough"
OUTPUT_PDF = os.path.join(OUTPUT_DIR, "Codetin_Notes_Book.pdf")

def create_preview_styles():
    """Generates a clean, GitHub-flavored preview typography map."""
    styles = getSampleStyleSheet()
    
    # Custom Light Theme / Markdown Preview styles
    styles.add(ParagraphStyle(
        name='MarkdownBody',
        fontName='Helvetica',
        fontSize=10,
        leading=15,
        textColor=colors.HexColor('#333333'),
        spaceAfter=10
    ))
    
    styles.add(ParagraphStyle(
        name='MarkdownH1',
        fontName='Helvetica-Bold',
        fontSize=20,
        leading=26,
        textColor=colors.HexColor('#111111'),
        spaceBefore=18,
        spaceAfter=12,
        keepWithNext=True
    ))

    styles.add(ParagraphStyle(
        name='MarkdownH2',
        fontName='Helvetica-Bold',
        fontSize=15,
        leading=20,
        textColor=colors.HexColor('#222222'),
        spaceBefore=14,
        spaceAfter=8,
        keepWithNext=True
    ))

    styles.add(ParagraphStyle(
        name='MarkdownH3',
        fontName='Helvetica-Bold',
        fontSize=12,
        leading=16,
        textColor=colors.HexColor('#333333'),
        spaceBefore=12,
        spaceAfter=6,
        keepWithNext=True
    ))

    styles.add(ParagraphStyle(
        name='MarkdownCodeBlock',
        fontName='Courier',
        fontSize=9,
        leading=13,
        textColor=colors.HexColor('#24292e'),
        backColor=colors.HexColor('#f6f8fa'),
        borderColor=colors.HexColor('#e1e4e8'),
        borderWidth=1,
        borderPadding=8,
        spaceBefore=8,
        spaceAfter=8,
        textTransform=None
    ))

    styles.add(ParagraphStyle(
        name='MarkdownInlineCode',
        fontName='Courier',
        fontSize=9.5,
        leading=12,
        textColor=colors.HexColor('#dd1144'),
        backColor=colors.HexColor('#f8f8f8')
    ))
    
    styles.add(ParagraphStyle(
        name='FolderChapter',
        fontName='Helvetica-Bold',
        fontSize=24,
        leading=30,
        textColor=colors.HexColor('#0056b3'),
        spaceBefore=30,
        spaceAfter=20
    ))
    
    return styles

def clean_html_tags(text):
    """Strips raw HTML cleanly to maintain text integrity in paragraphs."""
    text = re.sub(r'<code>(.*?)</code>', r'<font face="Courier" color="#dd1144" backColor="#f8f8f8">\1</font>', text)
    text = text.replace('<p>', '').replace('</p>', '\n')
    text = text.replace('<strong>', '<b>').replace('</strong>', '</b>')
    text = text.replace('<em>', '<i>').replace('</em>', '</i>')
    return text.strip()

def parse_html_to_flowables(html_text, styles):
    """Converts rendered markdown html string blocks safely to ReportLab elements."""
    flowables = []
    
    # Simple line-by-line block evaluation
    blocks = re.split(r'(<h1>.*?</h1>|<h2>.*?</h2>|<h3>.*?</h3>|<pre>.*?</pre>)', html_text, flags=re.DOTALL)
    
    for block in blocks:
        block = block.strip()
        if not block:
            continue
            
        if block.startswith('<h1>'):
            txt = re.sub('<[^<]+?>', '', block)
            flowables.append(Paragraph(txt, styles['MarkdownH1']))
        elif block.startswith('<h2>'):
            txt = re.sub('<[^<]+?>', '', block)
            flowables.append(Paragraph(txt, styles['MarkdownH2']))
        elif block.startswith('<h3>'):
            txt = re.sub('<[^<]+?>', '', block)
            flowables.append(Paragraph(txt, styles['MarkdownH3']))
        elif block.startswith('<pre>'):
            # Code block preservation logic
            txt = re.sub('<[^<]+?>', '', block)
            flowables.append(Paragraph(txt.replace('\n', '<br/>'), styles['MarkdownCodeBlock']))
        else:
            cleaned = clean_html_tags(block)
            if cleaned:
                for line in cleaned.split('\n'):
                    if line.strip():
                        flowables.append(Paragraph(line, styles['MarkdownBody']))
                        
    return flowables

def build_pdf():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)
        print(f"📁 Target Output Directory Ready: {OUTPUT_DIR}")

    styles = create_preview_styles()
    doc = SimpleDocTemplate(OUTPUT_PDF, pagesize=letter, leftMargin=54, rightMargin=54, topMargin=54, bottomMargin=54)
    story = []

    print(f"📚 Indexing files inside: {NOTES_DIR}")
    
    for root, dirs, files in os.walk(NOTES_DIR):
        if os.path.commonpath([root, OUTPUT_DIR]) == OUTPUT_DIR:
            continue
            
        dirs.sort()
        files.sort()
        
        rel_path = os.path.relpath(root, NOTES_DIR)
        if rel_path != ".":
            folder_name = os.path.basename(root).replace("_", " ").title()
            story.append(PageBreak())
            story.append(Paragraph(f"📁 Directory: {folder_name}", styles['FolderChapter']))
            story.append(Spacer(1, 15))

        for file in files:
            if file.endswith(".md"):
                file_path = os.path.join(root, file)
                
                with open(file_path, "r", encoding="utf-8") as f:
                    content = f.read()
                
                title = file.replace(".md", "").replace("_", " ").title()
                story.append(Paragraph(title, styles['MarkdownH1']))
                
                # Use markdown2 standard pure parser configuration
                html_raw = markdown2.markdown(content, extras=["fenced-code-blocks", "cuddled-lists"])
                elements = parse_html_to_flowables(html_raw, styles)
                story.extend(elements)
                story.append(Spacer(1, 10))

    print("🎨 Safely rendering PDF compiled book matrix...")
    doc.build(story)
    print(f"✨ Finished successfully! Output path:\n👉 {OUTPUT_PDF}")

if __name__ == "__main__":
    build_pdf()