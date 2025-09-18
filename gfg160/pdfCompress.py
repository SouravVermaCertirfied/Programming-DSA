#!/usr/bin/env python3
"""
PDF Compression Script using PyMuPDF and Pillow
Compresses PDF files to approximately 100KB (or specified target size)

Requirements:
pip install PyMuPDF pillow

Usage:
python pdf_compressor.py
"""

import os
import pymupdf  # Also known as fitz
from PIL import Image
import io

def compress_pdf_to_target_size(input_pdf_path, output_pdf_path, target_size_kb=100):
    """
    Compress a PDF to approximately the target size using PyMuPDF and Pillow.

    This function uses iterative compression with different DPI and quality settings
    until the target file size is achieved.

    Args:
        input_pdf_path (str): Path to input PDF file
        output_pdf_path (str): Path to output compressed PDF file
        target_size_kb (int): Target file size in KB (default 100KB)

    Returns:
        bool: True if compression successful, False otherwise
    """

    target_size_bytes = target_size_kb * 1024

    # Compression levels from mild to aggressive
    # Each level reduces DPI and quality progressively
    compression_levels = [
        {'dpi': 150, 'quality': 85, 'grayscale': False},
        {'dpi': 120, 'quality': 70, 'grayscale': False},
        {'dpi': 100, 'quality': 60, 'grayscale': False},
        {'dpi': 90, 'quality': 50, 'grayscale': False},
        {'dpi': 72, 'quality': 40, 'grayscale': False},
        {'dpi': 72, 'quality': 30, 'grayscale': True},   # Start using grayscale
        {'dpi': 60, 'quality': 25, 'grayscale': True},
        {'dpi': 50, 'quality': 20, 'grayscale': True},
        {'dpi': 40, 'quality': 15, 'grayscale': True},   # Very aggressive
    ]

    try:
        # Open the input PDF document
        doc = pymupdf.open(input_pdf_path)
        print(f"Opened PDF with {len(doc)} pages")

        # Try different compression levels until target size is achieved
        for i, level in enumerate(compression_levels):
            print(f"\nTrying compression level {i+1}/{len(compression_levels)}:")
            print(f"  DPI: {level['dpi']}, Quality: {level['quality']}, Grayscale: {level['grayscale']}")

            # Create a new document for this compression attempt
            new_doc = pymupdf.open()

            # Process each page of the original document
            for page_num in range(len(doc)):
                page = doc[page_num]

                # Set colorspace (grayscale or RGB)
                colorspace = pymupdf.csGRAY if level['grayscale'] else pymupdf.csRGB

                # Create transformation matrix for DPI scaling
                # 72 DPI is the default, so we scale relative to that
                scale_factor = level['dpi'] / 72.0
                mat = pymupdf.Matrix(scale_factor, scale_factor)

                # Render page to pixmap (raster image)
                pix = page.get_pixmap(matrix=mat, colorspace=colorspace)

                # Convert PyMuPDF pixmap to PIL Image for better compression control
                img_data = pix.tobytes("png")
                pil_img = Image.open(io.BytesIO(img_data))

                # Apply additional PIL optimizations
                if level['grayscale'] and pil_img.mode != 'L':
                    pil_img = pil_img.convert('L')  # Convert to grayscale
                elif not level['grayscale'] and pil_img.mode != 'RGB':
                    pil_img = pil_img.convert('RGB')  # Ensure RGB mode

                # Compress image to JPEG with specified quality
                output_buffer = io.BytesIO()
                pil_img.save(output_buffer, 
                           format='JPEG', 
                           quality=level['quality'], 
                           optimize=True,  # Enable PIL optimizations
                           progressive=True)  # Use progressive JPEG
                output_buffer.seek(0)

                # Create new page in output document with same dimensions
                rect = page.rect
                new_page = new_doc.new_page(width=rect.width, height=rect.height)

                # Insert the compressed image into the new page
                new_page.insert_image(new_page.rect, stream=output_buffer.getvalue())

            # Save the compressed document with maximum compression options
            temp_output = output_pdf_path.replace('.pdf', '_temp.pdf')
            new_doc.save(temp_output, 
                        garbage=4,        # Maximum garbage collection (remove all unused objects)
                        deflate=True,     # Compress all streams
                        deflate_images=True,  # Compress images
                        deflate_fonts=True,   # Compress fonts
                        clean=True)       # Clean up document structure

            new_doc.close()

            # Check the resulting file size
            file_size = os.path.getsize(temp_output)
            file_size_kb = file_size / 1024

            print(f"  Result: {file_size_kb:.2f} KB")

            # If we've achieved the target size, we're done!
            if file_size <= target_size_bytes:
                os.rename(temp_output, output_pdf_path)
                doc.close()
                print(f"\n✅ Successfully compressed to {file_size_kb:.2f} KB (target: {target_size_kb} KB)")
                return True
            else:
                # Remove temporary file and try next compression level
                if os.path.exists(temp_output):
                    os.remove(temp_output)
                print(f"  Too large, trying next level...")

        # If we reach here, none of the compression levels achieved the target
        print(f"\n⚠️ Warning: Could not compress to target size of {target_size_kb}KB")
        print("Saving with most aggressive compression...")

        # Apply the most aggressive compression level as fallback
        level = compression_levels[-1]
        new_doc = pymupdf.open()

        for page_num in range(len(doc)):
            page = doc[page_num]
            colorspace = pymupdf.csGRAY if level['grayscale'] else pymupdf.csRGB
            mat = pymupdf.Matrix(level['dpi']/72, level['dpi']/72)
            pix = page.get_pixmap(matrix=mat, colorspace=colorspace)

            img_data = pix.tobytes("png")
            pil_img = Image.open(io.BytesIO(img_data))

            if level['grayscale'] and pil_img.mode != 'L':
                pil_img = pil_img.convert('L')
            elif not level['grayscale'] and pil_img.mode != 'RGB':
                pil_img = pil_img.convert('RGB')

            output_buffer = io.BytesIO()
            pil_img.save(output_buffer, format='JPEG', quality=level['quality'], 
                        optimize=True, progressive=True)
            output_buffer.seek(0)

            rect = page.rect
            new_page = new_doc.new_page(width=rect.width, height=rect.height)
            new_page.insert_image(new_page.rect, stream=output_buffer.getvalue())

        new_doc.save(output_pdf_path, garbage=4, deflate=True, 
                    deflate_images=True, deflate_fonts=True, clean=True)
        new_doc.close()
        doc.close()

        final_size = os.path.getsize(output_pdf_path)
        print(f"Final compressed size: {final_size/1024:.2f} KB")
        return True

    except Exception as e:
        print(f"❌ Error during compression: {str(e)}")
        # Clean up any open documents
        try:
            if 'doc' in locals():
                doc.close()
            if 'new_doc' in locals():
                new_doc.close()
        except:
            pass
        return False

def get_file_size_mb(file_path):
    """Get file size in MB for display purposes."""
    return os.path.getsize(file_path) / (1024 * 1024)

def main():
    """
    Main function to demonstrate PDF compression.
    Modify the file paths below for your specific use case.
    """
    # Configuration - CHANGE THESE PATHS FOR YOUR FILES
    input_pdf = r"D:\Downloads\input222.pdf"        # Path to your input PDF
    output_pdf = "compressed_output222.pdf"   # Path for compressed output
    target_size = 200              # Target size in KB

    print("🗜️  PDF Compression Tool")
    print("=" * 50)
    print(f"Target size: {target_size} KB")

    # Validate input file
    if not os.path.exists(input_pdf):
        print(f"❌ Error: Input file '{input_pdf}' not found!")
        print("\nPlease ensure your PDF file exists and update the 'input_pdf' variable in the script.")
        return False

    # Display original file information
    try:
        original_size = os.path.getsize(input_pdf)
        original_size_kb = original_size / 1024
        original_size_mb = original_size / (1024 * 1024)

        print(f"\n📄 Input file: {input_pdf}")
        print(f"📊 Original size: {original_size_kb:.2f} KB ({original_size_mb:.2f} MB)")

        # Check if compression is needed
        if original_size <= target_size * 1024:
            print(f"✅ File is already smaller than target size!")
            return True

    except Exception as e:
        print(f"❌ Error reading input file: {e}")
        return False

    # Perform compression
    print(f"\n🚀 Starting compression...")
    success = compress_pdf_to_target_size(input_pdf, output_pdf, target_size)

    # Display results
    if success and os.path.exists(output_pdf):
        compressed_size = os.path.getsize(output_pdf)
        compressed_size_kb = compressed_size / 1024
        compression_ratio = (1 - compressed_size/original_size) * 100

        print("\n" + "=" * 50)
        print("📈 COMPRESSION RESULTS")
        print("=" * 50)
        print(f"📄 Original size:    {original_size_kb:.2f} KB")
        print(f"🗜️  Compressed size:  {compressed_size_kb:.2f} KB")
        print(f"📉 Size reduction:   {compression_ratio:.1f}%")
        print(f"💾 Output file:      {output_pdf}")

        if compressed_size <= target_size * 1024:
            print(f"✅ Target achieved: {compressed_size_kb:.2f} KB ≤ {target_size} KB")
        else:
            print(f"⚠️  Close to target: {compressed_size_kb:.2f} KB (target: {target_size} KB)")

    else:
        print("\n❌ Compression failed!")
        return False

    return True

# Additional utility function for batch processing
def compress_multiple_pdfs(pdf_list, target_size=100, output_suffix="_compressed"):
    """
    Compress multiple PDF files.

    Args:
        pdf_list (list): List of PDF file paths to compress
        target_size (int): Target size in KB for each file
        output_suffix (str): Suffix to add to output filenames
    """
    print(f"\n🔄 Batch processing {len(pdf_list)} files...")
    results = []

    for i, pdf_path in enumerate(pdf_list, 1):
        print(f"\n--- Processing {i}/{len(pdf_list)}: {pdf_path} ---")

        if not os.path.exists(pdf_path):
            print(f"❌ File not found: {pdf_path}")
            results.append(False)
            continue

        # Generate output filename
        base_name = os.path.splitext(pdf_path)[0]
        output_path = f"{base_name}{output_suffix}.pdf"

        # Compress the file
        success = compress_pdf_to_target_size(pdf_path, output_path, target_size)
        results.append(success)

    # Summary
    successful = sum(results)
    print(f"\n📊 Batch processing complete: {successful}/{len(pdf_list)} files compressed successfully")
    return results

if __name__ == "__main__":
    # Run the main compression function
    main()

    # Example for batch processing (uncomment to use):
    # pdf_files = ["file1.pdf", "file2.pdf", "file3.pdf"]
    # compress_multiple_pdfs(pdf_files, target_size=100)
