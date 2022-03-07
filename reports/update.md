git # TicTacToad: Terminal Based Minigames
# Project Update
### Berwin Lan, Emma Mack, Maya Sivanandan

## Project Goals
* Lower bound: We would like two computers on the same network to be able to play tic-tac-toe through the command line.
* Stretch goal(s): Implementing more games, implementing more users, setup script, AI battler, GUI

## Learning Goals
* Berwin: Improving and expanding my skills in C, building a basic understanding of how computers communicate across a network
* Maya: Understanding how to have two computers communicate in real time and increase my general competency in C
* Emma: Understanding computer networking, getting more practice with pointers, learning about shell scripts

## Resources
* We were inspired by this past project, which focuses more on the computer networking aspect of what we’re hoping to accomplish. We can start with their cited resources: https://github.com/NathanShuster/hackerchat/blob/master/reports/report.md#resources
* Socket programming:
  * https://www.geeksforgeeks.org/socket-programming-cc/#:~:text=What%20is%20socket%20programming%3F,reaches%20out%20to%20the%20server
  * https://www.binarytides.com/socket-programming-c-linux-tutorial/
  * https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf


## First steps
* Conceptual understanding of the computer networking we plan on doing (Berwin). Creating reading list for socket programming; while this will be an ongoing learning process, our goal is for each member of the team to have a conceptual understanding of our computer networking. This task will be done when all members of the team have completed the readings.
  * This is done.
* Set up basic connection between two machines on the same network (Maya, but all working closely). After completing this, we will be able to start up two command shells on separate machines and have them communicate with one another over the same network.
  * This is done.
* Write a minigame for two players that’s run on one machine (Emma). This is complete when there is a functional version of rock-paper-scissors in the terminal of a single device.
  * Our work on this ended up being slightly modified: Berwin worked on a simple one-terminal, two-player minigame (20 Questions instead of rock-paper-scissors), and Emma led the implementation into a two-terminal game.

## Current work
* **Using header files**: We started off by putting everything into the same `main.c` file for ease of testing, but it started to get unwieldy because of the number of functions we have. Berwin has been refactoring it into modular header files and separating out our game functions and helper functions from the main function. This task is done because the additional files exist and the program still compiles and works as expected; however, it will need ongoing maintenance as we add more functions to make sure our code remains organized and clean.
* **Creating Makefile**: A side effect of using header files is needing a more sophisticated Makefile to automate the compilation process. As part of refactoring into header files, Berwin also updated the Makefile to reflect the new dependencies. This is an ongoing task, since the Makefile needs to be kept up-to-date as new files are added. This will be considered done when the project is submitted, and all files can be compiled successfully with the Makefile.
* **20 Questions**: All team members collaboratively worked on this task, Emma finished it. As a test-run for Tic-Tac-Toe, we have successfully implemented a two-computer version of 20 Questions. One user runs a script that will attempt to connect to a socket until it succeeds, then waits for clients to join. The other user on a different computer can join the game, play, and then gets booted off the server when the game is over.
* **Setup script**: Emma is working on writing a setup script that a new git-cloner/downloader can run to get set up to host a server. She is learning a lot about shell scripts. As of now, the script installs telnet and moves the main executable such that it can be run as a command from anywhere.
* **Game chooser / GUI**: Berwin is working on a GUI / wrapper for playing games, because (as discussed in the 20 Questions section) right now you are put straight into 20 Questions and exit immediately after. This will be complete when the client and/or the server can pick which game they want to play, or if they want to leave the server.

<!-- 3) What have you done to get started?  Have you found the resources you need, do you have a plan to find them, or do you need help?  If you found any resources you think I should add to the list on the class web page, please email them to me.

4) What are you working on now?  Describe at least three concrete tasks that you are working on, and identify which members of the team are working on them.  For each one, what is the "definition of done"; that is, what will you produce to demonstrate that the task is done? -->

<!-- Link to Todoist board and Github -->
## Team links
* [Todoist](https://todoist.com/app/project/2285403013)
* [GitHub](https://github.com/emmamack/TicTacToad/)
