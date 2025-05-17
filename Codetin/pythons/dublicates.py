import os
from collections import defaultdict

def find_duplicates(input_path):
    # Normalize input_path (to handle both Windows and Unix-like paths)
    normalized_path = os.path.normpath(input_path)
    
    # Dictionary to store file names and their paths
    file_dict = defaultdict(list)
    
    # Walk through the directory and subdirectories
    for root, dirs, files in os.walk(normalized_path):
        for file in files:
            # For each file, add the full path to the file_dict under the filename
            file_dict[file].append(os.path.join(root, file))
    
    # Open a txt file to write the results
    with open('duplicate_files_report.txt', 'w') as f:
        # Iterate over the dictionary and find duplicates
        for filename, paths in file_dict.items():
            if len(paths) > 1:  # If there are duplicates
                f.write("{}\n".format(filename))
                for path in paths:
                    f.write("{}\n".format(path))
                f.write("\n")  # Add a blank line after each group of duplicates

# Example usage:
input_folder = raw_input("Enter the path to the folder to search for duplicates: ")
find_duplicates(input_folder)
print "Duplicate files report has been generated as 'duplicate_files_report.txt'."
