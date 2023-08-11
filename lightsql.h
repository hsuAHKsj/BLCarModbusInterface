#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <ctime>

class LightManager {
public:
    LightManager(const char* server, const char* user, const char* password, const char* database) {
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to connect to the database.");
        }
    }

    ~LightManager() {
        mysql_close(conn);
    }

    void insertLightData(int state) {
        std::time_t now = std::time(nullptr);
        struct tm *timeinfo = localtime(&now);
        char datestmstr[20];
        strftime(datestmstr, sizeof(datestmstr), "%Y-%m-%d %H:%M:%S", timeinfo);
        std::string currentTime(datestmstr);

        std::string insertQuery = "INSERT INTO light (time, State) VALUES ('" + currentTime + "', " +
          std::to_string(state) + ");";

        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "Insertion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to insert data into the light table.");
        }

        // Check if the number of rows in the table exceeds the limit (e.g., 10000)
        if (getRowCount() > 10000) {
            deleteOldData();
        }
    }

    void printLightData() {
        if (mysql_query(conn, "SELECT * FROM light ORDER BY time DESC;")) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to query data from the light table.");
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
        std::string countQuery = "SELECT COUNT(*) FROM light;";
        if (mysql_query(conn, countQuery.c_str())) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to get row count from the light table.");
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
        std::string deleteQuery = "DELETE FROM light ORDER BY time LIMIT 10000, 18446744073709551615;";

        if (mysql_query(conn, deleteQuery.c_str())) {
            std::cerr << "Deletion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to delete old data from the light table.");
        }
    }
};

