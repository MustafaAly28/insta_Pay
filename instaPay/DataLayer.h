#pragma once
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

namespace DataLayer
{

	const string PersonalInfoFile = "Personal.txt";
	const string AccountsInfoFile = "Accounts.txt";
	const string AddressInfoFile = "Address.txt";
	const string TransactionsInfoFile = "TransactionsHistory.txt";
	const string DepositsInfoFile = "Deposits.txt";
	const string WithDrawsInfoFile = "WithDraws.txt";
	const string DonationsInfoFile = "Donations.txt";
	const int USERS_COUNT = 10;
	int AddingUsersCounter = 0;
	const int MAX_TRANSACTIONS_PER_USER = 10;
	int AddingTransactionsCounter = 0;
	int AddingDepositsCounter = 0;
	int AddingWithDrawsCounter = 0;

	struct StAddress
	{
		string Street;
		string City;
		string HomeNumber;
	};

	struct StAccount
	{
		double Balance;
		string CVVCode;
		string ExpirationDate;
		string BankName;
		string CardNumber;
		string PINCode;
		string HolderName;
	};

	struct StTransactions
	{
		string BankNameForSender;
		string BankNameForReceiver;
		string PhoneNumber_From;
		string PhoneNumber_To;
		string Date;
		double Amount;
	};

	struct StDonation
	{
		string CardNumber = "";
		string OrganizationName = "";
		string BankNameForSender = "";
		string Date = "";
		double Amount = 0;
	};

	struct StUser
	{
		string UserName;
		int Id;
		string Phone;
		string Password;
		string Email;
		StAddress Address;	     									 // Each User Can Create One Account Only
		StAccount AccountsList[3];	   							    // Each User Can Create Three Accounts Only 
		StTransactions TransactionsSending[MAX_TRANSACTIONS_PER_USER];// Transactions (From) History Of User
		StTransactions TransactionsRecieving[MAX_TRANSACTIONS_PER_USER]; // Transactions (To) History Of User
		int CountAccounts = 0;
		int TransactionsCountSending = 0;
		int TransactionsCountRecieving = 0;
		StTransactions Deposits[MAX_TRANSACTIONS_PER_USER];
		StTransactions Withdrawals[MAX_TRANSACTIONS_PER_USER];
		StDonation Donations[MAX_TRANSACTIONS_PER_USER];
		int DepositsCount = 0;
		int WithdrawalsCount = 0;
		int DonationsCount = 0;
	};

	StUser Users[USERS_COUNT];
}