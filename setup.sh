#to run this script:
# $ chmod +x setup.sh && sudo ./setup.sh

echo ">> installing telnet (if you're in Ubuntu)..."
apt-get install telnet
echo ">> creating command line option to start server..."
echo ">> (run 'gameserver' from anywhere to open a connection)"
mv mainteest /bin/
