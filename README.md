# static code smell detector

Console application, detects Long Method, Long Parameter List, and structurally Duplicated Code in a .cpp file. 
Created for Software Refactoring and Design course at Seattle University. 

## Description

Given a valid .cpp file, the detector will can run the following code smell detection methods on any or all methods provided. 
1. **Long Method** 
    Threshold metric = more than 15 lines of code. Excludes blank lines.  
2. **Long Parameter List** 
    * Threshold metric = greater than 3 parameters. 
3. **Duplicated Code** (structural only)
    * Threshold metric = Hamming index greater than 0.75. 

### Dependencies
* C++ 17+ , CMake 17, g++ 10.2.0

### Build and Run Executable 
To build and run from source folder:
```
$ cmake -build .
$ g++ main.cpp -o myDetector
$./myDetector <filepath> 
```

To build and run in separate build folder:
```
mkdir build 
$ cmake -S . -B ./build 
$ g++ main.cpp -o myDetector
$./myDetector <filepath> 
```
