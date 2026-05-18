#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using std::cin;
using std::cerr;
using std::cout;
using std::string;


class BullsAndCows final{

	string number;
	size_t attempts;

	void generate(size_t size) noexcept{
		string digits = "0123456789";
		for (size_t i = 0; i < size; ++i) {
			size_t digit = ((i == 0) ? 1:0) + rand() % ((i == 0) ? 9 : digits.size());
			number.push_back( digits[digit]);
			digits.erase(digits.begin()+digit);
		}
	}

	bool hasDuplicates(const string& input) const noexcept{
		for (size_t i = 0; i < input.size() - 1; ++i) {
			for (size_t j = i + 1; j < input.size(); ++j) {
				if (input[i] == input[j]) {return true;}
			}
		}
		return false;
	}

	bool printBullsAndCows(const string& input) const noexcept{
		unsigned short bulls = 0;
		unsigned short cows = 0;
		for (size_t i = 0; i < number.size(); ++i) {
			if (input[i] == number[i]) {++bulls;}
			for (size_t j = 0; j < number.size(); ++j) {
				if (j != i && input[i] == number[j]) {++cows;}
			}
		}
		if (bulls == input.size()) {
			cout << "You won! The number is " << number << ". It took you " << attempts << " attempts to get it.\n";
			return true;
		}
		cout << "Incorrect guess. Bulls: " << bulls << ", Cows: " << cows << '\n';
		return false;
	}

public:

	BullsAndCows(size_t size): attempts(0) {
		if (size < 1 || size > 10) {throw std::out_of_range("Error: Incorrect number length.");}
		cout << "Game started! Try to guess the " << size << "-digit number.\n";
		srand((time(nullptr)));
		generate(size);
	}

	bool guess(const string& input) {
		if (input.size() != number.size()) {
			cerr << "Error: Guess size does not match number size. Try again.\n";
			return false;
		}
		for (size_t i = 0; i < number.size(); ++i) {
			if (input[i] < '0' || input[i] >'9') {
				cerr << "Error: Incorrect characters in a guess. Use digits 0-9. Try again.\n";
				return false;
			}
		}
		if (hasDuplicates(input)) {
			cerr << "Error: Guess has repeating digits. Try again.\n";
			return false;
		}
		++attempts;
		return printBullsAndCows(input);
	}

};


int main() {
	try {
		cout << "Enter the length of the number (1-10): ";
		size_t size = 0;
		cin >> size;
		BullsAndCows game(size);
		string guess;
		while (true) {
			cout << "Enter your guess: ";
			cin >> guess;
			if (game.guess(guess)) { return 0; }
		}
	}
	catch (const std::out_of_range& e) {
		cerr << e.what() << '\n';
		return 1;
	}
}