#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include"FilesLayer.h"
#include"DataLayer.h"
#include "Login.h"
#include "MainMenu.h"
#include "Services.h"
#include"CheckTransactions.h"

using namespace File;
//using namespace Print;
using namespace Date;

using namespace DataLayer;
using namespace Login;
using namespace MainMenu;
using namespace std;

void PrintTransaction(const StTransactions &Transaction)
{
    cout << endl << endl;
    cout << "\t\t\t\t Bank Name Of Sender     : " << Transaction.BankNameForSender << endl;
    cout << "\t\t\t\t Bank Name Of Reciever   : " << Transaction.BankNameForReceiver << endl;
    cout << "\t\t\t\t Date                    : " << Transaction.Date << endl;
    cout << "\t\t\t\t Sender Phone Number     : " << Transaction.PhoneNumber_From << endl;
    cout << "\t\t\t\t Reciever Phone Number   : " << Transaction.PhoneNumber_To << endl;
    cout << "\t\t\t\t Balance                 : " << Transaction.Amount << endl << endl;
}

int main() {
    File::Access_LoadUsersListFromFiles(Users, PersonalInfoFile, AccountsInfoFile, AddressInfoFile, TransactionsInfoFile);

    srand((unsigned int)time(0));
    system("color 0E");
    Login::HaveAccount();

    File::Access_SaveUsersToFiles(Users, AccountsInfoFile, AddressInfoFile, PersonalInfoFile);
}