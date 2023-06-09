#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <fstream>

# define Alpha 256

void badChar(char* str, int size, std::vector<int>& bchar) {
    for (int i = 0; i < Alpha; i++) {
        bchar.push_back(-1);
    }
    //creates a table a shift values based on chars
    for (int i = 0; i < size; i++) {
        bchar[(int)str[i]] = i;
    }
}

bool searchBC(std::string& pat, std::string& text) {
    int x = pat.size();
    int y = text.size();
    std::vector<int>bchar;
    badChar(strcpy(new char[pat.length() + 1], pat.c_str()), x, bchar);

    int i = 0;
    //creates table of suffixes in pattern
    while (i <= (y - x)) {
        int j = x - 1;
        //if current pattern char matches
        //current text char -1
        while (j >= 0 && pat[j] == text[i + j]) {
            j--;
        }
        if (j < 0) {
            return true;
        }
        else {
            //will move up by corresponding shift value
            //or 1
            i += std::max(1, j - bchar[text[i + j]]);
        }
    }
    return false;
}

void make_suff(std::vector<int>& shift, std::vector<int>& bpos,
    char* pat, int size)
{

    int i = size;
    int j = size + 1;
    bpos[i] = j;

    while (i > 0)
    {

        while (j <= size && pat[i - 1] != pat[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;

            //Update the position of next border 
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }
}

//Preprocessing for case 2
void make_pre(std::vector<int>& shift, std::vector<int>& bpos,
    char* pat, int m)
{
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++)
    {
        /* set the border position of the first character of the pattern
           to all indices in array shift having shift[i] = 0 */
        if (shift[i] == 0)
            shift[i] = j;

        /* suffix becomes shorter than bpos[0], use the position of
           next widest border as value of j */
        if (i == j)
            j = bpos[j];
    }
}

bool searchGS(char* text, char* pat) {
    int x = strlen(pat);
    int y = strlen(text);


    std::vector<int>bchar;
    std::vector<int> bpos(x + 1);
    std::vector<int> shift(x + 1);

    //initialize all occurrence of shift to 0
    for (int i = 0; i < x + 1; i++) {
        shift[i] = 0;
    }

    //do preprocessing
    badChar(pat, x, bchar);
    make_suff(shift, bpos, pat, x);
    make_pre(shift, bpos, pat, x);

    int i = 0;
    while (i <= (y - x))
    {
        int j = x - 1;

        while (j >= 0 && pat[j] == text[i + j])
            j--;


        if (j < 0)
        {
            return true;
        }
        else {
            //will move up by corresponding shift value
            //or 1
            i += shift[j + 1];
        }
    }
    return false;
}

bool boyerMoore(char* text, char* pat)
{

    int x = strlen(pat);
    int y = strlen(text);


    std::vector<int>bchar;
    std::vector<int> bpos(x + 1);
    std::vector<int> shift(x + 1);

    //initialize all occurrence of shift to 0
    for (int i = 0; i < x + 1; i++) {
        shift[i] = 0;
    }

    //do preprocessing
    badChar(pat, x, bchar);
    make_suff(shift, bpos, pat, x);
    make_pre(shift, bpos, pat, x);

    int i = 0;
    while (i <= (y - x))
    {
        int j = x - 1;

        while (j >= 0 && pat[j] == text[i + j])
            j--;


        if (j < 0)
        {
            return true;
        }
        else {
            //will move up by corresponding shift value
            //or 1
            i += std::max(shift[j + 1], std::max(1, j - bchar[text[i + j]]));
        }
    }
    return false;
}

// Return the execution time of the selected algorithm
float timer(uint16_t n, std::string name, std::string* pat, std::string* txt) {
    bool found;
    unsigned long c_start, c_end;

    // Executing the algorithm 
    if (!name.compare("bc")) {
        c_start = std::clock();
        found = searchBC(*pat, *txt);
        c_end = std::clock();
    }
    else if (!name.compare("gs")) {
        c_start = std::clock();
        found = searchGS(strcpy(new char[txt->length() + 1], txt->c_str()), strcpy(new char[pat->length() + 1], pat->c_str()));
        c_end = std::clock();
    }
    else if (!name.compare("bm")) {
        c_start = std::clock();
        found = boyerMoore(strcpy(new char[txt->length() + 1], txt->c_str()), strcpy(new char[pat->length() + 1], pat->c_str()));
        c_end = std::clock();
    }
    else {
        std::cout << "Invalid function call" << std::endl;
        return 0.0;
    }

    std::cout << "Search successful?: " << found << std::endl;

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Invalid number of arguments. Three needed:" << std::endl;
        std::cout << "First: Method (bc, gs, bm)" << std::endl;
        std::cout << "Second: A pattern to search for" << std::endl;
        std::cout << "Third: The name of the text file that will be searched"
            << std::endl;
        return 0;
    }

    // Declare and initialize variables
    std::string method = argv[1];
    std::string pat = argv[2];
    std::string filename = argv[3];
    std::string txt;
    std::ifstream file(filename);
    std::stringstream buffer;
    uint16_t max_char;

    // Get the text from the text file and hold it in a single string
    buffer << file.rdbuf();
    txt = buffer.str();
    file.close();

    // Open the output file
    std::ofstream myfile;
    myfile.open(pat + ".csv");

    // Used to iterate from 0 to max_char (incrementing by 100 each time) in 
    // order to see how long it takes to perform a search over an 
    // incrementally larger and larger text string.
    max_char = (uint16_t)txt.size();

    // Execute the selected method and write the time data to the output file
    myfile << "input" << "," << "time" << '\n';
    for (int i = 0; i <= max_char; i += 100) {
        std::cout << "Searching with method " << method << "..." << std::endl;
        std::string substring = txt.substr(0, i);
        float time = timer(i, method, &pat, &substring);
        myfile << i << "," << std::fixed << time << '\n';
    }
    myfile.close();

    return 0;
}
