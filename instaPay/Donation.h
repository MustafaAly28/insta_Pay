#pragma once
#include "AddNewAccount.h"
#include <iostream>
#include <string>
#include "Login.h"
#include "DataLayer.h"

using namespace Login;
using namespace std;
using namespace DataLayer;


namespace Donation {
	double amount = 0;
	int currentAcc = -1;

	string orgNames[10] = {
		"Magdi Yacoub Heart Foundation", "Zakat House", "57357 Hospital",
		"Orman Charity", "Misr El Kheir", "Shobra El Kheir",
		"Baheya Foundation", "Egyptian Food Bank", "Al Nas Hospital",
		"Resala Charity Organization"
	};




	void ShowAcc() {
		cout << "\n--- Select the account to donate from ---\n";
		for (int i = 0; i < Users[UserIndex].CountAccounts; i++)
		{
			cout << "[" << i + 1 << "]" << Users[UserIndex].AccountsList[i].BankName << endl;

		}
	}
	void SelectAcc() {
		int chois;

		bool chk = false;
		do
		{
			cout << "Select Account : ";
			cin >> chois;
			if (chois >= 1 && chois <= Users[UserIndex].CountAccounts)
			{
				chk = true;
			}
			else {
				Beep(200, 600);
				cout << "Invalid Choice! Please Try Again.\n";
			}
		} while (chk == false);

		currentAcc = chois - 1;
	}


	void Organaization() {
		PlaySound(TEXT("Sounds\\xmersounds-soft-treble-fast-collect-fade-out-ending-sound-effect-416828.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << "=========================================\n";
		cout << "                  Donation               \n";
		cout << "=========================================\n";
		cout << "\n---Available Organizations for Donation---" << endl;
		cout << "[1] Magdi Yacoub Heart Foundation\t[2] Zakat House\n";
		cout << "[3] 57357 Hospital\t\t\t[4] Orman Charity\n";
		cout << "[5] Misr El Kheir\t\t\t[6] Shobra El Kheir\n";
		cout << "[7] Baheya Foundation\t\t\t[8] Egyptian Food Bank\n";
		cout << "[9] Al Nas Hospital\t\t\t[10]Resala Charity Organization\n" << endl;
		cout << "-------------------------------------------------------------\n";
	}

	bool CheckBalance() {

		double TotalAmount = amount + amount * 0.01;


		if (TotalAmount <= Users[UserIndex].AccountsList[currentAcc].Balance)
		{


			return true;

		}
		return false;

	}

	void donation() {
		if (Users[UserIndex].DonationsCount >= MAX_TRANSACTIONS_PER_USER) {
			Beep(200, 600);
			cout << "Error: Transaction history is full! Cannot make more donations.\n";
			system("pause");
			return;
		}
		ShowAcc();
		SelectAcc();
		Organaization();

		int choseen;
		bool check = false;
		do {
			cout << "Enter the number of the organization you want to donate to (1-10): ";
			cin >> choseen;
			if (choseen >= 1 && choseen <= 10) check = true;
			else { Beep(200, 600); cout << "Invalid Choice! Please Try Again.\n"; }
		} while (!check);

		cout << "Enter donation amount: ";
		cin >> amount;

		if (amount <= 0) {
			Beep(200, 600);
			cout << "Error: Amount must be positive." << endl;
			return;
		}


		string enteredPin;
		int attempts = 3;
		bool pinCorrect = false;

		while (attempts > 0) {
			cout << "Enter your 4-digit PIN (Attempts left: " << attempts << "): ";
			cin >> enteredPin;

			if (enteredPin == Users[UserIndex].AccountsList[currentAcc].PINCode) {
				pinCorrect = true;
				break;
			}
			else {
				attempts--;
				if (attempts > 0) {
					Beep(200, 600);
					cout << "Incorrect PIN! Try again.\n";
				}
			}
		}


		if (!pinCorrect) {

			Beep(200, 600);
			cout << "\nError: Incorrect PIN 3 times. Operation cancelled for security.\n";

			return;
		}
		// ----------------------------------

		// ----------------------------------

		if (CheckBalance()) {
			double TotalAmount = amount + (amount * 0.01);
			Users[UserIndex].AccountsList[currentAcc].Balance -= TotalAmount;
			string targetOrg = orgNames[choseen - 1];


			time_t now = time(0);
			string currentTime = ctime(&now);
			currentTime.pop_back();


			int dIndex = Users[UserIndex].DonationsCount;


			Users[UserIndex].Donations[dIndex].CardNumber = Users[UserIndex].AccountsList[currentAcc].CardNumber;
			Users[UserIndex].Donations[dIndex].BankNameForSender = Users[UserIndex].AccountsList[currentAcc].BankName;
			Users[UserIndex].Donations[dIndex].OrganizationName = targetOrg;
			Users[UserIndex].Donations[dIndex].Amount = amount;
			Users[UserIndex].Donations[dIndex].Date = currentTime;


			Users[UserIndex].DonationsCount++;
			AddingTransactionsCounter++;


			StTransactions newTransaction;

			newTransaction.BankNameForSender = Users[UserIndex].AccountsList[currentAcc].BankName;
			newTransaction.BankNameForReceiver = targetOrg;
			newTransaction.Amount = amount;
			newTransaction.Date = currentTime;

			//File::Access_AddTransactionHistoryToFile(newTransaction);
			PlaySound(TEXT("Sounds\\ElevenLabs_Triumphant_chime_signaling_successful_task_completion.wav"), NULL, SND_FILENAME | SND_ASYNC);
			cout << "\n[Verifying PIN... Success!]\n";
			cout << "Success! Donated " << amount << " EGP to " << targetOrg << ".\n";
			cout << "Donation Time: " << currentTime << endl;
			cout << "New Balance: " << Users[UserIndex].AccountsList[currentAcc].Balance << endl;

			system("pause");
			system("cls");
		}
		else {
			Beep(200, 600);
			cout << "Insufficient balance!\n";
		}
	}
}