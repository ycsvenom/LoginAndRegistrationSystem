#pragma once
#include<iostream>

using namespace std;

#define MAX_MEMORY_SIZE 4000
const string EXTENSION = ".acc";
const string PATH = ".\\Accounts\\";

class Account
{
public:
	
	string username;

	static void Register(const string& username, const string& password);

	static Account* Login(const string& username, const string& password);

	void increaseMoneyWithMathQuiz();

	int getBalance();

	size_t getMemorySize();

	int getPricePerLocation();

	string getSavedMemory();

	void saveToMemory(string word);

	void buyMemoryStorage(int amount);

	void deleteAccount();

private:

	int m_pricePerLocation = 10;

	string m_password;

	char* m_memory = nullptr;

	size_t m_memSize = 0;

	int m_balance = 0;

	void increaseMemorySize(int amount);

	static string getFileName(string username);

	static void saveUserProfile(Account account);

	static bool checkUsername(const string& username);

	Account(const string& username, const string& password);

	Account(const Account& account);
};

