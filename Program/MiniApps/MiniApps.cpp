#include <iostream>
#include <time.h>

using namespace std;

int main() 
{
	int userChoice;

	do
	{
		cout << "\nWhat application would you like to run?\n";
		cout << "1) Counting \n2) Square Root Calculator \n3) Encrypt Text \n0) Quit \n"; // Give menu options 

		cin >> userChoice;
		cout << "\n";

		switch (userChoice) {
		case 1:
		{

			srand(time(nullptr));

			int num1 = (rand() % 10) + 1; // Get random number between 1 and 10
			int correct = 0; // Reset scoreboard
			int incorrect = 0; // Reset scoreboard

			cout << "Entering counting numbers...\n\n";

			for (int i = 0; i < 10; i++) // Make it only last 10 questions
			{
				int result = 0; // Reset result
				int input;
				int num2 = (rand() % 10) + 1; // Get random number between 1 and 10
				int addOrSubtract = rand() % 2; // Get a random number between 0 and 1

				// Randomly generate a add or minue question
				if (addOrSubtract == 0) {
					result = num1 - num2; // Get correct result

					// Display question
					cout << "\nQuestion " << i + 1 << ": " << num1 << " - " << num2 << " = ";
					cin >> input;

				}
				else {
					result = num1 + num2; // Get correct result

					// Display question
					cout << "\nQuestion " << i + 1 << ": " << num1 << " + " << num2 << " = ";
					cin >> input;

				}

				if (input == result) {
					// Congratualte on correct answer
					cout << "Well done!\n";

					correct++; // Update scoreboard
				}
				else {
					// Inform on what correct answer is supposed 
					cout << "So close! The answer was " << result << "\n";

					incorrect++; // Update scoreboard
				}

				num1 = result; // Set next number in next question
			}

			// Display scoreboard
			cout << "\nCorrect answers given: " << correct << ".\nIncorrect answers give: " << incorrect << ".\n";
		}
			break;

		case 2:
		{
			cout << "Entering square root calculator... \n\n";

			float input;
			float decimalPlaces;

			do {
				input = 0;

				cout << "What number would you like to square?\n";
				cin >> input;

				if (floor(input) != input) cout << "Please enter a whole number.\n";
			} 
			while (floor(input) != input);


			do {
				decimalPlaces = 1;
				cout << "How many decimal places would you like that too? Please choose a whole number between 1 - 6.\n";
				cin >> decimalPlaces;

				if ((decimalPlaces != 1 || decimalPlaces != 2 || decimalPlaces != 3 || decimalPlaces != 4 || decimalPlaces != 5 || decimalPlaces != 6) && ) {
					cout << "Please only enter a whole number between 1 - 6.\n";
				}

			} 
			while (decimalPlaces != 1 || decimalPlaces != 2 || decimalPlaces != 3 || decimalPlaces != 4 || decimalPlaces != 5 || decimalPlaces != 6);
		}
			break;

		case 3:
			cout << "\n3";
			break;
		case 0:
				cout << "\nGoodbye :)";
			break;

		default:
			if (userChoice > 4) 
			{
				cout << "\nEnter a single character\n";
			}
			else {
				cout << "\nPlease only enter the values '1', '2','3' or '0'\n";
			}
			break;
		}
	} 
	while (userChoice != 0);

	return 0;
}