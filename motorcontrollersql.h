#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <ctime>

class MotorController {
public:
    MotorController(const char* server, const char* user, const char* password, const char* database) {
        conn= mysql_init(NULL);
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to connect to the database.");
        }
    }

    ~MotorController() {
        mysql_close(conn);
    }

    void insertMotorData(int controlword1,int statusword1, int currentspeed1, int currentpositionL1,int currentpositionH1,int controlword2,int statusword2, int currentspeed2, int currentpositionL2,int currentpositionH2,int controlword3,int statusword3, int currentspeed3, int currentpositionL3,int currentpositionH3) {
        std::time_t now = std::time(nullptr);
        struct tm *timeinfo = localtime(&now);
        char datestmstr[20];
        strftime(datestmstr, sizeof(datestmstr), "%Y-%m-%d %H:%M:%S", timeinfo);
        std::string currentTime(datestmstr);

        std::string insertQuery = "INSERT INTO motor (time, Controlword1,Statusword1,Currentspeed1,CurrentpositionL1,CurrentpositionH1,Controlword2,Statusword2,Currentspeed2,CurrentpositionL2,CurrentpositionH2,Controlword3,Statusword3,Currentspeed3,CurrentpositionL3,CurrentpositionH3) VALUES ('" + currentTime + "', " + std::to_string(controlword1) + ", " + std::to_string(statusword1) + ", " + std::to_string(currentspeed1) + ", " + std::to_string(currentpositionL1) + ", " + std::to_string(currentpositionH1) + "," +std::to_string(controlword2) + ", " + std::to_string(statusword2) + ", " + std::to_string(currentspeed2) + ", " + std::to_string(currentpositionL2)  + ", " + std::to_string(currentpositionH2) + "," + std::to_string(controlword3) + ", " + std::to_string(statusword3) + ", " + std::to_string(currentspeed3) + ", " + std::to_string(currentpositionL3)  + ", " + std::to_string(currentpositionH3) + ");";

        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "Insertion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to insert data into the motor table.");
        }

        // Check if the number of rows in the table exceeds the limit (e.g., 10000)
        if (getRowCount() > 10000) {
            deleteOldData();
        }
    }

    void printMotorData() {
        if (mysql_query(conn, "SELECT * FROM motor ORDER BY time DESC;")) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to query data from the motor table.");
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
        std::string countQuery = "SELECT COUNT(*) FROM motor;";
        if (mysql_query(conn, countQuery.c_str())) {
            std::cerr << "Query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to get row count from the motor table.");
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
        std::string deleteQuery = "DELETE FROM motor ORDER BY time LIMIT 10000, 18446744073709551615;";

        if (mysql_query(conn, deleteQuery.c_str())) {
            std::cerr << "Deletion error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to delete old data from the motor table.");
        }
    }
};

