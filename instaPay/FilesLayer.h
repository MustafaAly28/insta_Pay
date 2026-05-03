#pragma once
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include<iostream>
#include<string>
#include<fstream>
#include"DataLayer.h"
#include"FilesSigns.h"
using namespace DataLayer;
using namespace std;

/*				----  Instructions For Dealing With Files Operations (For Our Team)  ----
			 1. Use (LoadUsersListFromFiles()) Function To Fill Users Array From Files
			 2. After Doing Transaction Operation, Execute (AddTransactionToUser()) Function To Add This Operation
*/
namespace Date
{
	string CleanDate(const string& Text)
	{
		string Line = "";
		for (int i = 0; i < Text.length(); i++)
			if (Text[i] != '\n')
				Line += Text[i];

		return Line;
	}

	string GetDateNow()
	{
		time_t TimeNow = time(0);
		char* Date = ctime(&TimeNow);

		return CleanDate(Date);
	}
}


namespace File
{
	void SplitTextToData(string LineData, string DataParts[], const string SperatorInLine)
	{
		int Position = 0;
		int Counter = 0;

		while ((Position = LineData.find(SperatorInLine)) != string::npos)
		{
			string PartData = LineData.substr(0, Position);

			if (PartData != "")
			{
				DataParts[Counter] = PartData;
				Counter++;
			}

			LineData.erase(0, Position + SperatorInLine.length());
		}

		if (!LineData.empty())
			DataParts[Counter] = LineData;
	}

	/* ------------------- Conversion Lines To Structures Like Data Layer Structure -------------------*/


	StAddress GetAddressFromLine(string LineOfDataAddress)
	{
		string AddressInfo[3] = {};
		StAddress Address;

		SplitTextToData(LineOfDataAddress, AddressInfo, SepratorAddressData);

		Address.Street = AddressInfo[0];
		Address.City = AddressInfo[1];
		Address.HomeNumber = AddressInfo[2];

		return Address;
	}

	StAccount GetAccountFromLine(string LineOfDataAccount, string& ConnectorPhoneNumber)
	{
		string AccountInfo[8] = {};
		StAccount Account;

		SplitTextToData(LineOfDataAccount, AccountInfo, SepratorAccountData);
		ConnectorPhoneNumber = AccountInfo[0];
		Account.CardNumber = AccountInfo[1];
		Account.PINCode = AccountInfo[2];
		Account.HolderName = AccountInfo[3];
		Account.BankName = AccountInfo[4];
		Account.CVVCode = AccountInfo[5];
		Account.ExpirationDate = AccountInfo[6];
		Account.Balance = stod(AccountInfo[7]);

		return Account;
	}

	StTransactions GetDataTransactionFromLine(string LineDataTransaction)
	{
		StTransactions TransactionsHistory;
		string TransactionsParts[6];

		SplitTextToData(LineDataTransaction, TransactionsParts, SepratorTransactionData);

		TransactionsHistory.BankNameForSender = TransactionsParts[0];
		TransactionsHistory.BankNameForReceiver = TransactionsParts[1];
		TransactionsHistory.PhoneNumber_From = TransactionsParts[2];
		TransactionsHistory.PhoneNumber_To = TransactionsParts[3];
		TransactionsHistory.Date = TransactionsParts[4];
		TransactionsHistory.Amount = stod(TransactionsParts[5]);

		return TransactionsHistory;
	}

	StTransactions GetDepositOrWithDrawFromLine(string Line, string& ConnectorPhone)
	{
		StTransactions DepositOrWithDraw;
		string DataParts[4];
		SplitTextToData(Line, DataParts, SepratorDepositOrWithDrawData);

		ConnectorPhone = DataParts[0];
		DepositOrWithDraw.BankNameForSender = DataParts[1];
		DepositOrWithDraw.Date = DataParts[2];
		DepositOrWithDraw.Amount = stod(DataParts[3]);

		return DepositOrWithDraw;
	}

	StDonation GetDonationFromLine(string Line)
	{
		StDonation Donation;

		string PartsData[5];
		SplitTextToData(Line, PartsData, SepratorDonationData);

		Donation.CardNumber = PartsData[0];
		Donation.BankNameForSender = PartsData[1];
		Donation.OrganizationName = PartsData[2];
		Donation.Date = PartsData[3];
		Donation.Amount = stod(PartsData[4]);

		return Donation;
	}
	void ConvertPersonalDataLineToStructure(string LineOfDataPersonal, StUser& User)
	{
		// لو السطر اللي جاي فاضي أساساً، ماتعملش حاجة واخرج
		if (LineOfDataPersonal.empty()) {
			return;
		}

		string PersonalInfo[5] = {};
		SplitTextToData(LineOfDataPersonal, PersonalInfo, SepratorPersonalData);

		User.UserName = PersonalInfo[0];

		// سطر الحماية السحري: ماتعملش stoi غير لو الخانة فيها داتا فعلاً
		if (PersonalInfo[1] != "") {
			User.Id = stoi(PersonalInfo[1]);
		}
		else {
			User.Id = 0; // قيمة افتراضية عشان البرنامج مايكراشش
		}

		User.Password = PersonalInfo[2];
		User.Phone = PersonalInfo[3];
		User.Email = PersonalInfo[4];
	}


	/* ------------------- Conversion Structures To One Line Like Line Of Its File -------------------*/



	string GetAddressLine(const StUser& User)
	{
		string AddressLine = "";
		return (User.Address.Street + "/#/" + User.Address.City + "/#/" + User.Address.HomeNumber);
	}

	string GetAccountLine(const StAccount& Account, const string& PhoneNumber)
	{
		string Line = "";

		Line += PhoneNumber + "$";
		Line += Account.CardNumber + "$";
		Line += Account.PINCode + "$";
		Line += Account.HolderName + "$";
		Line += Account.BankName + "$";
		Line += Account.CVVCode + "$";
		Line += Account.ExpirationDate + "$";
		Line += to_string(Account.Balance);

		return Line;
	}

	string GetPersonalLine(const StUser& User)
	{
		return User.UserName + SepratorPersonalData + to_string(User.Id) + SepratorPersonalData + User.Password + SepratorPersonalData + User.Phone + SepratorPersonalData + User.Email;
	}

	string GetLineTransactionDataFromStructure(const StTransactions& TransactionOperation)
	{
		// 	(BankNameOfSender%#%BankNameOfReceiver%#%From(PhoneNumber)%#%To(PhoneNumber)%#%Date%#%Amount
		return (TransactionOperation.BankNameForSender + SepratorTransactionData + TransactionOperation.BankNameForReceiver + SepratorTransactionData + TransactionOperation.PhoneNumber_From + SepratorTransactionData + TransactionOperation.PhoneNumber_To
			+ SepratorTransactionData + Date::GetDateNow() +
			SepratorTransactionData + to_string(TransactionOperation.Amount));
	}

	string GetLineDepositOrWithDrawsFromStructure(const StTransactions DepositOrWithDraw, string& ConnectorPhoneNumber)
	{
		return   ConnectorPhoneNumber
			+ SepratorDepositOrWithDrawData
			+ DepositOrWithDraw.BankNameForSender
			+ SepratorDepositOrWithDrawData
			+ DepositOrWithDraw.Date
			+ SepratorDepositOrWithDrawData
			+ to_string(DepositOrWithDraw.Amount);
	}

	string GetLineDonation(StDonation Donation)
	{
		return Donation.CardNumber
			+ SepratorDonationData
			+ Donation.BankNameForSender
			+ SepratorDonationData
			+ Donation.OrganizationName
			+ SepratorDonationData
			+ Donation.Date
			+ SepratorDonationData
			+ to_string(Donation.Amount);
	}



	/* ------------------- Load Data Types From Files -------------------  */


	void FillAccountListForOneUser(StUser& User, const string& AccountsFile)
	{
		fstream File(AccountsFile, ios::in);
		if (File.is_open())
		{
			string AccountLine = "";
			while (getline(File, AccountLine))
			{
				if (AccountLine == "")
					continue;

				string ConnectorPhoneNumber = "";
				StAccount Account = GetAccountFromLine(AccountLine, ConnectorPhoneNumber);

				if (User.Phone == ConnectorPhoneNumber)
				{
					User.AccountsList[User.CountAccounts] = Account;
					User.CountAccounts++;
				}
			}
		}
		File.close();
	}

	void FillDepositsForOneUser(StUser& User, const string& FileDepositsName)
	{
		fstream File(FileDepositsName, ios::in);
		if (File.is_open())
		{
			string Line = "";
			string ConnectorPhone = "";
			while (getline(File, Line))
			{
				if (Line == "")
					continue;

				StTransactions Deposit = GetDepositOrWithDrawFromLine(Line, ConnectorPhone);
				if (ConnectorPhone == User.Phone)
				{
					User.Deposits[User.DepositsCount] = Deposit;
					User.DepositsCount++;
				}
			}
		}
	}

	void FillWithDrawsForOneUser(StUser& User, const string& FileWithDrawsName)
	{
		fstream File(FileWithDrawsName, ios::in);
		if (File.is_open())
		{
			string Line = "";
			string ConnectorPhone = "";
			while (getline(File, Line))
			{
				if (Line == "")
					continue;

				StTransactions WithDraw = GetDepositOrWithDrawFromLine(Line, ConnectorPhone);
				if (ConnectorPhone == User.Phone)
				{
					User.Withdrawals[User.WithdrawalsCount] = WithDraw;
					User.WithdrawalsCount++;
				}
			}
		}
	}

	void FillDonationForOneUser(StUser& User, const string& FileDonationName)
	{
		fstream File(FileDonationName, ios::in);
		if (File.is_open())
		{
			string Line = "";
			while (getline(File, Line))
			{
				if (Line == "")
					continue;

				StDonation Donation = GetDonationFromLine(Line);
				for (int AccountPosition = 0; AccountPosition < User.CountAccounts; AccountPosition++)
				{
					if (Donation.CardNumber == User.AccountsList[AccountPosition].CardNumber && (User.DonationsCount < MAX_TRANSACTIONS_PER_USER))
					{
						User.Donations[User.DonationsCount] = Donation;
						User.DonationsCount++;
					}
				}
			}
		}
	}


	void LoadAccountsFromFile(const string& FileNameAccount, StUser Users[])
	{
		//  --  Account Layer Data File -- 
		for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
		{
			FillAccountListForOneUser(Users[UserPosition], FileNameAccount);
		}
		//
		//if (FileAccount.is_open())
		//{
		//	string AccountDataLine = "";
		//	while (getline(FileAccount, AccountDataLine))
		//	{
		//		if (Counter < AddingUsersCounter)
		//		{
		//			Users[Counter].Account = GetAccountFromLine(AccountDataLine);
		//			Users[Counter].CountAccounts++;
		//			Counter++;
		//		}
		//	}
		//}
		//FileAccount.close();
	}

	void LoadAddressFromFile(const string& FileNameAddress, StUser Users[])
	{
		fstream FileAddress;
		FileAddress.open(FileNameAddress, ios::in);
		int Counter = 0;

		//  --  Address Layer Data File -- 
		if (FileAddress.is_open())
		{
			string AddressDataLine = "";
			while (getline(FileAddress, AddressDataLine))
			{
				Users[Counter].Address = GetAddressFromLine(AddressDataLine);
				Counter++;
			}
		}
		FileAddress.close();
	}

	void LoadPersonalFromFile(const string& FileNamePersonal, StUser Users[])
	{
		fstream FilePersonal;
		FilePersonal.open(FileNamePersonal, ios::in);
		int Counter = 0;

		//  --  Personal Layer Data File -- 
		if (FilePersonal.is_open())
		{
			string PersonalDataLine = "";
			while (getline(FilePersonal, PersonalDataLine))
			{
				if (Counter <= USERS_COUNT && AddingUsersCounter <= USERS_COUNT)
				{
					ConvertPersonalDataLineToStructure(PersonalDataLine, Users[Counter]);
					Counter++;
				}
			}
			AddingUsersCounter = Counter;
		}
		FilePersonal.close();
	}

	void LoadTransactionsFromFile(StTransactions TransactionsList[], const string& TransactionsFile)
	{
		fstream File;
		File.open(TransactionsFile, ios::in);

		if (File.is_open())
		{
			string LineData = "";
			while (getline(File, LineData))
			{
				if (LineData == "")
					continue;

				TransactionsList[AddingTransactionsCounter] = GetDataTransactionFromLine(LineData);
				AddingTransactionsCounter++;
			}
		}
	}

	void LoadDepositsFromFile(StUser Users[], const string& FileDepositsName)
	{
		for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
		{
			FillDepositsForOneUser(Users[UserPosition], FileDepositsName);
		}
	}

	void LoadWithDrawsFromFile(StUser Users[], const string& FileWithDrawsName)
	{
		for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
		{
			FillWithDrawsForOneUser(Users[UserPosition], FileWithDrawsName);
		}
	}

	void LoadDonationsFromFile(StUser Users[], const string& FileDonationName)
	{
		for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
		{
			FillDonationForOneUser(Users[UserPosition], FileDonationName);
		}
	}


	/* ------------------- Save Data Of Structures In File ------------------- */


	void SaveToFileAddress(const StUser Users[], int CountUsers, const string& FileAddress)
	{
		fstream File;
		File.open(FileAddress, ios::out);

		if (File.is_open())
		{
			for (int Counter = 0; Counter < CountUsers; Counter++)
			{
				File << GetAddressLine(Users[Counter]) << endl;
			}
		}
		File.close();
	}

	void SaveToFileAccount(const StUser Users[], int CountUsers, const string& FileAccount)
	{
		fstream File;
		File.open(FileAccount, ios::out);

		if (File.is_open())
		{
			for (int Counter = 0; Counter < CountUsers; Counter++)
			{
				for (int AccountPosition = 0; AccountPosition < Users[Counter].CountAccounts; AccountPosition++)
				{
					File << GetAccountLine(Users[Counter].AccountsList[AccountPosition], Users[Counter].Phone) << endl;
				}
			}
		}
		File.close();
	}

	void SaveToFilePersonal(StUser Users[], int CountUsers, const string& FilePersonal)
	{
		fstream File;
		File.open(FilePersonal, ios::out);

		if (File.is_open())
		{
			for (int Counter = 0; Counter < CountUsers; Counter++)
			{
				File << GetPersonalLine(Users[Counter]) << endl;
			}
		}
		File.close();
	}

	void AddLineToTransactionsFile(const string& LineDataTransactions, const string& TransactionsFile)
	{
		fstream File;
		File.open(TransactionsFile, ios::app);

		if (File.is_open())
		{
			File << LineDataTransactions << endl;
		}

		File.close();
	}

	void SaveToFileDeposits(StUser Users[], const string& FileDepositsName)
	{
		fstream File(FileDepositsName, ios::out);
		if (File.is_open())
		{
			for (int UsersPosition = 0; UsersPosition < AddingUsersCounter; UsersPosition++)
			{
				for (int TransactionPosition = 0; TransactionPosition < Users[UsersPosition].DepositsCount; TransactionPosition++)
				{
					File << GetLineDepositOrWithDrawsFromStructure(Users[UsersPosition].Deposits[TransactionPosition], Users[UsersPosition].Phone) << endl;
				}
			}
		}
		File.close();
	}

	void SaveToFileWithDraws(StUser Users[], const string& FileWithDrawsName)
	{
		fstream File(FileWithDrawsName, ios::out);
		if (File.is_open())
		{
			for (int UsersPosition = 0; UsersPosition < AddingUsersCounter; UsersPosition++)
			{
				for (int TransactionPosition = 0; TransactionPosition < Users[UsersPosition].WithdrawalsCount; TransactionPosition++)
				{
					File << GetLineDepositOrWithDrawsFromStructure(Users[UsersPosition].Withdrawals[TransactionPosition], Users[UsersPosition].Phone) << endl;
				}
			}
		}
		File.close();
	}

	void SaveToFileDonation(StUser Users[], const string& FileDonationsName)
	{
		fstream File(FileDonationsName, ios::out);
		if (File.is_open())
		{
			for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
			{
				for (int AccountPosition = 0; AccountPosition < Users[UserPosition].DonationsCount; AccountPosition++)
				{
					File << GetLineDonation(Users[UserPosition].Donations[AccountPosition]) << endl;
				}
			}
		}
	}


	/* ------------------- Filteration For Users Transactions -------------------  */


	void FilterTransactions_From_(const StTransactions ListTransactions[], StUser& User)
	{
		for (int Position = 0; Position < AddingTransactionsCounter; Position++)
		{
			if (ListTransactions[Position].PhoneNumber_From == User.Phone)
			{
				User.TransactionsSending[User.TransactionsCountSending] = ListTransactions[Position];
				User.TransactionsCountSending++;
			}
		}
	}

	void FilterTransactions_To_(const StTransactions ListTransactions[], StUser& User)
	{
		for (int Position = 0; Position < AddingTransactionsCounter; Position++)
		{
			if (ListTransactions[Position].PhoneNumber_To == User.Phone)
			{
				User.TransactionsRecieving[User.TransactionsCountRecieving] = ListTransactions[Position];
				User.TransactionsCountRecieving++;
			}
		}
	}

	void FillTransactionUser(const StTransactions ListTransactions[], StUser& User)
	{
		FilterTransactions_From_(ListTransactions, User); // To Fill User (From) Transactions 
		FilterTransactions_To_(ListTransactions, User); // To Fill User (To) Transactions 
	}

	void LoadTransactionsForUsers(StUser Users[], const string& FileTransactions)
	{
		StTransactions ListTransactions[50];
		LoadTransactionsFromFile(ListTransactions, TransactionsInfoFile); // Fill Transactions In Array

		for (int PositionUser = 0; PositionUser < AddingUsersCounter; PositionUser++)
		{
			FillTransactionUser(ListTransactions, Users[PositionUser]);
		}
	}


	/* ----------- You Can Deal With Following Three Functions Only , Don't Use Any Function Else ----------- */


	// If The System In Starting Point Of Processing ,Execute This
	void Access_LoadUsersListFromFiles(StUser Users[USERS_COUNT], const string PerosnalFile, const string& AccountsFile, const string& AddressFile, const string& TransactionFile)
	{
		// -- Move Data Personal From File To Attributes Personal          -- 
		LoadPersonalFromFile(PersonalInfoFile, Users);

		// -- Move Data Accounts From File To Attributes Accounts          -- 
		LoadAccountsFromFile(AccountsInfoFile, Users);

		// -- Move Data Address From File To Attributes Address            -- 
		LoadAddressFromFile(AddressInfoFile, Users);

		// -- Move Data Transactions From File To Attributes  Transaction  -- 
		LoadTransactionsForUsers(Users, TransactionsInfoFile);

		// -- Move Data Deposits From File To Attributes  Transaction      -- 
		LoadDepositsFromFile(Users, DepositsInfoFile);

		// -- Move Data Deposits From File To Attributes  Transaction      -- 
		LoadWithDrawsFromFile(Users, WithDrawsInfoFile);

		// -- Move Data Deposits From File To Attributes  Transaction      --
		LoadDonationsFromFile(Users, DonationsInfoFile);
	}

	// If You Did Transaction Operation , In End Of Process (Function) Execute This
	void Access_AddTransactionHistoryToFile(const StTransactions& Transaction)
	{
		string LineDataTransaction = GetLineTransactionDataFromStructure(Transaction);
		AddLineToTransactionsFile(LineDataTransaction, TransactionsInfoFile);
	}

	// If The System In Ending Point Of Processing , Execute This
	void Access_SaveUsersToFiles(StUser Users[], const string& AccountsFile, const string& AddressFile, const string& PersonalFile)
	{
		SaveToFilePersonal(Users, AddingUsersCounter, PersonalFile);

		SaveToFileAccount(Users, AddingUsersCounter, AccountsInfoFile);

		SaveToFileAddress(Users, AddingUsersCounter, AddressInfoFile);

		SaveToFileDeposits(Users, DepositsInfoFile);

		SaveToFileWithDraws(Users, WithDrawsInfoFile);

		SaveToFileDonation(Users, DonationsInfoFile);
	}

}