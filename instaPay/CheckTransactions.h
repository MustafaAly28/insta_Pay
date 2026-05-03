#pragma once
#include <iostream>
#include <string>
#include "DataLayer.h"
#include "FilesLayer.h"
#include "Login.h"

using namespace std;
using namespace Login;
using namespace DataLayer;

namespace MainMenu
{
    void ShowDateTime();
    int AccountIndex;
}

using namespace MainMenu;

namespace CheckTransaction
{
    void PrintTransactionHeader(string title)
    {
        PlaySound(TEXT("Sounds\\xmersounds-soft-treble-fast-collect-fade-out-ending-sound-effect-416828.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "\n==========================================\n";
        cout << "           " << title << "           ";
        cout << "\n==========================================\n";
    }

    void ShowUserAccounts()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader(" YOUR LINKED ACCOUNTS ");

        cout << " ACCOUNTS IS  [" << CurrentUser.CountAccounts << "] :" << endl;

        for (int i = 0; i < CurrentUser.CountAccounts; i++)
        {
            cout << "  - Account     : " << i + 1 << endl;
            cout << "  - Bank Name   : " << CurrentUser.AccountsList[i].BankName << endl;
            cout << "------------------------------------------\n";
        }
    }

    string maskPhone(string phone)
    {
      
        if (phone.empty() || phone.length() < 5) return phone;

        int visibleStart = 3;
        int visibleEnd = 2;
        string masked = "";

        masked += phone.substr(0, visibleStart);
        for (int i = visibleStart; i < (int)phone.length() - visibleEnd; i++)
            masked += "*";
        masked += phone.substr(phone.length() - visibleEnd);

        return masked;
    }

    
    void PrintSingleTransaction(const StTransactions& Transaction, int Number, string Type)
    {
        cout << Type << " # " << Number << " #" << endl;

     
        if (Transaction.BankNameForSender != "")
            cout << "  - Bank (From) : " << Transaction.BankNameForSender << endl;

        if (Transaction.BankNameForReceiver != "")
            cout << "  - Bank (To)   : " << Transaction.BankNameForReceiver << endl;

        if (Transaction.PhoneNumber_From != "")
            cout << "  - From Phone  : " << maskPhone(Transaction.PhoneNumber_From) << endl;

        if (Transaction.PhoneNumber_To != "")
            cout << "  - To Phone    : " << maskPhone(Transaction.PhoneNumber_To) << endl;

        cout << "  - Amount      : " << Transaction.Amount << " EGP" << endl;
        cout << "  - Date        : " << Transaction.Date << endl;
        cout << "------------------------------------------\n";
    }

    void PrintSingleDonation(const StDonation& Donation, int Number, string Type)
    {
        cout << Type << " # " << Number << " #" << endl;

       
        if (Donation.BankNameForSender != "")
            cout << "  - Bank (From)  : " << Donation.BankNameForSender << endl;

        if (Donation.OrganizationName != "")
            cout << "  - Bank (To)    : " << Donation.OrganizationName << endl;

        if (Donation.CardNumber != "")
            cout << "  - Card Number  : " << Donation.CardNumber << endl;

        cout << "  - Amount       : " << Donation.Amount << " EGP" << endl;
        cout << "  - Date         : " << Donation.Date << endl;
        cout << "------------------------------------------\n";
    }

    void CheckDeposits()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader("DEPOSITS HISTORY");

        if (CurrentUser.DepositsCount == 0)
        {
            //Beep(200, 600);
            cout << "   No deposits found.\n";
        }
        else
        {
            for (int i = 0; i < CurrentUser.DepositsCount; i++)
            {
                PrintSingleTransaction(CurrentUser.Deposits[i], i + 1, "Deposit");
            }
        }
    }

    void CheckWithdrawals()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader("WITHDRAWALS HISTORY");

        if (CurrentUser.WithdrawalsCount == 0)
        {
            //Beep(200, 600);
            cout << "  No withdrawals found.\n";
        }
        else
        {
            for (int i = 0; i < CurrentUser.WithdrawalsCount; i++)
            {
                PrintSingleTransaction(CurrentUser.Withdrawals[i], i + 1, "Withdrawal");
            }
        }
    }

    void CheckSentTransactions()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader("SENT TRANSACTIONS");

        if (CurrentUser.TransactionsCountSending == 0)
        {
            //  Beep(200, 600);
            cout << "   No sent transactions found.\n";
        }
        else
        {
            for (int i = 0; i < CurrentUser.TransactionsCountSending; i++)
                PrintSingleTransaction(CurrentUser.TransactionsSending[i], i + 1, "Transfer (Sent)");
        }
    }

    void CheckReceivedTransactions()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader("RECEIVED TRANSACTIONS");

        if (CurrentUser.TransactionsCountRecieving == 0)
        {
            cout << "   No received transactions found.\n";
        }
        else
        {
            for (int i = 0; i < CurrentUser.TransactionsCountRecieving; i++)
                PrintSingleTransaction(CurrentUser.TransactionsRecieving[i], i + 1, "Transfer (Received)");
        }
    }

    
    void CheckDonations()
    {
        const StUser& CurrentUser = Users[UserIndex];
        PrintTransactionHeader("DONATIONS HISTORY");

        if (CurrentUser.DonationsCount == 0)
        {
            cout << "  No Donations found.\n";
        }
        else
        {
            for (int i = 0; i < CurrentUser.DonationsCount; i++)
                PrintSingleDonation(CurrentUser.Donations[i], i + 1, "Donation");
        }
    }

    void CheckTransactions()
    {
        PrintTransactionHeader(" TRANSACTIONS HISTORY ");

        ShowUserAccounts();
        cout << "\nPress any key to view Sent Transfers...\n";
        system("pause > nul");

        CheckSentTransactions();
        cout << "\nPress any key to view Received Transfers...\n";
        system("pause > nul");

        CheckReceivedTransactions();
        cout << "\nPress any key to view Deposits...\n";
        system("pause > nul");

        CheckDeposits();
        cout << "\nPress any key to view Withdrawals...\n";
        system("pause > nul");

        CheckWithdrawals();
        cout << "\nPress any key to view Donations...\n";
        system("pause > nul");

        CheckDonations();

        cout << "\n==========================================\n";
        cout << "        END OF TRANSACTION HISTORY        \n";
        cout << "==========================================\n";
        system("pause");
    }
}