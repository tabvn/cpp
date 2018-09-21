sudo apt-get install libssl-dev gyp
git clone https://github.com/libuv/libuv.git libuv
cd libuv
./gyp_uv.py -f make
BUILDTYPE=Release make -C out
cp ./out/Release/libuv.a /usr/lib
cd ..
rm -rf libuv
