#include "CRM-system_server.h"
#include <filesystem>
#include <fstream>

using grpc::Server;
using grpc::ServerBuilder;

namespace{
    namespace fs = std::filesystem;

    std::string get_hosts_server(){
        std::string path = fs::current_path();
        path += "/hosts_dir";
        if (!fs::exists(path)) { fs::create_directory(path); }
        if (!fs::exists(path + "/server_host")){
            std::ofstream out(path + "/server_host");
            out << "0.0.0.0:50051";
            out.close();
        }
        std::ifstream in(path + "/server_host");
        std::string host;
        getline(in, host);
        in.close();
//        std::cout << host << "\n";
        return host;
    }
}

void RunServer() {
    std::string server_address(get_hosts_server());
    service::CRM_ServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char ** argv) {
    RunServer();
    return 0;
}