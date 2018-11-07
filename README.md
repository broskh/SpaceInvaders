# Space Invaders
## Introduction
Reproduction of the famous *Space Invaders* videogame that keeps unchanged all the basic functionalities of the original game.
<br>
The player will then have to control a tank with which he will have the task of bringing down, as long as he has available lives, the waves of aliens that repeatedly approach.

## Game description
### Main menù
The game has a main menù with whom is possible to open the other screens.

![Space Invaders - Main menù](http://imgur.com/ohHFaJy.png)
> To move between the menu items, use *up arrow* and *down arrow*, while to enter the selected area press *enter*.

### The game
From the game screen it's possible to really play.
<br>
The game is based on a wave of aliens that move permanently with a zig-zag movment from right to the left an viceversa. Each time that a side margin is reached the wave go down and as soon as that aliens are killed the wave increase their movement speed.
<br>
Whenever an alien is hit, the player's score is increased by a value that depends on the type of alien. When an entire wave is killed, a new wave is immediately displayed.
<br>
The player, at the beginning of the game, has three barriers. Whenever they are hit by aliens or tanks, they first crumble and eventually they are destroyed.
<br>
Moreover, at random intervals, a mysterious spaceship appears. If hit, the player wins a lot of points with a random value.
<br>
The goal of the game is to prevent that alien wave from reaching the tank because if this happens, the game ends.

![Space Invaders - Game](http://imgur.com/2EChJ08.png)
> The user can use *right arrow* and *left arrow* to move the tank, while with *space bar* the user can shoot.
<br>

> During a match is possible to pause the game by pressing *esc*.

### Pause menu
From the game screen you can access the pause menu where the player can continue, quit or save the game in progress.
<br>
If the player saves the game, return to the main menu and the menu item that allows to load the game will be enabled.

![Space Invaders - Pause menu](http://imgur.com/o1t5O36.png)
> To move between menu items the player must use *up arrow* and *down arrow*, while to select a function simply press *enter*.

### End of the match
At the end of the game, if the player has obtained a score to be included in the highscore, you can enter a three-letter alias and save it.

![Space Invaders - End game](http://imgur.com/pXCDXam.png)
> By pressing *enter* the score is saved and the player returns to the main menu.

### Settings
From main menu is possible to access the settings menu.
<br>
This menu allows to enable or disable music and sound effects. In addition, the settings allow to change the color of the aliens and set the number of lives with which the player starts the games.

![Space Invaders - Settings menu](http://imgur.com/HPXLMAP.png)
> By pressing *arrow up* and *arrow down* can move between the various settings menu items. With *right arrow* and *left arrow* can change the selected value. With *r* the default values are reset. By pressing *enter* the new values are saved and the player returns to the main menu.

### Highscores
From the main menu can view the ranking of the top ten scores and the aliases of the players who have achieved these results.

![Space Invaders - Highscores](http://imgur.com/Rv0TCdn.png)
> By pressing *enter* the player can return to the main menu.

## Requirements
A basic requirement for compiling the code is the *allegro* graphics library.
For information on installing this library, simply follow the instructions [here](https://wiki.allegro.cc/index.php?title=Getting_Started).

## How to install
To install the game on debian-based distributions you can follow these simple steps:
- Download from github the .zip archive.
- Extract the archive content.
- Open a terminal into the directory.
- Enter on the terminal `cd src`.
- Enter on the terminal `make depend`.
- Enter on the terminal `make`. In this way you can compile and generate the executable *SpaceInvaders*.

To play, with a terminal in the folder, enter  `./SpaceInvaders`.

> Tested on *Ubuntu 16.04.1 64bit*.

## Other make options
You can use make with other options to get different results:
- `make clean` to delete all files generated in compilation phase.
- `make cleanAll` to delete all files generated in compilation phase and various save and configuration files.
- `make debug` to compile the code in debug mode (also console tracing is enabled).
- `make debugExtended` to compile the code in debug mode (also extended console tracing is enabled).
- `make depend` to generate the file *dependencies* that contains the dependencies (not present in the system default directories) of the files to compile.
- `make noAsserts` to compile the code disabling the asserts.

## Documentation
The documentation in HTML format is present in the *doc/html/* folder. By opening the *index.html* file you can browse it with any browser.

> Documentation generated automatically with Doxygen.

## References
- The music and the sound effects comes from: (http://www.classicgaming.cc/classics/space-invaders/sounds) and (http://downloads.khinsider.com/game-soundtracks/album/space-invaders-gbc-gb-).
- The used font for main menu title comes from:  (http://www.fontspace.com/dustbust/invaders).
- The font user in other game strings comes from: (http://it.fonts2u.com/space-invaders-regular.carattere).
