# DSA Final Project: String Search I

### Compilation Instructions for Rabin-Karp Algorithm

To compile the program that contains the Rabin-Karp algorithm, execute the line below in
the directory of the program's location.

    g++ -Wall rabinkarp.cpp -o rabinkarp

### Running the Rabin-Karp Algorithm

When running the program for the Rabin-Karp search algorithm the user
must provide a text file with the text they wish to search through, as well
as the specific pattern they are searching for (this is formatted as follows  < file_name pattern > ).
These are passed into the program as command line arguments. Below is what this should look like.

    ./rabinkarp text.txt "Vivamus"

In this example, our Lorem Ipsum text file, text.txt, is filled with latin placeholder
text. Within this text we are searching for the word "Vivamus". This is the format that
must be followed in order for this program to compile correctly, assuming the text file is
also placed within the current working directory.

### Compilation Instructions for Boyer-Moore Algorithm

To compile the program containing the Boyer-Moore algorithm, execute the following line in the directory containing boyermoore.cpp:

    g++ -Wall boyermoore.cpp -o boyermoore

### Running the Boyer-Moore Algorithm

When running the program for the Boyer-Moore search algorithm, it follows a similar format as the Rabin-Karp implementation. The main difference is that there is an additional command line argument that is needed for this code to compile correctly. Instead of using the < file_name pattern > format, the Boyer-Moore implementation requires < method pattern file_name > where the method is `bm` (which stands for "Boyer-Moore"). An example of this as a command line argument looks like this:

    ./boyermoore bm "Lorem" txt/text.txt

In this example, we are again searching through the text.txt file searching for the pattern "Lorem" and the bm in between indicates that the program will use the Boyer-Moore algorithm. The user can also enter `bc` for "Bad Character" and `gs` for "Good Suffix" as the method argument to use search algorithms based only on those rules.

**NOTE:** There is a chance that the program, when compiled on a machine running Windows, will fail to find the file in the "txt" directory due to file path format differences. If this is an issue, copy the text file into the same directory that the program is in and enter the name of the file as the argument.
