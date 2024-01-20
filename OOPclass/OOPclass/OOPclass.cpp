#include <iostream>
#include <string>
#include <chrono>

struct Num
{
    int country_code;
    int city_code;
    int personal_code;
    Num() : country_code(0), city_code(0), personal_code(0) {};
    Num(int count, int city, int pres): country_code(count), city_code(city), personal_code(pres) {};
};

class Document
{
public:
    int number;
    //data
    std::string who_give;
    //data
    //copy of doc
    Document() : number(0), who_give("") {}
    Document(int num, std::string who) : number(num), who_give(who) {}
};

class Lic : public Document
{
public:
    std::string possib;
    Lic() : Document(), possib("") {}
    Lic(int num, std::string who, std::string pos) : Document(num, who), possib(pos) {}
};

class Diplom : public Document
{
public:
    std::string stage;
    Diplom() : Document(), stage("") {}
    Diplom(int num, std::string who, std::string stg) : Document(num, who), stage(stg) {}
};

class Cert : public Document
{
public:
    std::string name_spec;
    Cert() : Document(), name_spec("") {}
    Cert(int num, std::string who, std::string name) : Document(num, who), name_spec(name) {}
};

class User
{
public:
    std::string fio;
    Num phone_num;
    std::string email;
    std::string doc_list;
    int age;

    void AddDoc(Lic lic) {
        this->doc_list += "{";
        this->doc_list += lic.number + " ";
        this->doc_list += lic.who_give + " ";
        this->doc_list += lic.possib;
        this->doc_list += "}";
    }
    void AddDoc(Diplom dip) {
        this->doc_list += "{";
        this->doc_list += dip.number + " ";
        this->doc_list += dip.who_give + " ";
        this->doc_list += dip.stage;
        this->doc_list += "}";
    }
    void AddDoc(Cert cert) {
        this->doc_list += "{";
        this->doc_list += cert.number + " ";
        this->doc_list += cert.who_give + " ";
        this->doc_list += cert.name_spec;
        this->doc_list += "}";
    }
    std::string getDoc_list() {
        return this->doc_list;
    }
    User() : fio(""), phone_num(Num()), email(""), doc_list("") {}
    User(std::string fio_, Num numb, std::string mail, std::string doc_l): fio(fio_), phone_num(numb), email(mail), doc_list(doc_l) {}
};

class Vacancy
{
public:
    int otkl_count;
    std::string req_skill;
    int pay;
    std::string name;
    std::string categ_vac;
    Vacancy() : otkl_count(0), req_skill(""), pay(0), name(""), categ_vac("") {}
    Vacancy(int otkl, std::string skill, int pay_, std::string name_, std::string cat) : otkl_count(otkl), req_skill(skill), pay(pay_), name(name_), categ_vac(cat) {}
};

class Employer : public User
{
public:
    std::string org;
    std::string vacans_list;
    void addVac(Vacancy vac) {
        this->vacans_list += "{";
        this->vacans_list += vac.otkl_count + " ";
        this->vacans_list += vac.req_skill + " ";
        this->vacans_list += vac.pay + " ";
        this->vacans_list += vac.categ_vac + " ";
        this->vacans_list += vac.name;
        this->vacans_list += "}";
    }
    Employer() : User(), org(""), vacans_list("") {}
    Employer(std::string fio_, Num numb, std::string mail, std::string doc_l, std::string org_, std::string vacans) : User(fio_, numb, mail, doc_l), org(org_), vacans_list(vacans) {}
};

class Spec : public User
{
public:
    int stage;
    std::string spec;
    std::string otkl_list;
    void Otkl(Employer emp, std::string vac_name) {
        std::size_t found = emp.vacans_list.find(vac_name);
        char ch;
        std::string count_otkl;
        int count;
        if (found != std::string::npos) {
            ch = emp.vacans_list[found];
            while (ch != '{') {
                --found;
                ch = emp.vacans_list[found];
            }
            found++;
            ch = emp.vacans_list[found];
            while (ch != ' ') {
                count_otkl += ch;
                ++found;
                ch = emp.vacans_list[found];
            }
            count = std::stoi(count_otkl);
            count++;
            count_otkl = count;
            while (ch != '{') {
                --found;
                ch = emp.vacans_list[found];
            }
            found++;
            ch = emp.vacans_list[found];
            for (int i = 0; i <= count_otkl.size(); i++) {
                emp.vacans_list[found] = count_otkl[i];
                ++found;
            }
            this->otkl_list += "{";
            this->otkl_list += emp.org + " ";
            this->otkl_list += vac_name + "}";
        }
    }
    Spec(): User(), stage(0), spec(""), otkl_list("") {}
    Spec(std::string fio_, Num numb, std::string mail, std::string doc_l, int stg, std::string spec_, std::string otkl) : User(fio_, numb, mail, doc_l), stage(stg), spec(spec_), otkl_list(otkl) {}
};

int main()
{
    std::cout << "Hello World!\n";
}