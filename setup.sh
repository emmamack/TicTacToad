#to run this script:
# $ chmod +x setup.sh && sudo ./setup.sh

echo "installing telnet (if you're in Ubuntu)..."
apt-get install telnet
#TODO: check for os to install correctly on other os?
# https://www.cyberciti.biz/faq/how-to-check-os-version-in-linux-command-line/
# https://www.redhat.com/sysadmin/error-handling-bash-scripting

echo "creating command line option to start server..."
echo "(run 'gameserver' from anywhere to open a connection)"
mv gameserver /bin/
# TODO: other setup = download required libraries? what libraries aren't already
# installed on most machines?
#TODO: name the compiled code gameserver when all other code is locked
