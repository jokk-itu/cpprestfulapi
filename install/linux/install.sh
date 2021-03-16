#INSTALL POSTGRES
sudo apt-get install -y libpqxx-dev

cd "$HOME" || stderr "home folder does not exist"

#INSTALL MONGOCDB (mongoc and libsson)
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.4/mongo-c-driver-1.17.4.tar.gz
tar xzf mongo-c-driver-1.17.4.tar.gz
cd mongo-c-driver-1.17.4
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
cmake --build .
sudo cmake --build . --target install

#INSTALL MONGOCXX
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.2/mongo-cxx-driver-r3.6.2.tar.gz
tar -xzf mongo-cxx-driver-r3.6.2.tar.gz
cd mongo-cxx-driver-r3.6.2/build
cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local
sudo cmake --build . --target EP_mnmlstc_core
cmake --build .
sudo cmake --build . --target install

#Move around bsoncxx and mongocxx, because they are installed incorrectly
cd /usr/local/include
sudo mv bsoncxx/v_noabi/bsoncxx ../
sudo mv mongocxx/v_noabi/mongocxx ../
sudo rm -r bsoncxx
sudo rm -r mongocxx
cd ..
sudo mv bsoncxx include
sudo mv mongocxx include


#INSTALL CPPRESTSDK
sudo apt-get install libcpprest-dev

#INSTALL GOOGLE TESTS
git clone https://github.com/google/googletest.git -b release-1.10.0
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install #inside /usr/local