#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Script Name: projectPrepare.py

Purpose:
--------
This script prepares a Git repository directory by:
1. Adding a `.gitkeep` file to every empty folder (to ensure Git tracks them).
2. Removing (.exe, .obj, .ilk and .pdb) files.

Compatibility:
--------------
- Compatible with both Python 2.7.3 and Python 3.x

Behavior:
---------
- Recursively walks through the target directory
- Detects and marks empty directories with `.gitkeep`
- Cleans up unwanted binary artifacts (.exe, .obj, .ilk and .pdb) left by C/C++ compilation
"""

from __future__ import print_function  # For Python 2/3 compatibility
import os
import sys

# File extensions to remove
UNWANTED_EXTENSIONS = ('.exe', '.obj', '.ilk', '.pdb')


def add_gitkeep_to_empty_dirs(root_dir):
    """Recursively add .gitkeep to empty directories."""
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Skip .git directory
        if '.git' in dirpath:
            continue

        # Directory is empty if it has no files and no subdirectories
        if not dirnames and not filenames:
            gitkeep_path = os.path.join(dirpath, '.gitkeep')
            if not os.path.exists(gitkeep_path):
                with open(gitkeep_path, 'w') as f:
                    pass  # Create empty .gitkeep file
                print("Added:", gitkeep_path)


def remove_unwanted_files(root_dir):
    """Remove unwanted binary files with specific extensions."""
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Skip .git directory
        if '.git' in dirpath:
            continue

        for filename in filenames:
            if filename.lower().endswith(UNWANTED_EXTENSIONS):
                file_path = os.path.join(dirpath, filename)
                try:
                    os.remove(file_path)
                    print("Removed:", file_path)
                except Exception as e:
                    print("Failed to remove {}: {}".format(file_path, e))


def main():
    # Determine the target directory (defaults to current directory)
    # if len(sys.argv) > 1:
    #     target_dir = sys.argv[1]
    # else:
    #     target_dir = os.getcwd()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    target_dir = os.path.normpath(os.path.join(script_dir, '..'))

    if not os.path.isdir(target_dir):
        print("Error: '{}' is not a valid directory.".format(target_dir))
        sys.exit(1)

    print("Preparing project directory:", target_dir)
    remove_unwanted_files(target_dir)
    add_gitkeep_to_empty_dirs(target_dir)
    print("Project preparation complete.")


if __name__ == '__main__':
    main()
