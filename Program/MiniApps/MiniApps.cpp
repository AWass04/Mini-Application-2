#include <algorithm> 
#include <cctype> 
#include <iostream>
#include <string>
#include <time.h>
#include <cmath>
#include <iomanip>


using namespace std;

int CheckStringIsNum(string input);
int GetLowerBound(int input);
double GetSquareRoot(int input, double upperBound, double lowerBound, double decimalPlaces);
void EncryptDecrypt(bool ecnrypt);
bool CheckInput(string input);
string CaeserCipher(int shiftAmount, string input, bool encrpyt);

int main() 
{
	string input;
	int userChoice = 5;

	do
	{
		cout << "\nWhat application would you like to run?\n";
		cout << "-----------------------------------------\n\n";
		cout << "1) Keep Counting \n2) Square Root Calculator \n3) Encrypt Text \n4) Decrpyt Text \n0) Quit \n"; // Give menu options 
		cout << "\nPlease enter option:\n";

		cin >> input;
		cout << "\n";

		userChoice = CheckStringIsNum(input);

		switch (userChoice) {
		case 1: // Counting 
		{

			srand(time(nullptr));

			int num1 = (rand() % 10) + 1; // Get random number between 1 and 10
			int correct = 0; // Reset scoreboard
			int incorrect = 0; // Reset scoreboard
			int result = 0; // Reset result

			cout << "Entering counting numbers...\n";
			cout << "----------------------------\n\n";


			for (int i = 0; i < 10; i++) // Lasts for 10 questions
			{
				string input;
				int userAnswer = 999999999;
				int num2 = (rand() % 10) + 1; // Get random number between 1 and 10
				int addOrSubtract = rand() % 2; // Get a random number between 0 and 1

				// Randomly generate a add or minue question
				if (addOrSubtract == 0) {
					
					result = num1 - num2; 

					cout << "\nQuestion " << i + 1 << ": " << num1 << " - " << num2 << " = ";
				}
				else {
					
					result = num1 + num2; 

					cout << "\nQuestion " << i + 1 << ": " << num1 << " + " << num2 << " = "; 
				}
				
				cin >> input;

				userAnswer = CheckStringIsNum(input);

				if (userAnswer == result) {

					cout << "Well done!\n"; 
					correct++; // Update scoreboard
				}
				else {
					
					cout << "So close! The answer was " << result << "\n"; // Inform on what correct answer is supposed 
					incorrect++; // Update scoreboard
				}

				num1 = result; // Set number in next question
			}

			// Display scoreboard
			cout << "\nCorrect answers given: " << correct << ".\nIncorrect answers give: " << incorrect << ".\n";
		}
			break;

		case 2: // Square root calculator
		{
			bool isValidNum = false;
			string input;
			int radicand;
			int decimalPlaces = 1;

			cout << "Entering square root calculator... \n";
			cout << "----------------------------------\n\n";

			cout << "What number would you like to find the square root of?\n";
			cin >> input;
			cout << "\n";
			
			radicand = CheckStringIsNum(input); 

			// Error Handling - Produce error message if its not a whole number or a number less than 0
			while (radicand == 999999999 || radicand < 1) {

				cout << "Please enter a whole number thats above 0.\n"; 
				cin >> input;

				radicand = CheckStringIsNum(input);
			} 

			cout <<"\nHow many decimal places would you like that too? Please choose a whole number between 1 - 6.\n";
			cin >> input;
			cout << "\n";

			decimalPlaces = CheckStringIsNum(input); 

			// Error handling - Produce an error if its not a number between 1 - 6
			while (decimalPlaces < 1 || decimalPlaces > 6) {
				
				cout << "Please only enter a whole number between 1 - 6. How many decimal places would you like it to be accurate to? \n";
				cin >> input;

				decimalPlaces = CheckStringIsNum(input); // Check user input is a number
			}

			double lowerBound = GetLowerBound(radicand); // Lower bound is the last known value that the true square root must be above
			double upperBound = lowerBound + 1; //Upper bound is the last know value that the true square root must be below

			double result = GetSquareRoot(radicand, upperBound, lowerBound, decimalPlaces);

			cout << "\nThe square root of " << radicand << " to " << decimalPlaces << " decimal places is: ";
			cout << fixed << setprecision(decimalPlaces); // Remove default amount of decimal places shown
			cout << result << "\n\n";
		}
			break;

		case 3: // Encrpt Text

			EncryptDecrypt(true);

			break;

		case 4: // Decrypt text

			EncryptDecrypt(false);

			break;
		case 0: // Close program
				cout << "\nGoodbye :)";
			break;

		default:

			// Error handelling - If user inputs anything other than 0 - 4, display error
			if (userChoice > 4)
			{
				cout << "Please only enter the values '1', '2','3', '4' or '0'\n";
			}
			else {
				cout << "Enter a single character\n";
			}
			break;
		}
	} 
	while (userChoice != 0);

	return 0;
}

int CheckStringIsNum(string input) {

	for (char x : input) { 

		switch (x) {

			case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0': case '-':
				// Ignore if valid input
			break;

			default: 
				return 999999999; // Return result that will produce error
		}
	}

	// Error handeling - if the input isnt a negative number but simply a '-' return result that will produce error
	if (input == "-") return 999999999; 

	input = input.substr(0, 10); // Make sure its not too big of a number
	int number = stoi(input); // Convert string to int

	return number;
}

int GetLowerBound(int input) {

	int lowerBound = 1;

	// Work out what the last known true square root value is
	for (int i = 1; i * i < input; i++) {
		
		lowerBound = i;
	}

	return lowerBound;
}

double GetSquareRoot(int input, double upperBound, double lowerBound, double decimalPlaces) {

	double average;
	double result;
	double accuracy = pow(10, -decimalPlaces);

	do {
		
		average = (lowerBound + upperBound) / 2; // Calculate average

		// If adverage squared is bigger than input, decrease upper bound otherwise increase lower bound
		if (average * average > input) upperBound = average; 
		else lowerBound = average;

	} while (abs((average * average) - input) > accuracy); // Dont stop until within n amount of decimal place accurancy

	// Refine to correct amount of decimal places
	double multiplier = pow(10, decimalPlaces);
	result = round(average * multiplier) / multiplier;
	
	return result;
}

void EncryptDecrypt(bool encrypt) {
	
	string text;
	string input;
	bool validInput;
	int shiftAmount;
	string resultText;

	cout << (encrypt ? "Enterting encrypt text...\n" : "Enterting decrypt text...\n");
	cout << "-------------------------\n\n";

	do {
		
		cout << "Enter text you wish to " << (encrypt ? "encrypt:\n" : "decrypt:\n");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, text);
		cout << "\n";

		transform(text.begin(), text.end(), text.begin(), ::toupper); // Make capitals
		validInput = CheckInput(text); // Check if has any special characters

	} while (!validInput);

	cout << "Enter shift amount (1 - 36)\n";
	cin >> input;

	shiftAmount = CheckStringIsNum(input);

	// Error handling - Produce error if input is not between 1 - 16. Repeat until it is. 
	while (shiftAmount < 1 || shiftAmount > 36) {

		cout << "Please enter a whole number between 1 - 36\n";
		cin >> input;

		shiftAmount = CheckStringIsNum(input); // Check input is number
	}

	resultText = CaeserCipher(encrypt ? shiftAmount : -shiftAmount, text, encrypt);

	cout << "\n" << (encrypt ? "Encoded" : "Decoded") << " message is: " << resultText << "\n";
}

bool CheckInput(string input) {

	for (char x : input) {

		switch (x) {
		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		case 'U': case 'V': case 'W': case 'X': case 'Y':
		case 'Z': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '0': case ' ':
			// Ignore if valid
			break;

		default: // If special characters are entered produce error
			cout << "Do not include special characters.\n\n";

			return false;
		}
	}
	return true;
}

string CaeserCipher(int shiftAmount, string input, bool encrypt) {

	string message;

	string caeserCipherAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

	for (char x : input) {

		int index = caeserCipherAlphabet.find(x); // Find location in array
		index += shiftAmount; // Move it along required amount of places

		if (index > 36 || index < 0) { // If goes out of range of array, cycle back.

			if (encrypt) index -= 37; // If encrypting go back to start
			else index += 37; // If decrypting go back to the end
		}

		message += caeserCipherAlphabet[index];
	}

	return message;
}