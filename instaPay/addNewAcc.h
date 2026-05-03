#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include"DataLayer.h"
#include"FilesLayer.h"
#include"Login.h"

using namespace std;
using namespace Login;
namespace AddNewAccount
{
    void PrintAddNewAccountHider()
    {
        cout << "\n==========================================\n";
        cout << "                AddNewAcount                  ";
        cout << "\n==========================================\n";
    }

    string ConvertTOLower(string S)
    {
        for (int i = 0; i < (int)S.length(); i++)
        {
            S[i] = tolower(S[i]);
        }
        return S;
    }

    bool ValidBank(string BankName)
    {


        string BankNames[] = { "Bank Al Ahly", "CIB" , "Bank Masr" ,"NBE","ADIB","QNB","FAB" };
        const int CountBank = 7;
        bool IsValid = true;

        for (int Bank = 0; Bank < CountBank; Bank++)
        {
            if (ConvertTOLower(BankNames[Bank]) == ConvertTOLower(BankName))
            {
                BankName = BankNames[Bank];
                return IsValid;
            }
        }
        return !IsValid;


    }



    bool ValidCardNumber(string CardNumber)
    {
        if (CardNumber[0] != '5' && CardNumber[0] != '4')
        {
            cout << "Card number must start with 4 or 5!\n"; return false;
        }
        if (CardNumber.length() != 16)
        {
            cout << "Card number must be xxxx xxxx xxxx xxxx!\n"; return false;
        }
        for (int i = 0; i < CardNumber.length(); i++)
        {
            if (!isdigit(CardNumber[i]))
            {
                cout << "Card number must contain only digits!\n"; return false;
            }
        }
        for (int i = 0; i < AddingUsersCounter; i++)
        {
            for (int j = 0; j < Users[i].CountAccounts; j++)
            {
                if (CardNumber == Users[i].AccountsList[j].CardNumber)
                {
                    cout << "This card number is already in use! Please enter a different one." << endl;
                    return false;
                }
            }
        }
        return true;
    }



    bool ValidExpirationDate(string ExpDate)
    {
        if (ExpDate.length() != 5 || ExpDate[2] != '/')
        {
            return false;
        }
        string Month = ExpDate.substr(0, 2);
        string Year = ExpDate.substr(3, 2);
        if (!isdigit(Month[0]) || !isdigit(Month[1]) || !isdigit(Year[0]) || !isdigit(Year[1])) {
            return false;
        }
        int MonthInt = stoi(Month);
        if (MonthInt < 1 || MonthInt > 12) {
            return false;
        }
        int YearInt = stoi(Year);
        if (YearInt < 26 || YearInt > 40) {
            return false;
        }
        return true;
    }

    bool ValidCVV(string CVV) {
        if (CVV.length() != 3) { cout << "CVV must be 3 digits!\n"; return false; }
        for (int i = 0; i < CVV.length(); i++) {
            if (!isdigit(CVV[i])) {
                cout << "CVV must contain only digits!\n"; return false;
            }
        }
        return true;
    }


    bool ValidPIN(string PIN) {
        if (PIN.length() != 4) { cout << "PIN must be 4 digits!\n"; return false; }
        for (int i = 0; i < PIN.length(); i++) {
            if (!isdigit(PIN[i])) {
                cout << "PIN must contain only digits!\n"; return false;
            }
        }
        return true;
    }



    StAccount ReadNewAccountData()
    {
        StAccount NewAccount;
        string TempInput;

        PrintAddNewAccountHider();



        // 1. Bank Name Validation
        while (true) {
            string CheckBank;
            cout << "Enter Bank Name ( Bank Al Ahly, CIB, Bank Masr, NBE, ADIB, QNB, FAB ) : ";
            getline(cin >> ws, CheckBank);

            if (ValidBank(CheckBank)) {
                NewAccount.BankName = CheckBank;
                break;
            }
            else {
                cout << "Invalid Bank Name! Please Choose from the available banks.\n";
            }
        }

        // 2. Card Number Validation
        while (true) {
            string CheckCard;
            cout << "Enter Card Number (16 digits starting with 4 or 5): ";
            cin >> CheckCard;
            if (ValidCardNumber(CheckCard)) {
                NewAccount.CardNumber = CheckCard;
                break;
            }
            cout << "Invalid Card Number! Please ensure it's 16 digits and starts with 4 or 5.\n";
        }

        //  Expiration_Date Validation
        while (true) {
            string CheckExp;
            cout << "Enter Expiration Date (MM/YY): ";
            cin >> CheckExp;
            if (ValidExpirationDate(CheckExp)) {
                NewAccount.ExpirationDate = CheckExp;
                break;
            }
            else {
                cout << "Invalid Expiration Date! Please enter a valid date in MM/YY format.\n";
            }
        }

        //  Holder Name
        cout << "Enter Holder Name: ";
        cin >> ws;
        getline(cin, NewAccount.HolderName);

        //  CVV Validation
        while (true) {
            string CheckCVV;
            cout << "Enter CVV Code (3 digits): ";
            cin >> CheckCVV;
            if (ValidCVV(CheckCVV)) {
                NewAccount.CVVCode = CheckCVV;
                break;
            }
        }

        //  PIN Validation
        while (true) {
            string CheckPIN;
            cout << "Create a 4 digit PIN code for your account: ";
            cin >> CheckPIN;
            if (ValidPIN(CheckPIN)) {
                NewAccount.PINCode = CheckPIN;
                break;
            }
        }

        //  Balance Generation
        NewAccount.Balance = (rand() % 9001) + 1000;
        cout << "Your initial balance is: " << NewAccount.Balance << endl;

        return NewAccount;
    }

    void addNewAccount()
    {
        if (Users[UserIndex].CountAccounts >= 3)
        {
            cout << "\nError: You reached maximum limit of Accounts.\n";
            return;
        }

        StAccount NewAccount = ReadNewAccountData();

        int CurrentAccPos;

        CurrentAccPos = Users[UserIndex].CountAccounts;

        Users[UserIndex].AccountsList[CurrentAccPos] = NewAccount;

        Users[UserIndex].CountAccounts++;


        cout << "\n Account added successfully .\n";
    }
}
