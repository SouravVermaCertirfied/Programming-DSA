from __future__ import print_function  # Ensure print() works in both Python 2 and 3
import os

"""
Script Name: projectPrepare.py

Purpose:
--------
This script prepares a Git repository directory by:
1. Adding a `.gitkeep` file to every empty folder (to ensure Git tracks them).
2. Removing `.exe` and `.obj` files that correspond to `.c` or `.cpp` source files.

Compatibility:
--------------
- Compatible with both Python 2.7.3 and Python 3.x

Behavior:
---------
- Recursively walks through the target directory
- Detects and marks empty directories with `.gitkeep`
- Cleans up unwanted binary artifacts (.exe, .obj) left by C/C++ compilation
"""

def add_gitkeep_to_empty_dirs(root_dir):
    """
    Recursively adds a `.gitkeep` file to every truly empty folder
    (no files, no subfolders) within the root_dir.
    """
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Check if folder is completely empty
        if not dirnames and not filenames:
            gitkeep_path = os.path.join(dirpath, '.gitkeep')
            if not os.path.exists(gitkeep_path):
                # Create the empty .gitkeep file
                with open(gitkeep_path, 'w') as f:
                    f.write("")  # Optional: could write a comment if desired
                print("Added .gitkeep to empty folder: {}".format(dirpath))


def remove_exe_obj_for_sources(root_dir):
    """
    For each `.c` or `.cpp` file found, deletes any `.exe` or `.obj` file
    with the same base name in the same directory.
    """
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith('.c') or filename.endswith('.cpp'):
                # Get the base filename without extension
                base_name = os.path.splitext(filename)[0]

                # Build paths for possible binary files
                exe_path = os.path.join(dirpath, base_name + '.exe')
                obj_path = os.path.join(dirpath, base_name + '.obj')
                ilk_path = os.path.join(dirpath, base_name + '.ilk')
                pdb_path = os.path.join(dirpath, base_name + '.pdb')

                # Remove if they exist
                for file_path in [exe_path, obj_path, ilk_path, pdb_path]:
                    if os.path.exists(file_path):
                        os.remove(file_path)
                        print("Deleted: {}".format(file_path))


def main():
    """
    Main function:
    - Determines target directory relative to script location
    - Runs both gitkeep and cleanup tasks
    """
    # Get the directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # The target directory is one level up from the script folder
    root_dir = os.path.normpath(os.path.join(script_dir, '..'))

    print("Preparing repo at: {}".format(root_dir))

    add_gitkeep_to_empty_dirs(root_dir)
    remove_exe_obj_for_sources(root_dir)

    print("Done.")


# Run the script
if __name__ == "__main__":
    main()
