## __Welcome!__

Follow these steps to set up and run the  game on your Windows machine.  

__Prerequisites__
- Git
- Visual Studio 2019 or later
- vcpkg (for installing raylib)

__Step 1: Clone the Repository__
- Clone the  repository to your local machine. Open a command prompt and run:

  git clone https://github.com/kai-z99/fire-tetris.git
  
  cd fire-tetris

__Step 2: Install raylib using vcpkg__
- If you haven't installed vcpkg, clone it from GitHub and run the bootstrap script:

  git clone https://github.com/Microsoft/vcpkg.git
  
  cd vcpkg
  
  ./bootstrap-vcpkg.bat
  
  cd ..

- Install raylib using vcpkg. Ensure you are in the directory where the vcpkg executable is located (this should be the vcpkg directory you cloned from GitHub). Run the following commands:

  ./vcpkg install raylib

  ./vcpkg/integrate install

__Step 3: Open the Project in Visual Studio__
- Navigate to the cloned repository's directory and open the tetrisGame.sln file to open the project in Visual Studio.
  
- In Visual Studio, select Build > Build Solution (or press Ctrl+Shift+B). This will compile the project and all its dependencies.

__Step 4: Run the Game__
- After the build is successful, you can run the game by selecting Debug > Start Without Debugging (or press Ctrl+F5).

__Game Controls__

- A, D = move block left, move block right
- W = rotate block
- S (hold) = move block down
- Enter (after game over) = play again
- Esc = exit game
