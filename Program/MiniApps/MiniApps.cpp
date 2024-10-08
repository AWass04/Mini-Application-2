#include <iostream>
#include <time.h>
#include<cmath>
#include <iomanip>

using namespace std;

int GetLowerBound(int input);
double GetSquareRoot(int input, double upperBound, double lowerBound, double decimalPlaces);

int main() 
{
	int userChoice;

	do
	{
		cout << "\nWhat application would you like to run?\n";
		cout << "1) Counting \n2) Square Root Calculator \n3) Encrypt Text \n0) Quit \n"; // Give menu options 

		cin >> userChoice;
		cout << "\n";

		// Use user input to open option
		switch (userChoice) {
		case 1: // Counting 
		{

			srand(time(nullptr));

			int num1 = (rand() % 10) + 1; // Get random number between 1 and 10
			int correct = 0; // Reset scoreboard
			int incorrect = 0; // Reset scoreboard
			int result = 0; // Reset result

			cout << "Entering counting numbers...\n\n";

			for (int i = 0; i < 10; i++) // Lasts for 10 questions
			{
				int input;
				int num2 = (rand() % 10) + 1; // Get random number between 1 and 10
				int addOrSubtract = rand() % 2; // Get a random number between 0 and 1

				// Randomly generate a add or minue question
				if (addOrSubtract == 0) {
					
					result = num1 - num2; // Get correct result

					cout << "\nQuestion " << i + 1 << ": " << num1 << " - " << num2 << " = "; // Display question
				}
				else {
					
					result = num1 + num2; // Get correct result

					cout << "\nQuestion " << i + 1 << ": " << num1 << " + " << num2 << " = "; // Display question

				}

				cin >> input;

				if (input == result) {

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
			cout << "Entering square root calculator... \n\n";

			double input = 0;
			double decimalPlaces = 1;

			cout << "What number would you like to find the square root of?\n";
			cin >> input;

			// Error Handling - Produce error message if its not a whole number
			while (floor(input) != input || input <= 0) {

				cout << "Please enter a whole number thats above 0.\n"; 
				cin >> input;

			} 

			cout <<"\nHow many decimal places would you like that too? Please choose a whole number between 1 - 6.\n";
			cin >> decimalPlaces;

			// Error handling - Produce an error if its not a number between 1 - 6
			while (decimalPlaces < 1 || decimalPlaces > 6 || floor(decimalPlaces) != decimalPlaces) {
				
				cout << "Please only enter a whole number between 1 - 6. How many decimal places would you like it to be accurate to? \n";
				cin >> decimalPlaces;

			}

			// Get upper and lower bounds 
			double lowerBound = GetLowerBound(input); // Lower bound is the last known value that the true square root must be above
			double upperBound = lowerBound + 1; //Upper bound is the last know value that the true square root must be below

			double result = GetSquareRoot(input, upperBound, lowerBound, decimalPlaces);

			// Show result
			cout << "\nThe square root of " << input << " to " << decimalPlaces << " decimal places is: ";
			cout << fixed << setprecision(decimalPlaces); // Remove default amount of decimal places shown
			cout << result << "\n\n";
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