# C++ Server Api &amp; Websocket

## Ubuntu
### Install OpenSSL 

```
sudo apt-get install libssl-dev
```
### Install Libuv

visit document: https://github.com/libuv/libuv/blob/master/README.md

copy libuv.a library to /usr/lib

```
cp .out/Release/libuv.a /usr/lib 
```

### Build Project

```
cmake .
make

```
### Run Project

```
./cpp
```
