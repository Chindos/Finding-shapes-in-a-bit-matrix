Finding shapes in a bit matrixDescription
figsearch is a C console utility for analyzing a bit matrix representing an image. The program allows you to:

Check if the image file is correct (values must be 0 or 1).
Find the longest horizontal line of black pixels.
Find the longest vertical line of black pixels.
Find the largest square of black pixels.
Features

Bit matrix validation:
The test command reads the dimensions and elements of the matrix, verifying that all values are correct. If successful, a Valid message is displayed.

Shape Finder:

hline: Finds the longest horizontal line and outputs the start and end coordinates in the format:
row_start col_start row_end col_end
vline: Finds the longest vertical line and outputs the corresponding coordinates.
square: Determines the largest square completely filled with black pixels and outputs the coordinates of the top left and bottom right corners.
Error handling:
If an incorrect file format or read errors are detected, the program displays error messages and terminates.

Compilation
Compile the program using gcc:

bash
Copy
gcc “figsearch (2) (1).c” -o figsearch
Note: Rename the file to figsearch.c for convenience if necessary.

Usage
The program accepts two command line arguments:

Command:
--help - help output.
test - check the validity of the bit matrix.
hline - search for the longest horizontal line.
vline - search for the longest vertical line.
square - search for the largest square.
Path to the image file.
Examples of launching:

bash
Copy
./figsearch --help
./figsearch test image.txt
./figsearch hline image.txt
./figsearch vline image.txt
./figsearch square image.txt
Input file format
The file must contain:

The first line contains two integers: the height and width of the matrix.
Subsequent numbers (0 or 1) representing the pixels of the image, arranged in line-by-line order.
An example of an image.txt file:

Copy
5 5
0 1 1 0 0
1 1 1 1 0
0 1 1 0 0
0 0 1 1 1
0 0 1 1 1
Command description

--help
Outputs help information about commands and program usage.

test
Checks that the input file contains a valid bit matrix. If the check is successful, the message Valid is output.

hline
Finds the longest horizontal line of black pixels and outputs the coordinates of the beginning and end of the line.

vline
Finds the longest vertical line of black pixels and outputs the corresponding coordinates.

square
Finds the largest square completely filled with black pixels and outputs the coordinates of the top left and bottom right corners.

Error handling

In case of a file reading error, incorrect input data format or failure to allocate memory, the program displays an error message and terminates execution.
If the sought figure is not found, the Not found message is displayed.
