#ifndef CRM_SYSTEM_PEOPLEMVP_H
#define CRM_SYSTEM_PEOPLEMVP_H

#include "people.h"

namespace people_MVP {
    struct Client_MVP : people::Client {
    private:
        std::vector<std::pair<std::string, bool>> deal_process;

    public:
        Client_MVP(std::string, std::string, std::string, std::string);
        Client_MVP();

        [[nodiscard]] std::vector<std::string> get_deal_process() const override;
        [[nodiscard]] std::string get_info() const override;

        friend void read_client(std::vector<Client> &lst, const std::string &path);
        friend struct Comp;
    };

    struct Comp {
        bool operator()(const Client_MVP &, const Client_MVP &);
    };

    struct Manager_MVP : people::Manager {
        Manager(std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_name() const;
        void load_clients();                                                  //load all clients from directory in the vector
        void add_client(const Client_MVP &);                                  //add client to the "./resources/Clients/<email>/<Client.email>"
        /* future */ [[maybe_unused]] void delete_client(const std::string &);//delete "./resources/Clients/<email>/<Client.email>"
        /* future */ [[maybe_unused]] void update_clients();                  //update all clients in the "./resources/Clients/<email>/<Client.email>"
        [[nodiscard]] std::string get_info() const;

        friend void add_manager(const Manager &);
        friend void get_manager(Manager &, const std::string &);
        friend struct testing::Testing;
    };
}// namespace people_MVP

#endif//CRM_SYSTEM_PEOPLEMVP_H
