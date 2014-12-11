//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number
    string temp;                          // Temp Name Placeholder

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
    acctFile >> entry.acctID;
    while(acctFile.good())
    {
        //Skip the beginning stuff, change to seekg/tellg
        acctFile >> temp >> temp >> temp;
        entry.recNum = recNum;
        recNum++;
        index.insert(entry);
        acctFile >> entry.acctID;
    }

    // Output the account IDs in ascending order.
    cout << endl << "Account IDs : " << endl;
    index.writeKeys();

    // Clear the status flags for the database file.
    acctFile.clear();
    acctFile.close();
    acctFile.open("accounts.dat");

    // Read an account ID from the keyboard and output the
    // corresponding record.
    cout << endl << "Enter account ID : ";
    while(cin >> searchID)
    {
        if(index.retrieve(searchID, entry))
        {
            for(int i = 0; i <= entry.recNum; i++)
            {
                acctFile >> acctRec.acctID;
                acctFile >> acctRec.firstName >> acctRec.lastName;
                acctFile >> acctRec.balance;
            }

            cout << entry.recNum << " : ";
            cout << acctRec.acctID << " " << acctRec.firstName << " ";
            cout << acctRec.lastName << " ";
            cout << acctRec.balance;
        }
        else
            cout << "No record with that account ID";

        acctFile.clear();
        acctFile.close();
        acctFile.open("accounts.dat");
        cout << endl << "Enter account ID (EOF to quit): ";
    }

    return 0;
}
