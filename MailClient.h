#ifndef __MAILCLIENT_H__
#define __MAILCLIENT_H__

#pragma once
#include <iostream>
#include "SmtpClient.h"
#include "Pop3Client.h"
#include "File.h"
#include "Mail.h"
#include <sstream>
#include <vector>
#include <dirent.h>
#include "sqlite3.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <nlohmann/json.hpp>
#include <atomic>
#include <fstream>
#include <thread>
#include <chrono>


using namespace std;

class MailClient
{
private:
    vector<string> local_uids;
    nlohmann::json config;
    string USERNAME;
    string PASSWORD;
    string SMTP_SERVER;
    int SMTP_PORT;
    string POP3_SERVER;
    int POP3_PORT;
    string DATABASE;
    string STORAGE_DIR;
    int AUTOLOAD_SEC;
    atomic<bool> stopFlag{false};
    thread pullEmailThread;
    
public:
    MailClient();
    ~MailClient();
    int sendMail(string to, string cc, string bcc, string subject, string content, vector<string> attachment_paths);
    vector<Mail> getMailsInFolder(string folder);
    vector<string> splitString(string str, char delimiter);
    void pullNewEmails();
    vector<Mail> retriveAllLocalEmails(string folder);
    vector<Mail> retriveEmailsInFolder(string folder);
    void initDatabase();
    void updateDatabaseFromLocalStorage(vector<Mail> localMails);
    void updateStatus(string message_id, int status);
    int getStatus(string message_id);
    vector<string> getFileNamesInFolder(string folder);
    nlohmann::json readJSONFile(string file_path);
    string filterFolder(Mail mail);

    void startPullEmailThread();
    void stopPullEmailThread();

    void saveConfig();

    void updateSenderEmail(const std::string& newEmail);
    void updateSmtpServer(const std::string& newServer);
    void updateSmtpPort(int newPort);
    void updatePop3Server(const std::string& newServer);
    void updatePop3Port(int newPort);
};

#endif
