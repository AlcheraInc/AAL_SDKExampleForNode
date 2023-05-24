# AAL_SDKExampleForNode
A project with napi to connect between C++ and Node.js

## Test Environments
### OS
Ubuntu 22.04
### GCC/G++
gcc 11.3.0
g++ 11.3.0
### cmake
cmake version ^3.22.1
### Current Node.js Version
 - v18.16.0
### Dependencies
 - bindings
 - cmake-js
 - node-addon-api

## Setup
### Install GCC/G++
```
sudo apt install gcc g++
```

### Install cmake
```
sudo apt install cmake
```

### Write PATH on the .bashrc
```
export PATH="$HOME/node-v18.16.0-linux-x64/bin:$PATH"
```

### Install packages with npm
```
npm install
npm update
```

### Build with cmake-js
```
cmake-js --directory ./examples/
```

### Run test
```
[PATH_OF_NODES].node index.js
```
![image](https://github.com/AlcheraInc/AAL_SDKExampleForNode/assets/106507679/59455a7e-4ab0-4da6-a968-6a5b6a3e7445)
