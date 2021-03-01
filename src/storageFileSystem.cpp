#include "storageFileSystem.h"
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
}// namespace repositories
