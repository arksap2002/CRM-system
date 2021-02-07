#include "client.h"
#include <vector>
#include <cassert>

int main() {
    std::vector<client::Client> clients;
    clients.emplace_back("Anna", "Popupanova");
    clients.emplace_back("Denis", "Shectakov");
    clients.emplace_back("Arkady", "Sapozhnikov");
    assert(clients.size() == 3);
    clients[0].setSurname("Lipatova");
    assert(clients[0].getSurname() == "Lipatova");
}
