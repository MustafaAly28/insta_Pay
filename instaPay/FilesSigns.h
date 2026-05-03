#pragma once
#include<iostream>
using namespace std;

// This Signs For Serilaization On Data Files
/*
	File (Address Data) => Seprator Or Delimeter Is /#/
	(Street/#/City/#/HomeNumber)

	File (Account  Data) => Seprator Or Delimeter Is $
	(PhoneNumber$CardNumber$PINCode$HolderName$BankName$CVVCode$ExpirationDate$Balance)
	/* The Phone Number Is Connector With All Accounts For One User *\

	File (Personal  Data) => Seprator Or Delimeter Is #
	(UserName!#!Id!#!Password!#!Phone!#!Email)

	File (Transactions  Data) => Seprator Or Delimeter Is %#%
	(BankNameOfSender%#%BankNameOfReceiver%#%From(PhoneNumber)%#%To(PhoneNumber)%#%Date%#%Amount

	File(Deposit - WithDraw) => Seprator Or Delimeter Is /%/
	(PhoneNumber/%/BankNameForSender/%/Date/%/Amount)

   File (Donations) =>  Seprator Or Delimeter Is &/&
	(CardNumber/%/BankNameForSender&/&OrganizationName&/&Date&/&Amount)
*/

const string SepratorPersonalData = "!#!";
const string SepratorAccountData = "$";
const string SepratorAddressData = "/#/";
const string SepratorTransactionData = "%#%";
const string SepratorDepositOrWithDrawData = "/%/";
const string SepratorDonationData = "&/&";