//
// Created by Toan on 9/23/18.
//

#include "service.h"


Service::Service() {

}


void Service::post(char *url, char *data) {


    struct curl_slist *chunk = NULL;

    // Custom header
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);


    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(data));

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {

        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

}


Response Service::get(const char *url) {


    struct Response response;

    curl = curl_easy_init();

    struct ResponseData m;

    m.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
    m.size = 0;


    struct curl_slist *headerList = NULL;

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

    // Custom header
    headerList = curl_slist_append(headerList, "Content-Type: application/json");

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

size_t Service::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct ResponseData *mem = (struct ResponseData *) userp;

    char *ptr = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;


}
