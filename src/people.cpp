#include "people.h"
#include <filesystem>
#include <cmath>

namespace people {
    namespace {
        namespace fs = std::filesystem;
    }
    void check_resources_tree() {
        std::string cur_path = fs::current_path();
        if (!fs::exists(cur_path + "/resources")){  fs::create_directory("resources");  }
        if (!fs::exists(cur_path + "/resources/Managers")){ fs::create_directory("resources/Managers"); }
        if (!fs::exists(cur_path + "/resources/Clients")){  fs::create_directory("resources/Clients"); }
    }

    bool check_exists(const std::string& path, const std::string& message, std::ostream& process, bool b){
        if(fs::exists(path) ^ b){
            process << message;
            return true;
        }
        return false;
    }

    people::Client::Client(std::string name_, std::string phone_, std::string email_, std::string deal_product_)
        : email(std::move(email_)), name(std::move(name_)), phone(std::move(phone_)), deal_product(std::move(deal_product_)) {
        deal_process = {{"Connection with client", false}, {"Concluding the contract", false}, {"Deal is completed", false}};
    }

    people::Client::Client() {
        deal_process = {{"Connection with client", false}, {"Concluding the contract", false}, {"Deal is completed", false}};
    }

    people::Manager::Manager(std::string name_, std::string phone_,
                             std::string email_, std::string password_)
        : name(std::move(name_)), phone(std::move(phone_)), email(std::move(email_)), password(std::move(password_)) {
    }

    std::string Manager::get_password() const {
        return password;
    }

    std::string Manager::get_email() const {
        return email;
    }

    std::string get_current_password(const std::string& input_email, std::ostream& process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Managers/" + input_email;
        if(check_exists(path, "Such user is not exists", process, true)){ return "*"; }
        std::ifstream in(path);
        std::string passw;
        getline(in, passw);
        in.close();
        process << "Read user password";
        return passw;
    }

    void add_manager(const Manager& manager, std::ostream& process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Managers/" + manager.email;
        if(check_exists(path, "Such user already exists", process, false)){ return; }
        std::ofstream out(path);
        out << manager.password << "\n" << manager.email << "\n" << manager.name << "\n" << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/resources/Clients/" + manager.email);
        process << "User created";
    }

    void get_manager(Manager& input_manager, const std::string& input_email, std::ostream& process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Managers/" + input_email;
        if(check_exists(path, "Such user is not exists", process, true)){  return; }
        std::ifstream in(path);
        getline(in, input_manager.password);
        getline(in, input_manager.email);
        getline(in, input_manager.name);
        getline(in, input_manager.phone);
        in.close();
        process << "Read information about user";
    }

    void read_client(std::vector<Client>& lst, const std::string& path){
        lst.emplace_back();
        std::size_t n = lst.size() - 1;
        std::ifstream in(path);
        getline(in, lst[n].email);
        getline(in, lst[n].name);
        getline(in, lst[n].phone);
        getline(in, lst[n].deal_product);
        int deal_pr_bits;           //It shows what points of vector<>deal_process is completed
        in >> deal_pr_bits;
        for (int i = 2; i > -1; --i){
            if (deal_pr_bits - std::pow(10,i) >= 0){
                lst[n].deal_process[2 - i].second = true;
                deal_pr_bits -= std::pow(10, i);
            }
        }
        in.close();
    }

    void Manager::load_clients() {
        check_resources_tree();
        list_clients.clear();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Clients/" + email;
        for (auto& p : fs::directory_iterator(path)){
            read_client(list_clients, p.path());
        }
    }

    void Manager::add_client(const Client &client, bool add_to_lstc, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Clients/" + client.email;
        if (check_exists(path, "Such client already exists", process, false)) { return; }
        std::ofstream out(path);
        out << client.email << "\n" << client.name << "\n" << client.phone << "\n" << client.deal_product << "\n";
        for (auto& p : client.deal_process){
            out << p.second;
        }
        out << "\n";
        out.close();
        if (add_to_lstc){
            read_client(list_clients, path);
        }
        process << "Client successfully added";
    }

    void Manager::delete_client(const Client &client, bool del_from_lst, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Clients/" + client.email;
        if (check_exists(path, "Such client is not exists", process, true)) { return; }
        fs::remove(path);
        if (del_from_lst) {
            for (auto &c : list_clients) {
                if (c.email == client.email) {
                    std::swap(c, list_clients[list_clients.size() - 1]);
                    list_clients.pop_back();
                }
            }
        }
        process << "Client successfully deleted";
    }

    void Manager::change_client(const Client &, std::ostream &) {
        //   TODO
    }

    std::string Testing::get_name(const Manager & m) {
        return m.name;
    }

    std::string Testing::get_phone(const Manager & m) {
        return m.phone;
    }
}// namespace people
