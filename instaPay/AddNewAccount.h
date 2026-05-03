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
        PlaySound(TEXT("Sounds\\xmersounds-soft-treble-fast-collect-fade-out-ending-sound-effect-416828.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "\n\t\t\t\t==========================================\n";
        cout << "\t\t\t\t                AddNewAcount                  ";
        cout << "\n\t\t\t\t==========================================\n";
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
            Beep(200, 600);
            cout << "\t\t\t\tCard number Must Start With 4 Or 5!\n"; return false;
        }
        if (CardNumber.length() != 16)
        {
            Beep(200, 600);
            cout << "\t\t\t\tCard Number Must Be XXXX XXXX XXXX XXXX!\n"; return false;
        }
        for (int i = 0; i < CardNumber.length(); i++)
        {
            if (!isdigit(CardNumber[i]))
            {
                Beep(200, 600);
                cout << "\t\t\t\tCard Number Must Contain Only Digits !\n"; return false;
            }
        }
        for (int i = 0; i < AddingUsersCounter; i++)
        {
            for (int j = 0; j < Users[i].CountAccounts; j++)
            {
                if (CardNumber == Users[i].AccountsList[j].CardNumber)
                {
                    Beep(200, 600);
                    cout << "\t\t\t\tThis Card Number Is Already In Use! Please Enter A Different One." << endl;
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
        if (CVV.length() != 3) { Beep(200, 600); cout << "\t\t\t\tCVV Must Be 3 Digits!\n"; return false; }
        for (int i = 0; i < CVV.length(); i++) {
            if (!isdigit(CVV[i])) {
                Beep(200, 600);
                cout << "\t\t\t\tCVV Must Contain Only Digits!\n"; return false;
            }
        }
        return true;
    }


    bool ValidPIN(string PIN) {
        if (PIN.length() != 4) { Beep(200, 600); cout << "\t\t\t\tPIN Must Be 4 Digits!\n"; return false; }
        for (int i = 0; i < PIN.length(); i++) {
            if (!isdigit(PIN[i])) {
                Beep(200, 600);
                cout << "\t\t\t\tPIN must Contain Only Digits!\n"; return false;
            }
        }
        return true;
    }



    StAccount ReadNewAccountData()
    {
        StAccount NewAccount;
        string TempInput;

        ShowLoading();

        PrintAddNewAccountHider();


        //  Bank Name Validation
        while (true) {
            string CheckBank;
            cout << "\t\t\tAvilable Banks : Bank Al Ahly, CIB, Bank Masr, NBE, ADIB, QNB, FAB\n";
            cout << "\t\t\t\tEnter Bank Name : ";

            getline(cin >> ws, CheckBank);

            if (ValidBank(CheckBank)) {
                NewAccount.BankName = CheckBank;
                break;
            }
            else {
                Beep(200, 600);
                cout << "\t\t\t\tInvalid Bank Name! Please Choose from the available banks.\n";
            }
        }

        //  Card Number Validation
        while (true) {
            string CheckCard;
            cout << "\t\t\t\tEnter Card Number (16 digits starting with 4 or 5): ";
            cin >> CheckCard;
            if (ValidCardNumber(CheckCard)) {
                NewAccount.CardNumber = CheckCard;
                break;
            }
            // cout << "Invalid Card Number! Please ensure it's 16 digits and starts with 4 or 5.\n";
        }

        //  Expiration_Date Validation
        while (true) {
            string CheckExp;
            cout << "\t\t\t\tEnter Expiration Date (MM/YY): ";
            cin >> CheckExp;
            if (ValidExpirationDate(CheckExp)) {
                NewAccount.ExpirationDate = CheckExp;
                break;
            }
            else {
                Beep(200, 600);
                cout << "\t\t\t\tInvalid Expiration Date! Please enter a valid date in MM/YY format.\n";
            }
        }

        //  Holder Name
        cout << "\t\t\t\tEnter Holder Name: ";
        cin >> ws;
        getline(cin, NewAccount.HolderName);

        //  CVV Validation
        while (true) {
            string CheckCVV;
            cout << "\t\t\t\tEnter CVV Code (3 digits): ";
            cin >> CheckCVV;
            if (ValidCVV(CheckCVV)) {
                NewAccount.CVVCode = CheckCVV;
                break;
            }
            Beep(200, 600);
        }

        //  PIN Validation
        while (true) {
            string CheckPIN;
            cout << "\t\t\t\tCreate a 4 digit PIN code for your account: ";
            cin >> CheckPIN;
            if (ValidPIN(CheckPIN)) {
                NewAccount.PINCode = CheckPIN;
                break;
            }
            Beep(200, 600);
        }

        //  Balance Generation
        NewAccount.Balance = (rand() % 9001) + 1000;
        cout << "\t\t\t\tYour Initial Balance Is: " << NewAccount.Balance << endl;

        return NewAccount;
    }

    void addNewAccount()
    {
        if (Users[UserIndex].CountAccounts >= 3)
        {
            Beep(200, 600);
            cout << "\t\t\t_____________________________________________________________________\n";
            cout << "\n\t\t\t\t\tError: You Reached Maximum Limit Of Accounts.\n";
            cout << "\t\t\t_____________________________________________________________________\n\n\n";

            return;
        }

        StAccount NewAccount = ReadNewAccountData();

        int CurrentAccountPosition = 0;

        CurrentAccountPosition = Users[UserIndex].CountAccounts;

        Users[UserIndex].AccountsList[CurrentAccountPosition] = NewAccount;

        Users[UserIndex].CountAccounts++;

        PlaySound(TEXT("Sounds\\ElevenLabs_Triumphant_chime_signaling_successful_task_completion.wav"), NULL, SND_FILENAME | SND_ASYNC);

        cout << "\n\t\t\t\t Account Added Successfully .\n";
        system("pause");
        system("cls");
    }
}