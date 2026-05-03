#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream> 
#include "DataLayer.h"
#include "Login.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include"UserProfile.h"
#include"AddNewAccount.h"
#include "TransferCheck.h"
#include"Donation.h"
#include"CheckTransactions.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace CheckTransaction;
using namespace Login;
using namespace std;
using namespace AddNewAccount;
using namespace TransferBalanceAndCheck;
using namespace UserProfile;
using namespace Donation;

namespace MainMenu
{
    void Deposit();
    void WithDraw();
    bool Exist = false;

    void AskUser(char Answer) {

        while (Answer != 'Y' && Answer != 'y' && Answer != 'N' && Answer != 'n')
        {
            cout << "invalid Answer \n";
            cout << "Answer Must Be Y/N ";
            cout << "Answer : ";
            cin >> Answer;
        }
        if (Answer == 'y' || Answer == 'Y')
        {

            ShowLoading();
            system("cls");
        }
        else

            Exist = true;
    }
    void mainWindow() {

        bool ValidChoice;
        char Answer;
        int Choice;
        while (true) {

            system("Color 0E"); // Color The Font

            cout << "\n\t\t\t\t========================================";
            cout << "\n\t\t\t\t            INSTAPAY EGYPT             ";
            cout << "\n\t\t\t\t========================================";
            cout << "\n\t\t\t\t  1. Check Balance      2. Add Account";
            cout << "\n\t\t\t\t  3. Transfer           4. User Info";
            cout << "\n\t\t\t\t  5. Transactions       6. Donation";
            cout << "\n\t\t\t\t  7. Deposit            8. Withdraw";
            cout << "\n\t\t\t\t  9. Logout             0.Exit    ";
            cout << "\n\t\t\t\t========================================\n";




            do
            {

                cout << "\t\t\t\tEnter Your Choice from (0-9) : ";
                cin >> Choice;


                if (Choice >= 0 && Choice <= 9)
                {

                    ValidChoice = true;
                }
                else
                {
                    cout << "\t\t\t\tInvalid Choice ! \n";
                    ValidChoice = false;
                }

            } while (ValidChoice == false);
            ShowLoading();
            system("cls");

            switch (Choice) {
            case 1:
                checkBalance();
                //cout << "To Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);
                break;
            case 2:
                addNewAccount();
                //cout << "\t\t\t\tFor Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);

                break;
            case 3:

                transfer();
                //cout << "\t\t\t\tFor Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);

                break;

            case 4:
                ShowUserBasicProfile(UserIndex);
                break;

            case 5:

                CheckTransactions();
                //cout << "\t\t\t\tFor Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);

                break;
            case 6:

                donation();

                break;
            case 7:
                Deposit();
                //cout << "\t\t\t\tFor Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);

                break;
            case 8:
                WithDraw();
                //cout << "\t\t\t\tFor Main Menu Y/y To Exist N/n ";
                //cout << "\t\t\t\tAnswer : ";
                //cin >> Answer;
                //AskUser(Answer);
                break;

            case 9:
                ShowLoading();
                system("cls");
                LoGin();
                break;

            case 0:
                cout << "\t\t\t\tThank You";
                Exist = true;

            }
            if (Exist) {
                ShowLoading();
                system("cls");
                break;
            }
        }


    }
    void ShowDateTime() {
        time_t now = time(0);
        cout << "\t\t\t\tDate & Time: " << ctime(&now);
    }           //Show Date And Time

    double GetValidAmount() {              // تاخذ مبلغ موجب واكبر من الصفر
        double Amount;
        while (true)
        {

            cout << "\t\t\t\tEnter Your Amount : ";
            cin >> Amount;

            if (Amount > 0)
                return Amount;
            cout << "\t\t\t\tAmount Must Be positive";



        }

    }
    bool CheckPIN(string PIN, int AccountIndex) {           // تشيك الرمز موجود في السيستم 


        if (Users[UserIndex].AccountsList[AccountIndex].PINCode == PIN)
        {


            return true;


        }

        return false;

    }


    bool CheckAccountExist(string CardNumber)               // تشيك الاكونت موجود في السيستم
    {


        for (int Index = 0; Index < 3; Index++)
        {
            if (Users[UserIndex].AccountsList[Index].CardNumber == CardNumber)
            {


                return true;

            }
        }
        return false;
    }


    bool CheckBalance(double Amount, int AccountIndex) {        // تشيك لو المبلغ الكلي كافي للسحب

        double TotalAmount = Amount + Amount * 0.01;


        if (TotalAmount <= Users[UserIndex].AccountsList[AccountIndex].Balance)
        {


            return true;

        }
        return false;

    }


    void Deposit() {

        if (Users[UserIndex].DepositsCount >= MAX_TRANSACTIONS_PER_USER) {
            cout << "\n\t\t\t\tError: Deposits history is full! Cannot make more deposits.\n";
            system("pause");
            return;
        }

        int CounterAttempts = 0;
        double Amount;
        string CardNumber;
        int AccountIndex = -1;
        string PIN;


        while (true) {
            cout << "\t\t\t\tEnter Card Number (16 digits starting with 4 or 5): ";
            cin >> CardNumber;
            if (CheckAccountExist(CardNumber)) break;
            else cout << "\t\t\t\tInvalid Card Number Or Does Not Exist \n";
        }

        for (int Index = 0; Index < 3; Index++) {
            if (Users[UserIndex].AccountsList[Index].CardNumber == CardNumber) {
                AccountIndex = Index;
                break;
            }
        }


        Amount = GetValidAmount();


        cout << "\t\t\t\tYou only have 3 attempts \n";
        while (true) {
            cout << "\t\t\t\tEnter a 4 digit PIN code for your account: ";
            cin >> PIN;
            if (CheckPIN(PIN, AccountIndex)) break;
            else {
                cout << "\t\t\t\tInvalid PIN !! \n";
                CounterAttempts++;
                if (CounterAttempts == 3) {
                    cout << "\n\t\t\t\tError: Incorrect PIN 3 times. Operation cancelled.\n";
                    system("pause");
                    return;
                }
            }
        }


        Users[UserIndex].AccountsList[AccountIndex].Balance += Amount;
        ShowLoading();


        time_t now = time(0);
        string currentTime = ctime(&now);
        currentTime.pop_back();

        int dIndex = Users[UserIndex].DepositsCount;
        Users[UserIndex].Deposits[dIndex].BankNameForSender = Users[UserIndex].AccountsList[AccountIndex].BankName;
        Users[UserIndex].Deposits[dIndex].Amount = Amount;
        Users[UserIndex].Deposits[dIndex].Date = currentTime;

        Users[UserIndex].DepositsCount++;
        AddingTransactionsCounter++;


        cout << "\t\t\t\t====================================\n";
        cout << "\t\t\t\t       TRANSACTION SUCCESSFUL       \n";
        cout << "\t\t\t\t====================================\n";
        cout << "\t\t\t\tAmount : " << Amount << " EGP\n";
        cout << "\t\t\t\tNew Balance: " << Users[UserIndex].AccountsList[AccountIndex].Balance << " EGP\n";
        cout << "\t\t\t\tDate & Time: " << currentTime << "\n";
        cout << "\t\t\t\t====================================\n";
        system("pause");
    }

    void WithDraw() {

        if (Users[UserIndex].WithdrawalsCount >= MAX_TRANSACTIONS_PER_USER) {
            cout << "\n\t\t\t\tError: Withdrawals history is full! Cannot make more withdrawals.\n";
            system("pause");
            return;
        }

        int CounterAttempts = 0;
        double Amount = 0;
        string CardNumber;
        int AccountIndex = -1;
        string PIN;


        while (true) {
            cout << "\t\t\t\tEnter Card Number (16 digits starting with 4 or 5): ";
            cin >> CardNumber;
            if (CheckAccountExist(CardNumber)) break;
            else cout << "\t\t\t\tInvalid Card Number Or Does Not Exist \n";
        }


        for (int Index = 0; Index < 3; Index++) {
            if (Users[UserIndex].AccountsList[Index].CardNumber == CardNumber) {
                AccountIndex = Index;
                break;
            }
        }


        while (true) {
            Amount = GetValidAmount();
            if (CheckBalance(Amount, AccountIndex)) break;
            cout << "\t\t\t\tInsufficient balance (including 1% tax)!! \n";
        }

        double TotalAmount = Amount + Amount * 0.01;


        cout << "\t\t\t\tYou only have 3 attempts \n";
        while (true) {
            cout << "\t\t\t\tEnter a 4 digit PIN code for your account: ";
            cin >> PIN;
            if (CheckPIN(PIN, AccountIndex)) break;
            else {
                cout << "\t\t\t\tInvalid PIN !! \n";
                CounterAttempts++;
                if (CounterAttempts == 3) {
                    cout << "\n\t\t\t\tError: Incorrect PIN 3 times. Operation cancelled.\n";
                    system("pause");
                    return;
                }
            }
        }


        Users[UserIndex].AccountsList[AccountIndex].Balance -= TotalAmount;
        ShowLoading();

        time_t now = time(0);
        string currentTime = ctime(&now);
        currentTime.pop_back();

        int wIndex = Users[UserIndex].WithdrawalsCount;
        Users[UserIndex].Withdrawals[wIndex].BankNameForSender = Users[UserIndex].AccountsList[AccountIndex].BankName;
        Users[UserIndex].Withdrawals[wIndex].Amount = Amount;
        Users[UserIndex].Withdrawals[wIndex].Date = currentTime;

        Users[UserIndex].WithdrawalsCount++;
        AddingTransactionsCounter++;

        cout << "\n\t\t\t\t====================================\n";
        cout << "\t\t\t\t\t        TRANSACTION SUCCESSFUL       \n";
        cout << "\t\t\t\t====================================\n";
        cout << "\t\t\t\tAmount : " << Amount << " EGP\n";
        cout << "\t\t\t\tTaxes : " << Amount * 0.01 << " EGP\n";
        cout << "\t\t\t\tAmount was Drawen : " << TotalAmount << " EGP\n";
        cout << "\t\t\t\tNew Balance: " << Users[UserIndex].AccountsList[AccountIndex].Balance << " EGP\n";
        cout << "\t\t\t\tDate & Time: " << currentTime << "\n";
        cout << "\t\t\t\t====================================\n";
        system("pause");
    }

}