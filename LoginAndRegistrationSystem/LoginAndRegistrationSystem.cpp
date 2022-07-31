#include "Account.h"

int main()
{
	bool isLoggedIn = false;
	Account* user = nullptr;

	while (true) {
		int choice;
		if (!isLoggedIn) {
			std::cout << "1: Register" << endl;
			std::cout << "2: Login" << endl;
		}
		else
		{
			std::cout << "1: Check Balance" << endl;
			std::cout << "2: Increase Balance with math quiz" << endl;
			std::cout << "3: Buy Storage" << endl;
			std::cout << "4: Check Storage" << endl;
			std::cout << "5: Set Storage" << endl;
			std::cout << "6: Log out" << endl;
			std::cout << endl;
			std::cout << "-404: Delete My Account" << endl;
		}
		std::cout << endl;
		std::cout << "99: Clear Window." << endl;
		std::cout << endl << endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cout << endl << endl;
		if (choice == 99) {
			system("cls");
			continue;
		}
		if (!isLoggedIn) {
			if (choice >= 1 && choice <= 2) {
				string username, password;
				std::cout << "username: ";
				std::cin >> username;
				std::cout << "password: ";
				std::cin >> password;

				try
				{
					if (choice == 1) {
						Account::Register(username, password);
					}
					else if (choice == 2) {
						user = Account::Login(username, password);
						isLoggedIn = true;
					}
				}
				catch (const std::exception& e)
				{
					std::cout << "\n\n[!!] " << e.what() << endl;
				}
			}
			else {
				std::cout << "Invalid Choice" << endl;
			}
		}
		else {
			if (choice == 1) {
				std::cout << "Your balance is: " << user->getBalance() << "$" << endl;
			}
			else if (choice == 2) {
				user->increaseMoneyWithMathQuiz();
			}
			else if (choice == 3) {
				std::cout << "Current balance = " << user->getBalance() << endl;
				std::cout << "Current Storage Size = " << user->getMemorySize() << endl;
				while (true)
				{
					int amount;
					std::cout << endl << endl;
					std::cout << "NOTE: type a negative number or zero to cancel." << endl;
					std::cout << "Enter amount of storage (every Location costs " << user->getPricePerLocation() << "): ";
					std::cin >> amount;
					std::cout << endl;
					if (amount > 0) {
						try
						{
							user->buyMemoryStorage(amount);
							std::cout << "Successfully Purchased." << endl;
							break;
						}
						catch (const std::exception& e)
						{
							std::cout << "\n\n[x] " << e.what() << endl;
							continue;
						}
					}
					else
						break;
				}
			}
			else if (choice == 4) {
				std::cout << "Current Storage Size = " << user->getMemorySize() << endl;
				std::cout << "Current Storage:";
				std::cout << endl << endl;
				std::cout << "************************************************************" << endl << endl;
				std::cout << user->getSavedMemory() << endl;
				std::cout << endl << endl;
				std::cout << "************************************************************" << endl << endl;
			}
			else if (choice == 5) {
				string word;
				std::cout << "Current Storage Size = " << user->getMemorySize() << endl;
				std::cout << "Enter string to be saved (only the first " << user->getMemorySize() << " characters will be saved): ";
				std::cin >> word;
				user->saveToMemory(word);
			}
			else if (choice == 6) {
				user = nullptr;
				isLoggedIn = false;
				std::cout << "Logged out " << endl;
			}
			else if (choice == -404) {
				user->deleteAccount();
				user = nullptr;
				isLoggedIn = false;
				std::cout << "Account Deleted Successfully." << endl;
			}
			else {
				std::cout << "Invalid Choice" << endl;
			}
		}
		std::cout << "____________________________________________________________" << endl << endl << endl;
	}
}