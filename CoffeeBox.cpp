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

int main()
{
	const double CAPPUCCINO_PRICE = 2.0;
	const double LATTE_PRICE = 3.0;
	const double ESPRESSO_PRICE = 1.5;

	int userChoice = 0;
	int cupCount = 2;
	double userBalance = 0.0;
	double boxBalance = 0.0;

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