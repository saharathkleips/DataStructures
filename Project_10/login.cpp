/** @file login.cpp
* @author Saharath Kleips
* @brief This program tests the username / password functionality of a Hash
* Table.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 10. This program will
* load username / password sets from a file and insert them into the Hash Table.
* There should be one username / password set (separated by 1 tab) per line.
* The program will ask for a login and password then will determine if
* authentication is successful or not.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include <iostream>
#include <fstream>
#include "HashTable.cpp"

//
// FORWARD DECLARATIONS ////////////////////////////////////////////////////////
//

class Login
{
public:
    void setKey(const string& username);
    void setPassword(const string& password);
    string getKey() const;
    string getPassword() const;
    static unsigned int hash(const string& s);

private:
    string key;
    string password;
};

//
// FUNCTION IMPLEMENTATIONS ////////////////////////////////////////////////////
//

/** The main entry point
* of this program.
*/
int main()
{
    ifstream ifs("password.dat");
    HashTable<Login, string> table(8);
    Login temp;

    string username, password;
    //grab the username
    ifs >> username;
    //while there is still data in the file
    while(ifs.good())
    {
        //grab the password
        ifs >> password;
        //set the login information (temp)
        temp.setKey(username);
        temp.setPassword(password);
        table.insert(temp);
        //grab the username
        ifs >> username;
    }
    table.showStructure();

    //Prompt for login
    cout << "Login: ";
    //While the user continues to input login information
    while(cin >> username)
    {
        //Prompt for password
        cout << "Password: ";
        cin >> password;

        //Determine if the login exists in the table
        if(table.retrieve(username, temp))
        {
            //Determine if the password matches the login
            if(temp.getPassword() == password)
                cout << "Authentication successful" << endl;
            //The password does not match
            else
                cout << "Authentication failure" << endl;
        }
        //The login does not exist
        else
            cout << "Authentication failure" << endl;
        cout << "Login: ";
    }

    return 1;
}

/** Mutator for username
* data of this Login.
* @post username is updated with the new username.
* @param username is the new username of this login.
*/
void Login::setKey(const string& username)
{
    key = username;
}

/** Mutator for password
* data of this Login.
* @post password is updated with the new password.
* @param password is the new password of this login.
*/
void Login::setPassword(const string& password)
{
    this->password = password;
}

/** Accessor for key
* data of this Login.
* @return The key of this Login.
*/
string Login::getKey() const
{
    return key;
}

/** Accessor for password
* data of this Login.
* @return The password of this Login.
*/
string Login::getPassword() const
{
    return password;
}

/** Generates a hash
* for a string value.
* @param s is the string to generate the hash value from.
* @return The hash value as an unsigned integer.
*/
unsigned int Login::hash(const string& s)
{
    unsigned int hashVal = 0;

    //Calculate the hash value by adding the ascii value of each character
    for(int i = 0; i < s.length(); ++i)
        hashVal += s[i];

    return hashVal;
}