import os
import shutil

def export_files(input_folder):
    # Define the name of the exported folder
    exported_folder = os.path.join(input_folder, 'exported')

    # Check if the "exported" folder exists, and delete it if it does
    if os.path.exists(exported_folder):
        shutil.rmtree(exported_folder)
        print("Existing 'exported' folder deleted.")

    # Create a new "exported" folder
    os.makedirs(exported_folder)
    print("'exported' folder created.")

    # Loop through files in the input folder
    for filename in os.listdir(input_folder):
        # Get the full path of the file
        file_path = os.path.join(input_folder, filename)

        # Check if the file is a .pdf or .doc
        if os.path.isfile(file_path) and (filename.endswith('.pdf') or filename.endswith('.doc')):
            # Move the file to the exported folder
            shutil.move(file_path, os.path.join(exported_folder, filename))
            print(f"Exported: {filename}")

if __name__ == "__main__":
    # Prompt the user for the folder to process
    input_folder = raw_input("Enter the folder path to export files from: ")
    input_folder = os.path.normpath(input_folder)
    # Check if the input folder exists
    if os.path.exists(input_folder) and os.path.isdir(input_folder):
        export_files(input_folder)
    else:
        print("The provided folder does not exist or is not a directory.")
