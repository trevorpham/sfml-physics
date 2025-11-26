# SFML Physics Simulations

A collection of simple physics animations made with the SFML C++ library. This project contains a copy of SFML version 3.0.2.

## How to build this project

### Command line

1. Install [Git](https://git-scm.com/downloads) and [CMake](https://cmake.org/download/). Use your system's package manager if available.
2. Clone your new GitHub repo and open the repo in your text editor of choice.
3. If you want to add or remove any .cpp files, change the source files listed in the `add_executable` call in src/CMakeLists.txt.
4. If you want to add other SFML modules, such as Audio or Network, then add `SFML::<ModuleName>` to the `target_link_libraries` call alongside the existing `SFML::Graphics` library that is being linked.
5. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
   ```
   sudo apt update
   sudo apt install \
       libxrandr-dev \
       libxcursor-dev \
       libxi-dev \
       libudev-dev \
       libfreetype-dev \
       libflac-dev \
       libvorbis-dev \
       libgl1-mesa-dev \
       libegl1-mesa-dev \
       libfreetype-dev
   ```
6. Configure and build your project. Most popular IDEs support CMake projects with very little effort on your part.

   - [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
   - [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
   - [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
   - [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

   Using CMake from the command line is straightforward as well.
   Be sure to run these commands in the root directory of the project you just created.

   ```
   cmake -B build
   cmake --build build
   ```

7. When you run the executable, a console window will open with printed instructions. Press a number on your keyboard to run the corresponding simulation. Press Esc to exit.

### Visual Studio

Using a Visual Studio workspace is the simplest way to get started on windows.

1. Ensure you have the [required components installed](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation).
2. Follow [GitHub's instructions](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) for how to use their project template feature to create your own project.
3. If you have already cloned this repo, you can [open the folder](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio0#ide-integration).
4. If not, you can [clone it directly in Visual Studio](https://learn.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo).

Visual Studio should automatically configure the CMake project, then you can build and run as normal through Visual Studio. See the links above for more details.