#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Contact.h"
#include "ContactList.h"
using namespace std;

int main() {
    char input;
    ContactList c;
    string filename;
    string searchterm;
    vector<int> found_contacts;
    string input2;
    char input3;
    char yes_no;
    string input_email;
    vector<string> numbers;
    char input4;
    string phone_num_in;
    char phonetype;
    string pt;
    while (input != 'X') {
        cout << "********************************************\nMain Menu\nEnter the letter for the desired menu option:\n   C - Get count\n   L - Load contacts from file\n   S - Search contacts\n   P - Print contacts\n   X - Exit\n";
        cin >> input;
        input = toupper(input);
        switch (input) {
            case 'C':
            cout << "There are " << c.getCount() << " contacts\n\n";
            break;
            case 'X':
            break;
            case 'L':
            cout << "Enter a filename\n";
            cin >> filename;
            cout << c.loadContactsFromFile(filename) << endl;
            break;
            case 'S':
            cout << "\nEnter a search term" << endl;
            cin >> searchterm;
            found_contacts = c.findContactsByName(searchterm);
            if (found_contacts.size() == 1){
                cout << "Found " << found_contacts.size() << " result" << endl;
            } else {
                cout << "Found " << found_contacts.size() << " results" << endl;
            }
            for (int i = 0; i < found_contacts.size(); ++i) {
                cout << i+1 << ". " << c.getContact(found_contacts[i])->getName() << endl;
            }
            cout << "Enter an option:\n   P - Print contacts\n   or a Contact number to view/edit\n   R - Return to main menu" << endl;
            cin >> input2;
            if (isalpha(input2[0])) {
                input2 = toupper(input2[0]);
                switch (input2[0]) {
                    case 'P':
                    c.printContacts(found_contacts);                     
                    break;
                    case 'R':
                    break;
            }
            } else {
                int in = stoi(input2);
                in -= 1;
                cout << c.getContact(found_contacts[in])->getAsString() << endl;
                cout << "Enter an option for contact: \n   A - Edit address\n   B - Edit date of birth\n   E - Edit email address\n   N - Edit name\n   P - Edit phone numbers\n   R - Return to main menu\n   D - Delete" << endl;
                cin >> input3;
                input3 = toupper(input3);
                switch (input3) {
                    case 'A':
                    break;
                    case 'B':
                    break;
                    case 'E':
                    cout << "Current email:\n" << c.getContact(found_contacts[in])->getEmail() << endl;
                    cout << "Enter new email or C to cancel:\n";
                    cin >> input_email;
                    if (input_email == "C" || input_email == "c") {
                        break;
                    } else {
                        c.getContact(found_contacts[in])->setEmail(input_email);
                        cout << "Email updated:\n" << c.getContact(found_contacts[in])->getEmail() << endl;
                    }
                    break;
                    case 'N':
                    break;
                    case 'P':
                    if ((c.getContact(found_contacts[in])->getPhoneNumbers()).size() > 1) {
                    cout << "Found "<< (c.getContact(found_contacts[in])->getPhoneNumbers()).size() << " phone numbers\n";
                    } else {
                    cout << "Found "<< (c.getContact(found_contacts[in])->getPhoneNumbers()).size() << " phone number\n"; 
                    }
                    numbers = c.getContact(found_contacts[in])->getPhoneNumbers();
                    for (int i = 0; i < numbers.size(); ++i) {
                        cout << i+1 << ". " <<numbers[i] << endl;
                    }
                    cout << "Enter an option:\n   A - Add a phone number\n   R - Return to main menu\n   or list number to delete" << endl;
                    cin >> input4;
                    if (isalpha(input4)){
                    switch (input4) {
                        case 'A':
                        cout << "Enter the letter for the phone number type: \nC(ell), W(ork) or H(ome)\n";
                        cin >> phonetype;
                        phonetype = toupper(phonetype);
                        cout << "Enter the phone number:" << endl;
                        cin >> phone_num_in;
                        c.getContact(found_contacts[in])->addPhone(phonetype, phone_num_in);
                        switch (phonetype) {
                            case 'W':
                            pt = "Work";
                            break;
                            case 'C':
                            pt = "Cell";
                            break;
                            case 'H':
                            pt = "Home";
                            break;
                        }
                        cout << "success: added number "<< phone_num_in << " " << pt;
                        break;
                        case 'R':
                        break;
                    }
                    } else {
                        int in2 = input4 - '0';
                        in2 -= 1;
                        cout << "Are you sure you want to delete phone: " << numbers[in2] <<"?" << endl;
                        cout << "Enter 'Y' to confirm." << endl;
                        cin >> yes_no;
                        yes_no = toupper(yes_no);
                        string num_only = numbers[in2].erase(0, 4);
                        if (yes_no == 'Y'){
                        cout << "success: deleted phone "  <<num_only << endl;
                        c.getContact(found_contacts[in])->deletePhone(in2);
                        }
                    }
                    break;
                    case 'R':
                    break;
                    case 'D':
                    cout << "Are you sure you want to delete contact " << c.getContact(found_contacts[in])->getName() <<"?" << endl << "Enter 'Y' to confirm."<<endl;
                    cin >> yes_no;
                    yes_no = toupper(yes_no);
                    if (yes_no == 'Y'){
                        cout << c.deleteContact(found_contacts[in]);
                    }
                    break;
                }
            }
            break;
        }
    }
}