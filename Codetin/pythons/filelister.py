import os
import logging

# Configure logging for debugging and production use
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def normalize_path(path):
    """
    Normalize file path to be independent of operating system path conventions.
    Converts all path separators to '/'.

    Args:
        path (str): The original file path.
    
    Returns:
        str: Normalized file path with '/' separators.
    """
    try:
        normalized = os.path.abspath(path).replace(os.sep, '/')
        return normalized
    except Exception as e:
        logging.error("Error normalizing path {}: {}".format(path, e))
        raise

def get_files_in_folder(folder_path):
    """
    Recursively get all files in the provided folder and its subfolders.

    Args:
        folder_path (str): The folder path to start traversing.
    
    Returns:
        list of tuple: List of tuples containing filename and normalized path.
    """
    file_info = []

    try:
        # Walk the directory tree
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                try:
                    full_file_path = os.path.join(root, file)
                    normalized_path = normalize_path(full_file_path)
                    file_info.append((file, normalized_path))
                except Exception as e:
                    logging.warning("Error processing file {}: {}".format(file, e))
        
        return file_info
    
    except Exception as e:
        logging.error("Error while traversing the directory {}: {}".format(folder_path, e))
        raise

def save_to_txt(file_info, output_file):
    """
    Save the list of files and their paths to a text file, with each file in its own paragraph.
    
    Args:
        file_info (list): List of tuples containing filenames and paths.
        output_file (str): The path of the output text file.
    """
    try:
        with open(output_file, 'w') as f:
            for file, path in file_info:
                f.write("{}\n{}\n\n".format(file, path))
        
        logging.info("Text file successfully saved to: {}".format(output_file))
    
    except Exception as e:
        logging.error("Error saving to text file {}: {}".format(output_file, e))
        raise

def validate_folder_path(folder_path):
    """
    Validate if the given folder path exists and is a directory.

    Args:
        folder_path (str): The folder path to validate.
    
    Returns:
        bool: True if valid folder, False otherwise.
    """
    if not folder_path:
        logging.error("No folder path provided.")
        return False

    if not os.path.isdir(folder_path):
        logging.error("The folder path '{}' does not exist or is not a directory.".format(folder_path))
        return False

    return True

def main():
    """
    Main function to process files in the hardcoded folder path and generate the output.
    """
    try:
        # Hardcoded folder path
        folder_path = r"D:\Nexteer\Nissan\SWEET500"  # Using raw string to avoid escape character issues

        # Validate the provided folder path
        if not validate_folder_path(folder_path):
            return

        # Get all files and their paths in the folder and subfolders
        logging.info("Starting to process files in folder: {}".format(folder_path))
        file_info = get_files_in_folder(folder_path)

        if not file_info:
            logging.warning("No files found in the provided directory.")

        # Define output text file path
        output_file = 'files_in_folders.txt'
        
        # Save file info to text file
        save_to_txt(file_info, output_file)

    except Exception as e:
        logging.error("An unexpected error occurred: {}".format(e))
        print("An error occurred. Please check the log for details.")

if __name__ == "__main__":
    main()
