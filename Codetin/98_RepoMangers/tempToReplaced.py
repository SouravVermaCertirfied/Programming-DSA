# Compatible with Python 2.7 to 3.9
import os

def main():
    # Path to the temp.c file
    temp_path = r"D:\Nexteer\Codetin\07_Concurrency\C_codes\temp.c"

    # Check if temp.c exists
    if not os.path.exists(temp_path):
        print("Error: File not found - {}".format(temp_path))
        return

    try:
        # Read content of temp.c
        with open(temp_path, 'r') as f:
            lines = f.readlines()

        if not lines:
            print("Error: File is empty.")
            return

        # First line should contain the new filename (e.g. //calculator.c)
        first_line = lines[0].strip()

        # Extract filename by removing leading slashes and spaces
        new_filename = first_line.lstrip('/').strip()

        # Validate that it ends with .c
        if not new_filename.endswith('.c'):
            print("Error: First line does not specify a valid .c filename.")
            return

        # Construct new file path in the same directory
        new_file_path = os.path.join(os.path.dirname(temp_path), new_filename)

        # Write all contents from temp.c to new file
        with open(new_file_path, 'w') as new_file:
            new_file.writelines(lines)

        print("New file created successfully at: {}".format(new_file_path))

    except Exception as e:
        print("An error occurred: {}".format(e))

if __name__ == "__main__":
    main()
