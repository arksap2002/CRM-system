#include "people.h"
#include <filesystem>

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

    people::Client::Client(std::string name_, std::string phone_, std::string email_)
        : name(std::move(name_)), phone(std::move(phone_)), email(std::move(email_)) {
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

    std::string get_current_password(const std::string &input_email, std::ostream &process) {
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

    void add_manager(const Manager &manager, std::ostream &process) {
        check_resources_tree();
        std::string path = static_cast<std::string>(fs::current_path()) + "/resources/Managers/" + manager.email;
        if(check_exists(path, "Such user already exists", process, false)){ return; }
        std::ofstream out(path);
        std::string output_name = manager.name;
        out << manager.password << "\n" << manager.email << "\n" << manager.name << "\n" << manager.phone << "\n";
        out.close();
        process << "User created";
    }
    
    void get_manager(Manager& input_manager, const std::string & input_email, std::ostream &process) {
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
}// namespace people
