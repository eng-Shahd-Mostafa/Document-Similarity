#include<iostream>
#include<fstream>
#include<ctype.h>//for transform the uppercase to lowercase
#include<vector>
#include<cmath>
#include <algorithm>
#include<string>

using namespace std;

class StringSet
{
private:
	vector<string>Words;

public:
	StringSet() {}
	StringSet(const string& name1)
	{
		ifstream file;
		file.open(name1);
		if (file.fail())
		{
			cerr << "Error, We can't open this File!\n\a";
			return;
		}
		string word;
		while (file >> word)
		{
			Process(word);
		}
		file.close();
	}

	void Process(const string& Word)
	{
		string Result;
		for (char s : Word)
		{
			if (isalpha(s) || s == '_' || s == '-' || s == '\'')
				Result += tolower(s);
			else if (!Result.empty())
			{
				if (find(Words.begin(), Words.end(), Result) == Words.end())
					Words.push_back(Result);
				Result.clear();
			}
		}
		if (!Result.empty() && find(Words.begin(), Words.end(), Result) == Words.end())
			Words.push_back(Result);
	}

	void add(const string& word)
	{
		if (find(Words.begin(), Words.end(), word) == Words.end())
			Words.push_back(word);
	}

	void remove(const string& word)
	{
		auto search = find(Words.begin(), Words.end(), word);
		if (search != Words.end())
			Words.erase(search);
	}

	void Clear()
	{
		Words.clear();
	}

	int No_of_string() const
	{
		return Words.size();
	}

	void output() const
	{
		for (int i = 0;i < Words.size();i++)
			cout << i + 1 << ") " << Words.at(i) << endl;
	}

	StringSet operator +(const StringSet& other) const//for union operation
	{
		StringSet Result = *this;
		for (const auto& words : other.Words)
		{
			if (find(Result.Words.begin(), Result.Words.end(), words) == Result.Words.end())
				Result.Words.push_back(words);
		}
		return Result;
	}

	StringSet operator *(const StringSet& other) const //for intersection operation
	{
		StringSet Result;
		for (const auto& words : Words)
		{
			if (find(other.Words.begin(), other.Words.end(), words) != other.Words.end())
				Result.Words.push_back(words);
		}
		return Result;
	}

	double Similarity(const StringSet& other) const
	{
		int intersect_size = (*this * other).No_of_string();
		int this_size = this->No_of_string();
		int other_size = other.No_of_string();
		if (this_size == 0 || other_size == 0)
			return 0.0;
		return static_cast<double>(intersect_size) / (sqrt(this_size) * sqrt(other_size));
	}

};

void DisplayMenu()
{
	cout << "                          Welcome to my Similarity Application                 \n";
	cout << "                        ========================================\n";
	cout << "  1) Load the 2 Files\n";
	cout << "  2) Enter 2 Strings manually\n";
	cout << "  3) Run 2 files or 2 strings\n";
	cout << "  4) Exit\n";
	cout << "Enter your choice\n";
}

void Display()
{
	cout << "          Test Menu          \n";
	cout << "       ================ \n";
	cout << " 1) Add word to set\n";
	cout << " 2) Remove word form set\n";
	cout << " 3) Clear set\n";
	cout << " 4) Show intersection in sets\n";
	cout << " 5) Calculate the similarity\n";
	cout << " 6) Display words in set\n";
	cout << " 7) Back to the main menu\n";
	cout << " Choose an Operation\n";
}

int main()
{
	StringSet s1, s2;
	while (true)
	{
		DisplayMenu();
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			string name1, name2;
			cout << "Enter the first file name: \n";
			cin >> name1;
			cout << "Enter the second file name: \n";
			cin >> name2;
			s1 = StringSet(name1);
			s2 = StringSet(name2);
			cout << "Files loaded successfully.\n";
		}
		break;
		case 2:
		{
			string str1, str2;
			cout << "Enter the first message\n";
			cin.ignore();
			getline(cin, str1);
			cout << "Enter the second message\n";
			getline(cin, str2);
			s1.Clear();
			s2.Clear();
			s1.Process(str1);
			s2.Process(str2);
			cout << "Strings processed successfully\n";
		}
		break;
		case 3:
		{
			bool submenu = true;
			while (submenu)
			{
				Display();
				int choice;
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					char ch;
					cout << "Do you want to add a word to first(a) or second(b) set?\n";
					cout << "Please enter a or b\n";
					cin >> ch;
					switch (ch)
					{
					case 'a':
					{
						string Word;
						cout << "Enter a word to add to the first set: \n";
						cin.ignore();
						getline(cin, Word);
						s1.add(Word);
					}
					break;
					case 'b':
					{
						string Word;
						cout << "Enter a word to add to the second set: \n";
						cin.ignore();
						getline(cin, Word);
						s2.add(Word);
					}
					break;
					default:
					{
						cerr << "Invalid input..\n";
						break;
					}
					}
				}
				break;
				case 2:
				{
					char ch;
					cout << "Do you want to remove a word to first(a) or second(b) set?\n";
					cout << "Please enter a or b\n";
					cin >> ch;
					switch (ch)
					{
					case 'a':
					{
						string Word;
						cout << "Enter a word to remove to the first set: \n";
						cin.ignore();
						getline(cin, Word);
						s1.remove(Word);
					}
					break;
					case 'b':
					{
						string Word;
						cout << "Enter a word to remove to the second set: \n";
						cin.ignore();
						getline(cin, Word);
						s2.remove(Word);
					}
					break;
					default:
					{
						cerr << "Invalid input..\n";
						break;
					}
					}
				}
				break;
				case 3:
				{
					char ch;
					cout << "Do you want to clear the first(a) or second(b) set?\n";
					cout << "Please enter a or b\n";
					cin >> ch;
					switch (ch)
					{
					case 'a':
					{
						s1.Clear();
						cout << "First set is cleared\n";
					}
					break;
					case 'b':
					{
						s2.Clear();
						cout << "Second set is cleared\n";
					}
					break;
					default:
					{
						cerr << "Invalid input..\n";
						break;
					}
					}
				}
				break;
				case 4:
				{
					StringSet intersection = s1 * s2;
					cout << "Common words between the two sets:\n";
					intersection.output();
				}
				break;
				case 5:
				{
					// Assume the similarity between 2 documents
					double Similarity = s1.Similarity(s2);
					cout << "\nThe similarity between the two files is: " << Similarity << endl;
					if (Similarity == 1.0)
						cout << "The Documents are identical\n\a";
					else if (Similarity == 0.0)
						cout << "The Documents have no common words.\n\a";
					else
						cout << "The Documents have some similarity\n\a";
				}
				break;
				case 6:
				{
					cout << "Words in the first set: \n";
					s1.output();
					cout << "Words in the second set: \n";
					s2.output();
				}
				break;
				case 7:
				default:
				{
					submenu = false;
					break;
				}
				}
			}
		}
		break;
		case 4:
		{
			cout << "Good Bye:)\n\a";
			return 0;
		}
		break;
		default:
		{
			cout << "Invalid Choice,please try again..\n";
			main();
		}
		}
	}
	return 0;
}
