__Tetris remake with a twist!__

Follow these steps to set up and run the  game on your Windows machine.

__Prerequisites__
Git
Visual Studio 2019 or later
vcpkg (for installing raylib)

__Step 1: Clone the Repository__
Clone the  repository to your local machine. Open a command prompt and run:

git clone https://github.com/kai-z99/fire-tetris.git
cd fire-tetris

__Step 2: Install raylib using vcpkg__
Install vcpkg: If you haven't installed vcpkg, clone it from GitHub and run the bootstrap script:

git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
cd ..

Install raylib: Install raylib using vcpkg:

./vcpkg/vcpkg install raylib

Integrate vcpkg with Visual Studio: This step allows Visual Studio to automatically use libraries installed with vcpkg:

./vcpkg/vcpkg integrate install

__Step 3: Open the Project in Visual Studio__
Open the Solution: Navigate to the cloned repository's directory and double-click on the tetrisGame.sln file to open the project in Visual Studio.

__Step 4: Build the Project__
Build the Solution: In Visual Studio, select Build > Build Solution (or press Ctrl+Shift+B). This will compile the project and all its dependencies.

__Step 5: Run the Game__
Run the Game: After the build is successful, run the game by selecting Debug > Start Without Debugging (or press Ctrl+F5).

This should launch the game window, and you can start playing the game.

__Game Controls__

A, D = move block left, move block right
W = Rotate
S (hold) = move block down
Enter (after game over) = play again
