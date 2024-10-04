#include <iostream>
#include <fstream>
#include <string>
#include <optional>


template <typename T>
class optional
{
    T* value;
public:
    optional() : value(nullptr) {}
    optional(T val) {
        value = new T(val);
    }

    ~optional()
    {
        value = nullptr;
    };

    optional& operator = (optional b)
    {
        value = new T(*b.value);
        return *this;
    }

    bool operator* ()
    {
        if (value == nullptr) return false;
        return true;
    }

    T* operator-> ()
    {
        return value;
    }


};

class User {
private:
    std::string login;
    std::string firstName;
    std::string familyName;
    std::string patronomic;
public:
    User(std::string l, std::string fi, std::string fa, std::string pat) : login(l), firstName(fi), familyName(fa), patronomic(pat) {}
    User() : login(""), firstName(""), familyName(""), patronomic("") {}
    std::string getLogin() {
        return this->login;
    }
    std::string getName() {
        return this->firstName;
    }
    std::string getFamily() {
        return this->familyName;
    }
    std::string getPatronomic() {
        return this->patronomic;
    }
    void changeName(std::string temp) {
        this->firstName = temp;
    }
    void changeFam(std::string temp) {
        this->familyName = temp;
    }
    void changePat(std::string temp) {
        this->patronomic = temp;
    }
};


struct Node {
    User user;
    Node* next;
    Node* prev;

    Node(User user_) : user(user_), next(nullptr), prev(nullptr) {}
};

struct list
{
    Node* first;
    list() : first(nullptr) {};

    void fill(std::string log, std::string name, std::string fam, std::string pat)///
    {
        User temp(log , name, fam, pat);
        Node* node1 = new Node(temp);
        if (first == nullptr) {
            first = node1;
            first->prev = first;
            first->next = first;
        }
        else {
            node1->next = first;
            node1->prev = first->prev;
            first->prev->next = node1;
            first->prev = node1;
        }
    }
    bool search_el(std::string login) {
        Node* arrow = first;
        if (first != nullptr)
        {
            if (first->next == first) {
                if (first->user.getLogin() == login) return true;
                else return false;
            }
            else {
                while (arrow->next != first and arrow->user.getLogin() != login) {
                    arrow = arrow->next;
                }
                if (arrow->user.getLogin() == login) return true;
                else return false;
            }
        }
        else return false;
    }
    void write() {
        std::ofstream out("Users.txt", std::ios::trunc);
        int i = 1;
        Node* arrow = first;
        if (first == nullptr) std::cout << "empty \n";
        else {
            do
            {
                out << arrow->user.getLogin() << ";" << arrow->user.getName() << ";" << arrow->user.getFamily() << arrow->user.getPatronomic() << ";" << "\n";
            } while (arrow != nullptr and arrow != first);
        }
    }
    void deleteUser(std::string& login)
    {
        Node* curr = first;
        if (first != nullptr) {
            do {
                if (curr->user.getLogin() == login) {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    /*curr->next = curr->next->next;
                    curr->next->next->prev = curr;*/
                }
                curr = curr->next;
            } while (curr != first);
        }
        write();
    }
    void ChangeUserName(std::string& login, std::string name)
    {
        Node* curr = first;
        if (first != nullptr) {
            do {
                if (curr->user.getLogin() == login) {
                    curr->user.changeName(name);
                }
                curr = curr->next;
            } while (curr != first);
        }
        write();
    }
    void ChangeUserFam(std::string& login, std::string fam)
    {
        Node* curr = first;
        if (first != nullptr) {
            do {
                if (curr->user.getLogin() == login) {
                    curr->user.changeFam(fam);
                }
                curr = curr->next;
            } while (curr != first);
        }
        write();
    }
    void ChangeUserPat(std::string& login, std::string pat)
    {
        Node* curr = first;
        if (first != nullptr) {
            do {
                if (curr->user.getLogin() == login) {
                    curr->user.changePat(pat);
                }
                curr = curr->next;
            } while (curr != first);
        }
        write();
    }

    void addUser(std::string login, std::string name, std::string fam, std::string pat) {
        if (this->search_el(login)) {
            login += '1';
        }
        this->fill(login, name, fam, pat);
        write();
    }

    void print()
    {
        int i = 1;
        Node* arrow = first;
        if (first == nullptr) std::cout << "empty \n";
        else {
            do
            {
                std::cout << i << ". " << arrow->user.getLogin() << ";" << arrow->user.getName() << ";" << arrow->user.getFamily() << ";" << arrow->user.getPatronomic() << '\n';
                ++i;
                arrow = arrow->next;
            } while (arrow != nullptr and arrow != first);
        }
    }
};

void read(list& arr, std::string file) {
    std::ifstream in(file);
    User buff();
    std::string str = "";
    int i = 0;
    std::string login = "", first = "", fam = "", pat = "";

    while (!in.eof()) {
        in >> str;
        login = "", first = "", fam = "", pat = "";
        i = 0;
        while (str[i] != ';') {
            login += str[i];
            i++;
        }
        i++;
        while (str[i] != ';') {
            first += str[i];
            i++;
        }
        i++;
        while (str[i] != ';') {
            fam += str[i];
            i++;
        }
        i++;
        while (str[i] != ';') {
            pat += str[i];
            i++;
        }
        arr.fill(login, first, fam, pat);
    }
}

int main()
{
    list users;
    read(users, "Users.txt");
    users.print();
}