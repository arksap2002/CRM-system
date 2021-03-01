#include "storageFileSystem.h"
#include <filesystem>
namespace repositories {
    namespace {
        namespace fs = std::filesystem;
        const std::string RESOURCES = "resources";
        const std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
        const std::string CLIENTS_RESORCES = RESOURCES + "/Clients";
    }// namespace

    std::string FolderNotExists::get_name() {
        return "Folder is not exists";
    }

    void ManagerFileSystem::preparatoryCheck() const {
        std::string cur_path = fs::current_path();
        if (!fs::exists(cur_path + "/" + RESOURCES)) { fs::create_directory(RESOURCES); }
        if (!fs::exists(cur_path + "/" + MANAGERS_RESORCES)) { fs::create_directory(MANAGERS_RESORCES); }
        if (!fs::exists(cur_path + "/" + CLIENTS_RESORCES)) { fs::create_directory(CLIENTS_RESORCES); }
    }

    void ManagerFileSystem::addManager(const people::Manager &manager) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (!fs::exists(path)) { throw FolderNotExists(); }
        std::ofstream out(path);
        out << manager.email << "\n"
            << manager.password << "\n"
            << manager.name << "\n"
            << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email);
    }

    bool ManagerFileSystem::is_correct_password(const std::string &email, const std::string &inputPassword) const {
        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + email;
        if (!fs::exists(path)) { throw; }
        std::ifstream in(path);
        std::string email_not_use, passw;
        getline(in, email_not_use);
        getline(in, passw);
        in.close();
        return passw == inputPassword;
    }
}// namespace repositories
