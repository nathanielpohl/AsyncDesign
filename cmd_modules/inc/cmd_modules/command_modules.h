// This file is where commands are registered.
#pragma once

#include "cmd_modules/checksum.h"
#include "cmd_modules/word_count.h"
#include "cmd_modules/word_freq.h"

#define LIST_OF_COMMANDS(COMMAND) \
COMMAND(cmd_modules, Checksum, "CHECKSUM") \
COMMAND(cmd_modules, WordCount, "WORDCOUNT") \
COMMAND(cmd_moduels, WordFreq, "WORDFREQ")
