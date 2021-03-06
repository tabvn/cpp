//
// Created by Toan on 9/23/18.
//

#include "service.h"


Service::Service() {

}

Service::~Service() {

}

Response Service::post(const char *url, char *data) {

    close();

    curl = curl_easy_init();


    headerList = nullptr;

    m.memory = (char *) malloc(1);
    m.size = 0;

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

    // headers
    headerList = curl_slist_append(headerList, "Accept: application/json");
    headerList = curl_slist_append(headerList, "Content-Type: application/json");
    headerList = curl_slist_append(headerList, "charsets: utf-8");


    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Service::WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &m);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));


    res = curl_easy_perform(curl);

    response.data = m.memory;
    response.size = m.size;
    response.error = res;

    long http_code = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    response.code = http_code;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl_slist_free_all(headerList);

    return response;

}


Response Service::get(const char *url) {

    close();

    curl = curl_easy_init();


    headerList = nullptr;

    m.memory = (char *) malloc(1);
    m.size = 0;

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

    // headers
    headerList = curl_slist_append(headerList, "Accept: application/json");
    headerList = curl_slist_append(headerList, "Content-Type: application/json");
    headerList = curl_slist_append(headerList, "charsets: utf-8");

    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Service::WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &m);

    res = curl_easy_perform(curl);

    response.data = m.memory;
    response.size = m.size;
    response.error = res;

    long http_code = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    response.code = http_code;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl_slist_free_all(headerList);

    return response;


}

void Service::close() {
    if (!clearMemory) {
        free(m.memory);
        clearMemory = 1;
    }

}


size_t Service::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct ResponseData *mem = (struct ResponseData *) userp;

    char *ptr = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        /* out of memory! */
        printf("not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;

}
