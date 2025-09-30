#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct User;




vector<string> roleToPermissions(const string &role);


User *findUser(User *head, const string &username);
bool insertUser(User *&head, const string &username, const string &password, const vector<string> &perms);
bool removeFront(User *&head);
bool removeByUsername(User *&head, const string &username);
void clearList(User *&head);
bool authenticate(User *head, const string &username, const string &password);
bool authorize(User *head, const string &username, const string &action);


struct User
{
    string username;
    string password;
    vector<string> permissions;
    User *next;


    User(const string &u,
         const string &p,
         const vector<string> &perms = {"view"})
        : username(u),
          password(p),
          permissions(perms),
          next(nullptr)
    {
    }
};






int main()
{
    User *head = nullptr;
    int option;
    string username, password, role;
    string action;
    vector<string> new_user_perms;


    insertUser(head, "guest", "pass123", {"view"});
    insertUser(head, "adminUser", "securePass", roleToPermissions("admin"));
    insertUser(head, "myEditor", "editPass", roleToPermissions("editor"));
   
    do
    {
        cout << "\n  User Management System" << endl;
        cout << "1. Add a new user" << endl;
        cout << "2. Authenticate a user" << endl;
        cout << "3. Authorize a user for an action" << endl;
        cout << "4. Remove a user by username" << endl;
        cout << "5. Remove the first user" << endl;
        cout << "6. Clear list" << endl;
        cout << "7. Exit" << endl;
        cout << "Select an option: ";
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            option = 0;
            continue;
        }
        cin.ignore();
       
        string display_role = role.empty() ? "viewer" : role;




        switch (option)
        {
        case 1:
            cout << "Enter a username: ";
            getline(cin, username);
            cout << "Enter the password: ";
            getline(cin, password);
            cout << "Enter the role (admin, editor, viewer - leave blank for default 'viewer'): ";
            getline(cin, role);


            new_user_perms = roleToPermissions(role);


            if (insertUser(head, username, password, new_user_perms))
            {
                cout << "User: " << username << " (" << display_role << ") added." << endl;
            }
            else
            {
                cout << "Error: User " << username << " already exists." << endl;
            }
            break;


        case 2:
            cout << "Enter username to authenticate: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            if (authenticate(head, username, password))
            {
                cout << "Authentication SUCCESS: User " << username << "." << endl;
            }
            else
            {
                cout << "Authentication FAILED: Invalid username or password." << endl;
            }
            break;


        case 3:
            cout << "Enter username to authorize: ";
            getline(cin, username);
            cout << "Enter the action (view, edit, create, delete, etc.): ";
            getline(cin, action);


            if (authorize(head, username, action))
            {
                cout << "Authorization SUCCESS: User " << username << " is ALLOWED to perform '" << action << "'." << endl;
            }
            else
            {
                cout << "Authorization DENIED: User " << username << " is NOT ALLOWED to perform '" << action << "'." << endl;
            }
            break;


        case 4:
            cout << "Enter username to remove: ";
            getline(cin, username);
            if (removeByUsername(head, username))
            {
                cout << "User '" << username << "' removed successfully!" << endl;
            }
            else
            {
                cout << "User '" << username << "' not found." << endl;
            }
            break;


        case 5:
            if (removeFront(head))
            {
                cout << "First user removed from the list." << endl;
            }
            else
            {
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


    clearList(head);
    return 0;
}




vector<string> roleToPermissions(const string &role)
{
    if (role == "admin")
    {
        return {"view", "edit", "create", "delete", "manage"};
    }
    else if (role == "editor")
    {
        return {"view", "edit", "create"};
    }
    else if (role == "viewer" || role.empty())
    {
        return {"view"};
    }
    return {};
}


User *findUser(User *head, const string &username)
{
    User *current = head;
    while (current != nullptr)
    {
        if (current->username == username)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}


bool authenticate(User *head, const string &username, const string &password)
{
    User *user = findUser(head, username);
    if (user != nullptr && user->password == password)
    {
        return true;
    }
    return false;
}


bool authorize(User *head, const string &username, const string &action)
{
    User *user = findUser(head, username);


    if (user == nullptr)
    {
        return false;
    }


    auto it = std::find(user->permissions.begin(), user->permissions.end(), action);
   
    return (it != user->permissions.end());
}


bool insertUser(User *&head, const string &username, const string &password, const vector<string> &perms)
{
    if (findUser(head, username) != nullptr)
    {
        return false;
    }
    User *newUser = new User(username, password, perms);
    newUser->next = head;
    head = newUser;
    return true;
}


bool removeFront(User *&head)
{
    if (head == nullptr)
    {
        return false;
    }
    User *temp = head;
    head = head->next;
    delete temp;
    return true;
}


bool removeByUsername(User *&head, const string &username)
{
    if (head == nullptr)
    {
        return false;
    }


    if (head->username == username)
    {
        return removeFront(head);
    }


    User *current = head;
    while (current->next != nullptr && current->next->username != username)
    {
        current = current->next;
    }


    if (current->next == nullptr)
    {
        return false;
    }


    User *temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}


void clearList(User *&head)
{
    while (head != nullptr)
    {
        removeFront(head);
    }
}
