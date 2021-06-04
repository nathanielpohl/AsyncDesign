# Update and upgrade.
sudo apt update -qq
sudo apt upgrade -qq -y
sudo apt install -qq -y ccache clang-format cmake cmake-curses-gui g++ gcc git libgflags-dev libgtest-dev make ninja-build perl ripgrep vim

# Create directories.
TOP_LEVEL_CODE_DIR=~/code
if [ ! -d "$TOP_LEVEL_CODE_DIR" ]; then
	mkdir "$TOP_LEVEL_CODE_DIR"
fi

# Manually run these steps to set up QT if.
FILE=~/qtcreator-4.4.1
if [ ! -d "$FILE" ]; then
	printf "\n\n"
	printf "Download QT creator: https://download.qt.io/archive/qtcreator/\n"
	printf "BugMeNot: http://bugmenot.com/view/qt.io\n"
	printf "Set theme and Enalbe beautifier, restart qt\n"
	printf "Tools -> Options -> Beautifier -> Clang Format -> Google/autosave\n"
	printf "\n\n"
fi

# Set up github. You probably want to change some values in here.
FILE=~/.ssh/id_ed25519
if [ ! -f "$FILE" ]; then
	printf "\n\nSet up new key for github: https://docs.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent\n\n"
	ssh-keygen -t ed25519 -C "nathaniel.pohl@gmail.com"
	git config --global user.email "nathaniel.pohl@gmail.com"
        git config --global user.name "Nathaniel Pohl"
	ssh-add ~/.ssh/id_ed25519
	# The next steps need github set up, so exit.
	exit 1
fi

# Install glog.
FILE="$TOP_LEVEL_CODE_DIR"/glog
if [ ! -d "$FILE" ]; then
	cd "$TOP_LEVEL_CODE_DIR"
	git clone https://github.com/google/glog.git
	cd glog
	cmake -S . -B build -G "Unix Makefiles"
	cmake --build build
	sudo cmake --build build --target install
fi

# Clone and build the project.
FILE="$TOP_LEVEL_CODE_DIR"/AsyncDesign
if [ ! -d "$FILE" ]; then
	cd "$TOP_LEVEL_CODE_DIR"
	git clone git@github.com:nathanielpohl/AsyncDesign.git ./AsyncDesign
	cd AsyncDesign
	mkdir -p build && cd build
	cmake -G "Ninja"  ..
	ninja
fi
