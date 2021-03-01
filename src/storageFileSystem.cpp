#include "storageFileSystem.h"
#include <cmath>
#include <filesystem>

namespace repositories {
    namespace {
        namespace fs = std::filesystem;
        const std::string RESOURCES = "resources";
        const std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
        const std::string CLIENTS_RESORCES = RESOURCES + "/Clients";
    }// namespace

    std::string FolderExists::get_name() {
        return "Folder already exists";
    }

    std::string FolderNotExists::get_name() {
        return "Folder is not exists";
    }

    std::string IncorrectPassword::get_name() {
        return "Password is incorrect";
    }

    ManagerFileSystem::ManagerFileSystem() {
        std::string cur_path = fs::current_path();
        if (!fs::exists(cur_path + "/" + RESOURCES)) { fs::create_directory(RESOURCES); }
        if (!fs::exists(cur_path + "/" + MANAGERS_RESORCES)) { fs::create_directory(MANAGERS_RESORCES); }
        if (!fs::exists(cur_path + "/" + CLIENTS_RESORCES)) { fs::create_directory(CLIENTS_RESORCES); }
    }

    void ManagerFileSystem::addManager(const people::Manager &manager) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (fs::exists(path)) { throw FolderExists(); }
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

    struct Comp{
        bool operator()(const people::Client &c1, const people::Client &c2) {
            return c1.email < c2.email;
        }
    };

    void ManagerFileSystem::load_clients(people::Manager &manager) const {
        manager.list_clients.clear();
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email;
        for (auto &p : fs::directory_iterator(path)) {
            read_client(manager.list_clients, p.path());
        }
        std::sort(manager.list_clients.begin(), manager.list_clients.end(), Comp());
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

    bool ManagerFileSystem::is_correct_password(const std::string &input_email, const std::string &input_password) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + input_email;
        if (!fs::exists(path)) { throw FolderNotExists(); }
        std::ifstream in(path);
        std::string email_not_use, pass;
        getline(in, email_not_use);
        getline(in, pass);
        in.close();
        return pass == input_password;
    }
}// namespace repositories
