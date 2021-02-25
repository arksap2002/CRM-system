#ifndef CRM_SYSTEM_TESTING_H
#define CRM_SYSTEM_TESTING_H
namespace testing {
    struct Testing {
        static std::string get_name_manager(const people::Manager &);
        static std::string get_phone_manager(const people::Manager &);
        static std::string get_name_client(const people::Client &);
        static std::string get_phone_client(const people::Client &);
        static std::string get_email_client(const people::Client &);
        static std::string get_deal_product_client(const people::Client &);
        static void change_name1(people::Client &);
        static void change_name2(people::Client &);
    };
}// namespace testing
#endif//CRM_SYSTEM_TESTING_H
