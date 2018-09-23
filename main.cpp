#include <iostream>
#include "uws/uWS.h"
#include "service.h"

using namespace std;

uWS::WebSocket<uWS::CLIENT> *client;

bool isConnected = false;

Service service;


int main() {

    string url = "ws://127.0.0.1:3007/ws";

    uWS::Hub h;


    std::vector<std::string> messages = {"hello", "world"};

    std::vector<int> excludes;


    h.onError([&](void *user) {

        cout << "Error" << endl;

        isConnected = false;
        sleep(1);

        if (!isConnected) {
            h.connect(url, (void *) 10, {}, 60000);
        }


        const char *requestUrl = "https://reqres.in/api/users?page=2";
        Response res = service.get(requestUrl);

        cout << "Response: " << res.code << ":" << res.error << res.data << endl;


    });


    h.onConnection([&messages, &excludes](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {


        isConnected = true;
        client = ws;

        std::cout << "Connected" << endl;

        const char *msg = "How are you Server";


        client->send(msg);

    });

    h.onDisconnection([&](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {

        isConnected = false;

        std::cout << "closed" << endl;

        sleep(1);

        if (!isConnected) {
            h.connect(url, (void *) 10, {}, 60000);
        }


    });

    int receivedMessages = 0;

    h.onMessage(
            [&receivedMessages, &h](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {

                std::cout << "Server Message: " << std::string(message, length) << std::endl;


            });


    h.connect(url, (void *) 10, {}, 60000);


    h.run();


    return 0;
}