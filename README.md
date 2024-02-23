# Computations on Paley clique number
This program computes clique number of Paley graph under relaxation hierarchies such as:
- Lovasz-Theta (SOS-2)
- Block-diagonal hierarchy of order 2 (L2) and order 3 (L3)

## Running locally

### Installing and using MOSEK
We're using [MOSEK version 10.1](https://docs.mosek.com/latest/install/installation.html#general-setup) (click for installation guide) 
to perform SDP computations for Lovasz, L2, L3 computations.

Follow the steps in MOSEK, and make sure it's installed correctly.

### Setting up .env files to import MOSEK
In `env` folder of this project (create one if you don't have one), create a file called `.env.local`, and add the following 
variables:
```
MSKHOME=<your_mosek_path>
PLATFORM=<your_platform>
```
- `<MSKHOME>` is the folder in which the MOSEK Optimization Suite has been installed, **relative to `~`, with no trailing
slash (`/`)**.
- `<PLATFORM>` is the actual platform among those supported by MOSEK, i.e. win64x86, linux64x86, osx64x86, or osxaarch64

For example, if you installed mosek in `~/my_package_folder/dev-tools` (i.e., your `/mosek/10.1/...` folders are located 
there), and you are using Apple Silicon machine. Your `.env.local` file should look like this:
```
MSKHOME=my_package_folder/dev-tools
PLATFORM=osxaarch64
```

### Running code
See `CMakeLists.txt` for version requirements. Edit code in `main.cpp` and run the following commands.

```bash
mkdir build
cd build
cmake ..
make
./ exec
```

Alternatively, use CLion (or similar IDEs) to load the project's `CMakeLists.txt` and streamline the build process.