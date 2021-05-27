# High CRM

## Содержание

1. [Содержание](#содержание)
1. [Компиляция](#Компиляция)


## Компиляция
0) `sudo apt update`
1) распаковать `.zip` файл c библиотекой `grpc` [тут](https://drive.google.com/file/d/1MDRKG8vkr3LXCggyRoUdm_LzW-30a8an/view?usp=sharing).
2) далее выполнить следующие команды:
```
cd grpc
    mkdir -p cmake/build
    cd cmake/build
    cmake -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
        ../..
    make -j${NUM_JOBS}
    make install
```
3) скачать `boost`: `sudo apt-get install libboost-all-dev`
4) скачать `mysql`: `sudo apt install libmysqlcppconn-dev`
5) в первом окне терминала написать следующие команды:
```
cmake -B build
cmake --build build
./build/CRM-system/CRM-system_server
```
6) во втором окне:
```
./build/CRM-system/CRM-system_client
```

