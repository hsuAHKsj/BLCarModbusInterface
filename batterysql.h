#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <ctime>

class BatteryManager {
public:
    BatteryManager(const char* server, const char* user, const char* password, const char* database) {
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to connect to the database.");
        }
    }

    ~BatteryManager() {
        mysql_close(conn);
    }

    void insertBatteryData(int voltage,int current, int soc, int temperature, int alarmValue) {
        std::time_t now = std::time(nullptr);
        struct tm *timeinfo = localtime(&now);
        char datestmstr[20];
        strftime(datestmstr, sizeof(datestmstr), "%Y-%m-%d %H:%M:%S", timeinfo);
        std::string currentTime(datestmstr);

        std::string insertQuery = "INSERT INTO battery (time, Voltage, Current, SoC, Temperature, AlarmValue) VALUES ('" + currentTime + "', " +
          std::to_string(voltage) + ", " + std::to_string(current) + ", " + std::to_string(soc) + ", " + std::to_string(temperature) + ", " + std::to_string(alarmValue) + ");";

        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "Insertion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to insert data into the battery table.");
        }

        // Check if the number of rows in the table exceeds the limit (e.g., 10000)
        if (getRowCount() > 10000) {
            deleteOldData();
        }
    }

    void printBatteryData() {
        if (mysql_query(conn, "SELECT * FROM battery ORDER BY time DESC;")) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to query data from the battery table.");
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            int numFields = mysql_num_fields(result);
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result))) {
                for (int i = 0; i < numFields; i++) {
                    std::cout << row[i] << " ";
                }
                std::cout << std::endl;
            }

            mysql_free_result(result);
        }
    }

private:
    MYSQL* conn;

    unsigned int getRowCount() {
        std::string countQuery = "SELECT COUNT(*) FROM battery;";
        if (mysql_query(conn, countQuery.c_str())) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to get row count from the battery table.");
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            unsigned int rowCount = std::stoi(row[0]);
            mysql_free_result(result);
            return rowCount;
        }

        return 0;
    }

    void deleteOldData() {
        std::string deleteQuery = "DELETE FROM battery ORDER BY time LIMIT 10000, 18446744073709551615;";

        if (mysql_query(conn, deleteQuery.c_str())) {
            std::cerr << "Deletion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to delete old data from the battery table.");
        }
    }
};

// int main() {
//     const char* server = "localhost";
//     const char* user = "your_username"; // Replace with your MySQL username
//     const char* password = "your_password"; // Replace with your MySQL password
//     const char* database = "car";

//     try {
//         BatteryManager batteryManager(server, user, password, database);

//         // Insert data into the battery table (you can repeat this step as needed)
//         batteryManager.insertBatteryData(100, 90, 25, 0);

//         // Query and print data from the battery table
//         batteryManager.printBatteryData();
//     } catch (std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
