# Update and upgrade
sudo apt update
sudo apt upgrade
sudo apt install clang-format cmake cmake-curses-gui g++ gcc git make ninja-build perl ripgrep vim

# Create directories
FILE=~/code
if [ ! -d "$FILE" ]; then
	mkdir "$FILE"
fi

# Manually run steps
FILE=~/qtcreator-4.4.1
if [ ! -d "$FILE" ]; then
	printf "\n\n"
	printf "Download QT creator: https://download.qt.io/archive/qtcreator/"
	printf "BugMeNot: http://bugmenot.com/view/qt.io"
	printf "Set theme and Enalbe beautifier, restart qt"
	printf "Tools -> Options -> Beautifier -> Clang Format -> Google/auto"
	printf "\n\n"
fi

# Set up github
FILE=~/.ssh/id_ed25519
if [ ! -f "$FILE" ]; then
	printf "\n\nSet up new key for github: https://docs.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent\n\n"
	ssh-keygen -t ed25519 -C "nathaniel.pohl@gmail.com"
	ssh-add ~/.ssh/id_ed25519
fi

# Clone and build the project.
cd ~/code
git clone git@github.com:nathanielpohl/AsyncDesign.git ./AsyncDesign
git config --global user.email "nathaniel.pohl@gmail.com"
git config --global user.name "Nathaniel Pohl"
cd ./AsyncDesign
mkdir build && cd build
cmake -G "Ninja"  ..
