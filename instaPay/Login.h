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
namespace AddNewAccount {

    void addNewAccount();
    string ConvertTOLower(string S);
}

namespace MainMenu {
    void mainWindow();
}

using namespace std;
using namespace DataLayer;
namespace Login {

    void Register();
    void LoGin();
    void HaveAccount();

    //inline int UserIndex;
    inline int UserIndex;
    int FindUser(string Name, string Pass) {
        for (int i = 0; i < AddingUsersCounter; i++) {
            if (Name == Users[i].UserName && Pass == Users[i].Password) {
                return i;
            }
        }
        return -1;
    }


    bool ValidePhone(string Phone) {//اجمد حاجة عملتها حتي الأن بيتشك علي انه 11 رقم وكمان يكونوا مصري فودافون اورنج اتصالات هكذا

        if (Phone.length() != 11) { Beep(200, 600); cout << "The number must be 01XXXXXXXX!\n"; return false; }
        if (Phone[0] != '0' || Phone[1] != '1') { Beep(200, 600); cout << "Invalid Number! please make sure it's correct." << endl; return false; }

        char ThirdNum = Phone[2];
        if (ThirdNum != '0' && ThirdNum != '1' && ThirdNum != '2' && ThirdNum != '5') {
            Beep(200, 600);
            cout << "Invalid Number! please make sure it's correct." << endl; return false;
        }

        for (int i = 0; i < Phone.length(); i++) {
            if (Phone[i] < '0' || Phone[i]> '9') {
                Beep(200, 600);
                cout << "Invalid Number! please make sure it's correct." << endl;
                return false;
            }
        }
        for (int i = 0; i < AddingUsersCounter; i++) {
            if (Users[i].Phone == Phone) {
                Beep(200, 600);
                cout << "This number is not available!" << endl;

                return false;

            }
        }

        return true;
    }




    void ShowLoading() {
        cout << "\nConnecting to Instapay Servers ";
        for (int i = 0; i < 3; i++) {
            Sleep(500); // بينتظر نص ثانية (500 مللي ثانية)
            cout << ".";
        }
        cout << "\n";
        system("cls"); // بيمسح الشاشة بعد ما يخلص
    }



    bool StrongPassword(string Pass) {
        bool HasSymbol = false;
        bool HasUpper = false;
        if (Pass.length() < 8) {
            Beep(200, 600);
            cout << "[!] Password too short! Minimum length is 8 characters.\n";
            return false;
        }
        for (int i = 0; i < Pass.length(); i++) {
            if (Pass[i] == '@' || Pass[i] == '#' || Pass[i] == '$' || Pass[i] == '%' || Pass[i] == '&' || Pass[i] == '!') {
                HasSymbol = true;
            }
        }
        if (!HasSymbol) { Beep(200, 600); cout << "Password must include symbol! (#,$,@)\n"; return false; }
        for (int i = 0; i < Pass.length(); i++) {
            if (isupper(Pass[i])) {
                HasUpper = true;
                break;
            }
        }
        if (!HasUpper) { Beep(200, 600); cout << "Password must include uppercase letter!\n"; return false; }
        return true;
    }




    bool ValidEmail(string Email) {
        string AllowedDomains[] = { "@gmail.com", "@yahoo.com", "@outlook.com", "@hotmail.com",//17 Domains
            "@icloud.com", "@aol.com", "@msn.com","@live.com", "@cox.net", "@me.com", "@comcast.net",//GMass
            "@ymail.com", "@sbcglobal.net", "@att.net", "@hotmail.it", "@kw.com", "@mail.ru" };//كل الدومينات بتاعة الايميلات دي جايبها من الموقع ده اشهر دومينات  

        int CounterAt = 0;
        int CounterDot = 0;
        bool DomainFound = false;
        for (int i = 0; i < Email.length(); i++) {

            if (Email[i] == ' ') {
                Beep(200, 600);
                cout << "[!] No spaces allowed!\n"; return false;
            }


            if (Email[i] == '@') CounterAt++;
            if (Email[i] == '.') CounterDot++;
        }

        for (int i = 0; i < AddingUsersCounter; i++) {
            if (Email == Users[i].Email) { Beep(200, 600); cout << "This Email is not available!" << endl; return false; }
        }
        if (CounterAt != 1 || CounterDot < 1) {
            Beep(200, 600);
            cout << "[!] Invalid Email format!\n";
            return false;
        }
        for (int i = 0; i < 17; i++) {
            if (Email.find(AllowedDomains[i]) != string::npos)
            {
                DomainFound = true;
            }
        }
        if (!DomainFound) { Beep(200, 600);  cout << "[!] Please use a valid email provider \n"; return false; }
        return true;
    }





    void Register() {
        if (AddingUsersCounter >= USERS_COUNT) {
            Beep(200, 600);
            cout << "System Full!" << endl;
            return;
        }

        cout << "========= Register =========" << endl;

        bool IsTaken;
        string TempName;
        // cin.ignore(1000, '\n');
        do {
            IsTaken = false;
            cout << "Enter your name : ";

            getline(cin >> ws, TempName);

            for (int i = 0; i < AddingUsersCounter; i++) {
                if (TempName == Users[i].UserName) {
                    IsTaken = true;
                    Beep(200, 600);
                    cout << "This name already taken! enter another name.\n" << endl;
                    break;
                }
            }
        } while (IsTaken);

        Users[AddingUsersCounter].UserName = TempName;




        string CheckEmail;
        bool EmailFalse;
        while (true) {
            cout << "Enter email : ";

            cin >> CheckEmail;
            EmailFalse = ValidEmail(CheckEmail);
            if (EmailFalse) {
                Users[AddingUsersCounter].Email = CheckEmail;
                break;
            }
        } while (!EmailFalse);





        bool TestPhone = false;
        do {

            cout << "Enter phone : ";
            cin >> Users[AddingUsersCounter].Phone;
            TestPhone = ValidePhone(Users[AddingUsersCounter].Phone);


        } while (TestPhone == false);

        cout << "Enter your address details\n";
        cout << "-----------------------------\n";
        cout << "Enter city : ";
        getline(cin >> ws, Users[AddingUsersCounter].Address.City);
        cout << "Enter street name : ";
        getline(cin >> ws, Users[AddingUsersCounter].Address.Street);
        cout << "Enter home number : ";
        getline(cin >> ws, Users[AddingUsersCounter].Address.HomeNumber);
        cout << "-----------------------------\n";
        string Pass, Confirm;
        do {
            while (true) {
                cout << "Enter password : ";
                cin >> Pass;

                if (StrongPassword(Pass)) { break; }

            }

            cout << "Confirm password : ";
            cin >> Confirm;

            if (Pass != Confirm) { Beep(200, 600); cout << "Passwords do not match! Try again." << endl; }
        } while (Pass != Confirm);

        Users[AddingUsersCounter].Password = Confirm;

        Users[AddingUsersCounter].CountAccounts = 0;
        Users[AddingUsersCounter].Id = AddingUsersCounter + 1;
        AddingUsersCounter++;
        PlaySound(TEXT("Sounds\\ElevenLabs_Triumphant_chime_signaling_successful_task_completion.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "Sign Up Successful!\n";
        cout << "Your ID is : " << Users[AddingUsersCounter - 1].Id << endl;
        LoGin();


        cin.ignore();
    }

    void LoGin() {
        ShowLoading();
        cout << "\t\t\t\t=================================" << "\n";
        cout << "\t\t\t\t            INSTAPAY            " << "\n";
        cout << "\t\t\t\t=================================" << "\n";

        // يفضل تشيل ShowLoading() من هنا عشان ملهاش لازمة تظهر قبل ما اليوزر يكتب حاجة

        string CheckName, CheckPassword;
        int Counter = 0;

        cout << "\t\t\t\tThree Attempts to login\n";

        // شيلنا الـ cin.ignore من هنا عشان متعملش تعليقة للبرنامج

        do {
            cout << "\n\t\t\t\t=========== Login Page ==========" << endl;
            cout << "\t\t\t\tEnter Your Name     : ";


            if (cin.peek() == '\n') cin.ignore();
            getline(cin >> ws, CheckName);

            cout << "\t\t\t\tEnter Your Password : ";
            cin >> CheckPassword;
            //  cin.ignore(1000, '\n');

            UserIndex = FindUser(CheckName, CheckPassword);


            if (UserIndex != -1) {

                ShowLoading();
                //PlaySound(TEXT("Sounds\\ElevenLabs_Triumphant_chime_signaling_successful_task_completion.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cout << "\t\t\t\a Login Successful! Welcome, " << Users[UserIndex].UserName << " Your ID : " << Users[UserIndex].Id << endl;


                if (Users[UserIndex].CountAccounts == 0) {
                    //FirstAccount();
                    AddNewAccount::addNewAccount();
                }



                MainMenu::mainWindow();



                return;
            }
            else {
                Beep(200, 600);
                cout << "\t\t\t\tInvalid!! username or password." << endl;
                Counter++;

            }

        } while (Counter < 3);

        Beep(200, 600);
        cout << "\n\t\t\t\t[!] Access Denied. Returning to start..." << endl;
    }
    void HaveAccount() {
        string Choice;
        cout << "\t\t\t\tDo You Have An Account? (Y/N) : ";
        cin >> Choice;
        if (Choice.length() == 1 && (Choice == "Y" || Choice == "y")) {
            ShowLoading();
            PlaySound(TEXT("Sounds\\ps4_login.wav"), NULL, SND_FILENAME | SND_ASYNC);
            LoGin();
        }
        else if (Choice.length() == 1 && (Choice == "N" || Choice == "n")) {
            ShowLoading();
            PlaySound(TEXT("Sounds\\ps4_login.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Register();
        }
        else {
            Beep(200, 600);
            cout << "\t\t\t\t Invalid Choice! Please Enter Y Or N.\n";
            HaveAccount();
        }
    }

    bool AreTermsAccepted() {
        ifstream CheckFile("config.txt");
        string status;
        if (CheckFile >> status && status == "Accepted") {
            return true; // وافق قبل كدة
        }
        return false; // أول مرة يفتح
    }

    void SaveTermsAcceptance() {
        ofstream WriteFile("config.txt");
        WriteFile << "Accepted";
        WriteFile.close();
    }


    // الاستخدام:
    //SetColor(10); // أخضر للنجاح
    //cout << "Transaction Successful!";
    //SetColor(12); // أحمر للأخطاء
    //cout << "Insufficient Balance!";
    //SetColor(7);  // رجوع للون الأبيض العادي
    void Terms() {
        string Accept;
        cout << "================ Terms and Conditions ===============\n\n";
        cout << "1. By using InstaPay, you agree to our terms and conditions.\n";
        cout << "2. InstaPay is a secure platform for digital payments and transfers.\n";
        cout << "3. Users are responsible for maintaining the confidentiality of their account information.\n";
        //cout << "4. InstaPay is not liable for any unauthorized transactions or account breaches." << endl;
        cout << "4. Users must comply with all applicable laws and regulations when using InstaPay.\n";
        //cout << "6. InstaPay reserves the right to suspend or terminate accounts that violate our terms." << endl;
        cout << "5. By creating an account, you confirm that you are at least 18 years old.\n";
        //cout << "8. InstaPay may collect and use personal data in accordance with our privacy policy." << endl;
        cout << "6. Users must not use InstaPay for illegal activities or fraudulent purposes.\n";
        // cout << "10. By using InstaPay, you acknowledge that you have read and understood these terms." << endl;
        cout << "====================================================\n\n";
        //cout << " Please type 'I AGREE' to finalize your registration : ";

        int Counter = 0;
        while (Counter < 3) {
            cout << "Please type 'I AGREE' to finalize your registration : ";
            getline(cin >> ws, Accept);
            if (AddNewAccount::ConvertTOLower(Accept) == "i agree") {

                cout << "Thank you for accepting the terms and conditions" << endl;
                SaveTermsAcceptance();
                cout << "Loading";
                for (int i = 0; i < 3; i++) {
                    Counter = 0;
                    Sleep(1000);
                    cout << ".";
                }
                cout << endl;
                system("cls");
                HaveAccount();

            }
            else {
                //cout << "You must accept the terms and conditions to continue. Please try again." << endl;
                Counter++;
            }
        }
    }
}