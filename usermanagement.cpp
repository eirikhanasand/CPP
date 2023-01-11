//
//  Simple user management system with encrypted password
//
//  login.cpp
//  CPP
//
//  Created by Eirik Hanasand on 11/01/2023.
//


#include <iostream>
using namespace std;

const int STRLEN = 80;                      //  Max input length
const int MAXUSERS = 20;                    //  Max number of users
const int ASCIIFIRST = 33;                  //  First legal ASCII value
const int ASCIINRSIST = 126;                //  Last legal ASCII value.
const int MOD = (ASCIINRSIST-ASCIIFIRST);   //  Modding with ASCII interval
const int CIPHER = 42;                      //  Rotating 42 positions

int main(){
    //Arrays
    char userName[MAXUSERS][STRLEN];        //  Array for username
    char userPass[MAXUSERS][STRLEN];        //  Array for password
    char nameLogin[STRLEN];                 //  Username when login
    char passLogin[STRLEN];                 //  Password when login

    //Overview
    char choice;                            //  Users choice
    int userCount   = 0;                    //  Number of users existing
    int userNumber  = 0;                    //  Username logged in
    int hasSpace    = 0;                    //  Checking for space

    //Used for password
    int hasUpper = 0;                       //  Amount of uppercase letters
    int hasLower = 0;                       //  Amount of lowercase letters
    int hasOther = 0;                       //  Amount of other characters
    int illegalChar = 0;                    //  Amount of illegal characters
    bool approved = false;                  //  Password validity
    int value;                              //  ASCII value when encryption
    int encryptedChar;                      //  Value of encrypted character

    //Used at login
    bool brukerMatch = false;               //  Checks if username exists
    bool passMatch = false;                 //  Checks if password exists
    
    do{
                                            //  Asks for user input
        cout << "What would you like to do? (N, L, S, R, Q)\n";
        cin >> choice;                      //  Gets the users choice
        choice = toupper(choice);           //  Sets it to uppercase

        switch (choice) {                   //  Contains all user options
                
            case 'N':                       //  Create account
                
                if (userCount < MAXUSERS) { //  Checks for space for new user
                    
                    do{                     // Loops till username is legal
                        hasSpace = 0;                   //  Amount of spaces
                        cout << "Choose username:\n";   //  Asking for username
                        cin >> userName[userCount];     //  Getting username
                        if (strlen(userName[userCount]) == 0) {
                            cout << "Username may not be empty.\n";
                            hasSpace++;
                        }
                        //  Checks for spaces in username
                        if (strchr(userName[userCount], ' ') != 0){
                            cout << "Spaces are not allowed!\n";
                            hasSpace++;
                        }
                        
                        //Looper till username is legal
                        }while(hasSpace > 0);
                        
                    do{     //Until password satisfies all requirements
                        
                        //In case of multiple rounds
                        hasSpace = 0;       //Amount of spaces
                        hasUpper = 0;       //Amount of uppercase
                        hasLower = 0;       //Amount of lowercase
                        hasOther = 0;       //Amount of other chars
                        illegalChar = 0;    //Amount of illegal chars
                        
                        do{ //Loops till passord exists without spaces
                            
                            hasSpace = 0;                   //Amount of spaces
                            cout << "Choose password:\n";
                            cin >> userPass[userCount];
                            
                            //Checking for empty password
                            if (strlen(userPass[userCount]) == 0) {
                                cout << "Password may not be empty.\n";
                                hasSpace++; // Amount of spaces
                            }
                            //Checking for spaces in password
                            if (strchr(userPass[userCount], ' ') != 0){
                                cout << "Spaces not allowed!\n";
                                
                                //Increasing hasSpaces (checked later)
                                hasSpace++;
                            }
                        }while(hasSpace > 0); // Loops till no spaces
                                                
                        //Checking every character in the password
                        for (int i = 0; i <= strlen(userPass[userCount]
                                                    )-1; i++) {
                            
                            //Checking if they are legal ASCII chars
                            if(ASCIIFIRST <= (userPass[userCount][i]) &&
                               ASCIINRSIST >= (userPass[userCount][i])){
                                
                                if(isupper(userPass[userCount][i])){
                                    hasUpper++; // Amount of uppercase
                                }else if(islower(userPass[userCount][i])){
                                    hasLower++; // Amount of lowercase
                                }else{
                                    hasOther++; // Amount of special characters
                                }
                            }else{
                                illegalChar++;  // Amount of illegal characters
                            }
                        }
                        
                        //Error if illegal characters
                        if(illegalChar-1 == 0){
                            cout << "Password contains illegal characters.\n";
                            approved = false;
                        
                        //Error if uppercase is missing
                        }else if (hasUpper == 0){
                            cout << "Password must contain uppercase letter.\n";
                            approved = false;
                        
                        //Error if lowercase is missing
                        }else if (hasLower == 0){
                            cout << "Password must contain lowercase letter.\n";
                            approved = false;
                        
                        //Error if other character is missing
                        }else if (hasOther == 0){
                            cout << "Password must contain a special character"
                                 << "or number.\n";
                            approved = false;
                        
                        //Bool is true if password is approved
                        }else{
                            approved = true;
                        }
                
                    //Loops till password satisifies all requirements
                    }while(approved == false);
                            
                    //Encrypting every sign in the password
                    for (int i = 0; i < strlen(userPass[userCount]); i++) {

                        //Subtracting first ascii and modding by cipher
                        value = ((int)userPass[userCount][i]
                                        - ASCIIFIRST + CIPHER) % MOD;
                                
                        //Adding first ascii again
                        int kryptertTegn = value + ASCIIFIRST;
                                
                        //Writing encrypted password to array userPass
                        userPass[userCount][i] = (char)kryptertTegn;
                        approved = true;
                    }
                    
                    approved = false;
                    userCount++;  //Increasing amount of users
                    
                    //Nr and name for the user made
                    cout << "Created user: " << userCount << "\tUsername: " <<
                            userName[userCount-1] << "\n";
                    
                }else{
                    //If there is not room for more users
                    cout << "There is no room for more users!\n";
                }
                
                break;  //Creating user completed
                
            case 'L':   //Login
                
                //Checking if there are users
                if(userCount == 0) {
                    
                    //Error message if there are no users
                    cout << "Make an account first!\n";
                    
                }else{                      //If there are users
                    cout << "Username:\n";  //Asking for username
                    cin >> nameLogin;        //Getting username
                    
                    cout << "Password:\n";  //Asking for password
                    cin >> passLogin;        //Getting password
                    
                    //Loops through every character
                    for (int i = 0; i < strlen(passLogin); i++) {
                        
                        //Subtracting first ASCII value and modding by CIPHER
                        value = ((int)passLogin[i] - ASCIIFIRST + CIPHER) % MOD;
                        
                        //Adding first ASCII value back on
                        encryptedChar = value + ASCIIFIRST;
                        
                        //Writing encrypted password to passLogin
                        passLogin[i] = (char)encryptedChar;
                    }
                    
                    //Loops through all users
                    for (int i = 0; i < userCount; i++) {
                        
                        //Searching for matching user
                        brukerMatch = strcmp(nameLogin, userName[i]);
                        
                        //Searching for matching password
                        passMatch = strcmp(passLogin, userPass[i]);
                        
                        //If there is a match
                        if (brukerMatch == 0 && passMatch == 0) {
                            userNumber = i+1;
                        }
                    }
                    
                    //Logging in if login information is correct
                    if (userNumber > 0) {
                        
                        //Which account was logged in
                        cout << "Logged in as " <<
                                userName[userNumber-1] << "\n";
                        
                    //Error message if username or password is wrong
                    }else{
                        cout << "This is not correct.\n";
                    }
                }

                break;  //Login Complete
             
            case 'R':   //Remove user
                
                //Checking if there are users
                if(userCount == 0) {
                    
                    //Error message if there are no users
                    cout << "There are no users to remove!\n";
                    
                }else{                          // If there are users
                    cout << "Username to remove:\n";      // Asking for username
                    cin >> nameLogin;
                    
                    cout << "Password:\n";      //Asking for password
                    cin >> passLogin;
                    
                    //Loops through every character
                    for (int i = 0; i < strlen(passLogin); i++) {
                        
                        //Subtracting first ASCII value and modding by CIPHER
                        value = ((int)passLogin[i] - ASCIIFIRST + CIPHER) % MOD;
                        
                        //Adding first ASCII value back on
                        encryptedChar = value + ASCIIFIRST;
                        
                        //Writing encrypted password to passLogin
                        passLogin[i] = (char)encryptedChar;
                    }
                    
                    //Loops through all users
                    for (int i = 0; i < userCount; i++) {
                        
                        //Searching for matching user
                        brukerMatch = strcmp(nameLogin, userName[i]);
                        
                        //Searching for matching password
                        passMatch = strcmp(passLogin, userPass[i]);
                        
                        //If there is a match
                        if (brukerMatch == 0 && passMatch == 0) {
                            userNumber = i+1;
                        }
                    }
                    
                    //Removing user if user details are correct
                    if (userNumber > 0) {
                        
                        //Which account is going to be removed
                        cout << "Press y to remove user " <<
                        userName[userNumber-1] << " (id: " << userNumber << ")\n";
                        
                        cin >> choice;
                        if (choice == 'y') {
                            for (int i = userNumber-1; i < userCount; i++) {
                                strcpy(userName[i], userName[i+1]);
                                strcpy(userPass[i], userPass[i+1]);
                            }
                            userCount--;
                            cout << "User removed.\n";
                            
                        } else {
                            cout << "Cancelled user removal.\n";
                        }
                        
                    //Error message if username or password is wrong
                    }else{
                        cout << "This is not correct.\n";
                    }
                }

                break;  //Login Complete
                
            case 'S':   //See all users
                
                //Checking if there are users
                if(userCount == 0) {
                    
                    //Error message if there aare no users
                    cout << "There are no users!\n";
                    
                }else{  //If there are users
                    cout << "Showing users:\n";
                    
                    //Looping through the arrays and showing all users
                    for (int i = 0; i < userCount; i++) {
                        
                        //Writing userNumber, username and password
                        cout << "User: " << i+1 << "\tUsername: " << userName[i]
                             << "\tPassword: " << userPass[i] << "\n";
                    }
                }
                
                break;              //Done showing users
                
            case 'Q':               //Quitting the program
                break;              //Going to while statement
                
          //Error message if input was not a choice
            default:
                cout << "You entered \"" << choice << "\". Try again.\n";
                break;
        }
        
    }while(choice != 'Q');    //Exiting the do while loop if Q was entered
    
    //Informing the user that the program is terminated
    cout << "You terminated the program using " << choice << ".\n";
    
    return 0;   //Terminating the program
}
