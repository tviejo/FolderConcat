# FolderConcat

**FolderConcat** is a C program that recursively concatenates all printable (text) files in a specified directory, generating a single output file (or printing to `stdout` if no output file is provided). The output includes a directory tree at the beginning, followed by the content of each printable file.

## Features

- **Directory Tree**: Displays the directory structure at the top of the output for easy navigation.
- **File Concatenation**: Combines the content of all printable files in the specified directory and its subdirectories into a single output.
- **Flexible Output**: Writes to an output file if provided, or prints to `stdout` if not.

## Requirements

- A C compiler (`gcc` or `cc`)
- `make` for easy compilation and running

## Installation

Clone the repository:
```bash
git clone https://github.com/tviejo/FolderConcat.git
cd FolderConcat

Usage
Build the Program

Use the provided Makefile to compile the program:

bash

make

Run the Program

To run FolderConcat, provide a directory path. Optionally, specify an output file.
Basic Usage

bash

./FolderConcat <directory_path> [output_file]

    directory_path: The path to the directory containing files to be concatenated.
    output_file (optional): If specified, the output is saved to this file. Otherwise, output is printed to stdout.

Example:

bash

./FolderConcat /path/to/directory output.txt

This will generate output.txt with the directory structure and concatenated content of each printable file.
Run Examples

You can also use the Makefile to execute a sample run:

bash

make run

Or display usage information:

bash

make help

Clean Up

Remove object files and the executable:

bash

make clean

Remove all build artifacts, including the executable:

bash

make fclean

How It Works

    Directory Tree: The program starts by recursively traversing the specified directory, printing a tree-like structure to the output.
    Printable File Detection: It identifies printable files by scanning their content to ensure they contain only printable characters.
    Concatenation: Only files identified as printable are concatenated in the output, with each file's name and content included in the final result.

License

This project is licensed under the MIT License - see the LICENSE file for details.
Contributing

Feel free to fork the repository and submit pull requests. Contributions are welcome!
Author

Developed by tviejo.