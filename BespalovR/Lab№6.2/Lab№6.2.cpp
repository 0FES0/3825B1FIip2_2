#include <stdexcept>
#include <iostream>
#include <string>
using std::string;
using std::cerr;
using std::cout;
using std::cin;


class BullsAndCows final{

	string number;
	unsigned int attempts;

	void generate(const unsigned short& size) noexcept{
		string digits = "0123456789";
		for (unsigned short i = 0; i < size; ++i) {
			char digit = rand() % digits.size();
			number.push_back( digits[digit]);
			digits.erase(digits.begin()+digit);
		}
	}

	bool hasDuplicates(const string& input) const noexcept{
		for (unsigned short i = 0; i < input.size() - 1; ++i) {
			for (unsigned short j = i + 1; j < input.size(); ++j) {
				if (input[i] == input[j]) {return true;}
			}
		}
		return false;
	}

	bool printBullsAndCows(const string& input) const noexcept{
		unsigned short bulls = 0;
		unsigned short cows = 0;
		for (unsigned short i = 0; i < number.size(); ++i) {
			if (input[i] == number[i]) {++bulls;}
			for (unsigned short j = 0; j < number.size(); ++j) {
				if (j != i && input[i] == number[j]) {++cows;}
			}
		}
		if (bulls == input.size()) {
			cout << "You won! The number is " << number << ".It took you " << attempts << " attempts to get it.\n";
			return true;
		}
		cout << "Incorrect guess. Bulls: " << bulls << ", Cows: " << cows << '\n';
		return false;
	}

public:

	BullsAndCows(const unsigned short& size):attempts(0){
		if (size < 1 || size > 10) {throw std::out_of_range("Incorrect size");}
		generate(size);
	}

	bool guess(const string& input) {
		for (unsigned short i = 0; i < number.size(); ++i) {
			if (input[i] < '0' || input[i] >'9') { throw std::out_of_range("Incorrect chracters used in a guess"); }
		}
		if (hasDuplicates(input)) { throw std::out_of_range("Guess has repeating digits"); }
		if (input.size() != number.size()) {throw std::out_of_range("Guess size does not match number size");}
		++attempts;
		return printBullsAndCows(input);
	}

};


int main() {
	try {
		unsigned short size;
		cout << "Enter the length of the number (1-10): ";
		cin >> size;
		BullsAndCows game(size);
		string guess;
		cout << "Game started! Try to guess the " << size << "-digit number.\n";
		while (true) {
			cout << "Enter your guess: ";
			cin >> guess;
			if (game.guess(guess)) {break;}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}