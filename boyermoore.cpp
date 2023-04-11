#include <iostream>
#include <string>
#include <vector>


# define Alpha 256

void badChar(std::string& str, int size, std::vector<int>& bchar) {
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
	badChar(pat, x, bchar);

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

void make_suff(std::vector<int>& shift, std::vector<int>& borpo, int size, std::string& pat) {
	int i = size;
	int j = size + 1;
	borpo[i] = j;
	while (i > 0) {
		//if char at i-1 = char at j-1
		while (j <= size && pat[i - 1] != pat[j - 1]) {
			if (shift[j] == 0) {
				shift[j] = j - 1;
			}
			j = borpo[j];
		}
		i--;
		j--;
		borpo[i] = j;
	}
}

void make_pre(std::vector<int>& shift, std::vector<int>& borpo, int size, std::string& pat) {
	int j = borpo[0];
	//creates table of shift values based on suffix
	for (int i = 0; i <= size; i++) {
		if (shift[i] == 0) {
			shift[i] = j;
		}
		if (i == j) {
			j = borpo[j];
		}
	}
}

bool searchGS(std::string& pat, std::string& text) {
	int x = pat.size();
	int y = text.size();
	std::vector<int> borpo(x + 1);
	std::vector<int>shift;

	for (int i = 0; i < x + 1; i++) {
		shift.push_back(0);
	}

	make_suff(shift, borpo, x, pat);
	make_pre(shift, borpo, x, pat);

	int i = 0;
	while (i <= (y - x)) {
		int j = x - 1;
		while (j >= 0 && pat[j] == text[i + j]) {
			j--;
		}
		if (j < 0) {
			return true;
		}
		else {
			//will shift by corresponding shift value
			i += shift[j + 1];
		}
	}
	return false;
}


int main()
{
	std::string txt = "ABAABABCABAB";
	std::string pat = "CABAB";
	//Best = O(1)
	//Worst = O(mn)
	//Average = O(m/n)
	std::cout << searchBC(pat, txt);
	//Best = O(1)
	//Worst = O(mn)
	//Average = O(m/n)
	std::cout << searchGS(pat, txt);

}