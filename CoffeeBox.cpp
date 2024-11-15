#include <iostream>
#include <iomanip>
using namespace std;

//userFunctions
void showCoffeeMenu(double balance);
void showCoinMenu(double balance);
void showMaintenanceMenu();
double getCoin(double userBalance);
double payment(double userBalance, double price);
bool isEnough(double balance, double price);
void setPrecision(int precision);

//Service functions
void ShowServicePIN();
void ShowServiceMenu(int cupsCount, double balance);
void InputPIN(bool& isCorrectPIN, bool& isMachineBlocked, const int PIN, const int MAX_TRYS_FOR_PIN);
void ServiceSelectOption(const int CUPS_MAX, double& balance, int& cupCount, int input, bool& isCorrectPIN);

int main()
{
	const int PIN = 1234;
	const int CUP_MAX = 50;
	const int MAX_TRYS_FOR_PIN = 3;
	const double CAPPUCCINO_PRICE = 2.0;
	const double LATTE_PRICE = 3.0;
	const double ESPRESSO_PRICE = 1.5;

	int userChoice = 0;
	int cupCount = 2;
	double userBalance = 0.0;
	double boxBalance = 0.0;
	bool isCorrectPIN = false;
	bool isMachineBlocked = false;

	setPrecision(2);
	while (true)
	{
		//Проверка для взаимодействия с модулем Сервиса, не понадобится уберешь
		if (boxBalance == 0)
			userBalance = 0.0;

		if (cupCount > 0)
		{
			showCoffeeMenu(userBalance);
		}
		else
		{
			showMaintenanceMenu();
			//Если кончились стаканчики доступен переход в сервис меню, для их пополнения
		}

		cout << "Your choice: ";
		cin >> userChoice;

		if (userChoice == 1)
		{
			userBalance = getCoin(userBalance);
			boxBalance += userBalance;

		}
		else if (userChoice == 2 && isEnough(userBalance, CAPPUCCINO_PRICE))
		{
			userBalance = payment(userBalance, CAPPUCCINO_PRICE);
			cout << "Ok, take your cappuccino\n";
			cupCount--;
		}
		else if (userChoice == 3 && isEnough(userBalance, LATTE_PRICE))
		{
			userBalance = payment(userBalance, LATTE_PRICE);
			cout << "Ok, take your latte\n";
			cupCount--;
		}
		else if (userChoice == 4 && isEnough(userBalance, ESPRESSO_PRICE))
		{
			userBalance = payment(userBalance, ESPRESSO_PRICE);
			cout << "Ok, take your espresso\n";
			cupCount--;
		}
		else if (userChoice == 5)
		{
			while (!isMachineBlocked) {
				if (!isCorrectPIN) {
					ShowServicePIN();
					cout << "Your choise: ";
					cin >> userChoice;
					if (userChoice == 1) {
						InputPIN(isCorrectPIN, isMachineBlocked, PIN, MAX_TRYS_FOR_PIN);
					}
					else {
						break;
					}
				}

				if (isCorrectPIN) {
					ShowServiceMenu(cupCount, boxBalance);
					cout << "Your choise: ";
					cin >> userChoice;
					if (userChoice == 3) {
						BlockMaintance(isCorrectPIN);
						break;
					} else {
						ServiceSelectOption(CUP_MAX, boxBalance, cupCount, userChoice, isCorrectPIN);
					}
				}
			}
		}
		else if (userChoice < 1 || userChoice > 5)
		{
			cout << "\nWrong choice. Input [1..5], please\n\n";

		}
		system("pause");
	}
	return 0;
}

void setPrecision(int precision)
{
	cout << fixed << setprecision(precision);
}

void showCoffeeMenu(double balance)
{
	system("cls");
	cout << "==============\n"
			 << "Balance: " << balance << endl
			 << "1) Insert coin\n"
			 << "2) Cappuccino\n"
			 << "3) Latte\n"
			 << "4) Espresso\n"
			 << "5) Service\n"
			 << "==============\n";
}

void showCoinMenu(double balance)
{
	system("cls");
	cout << "===========================\n"
			 << "Balance: " << balance << endl
			 << "1) 10 kopeks\n"
			 << "2) 20 kopeks\n"
			 << "3) 30 kopeks\n"
			 << "4) 1 ruble\n"
			 << "5) 2 rubles\n"
			 << "6) Back to Coffee selection\n"
			 << "===========================\n";
}

void showMaintenanceMenu()
{
	system("cls");
	cout << "ON MAINTENANCE\n";
	cout << "5) Service\n";
}

double getCoin(double balance)
{
	int choice = 0;

	while (true)
	{
		showCoinMenu(balance);

		cout << "Insert coin: ";
		cin >> choice;

		if (choice == 1)
			balance += 0.1;
		else if (choice == 2)
			balance += 0.2;
		else if (choice == 3)
			balance += 0.5;
		else if (choice == 4)
			balance += 1;
		else if (choice == 5)
			balance += 2;
		else if (choice == 6)
			return balance;
		else
		{
			cout << "\nWrong choice. Input [1..6], please\n";
			system("pause");
		}
		system("cls");
	}
}

bool isEnough(double balance, double price)
{
	if (balance < price)
	{
		cout << "Insufficient funds.\n";
		return false;
	}
	else
		return true;
}

double payment(double balance, double price)
{
	return balance - price;
}

void ShowServicePIN(){
	system("cls");
	cout << "=====================\n";
	cout << "1) Enter PIN\n";
	cout << "2) Back to CoffeeMenu\n"; 
	cout << "=====================\n";
}

void InputPIN(bool& isCorrectPIN, bool& isMachineBlocked, const int PIN, const int MAX_TRYS_FOR_PIN){
	int input;

	for(int i = 0; i < MAX_TRYS_FOR_PIN; i++){
		cout << "Enter PIN:";
		cin >> input;
		if(input == PIN){
			isCorrectPIN = true;
			return;
		}
	}

	system("cls");
	cout << "Input PIN INCORRECT! Machine blocked!\n";
	system("pause");
	isMachineBlocked = true;
}

void ShowServiceMenu(int cupsCount, double balance){
	system("cls");
	cout << "=====================\n";
	cout << "Cups: " << cupsCount << endl;
	cout << "Balance: " << balance << endl;
	cout << "1) Add cups\n";
	cout << "2) Withdrawal\n";
	cout << "3) Back to Coffee menu\n"; 
	cout << "=====================\n";
}

void BlockMaintance(bool& isCorrectPIN){
	isCorrectPIN = false;
}

void ShowCupsMenu(){
	system("cls");
	cout << "=====================\n";
	cout << "1) Input cups [0...50]\n";
	cout << "4) Back to Service menu\n"; 
	cout << "=====================\n";
}

void Withdrawal(int& balance){
	balance = 0;
	cout << "Balance cleared";
	system("pause");
}


void ServiceSelectOption(const int CUPS_MAX, double& balance, int& cupCount, int input, bool& isCorrectPIN){
	while(true){
		switch (input)
		{
		case 1:
			break;
		case 2:
			break;
		default:
			"Your input Incorrect! Input [1..3], please\n";
			break;
		}
	}
}

void AddCups(const int CUPS_MAX, int& cupCount) {
	int addCups;
	cout << "Input cups for add:";
	cin >> addCups;
	cupCount = max(CUPS_MAX, cupCount + addCups);
	cout << "New count of cups: " << cupCount << endl;
	system("pause");
}
