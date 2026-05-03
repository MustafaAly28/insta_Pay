#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream> 
#include <windows.h> 
#include "DataLayer.h"
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "winmm.lib")
namespace TransferBalanceAndCheck
{
    void transfer()
    {

        if (Users[UserIndex].TransactionsCountSending >= MAX_TRANSACTIONS_PER_USER) {
            Beep(200, 600);
            cout << "\n\t\t\t\tError Transfer History Is Full Cannot Make More Transfers\n";
            system("pause");
            return;
        }

        int senderAcc, receiverAcc;
        string receiverPhone;
        double amount;
        int receiverIndex = -1;


        cout << "\t\t\t\tYour Accounts\n";

        for (int i = 0; i < Users[UserIndex].CountAccounts; i++)
        {
            cout << "\t\t\t\t[" << i + 1 << "] "
                << Users[UserIndex].AccountsList[i].BankName << endl;
        }

        char choiceSenderYN;

        while (true)
        {
            cout << "\t\t\t\tChoose Your Account: ";
            cin >> senderAcc;

            if (senderAcc >= 1 && senderAcc <= Users[UserIndex].CountAccounts)
            {
                break;
            }
            Beep(200, 600);
            cout << "\t\t\t\tInvalid Sender Account\n";
            cout << "\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceSenderYN;

            if (choiceSenderYN == 'N' || choiceSenderYN == 'n')
            {

                cout << "\t\t\t\tOperation Cancelled\n";
                return;
            }
        }

        senderAcc--;


        char choiceRecPhoneYN;

        while (true)
        {
            cout << "\t\t\t\tEnter Receiver Phone Number: ";
            cin >> receiverPhone;

            if (receiverPhone == Users[UserIndex].Phone)
            {
                Beep(200, 600);
                cout << "\t\t\t\tCannot Transfer To Your Own Phone Number\n";
            }
            else
            {
                receiverIndex = -1;

                for (int i = 0; i < AddingUsersCounter; i++)
                {
                    if (Users[i].Phone == receiverPhone)
                    {
                        receiverIndex = i;
                        break;
                    }
                }

                if (receiverIndex == -1)
                {
                    Beep(200, 600);

                    cout << "\t\t\t\tReceiver Not Found\n";
                }
                else if (Users[receiverIndex].CountAccounts == 0)
                {
                    Beep(200, 600);
                    cout << "\t\t\t\tReceiver Has No Accounts\n";
                }
                else
                {
                    break;
                }
            }

            cout << "\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceRecPhoneYN;

            if (choiceRecPhoneYN == 'N' || choiceRecPhoneYN == 'n')
            {

                cout << "\t\t\t\tOperation Cancelled\n";
                return;
            }
        }


        cout << "\t\t\t\tThe Receiver Accounts\n";

        for (int i = 0; i < Users[receiverIndex].CountAccounts; i++)
        {
            cout << "\t\t\t\t[" << i + 1 << "] "
                << Users[receiverIndex].AccountsList[i].BankName
                << endl;
        }

        char choiceRecAccYN;

        while (true)
        {
            cout << "\t\t\t\tChoose The Account: ";
            cin >> receiverAcc;

            if (receiverAcc >= 1 && receiverAcc <= Users[receiverIndex].CountAccounts)
            {
                break;
            }

            Beep(200, 600);
            cout << "\t\t\t\tInvalid Receiver Account\n";
            cout << "\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceRecAccYN;

            if (choiceRecAccYN == 'N' || choiceRecAccYN == 'n')
            {

                cout << "\t\t\t\tOperation Cancelled\n";
                return;
            }
        }

        receiverAcc--;

        char choiceAmountYN;

        while (true)
        {
            cout << "\t\t\t\tEnter Amount You Want To Send: ";
            cin >> amount;

            if (amount > 0)
            {
                if (Users[UserIndex].AccountsList[senderAcc].Balance >= amount)
                {
                    break;
                }
                else
                {
                    Beep(200, 600);
                    cout << "\t\t\t\tInsufficient Balance\n";
                }
            }
            else
            {
                Beep(200, 600);
                cout << "\t\t\t\tInvalid Amount\n";
            }

            cout << "\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceAmountYN;

            if (choiceAmountYN == 'N' || choiceAmountYN == 'n')
            {
                cout << "\t\t\t\tOperation Cancelled\n";
                return;
            }
        }

        string enteredTransferPIN; char choiceTransferPin;

        while (true)
        {
            cout << "\t\t\t\tEnter PIN For This Account: ";
            cin >> enteredTransferPIN;

            if (enteredTransferPIN == Users[UserIndex].AccountsList[senderAcc].PINCode)
            {
                break;
            }
            Beep(200, 600);
            cout << "\t\t\t\tIncorrect PIN\n";
            cout << "\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceTransferPin;

            if (choiceTransferPin == 'N' || choiceTransferPin == 'n')
            {
                cout << "\t\t\t\tOperation Cancelled\n";
                return;
            }
        }


        Users[UserIndex].AccountsList[senderAcc].Balance -= amount;
        Users[receiverIndex].AccountsList[receiverAcc].Balance += amount;


        time_t now = time(0);
        string currentTime = ctime(&now);
        currentTime.pop_back();


        int tFrom = Users[UserIndex].TransactionsCountSending;

        Users[UserIndex].TransactionsSending[tFrom].BankNameForSender = Users[UserIndex].AccountsList[senderAcc].BankName;
        Users[UserIndex].TransactionsSending[tFrom].BankNameForReceiver = Users[receiverIndex].AccountsList[receiverAcc].BankName;
        Users[UserIndex].TransactionsSending[tFrom].PhoneNumber_From = Users[UserIndex].Phone;
        Users[UserIndex].TransactionsSending[tFrom].PhoneNumber_To = Users[receiverIndex].Phone;
        Users[UserIndex].TransactionsSending[tFrom].Amount = amount;
        Users[UserIndex].TransactionsSending[tFrom].Date = currentTime;

        Users[UserIndex].TransactionsCountSending++;


        int tTo = Users[receiverIndex].TransactionsCountRecieving;

        Users[receiverIndex].TransactionsRecieving[tTo].BankNameForSender = Users[UserIndex].AccountsList[senderAcc].BankName;
        Users[receiverIndex].TransactionsRecieving[tTo].BankNameForReceiver = Users[receiverIndex].AccountsList[receiverAcc].BankName;
        Users[receiverIndex].TransactionsRecieving[tTo].PhoneNumber_From = Users[UserIndex].Phone;
        Users[receiverIndex].TransactionsRecieving[tTo].PhoneNumber_To = Users[receiverIndex].Phone;
        Users[receiverIndex].TransactionsRecieving[tTo].Amount = amount;
        Users[receiverIndex].TransactionsRecieving[tTo].Date = currentTime;

        Users[receiverIndex].TransactionsCountRecieving++;

        AddingTransactionsCounter++;


        StTransactions newTransaction;
        newTransaction.BankNameForSender = Users[UserIndex].AccountsList[senderAcc].BankName;
        newTransaction.BankNameForReceiver = Users[receiverIndex].AccountsList[receiverAcc].BankName;
        newTransaction.PhoneNumber_From = Users[UserIndex].Phone;
        newTransaction.PhoneNumber_To = Users[receiverIndex].Phone;
        newTransaction.Amount = amount;
        newTransaction.Date = currentTime;

        File::Access_AddTransactionHistoryToFile(newTransaction);

        PlaySound(TEXT("Sounds\\ElevenLabs_Triumphant_chime_signaling_successful_task_completion.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "\n\t\t\t\t\t====================================\n";
        cout << "\t\t\t\t\t       Transaction Successful\n";
        cout << "\t\t\t\t\t====================================\n";
        cout << "\t\t\t\t\tAmount Transferred : " << amount << " EGP\n";
        cout << "\t\t\t\t\tTo Account : " << Users[receiverIndex].AccountsList[receiverAcc].BankName << " (" << Users[receiverIndex].UserName << ")\n";
        cout << "\t\t\t\t\tNew Balance : " << Users[UserIndex].AccountsList[senderAcc].Balance << " EGP\n";
        cout << "\t\t\t\t\tDate And Time : " << currentTime << "\n";
        cout << "\t\t\t\t\t====================================\n";

        system("pause");
    }

    void checkBalance()
    {
        cout << "\t\t\t\t\tYour Accounts\n";

        for (int i = 0; i < Users[UserIndex].CountAccounts; i++)
        {
            cout << "\t\t\t\t\t[" << i + 1 << "] "
                << Users[UserIndex].AccountsList[i].BankName << endl;
        }

        int choice; char choiceBalanceYN;

        while (true)
        {
            cout << "\t\t\t\t\tChoose Your Account: ";
            cin >> choice;

            if (choice >= 1 && choice <= Users[UserIndex].CountAccounts)
            {
                break;
            }
            Beep(200, 600);
            cout << "\t\t\t\t\tInvalid Choice\n";
            cout << "\t\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceBalanceYN;

            if (choiceBalanceYN == 'N' || choiceBalanceYN == 'n')
            {
                cout << "\t\t\t\t\tOperation Cancelled\n";
                return;
            }
        }

        choice--;

        string enteredBalancePIN; char choiceBalancePin;

        while (true)
        {
            cout << "\t\t\t\t\tEnter PIN For This Account: ";
            cin >> enteredBalancePIN;

            if (enteredBalancePIN == Users[UserIndex].AccountsList[choice].PINCode)
            {
                break;
            }

            Beep(200, 600);
            cout << "\t\t\t\t\tIncorrect PIN\n";
            cout << "\t\t\t\t\tDo You Want To Try Again Y N: ";
            cin >> choiceBalancePin;

            if (choiceBalancePin == 'N' || choiceBalancePin == 'n')
            {
                cout << "\t\t\t\t\tOperation Cancelled\n";
                return;
            }
        }

        cout << "\n\t\t\t\t\tYour Balance Is: "
            << Users[UserIndex].AccountsList[choice].Balance << " EGP"
            << endl;

        system("pause");
        system("cls");
    }
}