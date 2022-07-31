#include "Account.h"
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<time.h>

void Account::Register(const string& username, const string& password)
{
	if (!checkUsername(username)) {
		Account user = Account(username, password);
		saveUserProfile(user);
	}
	else
		throw exception("Username Already Exists");
}

Account* Account::Login(const string& username, const string& password)
{
	bool isLoggedIn = false;
	Account* user = nullptr;
	if (checkUsername(username))
	{
		string actual_username, actual_password;
		ifstream file;

		file.open(getFileName(username), ios::in);
		file >> actual_username;
		file >> actual_password;
		if (password == actual_password) {
			isLoggedIn = true;
			user = new Account(username, password);
			int newSize;
			string word;
			file >> user->m_balance;
			file >> newSize;
			file >> word;
			user->m_balance += 10;
			user->increaseMemorySize(newSize);
			user->saveToMemory(word);
		}
		file.close();

		if (isLoggedIn)
			saveUserProfile(*user);
	}

	if (!isLoggedIn)
		throw exception("Username or password is wrong");

	return user;
}

int Account::getBalance() {
	return m_balance;
}

void Account::saveUserProfile(Account account) {
	ofstream file;
	file.open(getFileName(account.username), ios::out | ios::trunc);
	file << account.username << endl;
	file << account.m_password << endl;
	file << account.m_balance << endl;
	file << account.m_memSize << endl;
	file << account.getSavedMemory() << endl;
	file.close();
}

bool Account::checkUsername(const string& username) {
	if (FILE* file = fopen(getFileName(username).c_str(), "r")) {
		fclose(file);
		return true;
	}
	return false;
}

Account::Account(const string& username, const string& password)
	:username(username), m_password(password), m_balance(0), m_memSize(0), m_memory(nullptr)
{}

int genRandom(int min, int max) {
	return rand() % (max - min + 1) - min;
}

void Account::increaseMoneyWithMathQuiz() {
	cout << endl << endl << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl << "You have to answer some Math questions to increase your balance" << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
		srand((unsigned int)time(0));
		int answer;
		int a = genRandom(0, 10), b = genRandom(0, 10);
		cout << a << " + " << b << " = ";
		cin >> answer;
		if (a + b == answer) {
			cout << "[+] Correct. +" << answer << endl;
			m_balance += answer;
		}
		else {
			cout << "[+] Wrong. -5 " << endl;
			if (m_balance - 5 >= 0)
				m_balance -= 5;
		}
		cout << endl;
	}
	Account user = Account(*this);
	saveUserProfile(user);
}

size_t Account::getMemorySize() {
	return m_memSize;
}

string Account::getSavedMemory() {
	if (m_memory != nullptr)
		return string(m_memory).substr(0, m_memSize);
	return "";
}

int Account::getPricePerLocation() {
	return m_pricePerLocation;
}

void Account::saveToMemory(string word) {
	m_memory = new char[m_memSize];
	for (size_t i = 0; i < m_memSize && i < word.length(); i++)
		m_memory[i] = word[i];
	saveUserProfile(Account(*this));
}

void Account::buyMemoryStorage(int amount) {
	if (m_memSize + amount <= MAX_MEMORY_SIZE) {
		int price = amount * m_pricePerLocation;
		if (price <= m_balance) {
			m_balance -= price;
			increaseMemorySize(amount);
			saveUserProfile(Account(*this));
		}
		else {
			stringstream ss("");
			ss << "you don\'t have enough balance. you need " << price - m_balance;
			throw exception(ss.str().c_str());
		}
	}
	else {
		stringstream ss("");
		ss << "you can\'t exceed the Maximum Storage limit which is " << MAX_MEMORY_SIZE;
		int avialableSize = MAX_MEMORY_SIZE - m_memSize;
		if (avialableSize > 0)
			ss << endl << "you can buy only " << avialableSize << " Locations.";
		throw exception(ss.str().c_str());
	}
}

void Account::increaseMemorySize(int amount) {
	size_t newSize = m_memSize + amount;
	char* newMem = new char[newSize];
	memset(newMem, '0', newSize * sizeof(char));
	memcpy(newMem, m_memory, m_memSize);
	m_memSize = newSize;
	m_memory = newMem;
}

Account::Account(const Account& account) {
	username = account.username;
	m_password = account.m_password;
	m_balance = account.m_balance;
	m_memSize = account.m_memSize;
	m_memory = account.m_memory;
}

void Account::deleteAccount() {
	remove(getFileName(username).c_str());
	username = "";
	m_password = "";
	m_balance = 0;
	m_memSize = 0;
	m_memory = nullptr;
}

string Account::getFileName(string username) {
	stringstream ss;
	ss << username << EXTENSION;
	return ss.str();
}