#include "people.h"
#include <cmath>
#include <filesystem>

namespace people {
    namespace {
        namespace fs = std::filesystem;
    }

    void check_resources_tree() {
        std::string cur_path = fs::current_path();
        if (!fs::exists(cur_path + "/" + RESOURCES)) { fs::create_directory(RESOURCES); }
        if (!fs::exists(cur_path + "/" + MANAGERS_RESORCES)) { fs::create_directory(MANAGERS_RESORCES); }
        if (!fs::exists(cur_path + "/" + CLIENTS_RESORCES)) { fs::create_directory(CLIENTS_RESORCES); }
    }

    bool is_already_exists(const std::string &path, const std::string &message, std::ostream &process, bool b) {
        if (fs::exists(path) ^ b) {
            process << message;
            return true;
        }
        return false;
    }

    people::Client::Client(std::string name_, std::string phone_, std::string email_, std::string deal_product_)
        : email(std::move(email_)), name(std::move(name_)), phone(std::move(phone_)),
          deal_product(std::move(deal_product_)) {
        deal_process = {{"Connection with client", false},
                        {"Concluding the contract", false},
                        {"Deal is completed", false}};
    }

    people::Client::Client() {
        deal_process = {{"Connection with client", false},
                        {"Concluding the contract", false},
                        {"Deal is completed", false}};
    }

    void people::Client::print_info(std::ostream &os) {
        os << email << " " << name << " " << phone << " " << deal_product << "\n";
    }

    people::Manager::Manager(std::string name_, std::string phone_,
                             std::string email_, std::string password_)
        : name(std::move(name_)), phone(std::move(phone_)), email(std::move(email_)),
          password(std::move(password_)) {
    }

    std::string Manager::get_password() const {
        return password;
    }

    std::string Manager::get_email() const {
        return email;
    }

    std::string get_current_password(const std::string &input_email, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (is_already_exists(path, "Such user is not exists\n", process, true)) { return "*"; }
        std::ifstream in(path);
        std::string passw;
        getline(in, passw);
        in.close();
        process << "Read user password\n";
        return passw;
    }

    bool add_manager(const Manager &manager, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (is_already_exists(path, "Such user already exists\n", process, false)) { return false; }
        std::ofstream out(path);
        out << manager.password << "\n"
            << manager.email << "\n"
            << manager.name << "\n"
            << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email);
        process << "User created\n";
        return true;
    }

    bool get_manager(Manager &input_manager, const std::string &input_email, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (is_already_exists(path, "Such user is not exists\n", process, true)) { return false; }
        std::ifstream in(path);
        getline(in, input_manager.password);
        getline(in, input_manager.email);
        getline(in, input_manager.name);
        getline(in, input_manager.phone);
        input_manager.load_clients();
        in.close();
        process << "Read information about user\n";
        return true;
    }

    void people::Manager::print_info(std::ostream &os) {
        os << email << " " << name << " " << phone << "\n";
    }

    bool people::Manager::is_correct_password(const std::string &input_password, std::ostream &process) {
        if (password != input_password) {
            process << "Incorrect password\n";
            return false;
        }
        return true;
    }

    void read_client(std::vector<Client> &lst, const std::string &path) {
        lst.emplace_back();
        std::size_t n = lst.size() - 1;
        std::ifstream in(path);
        getline(in, lst[n].email);
        getline(in, lst[n].name);
        getline(in, lst[n].phone);
        getline(in, lst[n].deal_product);
        int deal_pr_bits;//It shows what points of vector<>deal_process is completed
        in >> deal_pr_bits;
        for (int i = 2; i > -1; --i) {
            if (deal_pr_bits - std::pow(10, i) >= 0) {
                lst[n].deal_process[2 - i].second = true;
                deal_pr_bits -= std::pow(10, i);
            }
        }
        in.close();
    }

    bool Comp::operator()(const Client &c1, const Client &c2) {
        return c1.name < c2.name;
    }

    void Manager::load_clients() {
        check_resources_tree();
        list_clients.clear();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email;
        for (auto &p : fs::directory_iterator(path)) {
            read_client(list_clients, p.path());
        }
        std::sort(list_clients.begin(), list_clients.end(), Comp());
    }

    void Manager::add_client(const Client &client, bool add_to_lstc, std::ostream &process) {
        check_resources_tree();
        std::string path =
                static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email + "/" + client.email;
        if (is_already_exists(path, "Such client already exists\n", process, false)) { return; }
        std::ofstream out(path);
        out << client.email << "\n"
            << client.name << "\n"
            << client.phone << "\n"
            << client.deal_product << "\n";
        for (auto &p : client.deal_process) {
            out << p.second;
        }
        out << "\n";
        out.close();
        if (add_to_lstc) {
            read_client(list_clients, path);
        }
        process << "Client successfully added\n";
    }

    void Manager::delete_client(const std::string &client_email, bool del_from_lst, std::ostream &process) {
        check_resources_tree();
        std::string path =
                static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email + "/" + client_email;
        if (is_already_exists(path, "Such client is not exists\n", process, true)) { return; }
        fs::remove(path);
        if (del_from_lst) {
            for (auto &c : list_clients) {
                if (c.email == client_email) {
                    std::swap(c, list_clients[list_clients.size() - 1]);
                    list_clients.pop_back();
                    break;
                }
            }
            sort(list_clients.begin(), list_clients.end(), Comp());
        }
        process << "Client successfully deleted\n";
    }

    void Manager::update_clients() {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email;
        for (auto &p : fs::directory_iterator(path)) {
            read_client(list_clients, p.path());
            fs::remove(p.path());
        }
        std::stringstream ss;
        for (auto &client : list_clients) {
            add_client(client, false, ss);
            ss.str("");
        }
    }
}// namespace people


namespace testing {
    std::string Testing::get_name_manager(const people::Manager &m) {
        return m.name;
    }

    std::string Testing::get_phone_manager(const people::Manager &m) {
        return m.phone;
    }

    std::string Testing::get_phone_client(const people::Client &c) {
        return c.phone;
    }

    std::string Testing::get_name_client(const people::Client &c) {
        return c.name;
    }

    std::string Testing::get_email_client(const people::Client &c) {
        return c.email;
    }

    std::string Testing::get_deal_product_client(const people::Client &c) {
        return c.deal_product;
    }

    void Testing::change_name1(people::Client &c) {
        c.name = "1-Naruto Uzumaki";
    }

    void Testing::change_name2(people::Client &c) {
        c.name = "1-Turtle Leonardo";
    }
}//namespace testing
