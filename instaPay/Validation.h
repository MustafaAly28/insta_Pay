#pragma once
#pragma once
#include<iostream>
#include"DataLayer.h"
#include "Login.h"
using namespace std;
using namespace DataLayer;
using namespace Login;

//namespace Validation
//
////{
////
//	bool IsUserExist(StUser& User, const StUser Users[], const int CountUsers)
//	{
//		bool IsExist = true;
//
//		for (int PositionUser = 0; PositionUser < CountUsers; PositionUser++)
//		{
//			if (User.UserName == Users[PositionUser].UserName && User.Password == Users[PositionUser].Password)
//			{
//				User = Users[PositionUser];
//				return IsExist;
//			}
//		}
//		return !IsExist;
//	}
//
//	bool IsPhoneRulesValid(const string& PhonePart)
//	{
//		const short PhoneRulesCount = 4;
//		string PhoneRules[PhoneRulesCount] = { "011", "010", "012", "015" };
//		bool IsValidRule = true;
//
//		for (int Char = 0; Char < PhoneRulesCount; Char++)
//		{
//			if (PhonePart == PhoneRules[Char])
//				return IsValidRule;
//		}
//
//		return !IsValidRule;
//	}
//
//	bool IsPhoneNumberValid(const string& PhoneNumber)
//	{
//		short Counter = 0;
//		bool IsValid = true;
//
//		if (!IsPhoneRulesValid(PhoneNumber.substr(0, 3)))
//			return !IsValid;
//
//		for (int Character = 0; Character < PhoneNumber.length(); Character++)
//		{
//			Counter++;
//			if (!isdigit(PhoneNumber[Character]))
//				return !IsValid;
//		}
//
//		return (Counter == 11) ? IsValid : !IsValid;
//	}
//
//	bool IsCardNumberExist(const string& CardNumber, const StUser Users[], const int CountUsers)
//	{
//		bool IsExist = true;
//
//		for (int UserPosition = 0; UserPosition < AddingUsersCounter; UserPosition++)
//		{
//			for (int AccountPosition = 0; AccountPosition < Users[UserPosition].CountAccounts; AccountPosition++)
//			{
//				if (Users[UserPosition].AccountsList[AccountPosition].CardNumber == CardNumber)
//					return IsExist;
//			}
//		}
//		return !IsExist;
//	}
//
//	bool IsBankNameValid(string& BankName)
//	{
//		string BankNames[] = { "Bank Al Ahly", "CIB" , "Bank Masr" };
//		const int CountBank = 3;
//		bool IsValid = true;
//
//		for (int Bank = 0; Bank < CountBank; Bank++)
//		{
//			if (ConvertToLower(BankNames[Bank]) == ConvertToLower(BankName))
//			{
//				BankName = BankNames[Bank];
//				return IsValid;
//			}
//		}
//		return !IsValid;
//	}
//
//	bool IsCvvCodeExist(const string& CvvCode, const StUser Users[], const int CountUsers)
//	{
//		for (int UserPosition = 0; UserPosition < CountUsers; UserPosition++)
//		{
//			for (int AccountPosition = 0; AccountPosition < Users[UserPosition].CountAccounts; AccountPosition++)
//			{
//				if (Users[UserPosition].AccountsList[AccountPosition].CVVCode == CvvCode)
//					return true;
//			}
//		}
//		return false;
//	}
//
//	bool IsEmailValid(const string& Email)
//	{
//		int CountCharacters = 0;
//		for (size_t Char = 0; Char < Email.length(); Char++)
//		{
//			CountCharacters++;
//			if (Email[Char] == '@')
//				break;
//		}
//
//		if ((Email.find("@gmail.com") != string::npos) && CountCharacters >= 5)
//			return true;
//
//		return false;
//	}
//
//	bool IsEmailExist(const string& Email, const StUser Users[], const int CountUsers)
//	{
//		for (int UserPosition = 0; UserPosition < CountUsers; UserPosition++)
//		{
//			if (Users[UserPosition].Email == Email)
//				return true;
//		}
//		return false;
//	}
//
//	bool IsIdExist(int Id, const StUser Users[], const int CountUsers)
//	{
//		for (int UserPosition = 0; UserPosition < CountUsers; UserPosition++)
//		{
//			if (Users[UserPosition].Id == Id)
//				return true;
//		}
//		return false;
//	}
//
//	bool IsBalanceValid(double Balance)
//	{
//		return (Balance > 0);
//	}
//}
