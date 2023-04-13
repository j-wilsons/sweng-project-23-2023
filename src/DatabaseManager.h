#ifndef DATEBASE_MANAGER_H
#define DATABASE_MANAGER_H
#include "json.hpp"
using json = nlohmann::json;

void connectToDB();
void deleteOrder(int orderId);
void addOrderToDatabase(int orderId, const std::string& side, double price, int quantity, const std::string& timestamp, const std::string& username, const std::string& ticker);
json pullOrderTable();

#endif DATABASE_MANAGER_H
