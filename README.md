# TicTacToad: A Cross-Machine Minigame Server

### Setup
After downloading the repo, run `$ chmod +x setup.sh && sudo ./setup.sh` from inside the folder. This will install library dependencies and a command to open the server from anywhere in your directories (`$ gameserver`). 

You will need to determine your IP address for a client to connect to your server. Run `$ ip r` and note down the IP address from the first line of the output.

To play games with a friend, instruct your friend to do the same setup as laid out earlier. They should also be connected to the same wifi network as you are. Open the server with `$ gameserver`, and have your friend run `$ telnet [your-ip-address] 3000`. 

Enjoy!

### Reports
Check out our [reports folder](https://github.com/emmamack/TicTacToad/tree/main/reports) for demonstrations and process documentation.
