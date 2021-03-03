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

    people::Client::Client(std::string email_, std::string name_, std::string phone_, std::string deal_product_)
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

    std::vector<std::string> people::Client::get_deal_process() const {
        std::vector<std::string> result(3);
        for (int i = 0; i < 3; ++i) {
            result[i] = deal_process[i].first + ' ' + std::to_string(deal_process[i].second);
        }
        return result;
    }

    std::string people::Client::get_info() const {
        return email + " " + name + " " + phone;
    }

    std::string people::Client::get_email() const {
        return email;
    }

    std::string people::Client::get_name() const {
        return name;
    }

    std::string people::Client::get_phone() const {
        return phone;
    }

    people::Manager::Manager(std::string email_, std::string password_, std::string name_, std::string phone_)
        : email(std::move(email_)), password(std::move(password_)), name(std::move(name_)), phone(std::move(phone_)) {
    }

    std::string Manager::get_name() const {
        return name;
    }

    std::string Manager::get_info() const {
        return email + " " + name + " " + phone;
    }

    bool is_correct_password(const std::string &input_email, const std::string &input_password) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (!fs::exists(path)) { throw; }
        std::ifstream in(path);
        std::string email_not_use, passw;
        getline(in, email_not_use);
        getline(in, passw);
        in.close();
        return passw == input_password;
    }

    void add_manager(const Manager &manager) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (fs::exists(path)) { throw; }
        std::ofstream out(path);
        out << manager.email << "\n"
            << manager.password << "\n"
            << manager.name << "\n"
            << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email);
    }

    void get_manager(Manager &input_manager, const std::string &input_email) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (!fs::exists(path)) { throw std::exception(); }
        std::ifstream in(path);
        getline(in, input_manager.email);
        getline(in, input_manager.password);
        getline(in, input_manager.name);
        getline(in, input_manager.phone);
        input_manager.load_clients();
        in.close();
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
        return c1.email < c2.email;
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

    void Manager::add_client(const Client &client) {
        check_resources_tree();
        std::string path =
                static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email + "/" + client.email;
        if (fs::exists(path)) { throw; }
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
        read_client(list_clients, path);
    }

    [[maybe_unused]] void Manager::delete_client(const std::string &client_email) {
        check_resources_tree();
        std::string path =
                static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email + "/" + client_email;
        if (!fs::exists(path)) { throw; }
        fs::remove(path);
        for (auto &c : list_clients) {
            if (c.email == client_email) {
                std::swap(c, list_clients[list_clients.size() - 1]);
                list_clients.pop_back();
                break;
            }
        }
        sort(list_clients.begin(), list_clients.end(), Comp());
    }

    void Manager::update_clients() {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + email;
        for (auto &p : fs::directory_iterator(path)) {
            read_client(list_clients, p.path());
            fs::remove(p.path());
        }
        for (auto &client : list_clients) {
            add_client(client);
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
