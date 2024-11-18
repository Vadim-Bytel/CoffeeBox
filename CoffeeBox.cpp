#include <iostream>
#include <iomanip>

using namespace std;

const int PIN = 1234;
const int CUP_MAX = 700;
const int MAX_TRYS_FOR_PIN = 3;

const double CAPPUCCINO_PRICE = 2.0;
const double LATTE_PRICE = 3.0;
const double ESPRESSO_PRICE = 1.5;

bool isCorrectPIN = false;
bool isMachineBlocked = false;

int cupCount = 7;
double userBalance = 0.0;
double boxBalance = 0.0;

// userFunctions
void ShowCoffeeMenu();
void ShowCoinMenu();
void ShowMaintenanceMenu();
void GetCoin();
bool IsEnoughMoney(double price);
bool IsEnoughCups();
void SetPrecision(int precision);
void UserSelectionMenu();
void CoffeeOrder(int userChoice);
void OrderFulfilment(const double PRICE, const char *CoffeeText);

// Service functions
void ServiceSelectorMenu();
void ShowServicePIN();
void ShowCupsMenu();
void Withdrawal();
void AddCups();
void ShowServiceMenu();
void BlockMaintance();
void InputPIN();
void PinCorrectMenuSelector();

int main()
{
    SetPrecision(2);

    UserSelectionMenu();

    return 0;
}

void SetPrecision(int precision)
{
    cout << fixed << setprecision(precision);
}

void ShowCoffeeMenu()
{
    system("cls");
    cout << "==============\n"
         << "Balance: " << userBalance << endl
         << "1) Insert coin\n"
         << "2) Cappuccino\n"
         << "3) Latte\n"
         << "4) Espresso\n"
         << "5) Service\n"
         << "==============\n";
}

void ShowCoinMenu()
{
    system("cls");
    cout << "===========================\n"
         << "Balance: " << userBalance << endl
         << "1) 10 kopeks\n"
         << "2) 20 kopeks\n"
         << "3) 50 kopeks\n"
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

void GetCoin()
{
    int choice = 0;

    while (true)
    {
        ShowCoinMenu();

        cout << "Insert coin: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            userBalance += 0.1;
            break;
        case 2:
            userBalance += 0.2;
            break;
        case 3:
            userBalance += 0.5;
            break;
        case 4:
            userBalance += 1;
            break;
        case 5:
            userBalance += 2;
            break;
        case 6:
            return;
        default:
            cout << "\nWrong choice. Input [1..6], please\n";
            system("pause");
            break;
        }
        system("cls");
    }
}

bool IsEnoughMoney(double price)
{
    return price < userBalance;
}

bool IsEnoughCups()
{
    return cupCount > 0;
}

double Payment(double price)
{
    return userBalance - price;
}

void UserSelectionMenu()
{
    int userChoice = 0;

    do
    {
        if (boxBalance == 0)
            userBalance = 0.0;

        if (IsEnoughCups())
        {
            ShowCoffeeMenu();
        }
        else
        {
            ShowMaintenanceMenu();
        }

        cout << "Your choice: ";
        cin >> userChoice;

        if (IsEnoughCups())
        {
            if (userChoice == 1)
            {
                GetCoin();
                boxBalance += userBalance;
            }
            else if (2 <= userChoice && userChoice <= 4)
            {
                CoffeeOrder(userChoice);
            }
        }
        else if (userChoice == 5)
        {
            ServiceSelectorMenu();
        }
        else
        {
            cout << "\nWrong choice. Input [1..5], please\n\n";
        }
        system("pause");
    } while (true);
}

void CoffeeOrder(int userChoice)
{
    const char *CapuchinnoMessage = "Ok, take your cappuccino";
    const char *LatteMessage = "Ok, take your latte";
    const char *EspressoMessage = "Ok, take your espresso";

    switch (userChoice)
    {
    case 2:
        OrderFulfilment(CAPPUCCINO_PRICE, CapuchinnoMessage);
        break;
    case 3:
        OrderFulfilment(LATTE_PRICE, LatteMessage);
        break;
    case 4:
        OrderFulfilment(ESPRESSO_PRICE, EspressoMessage);
        break;
    }
}

void OrderFulfilment(const double PRICE, const char *CoffeeText)
{
    if (IsEnoughMoney(PRICE))
    {
        cout << CoffeeText << endl;
        userBalance -= PRICE;
        cupCount--;
    }
    else
    {
        cout << "Insufficient funds.\n";
    }
}

// Service functions
void ServiceSelectorMenu()
{
    int userChoice;

    if (isMachineBlocked)
    {
        cout << "Machine Blocked!" << endl;
    }

    while (!isMachineBlocked)
    {
        if (!isCorrectPIN)
        {
            ShowServicePIN();
            cout << "Your choise: ";
            cin >> userChoice;

            if (userChoice == 1)
            {
                InputPIN();
            }
            else
            {
                cout << "Back to Coffee menu!" << endl;
                system("pause");
                break;
            }
        }

        if (isCorrectPIN)
        {
            PinCorrectMenuSelector();
        }
    }
}

void ShowServicePIN()
{
    system("cls");
    cout << "=====================\n";
    cout << "1) Enter PIN\n";
    cout << "2) Back to CoffeeMenu\n";
    cout << "=====================\n";
}

void InputPIN()
{
    int input;

    for (int i = 0; i < MAX_TRYS_FOR_PIN; i++)
    {
        cout << "Enter PIN:";
        cin >> input;
        if (input == PIN)
        {
            isCorrectPIN = true;
            return;
        }
    }

    system("cls");
    cout << "Input PIN INCORRECT! Machine blocked!\n";
    system("pause");
    isMachineBlocked = true;
}

void ShowServiceMenu()
{
    system("cls");
    cout << "=====================\n";
    cout << "Cups: " << cupCount << endl;
    cout << "Balance: " << boxBalance << endl;
    cout << "1) Add cups\n";
    cout << "2) Withdrawal\n";
    cout << "3) Back to Coffee menu\n";
    cout << "=====================\n";
}

void PinCorrectMenuSelector()
{
    int userChoice;

    ShowServiceMenu();

    cout << "Your choise: ";
    cin >> userChoice;

    switch (userChoice)
    {
    case 1:
        ShowCupsMenu();
        AddCups();
        break;
    case 2:
        Withdrawal();
        break;
    case 3:
        BlockMaintance();
        return;
        break;
    default:
        cout << "\nWrong choice. Input [1..3], please\n\n";
        system("pause");
        break;
    }
}

void BlockMaintance()
{
    isCorrectPIN = false;
}

void ShowCupsMenu()
{
    system("cls");
    cout << "=====================\n";
    cout << "1) Input cups [0...50]\n";
    cout << "2) Back to Service menu\n";
    cout << "=====================\n";
}

void Withdrawal()
{
    boxBalance = 0.0;
    cout << "Balance cleared" << endl;
    system("pause");
}

// Need refactoring for new Requirments
void AddCups()
{
    int addCups;

    do
    {
        cout << "Input cups for add:";
        cin >> addCups;

        if (addCups < 0 || (addCups + cupCount) > 700)
        {
            cout << "Input correct cup count to add, please (sum of cups might be less or equals than " << CUP_MAX << ")!" << endl;
            system("pause");
        }
        else
        {
            break;
        }
    } while (true);

    cupCount = addCups + cupCount;
    cout << "New count of cups: " << cupCount << endl;
    system("pause");
}
