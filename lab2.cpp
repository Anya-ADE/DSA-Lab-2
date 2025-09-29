#include <iostream>
#include <string>
using namespace std;


struct User {
    string username;
    string password;
    string role;
    User* next;
   
    User(const string& u, const string& p, const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};


bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer");
User* findUser(User* head, const string& username);
bool authenticate(User* head, const string& username, const string& password);
bool authorize(User* head, const string& username, const string& action);
bool removeFront(User*& head);
bool removeByUsername(User*& head, const string& username);
void clearList(User*& head);


int main() {
   
    User* head = nullptr;
    int option;
    string username, password, role;
    string action;


    do {
        cout << "  User Management System" << endl;
        cout << "1. Add a new user" << endl;
        cout << "2. Authenticate a user" << endl;
        cout << "3. Authorize a user for an action" << endl;
        cout << "4. Remove a user by username" << endl;
        cout << "5. Remove the first user" << endl;
        cout << "6. Clear list" << endl;
        cout << "7. Exit" << endl;
        cout << "Select an option: ";
        cin >> option;
        cin.ignore();


        switch (option) {
            case 1:
                cout << "Enter a username: ";
                getline(cin, username);
                cout << "Enter the password: ";
                getline(cin, password);
                cout << "Enter the role (admin, editor, viewer - leave blank for default 'viewer'): ";
                getline(cin, role);
               
                if (role.empty()) {
                    if (insertUser(head, username, password)) {
                        cout << "User: " << username << " (viewer) has been added." << endl;
                    } else {
                        cout << "Error: User " << username << " already exists." << endl;
                    }
                } else {
                    if (insertUser(head, username, password, role)) {
                        cout << "User: " << username << " (" << role << ") has been added." << endl;
                    } else {
                        cout << "Error: User " << username << " already exists." << endl;
                    }
                }
                break;


            case 2:
                cout << "Enter username to authenticate: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (authenticate(head, username, password)) {
                    User* user = findUser(head, username);
                    cout << "Authentication SUCCESS: User " << username << " (Role: " << user->role << ")." << endl;
                } else {
                    cout << "Authentication FAILED: Invalid username or password." << endl;
                }
                break;


            case 3:
                cout << "Enter username to authorize: ";
                getline(cin, username);
                cout << "Enter the action (view, edit, create, delete, etc.): ";
                getline(cin, action);


                if (authorize(head, username, action)) {
                    cout << "Authorization SUCCESS: User " << username << " is ALLOWED to perform '" << action << "'." << endl;
                } else {
                    cout << "Authorization DENIED: User " << username << " is NOT ALLOWED to perform '" << action << "'." << endl;
                }
                break;


            case 4:
                cout << "Enter username to remove: ";
                getline(cin, username);
                if (removeByUsername(head, username)) {
                    cout << "User '" << username << "' removed successfully!" << endl;
                } else {
                    cout << "User '" << username << "' not found." << endl;
                }
                break;
               
            case 5:
                if (removeFront(head)) {
                    cout << "First user removed from the list." << endl;
                } else {
                    cout << "List is empty" << endl;
                }
                break;
               
            case 6:
                clearList(head);
                cout << "List has been emptied" << endl;
                break;
               
            case 7:
                cout << "Program Exited" << endl;
                break;
               
            default:
                cout << "Enter an option between 1 and 7" << endl;
        }
        cout << endl;
    } while (option != 7);


    return 0;
}




bool insertUser(User*& head, const string& username, const string& password, const string& role) {
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            return false;
        }
        current = current->next;
    }


    User* newUser = new User(username, password, role);
    newUser->next = head;
    head = newUser;
    return true;
    //Overall Function Run Time: O(n)
}

User* findUser(User* head, const string& username){
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
    //Overall Function Run Time: O(n)
}


bool authenticate(User* head, const string& username, const string& password){
    User* user = findUser(head, username);
   
    if (user != nullptr && user->password == password) {
        return true;
    }
    return false;
    //Overall Function Run Time: O(n)
}


bool authorize(User* head, const string& username, const string& action) {
    User* user = findUser(head, username);


    if (user == nullptr) {
        return false;
    }


    const string& role = user->role;


    if (role == "admin") {
        return true;
    } else if (role == "editor") {
        return (action == "view" || action == "edit" || action == "create");
    } else if (role == "viewer") {
        return (action == "view");
    }
   
    return false;
    //Overall Function Run Time: O(n)
}
   
bool removeFront(User*& head){
    if (head == nullptr) {
        return false;
    }
    User* temp = head;
    head = head->next;
    delete temp;
    return true;
    //Overall Function Run Time: O(1)
}

bool removeByUsername(User*& head, const string& username){
    if (head == nullptr) {
        return false;
    }


    if (head->username == username) {
        return removeFront(head);
    }


    User* current = head;
    while (current->next != nullptr && current->next->username != username) {
        current = current->next;
    }


    if (current->next == nullptr) {
        return false;
    }


    User* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
    //Overall Function Run Time: O(n)
}


void clearList(User*& head){
    while (head != nullptr) {
        removeFront(head);
    }
    //Overall Function Run Time: O(n)
}
