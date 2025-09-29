#include <string>
#include <vector>
#include <iostream>
using namespace std;

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


int main() {
    
    User anya2012("guest", "pass123");
    User anthony1999("adminUser", "securePass", {"view", "delete", "audit"});
    User adien2011("myEditor", "editPass", roleToPermissions("editor"));

    cout << "User: " << anya2012.username << " | Permissions: ";
    for (const auto& perm : anya2012.permissions) {
        cout << perm << " ";
    }
    cout << endl;

    cout << "User: " << adien2011.username << " | Permissions: ";
    for (const auto& perm : adien2011.permissions) {
        cout << perm << " ";
    }
    cout << endl;

    return 0;
}

