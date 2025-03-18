**Environment**: Ubuntu 24.01

**Dependencies**: Python 3.12, Clang-18, LLVM-18 (other versions have not been tested).

Please activate the **virtual environment** with the following command:

```bash
source venv/bin/activate
```



# Usage Instructions

The script `make.sh` includes parts for compiling and installing LLVM 16.0.0 as well as compiling and installing the interface extraction tool. If you have already installed LLVM 16.0.0, you can comment out the installation part of LLVM and change `_DLLVM_DIR` to your own environment's LLVM directory.

Run the following commands to compile and install LLVM 16.0.0 and  interface extraction tool:

```bash
chmod +x make.sh
./make.sh
```

For **Lua** projects:
	1.Set the `LLVM_COMPILER` environment variable:

```bash
export LLVM_COMPILER=clang
```
​	2.Use `wllvm` and `extract_bc` tools to extract the `.bc` format file of the project executable: We've already set Lua's compiler to `wllvm`. Just run `make all test` followed by using the `extract-bc` tool to extract the `.bc` format file of the project executable:

```bash
cd Input/lua
make all test
extract-bc lua
```
Running the Tool:

```bash
cd ../../IP_extract_tool
python3 app.py ../Input/lua/llex.c ../Input/lua save lua
```

Here, `'../Input/lua/llex.c'` is the path to the .c file containing the target function, `'../Input/lua'` is the project root directory, `'save'` is the name of the target function, and `'lua'` is the name of the executable file in `.bc` format. The `.c` and `.h` files for IP will be output in `./Output`, while the JSON formatted file for the function interface will be output in `./Input/lua`.	

The experimental data is placed in the `./result` directory.
