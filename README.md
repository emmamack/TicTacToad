# TicTacToad
A cross-machine minigame program

## 2/24/2022
* Ran socket_test.c from Emma's computer as server and Berwin and Maya's WSLs as clients, which WORKED!
* `hostname -i` to get a machine's IP address, which changes when you change Wifi networks
    * Maya and Berwin have the same address, which suggests that it might be an IP address thing (`127.0.1.1`)
    * Maya on OLIN is `10.7.88.62`
* need to `printf` with `\n` smh
* implemented most of 20Q
* Blocked by not understanding why `strcmp` isn't working, will address during first check-in (2/25)
* WSL can connect to itself, but not between different machines

## 2/25/2022 Check-in with Steve
* Suggests making sure everyone has something to do under the "to-do" column in Todoist
    * subtasks?? so we can assign more than one person? oh???
* Investigate multi-way communication, set things up to resume game if someone drops and reconnections (state restoration)
* Playing against AI ??
* \>2-player games
* don't commit `a.out` files - a `.gitignore` file
* make a `Makefile`