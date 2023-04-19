# dsa-final-project

### Compilation Instructions for Rabin-Karp Algorithm

When compiling the program for the Rabin-Karp search algorithm the user
must provide a text file with the text they wish to search through, as well
as the specific pattern they are searching for (formatted like this <file_name pattern> ).
These are passed into the program as command line arguments. Below is what this should look like.

    C:\Users\Jason\Documents\GitHub\dsa-final-project\cmake-build-debug\rabinkarp.exe text.txt Vivamus

In this example, our Lorem Ipsum text file, text.txt, is filled with latin placeholder
text. Within this text we are searching for the word "Vivamus". This is the format that
must be followed in order for this program to compile correctly, assuming the text file is
also placed within the current working directory.

### Compilation Instructions for Boyer-Moore Algorithm

When compiling the program for the Boyer-Moore search algorithm, it follows a similar format 
as the Rabin-Karp implementation. The main difference is that there is an additional command line
argument that is needed for this code to compile correctly. Instead of using the <file_name pattern>
format, the Boyer-Moore implementation requires <file_name method pattern> where method is either
bc (bad character), gs (good suffix), or bm (Boyer-Moore) depending on which method the user wishes
to used for searching. An example of this as a command line argument looks like this:

    C:\Users\Jason\Documents\GitHub\dsa-final-project\cmake-build-debug\rabinkarp.exe text.txt gs ut

In this example, we are again searching through the text.txt file searching for the pattern "ut" and the gs in
between indicates that the program will use the good suffix heuristic.