//
// Created by Toan on 9/23/18.
//

#include <iostream>
#include <curl/curl.h>
#include <string>

#ifndef CPP_SERVICE_H
#define CPP_SERVICE_H


using namespace std;


struct ResponseData {
    char *memory;
    size_t size;
};


struct Response {
    long error;
    long code;
    char *data;
    size_t size;


};

class Service {

private:

    CURL *curl;
    CURLcode res;
    struct curl_slist *headerList;
    struct Response response;
    struct ResponseData m;
    int clearMemory = 0;



public:


    Service();

    void post(char *url, char *data);

    void close();

    Response get(const char *url);

    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

    ~Service() {

    }


};

#endif //CPP_SERVICE_H
