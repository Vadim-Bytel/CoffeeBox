#include <iostream>
#include <iomanip>
using namespace std;

//userFunctions
void ShowCoffeeMenu(double balance);
void ShowCoinMenu(double balance);
void ShowMaintenanceMenu();
double GetCoin(double userBalance);
double Payment(double userBalance, double price);
bool IsEnough(double balance, double price);
void SetPrecision(int precision);

int main()
{
	const double CAPPUCCINO_PRICE = 2.0;
	const double LATTE_PRICE = 3.0;
	const double ESPRESSO_PRICE = 1.5;

	int userChoice = 0;
	int cupCount = 2;
	double userBalance = 0.0;
	double boxBalance = 0.0;

	SetPrecision(2);
	while (true)
	{
		//Проверка для взаимодействия с модулем Сервиса, не понадобится уберешь
		if (boxBalance == 0)
			userBalance = 0.0;

		if (cupCount > 0)
		{
			ShowCoffeeMenu(userBalance);
		}
		else
		{
			ShowMaintenanceMenu();
			//Если кончились стаканчики доступен переход в сервис меню, для их пополнения
		}

		cout << "Your choice: ";
		cin >> userChoice;

		if (userChoice == 1)
		{
			userBalance = GetCoin(userBalance);
			boxBalance += userBalance;

		}
		else if (userChoice == 2 && IsEnough(userBalance, CAPPUCCINO_PRICE))
		{
			userBalance = Payment(userBalance, CAPPUCCINO_PRICE);
			cout << "Ok, take your cappuccino\n";
			cupCount--;
		}
		else if (userChoice == 3 && IsEnough(userBalance, LATTE_PRICE))
		{
			userBalance = Payment(userBalance, LATTE_PRICE);
			cout << "Ok, take your latte\n";
			cupCount--;
		}
		else if (userChoice == 4 && IsEnough(userBalance, ESPRESSO_PRICE))
		{
			userBalance = Payment(userBalance, ESPRESSO_PRICE);
			cout << "Ok, take your espresso\n";
			cupCount--;
		}
		else if (userChoice == 5)
		{
			//service functions
		}
		else if (userChoice < 1 || userChoice > 5)
		{
			cout << "\nWrong choice. Input [1..5], please\n\n";
		}
		system("pause");
	}
	return 0;
}

void SetPrecision(int precision)
{
	cout << fixed << setprecision(precision);
}

void ShowCoffeeMenu(double balance)
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

void ShowCoinMenu(double balance)
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

void ShowMaintenanceMenu()
{
	system("cls");
	cout << "ON MAINTENANCE\n";
	cout << "5) Service\n";
}

double GetCoin(double balance)
{
	int choice = 0;

	while (true)
	{
		ShowCoinMenu(balance);

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

bool IsEnough(double balance, double price)
{
	if (balance < price)
	{
		cout << "Insufficient funds.\n";
		return false;
	}
	else
		return true;
}

double Payment(double balance, double price)
{
	return balance - price;
}