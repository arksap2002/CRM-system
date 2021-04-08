#include "storageFileSystem.h"
#include <cmath>
#include <filesystem>

namespace repositories {
    namespace {
        namespace fs = std::filesystem;
        std::string RESOURCES = "resources";
        std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
        std::string CLIENTS_RESORCES = RESOURCES + "/Clients";
    }// namespace

    void checkResourcesTree() {
        std::string cur_path = fs::current_path();
        if (!fs::exists(cur_path + "/" + RESOURCES)) { fs::create_directory(cur_path + "/" + RESOURCES); }
        if (!fs::exists(cur_path + "/" + MANAGERS_RESORCES)) { fs::create_directory(cur_path + "/" + MANAGERS_RESORCES); }
        if (!fs::exists(cur_path + "/" + CLIENTS_RESORCES)) { fs::create_directory(cur_path + "/" + CLIENTS_RESORCES); }
    }

    ManagerFileSystem::ManagerFileSystem() {
        checkResourcesTree();
    }

    void ManagerFileSystem::addManager(const people::Manager &manager) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (fs::exists(path)) { throw FileExists(); }
        std::ofstream out(path);
        out << manager.email << "\n"
            << manager.password << "\n"
            << manager.name << "\n"
            << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email);
    }

    void read_client(std::vector<people::Client> &lst, const std::string &path) {
        lst.emplace_back();
        std::size_t n = lst.size() - 1;
        std::ifstream in(path);
        getline(in, lst[n].email);
        getline(in, lst[n].name);
        getline(in, lst[n].phone);
        getline(in, lst[n].dealProduct);
        int deal_pr_bits;//It shows what points of vector<>dealProcess is completed
        in >> deal_pr_bits;
        for (int i = 2; i > -1; --i) {
            if (deal_pr_bits - std::pow(10, i) >= 0) {
                lst[n].dealProcess[2 - i].second = true;
                deal_pr_bits -= std::pow(10, i);
            }
        }
        in.close();
    }

    struct Comp {
        bool operator()(const people::Client &c1, const people::Client &c2) {
            return c1.email < c2.email;
        }
    };

    void ManagerFileSystem::load_clients(people::Manager &manager) {
        manager.listClients.clear();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email;
        for (auto &p : fs::directory_iterator(path)) {
            read_client(manager.listClients, p.path());
        }
        std::sort(manager.listClients.begin(), manager.listClients.end(), Comp());
    }

    void ManagerFileSystem::getManager(people::Manager &input_manager, const std::string &input_email) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        std::ifstream in(path);
        getline(in, input_manager.email);
        getline(in, input_manager.password);
        getline(in, input_manager.name);
        getline(in, input_manager.phone);
        load_clients(input_manager);
        in.close();
    }

    bool ManagerFileSystem::isCorrectPassword(const std::string &input_email, const std::string &input_password) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (!fs::exists(path)) { throw FileNotExists(); }
        std::ifstream in(path);
        std::string email_not_use, pass;
        getline(in, email_not_use);
        getline(in, pass);
        in.close();
        return pass == input_password;
    }

    std::string ManagerFileSystem::managerInfo(people::Manager &manager) const {
        return manager.email + " " + manager.name + " " + manager.phone;
    }

    ClientFileSystem::ClientFileSystem() {
        checkResourcesTree();
    }

    void ClientFileSystem::addClient(const people::Client &client, const std::string &managerEmail) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES +
                           "/" + managerEmail + "/" + client.email;
        if (fs::exists(path)) { throw FileExists(); }
        std::ofstream out(path);
        out << client.email << "\n"
            << client.name << "\n"
            << client.phone << "\n"
            << client.dealProduct << "\n";
        for (auto &p : client.dealProcess) {
            out << p.second;
        }
        out << "\n";
        out.close();
    }

    void ClientFileSystem::deleteClient(const std::string &client_email, const std::string &managerEmail) const {
        std::string path =
                static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + managerEmail + "/" + client_email;
        if (!fs::exists(path)) { throw FileNotExists(); }
        fs::remove(path);
    }

    void ClientFileSystem::updateAllClients(const people::Manager &manager) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email;
        for (auto &p : fs::directory_iterator(path)) {
            fs::remove(p.path());
        }
        for (auto &client : manager.listClients) {
            addClient(client, manager.email);
        }
    }
    std::string ClientFileSystem::clientInfo(const people::Client &client) const {
        return client.email + " " + client.name + " " + client.phone;
    }
    std::vector<std::string> ClientFileSystem::getDealProcess(const people::Client &client) const {
        std::vector<std::string> result(3);
        for (int i = 0; i < 3; ++i) {
            result[i] = client.dealProcess[i].first + ' ' + std::to_string(client.dealProcess[i].second);
        }
        return result;
    }
}// namespace repositories
