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

### Install OpenCV
[OpenCV Github](https://github.com/opencv/opencv)

### Install libtorch & torchvision
[Install libtorch](https://pytorch.org/get-started/locally/)   
[Install torchvision](https://github.com/pytorch/vision)   
We tested at libtorch 1.13.1.

### Write PATH on the .bashrc
```
export PATH="$HOME/node-v18.16.0-linux-x64/bin:$PATH"
```
You should add some paths on the LD_LIBRARY_PATH as below:
```
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:/lib/x86_64-linux-gnu:/usr/local/cuda/lib64:/home/systembug/opencv/lib:/usr/local/cuda/extras/CUPTI/lib64:/home/systembug/TensorRT/TensorRT/lib:/home/systembug/libtorch/lib:/home/systembug/torchvision/lib:${LD_LIBRARY_PATH}
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
