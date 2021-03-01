#INSTALL POSTGRES
sudo apt-get install -y libpqxx-dev #Postgres Driver

cd "$HOME" || stderr "home folder does not exist"

#INSTALL MONGOCDB (mongoc and libsson)
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.4/mongo-c-driver-1.17.4.tar.gz
tar xzf mongo-c-driver-1.17.4.tar.gz
cd mongo-c-driver-1.17.4 || stderr ""
mkdir cmake-build
cd cmake-build || stderr ""
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
cmake --build .
sudo cmake --build . --target install

#INSTALL MONGOCXX
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.2/mongo-cxx-driver-r3.6.2.tar.gz
tar -xzf mongo-cxx-driver-r3.6.2.tar.gz
cd mongo-cxx-driver-r3.6.2/build || stderr "build folder does not exist in cxx driver"
cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local
sudo cmake --build . --target EP_mnmlstc_core
cmake --build .
sudo cmake --build . --target install

#INSTALL CPPRESTSDK
sudo apt-get install libcpprest-dev #cpprestsdk