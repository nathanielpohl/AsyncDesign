// This file is where commands are registered.
#pragma once

#include "cmd_modules/checksum.h"
#include "cmd_modules/word_count.h"
#include "cmd_modules/word_freq.h"
#include "fpic_modules/fpincppch10.h"
#include "fpic_modules/fpincppch11.h"
#include "fpic_modules/fpincppch2.h"
#include "fpic_modules/fpincppch3.h"
#include "fpic_modules/fpincppch4.h"
#include "fpic_modules/fpincppch6.h"
#include "fpic_modules/fpincppch7.h"
#include "fpic_modules/fpincppch9.h"

#define LIST_OF_COMMANDS(COMMAND)                \
  COMMAND(cmd_modules, Checksum, "CHECKSUM")     \
  COMMAND(cmd_modules, WordCount, "WORDCOUNT")   \
  COMMAND(cmd_modules, WordFreq, "WORDFREQ")     \
  COMMAND(fpic_modules, FPInCppCh2, "FPICCH2")   \
  COMMAND(fpic_modules, FPInCppCh3, "FPICCH3")   \
  COMMAND(fpic_modules, FPInCppCh4, "FPICCH4")   \
  COMMAND(fpic_modules, FPInCppCh6, "FPICCH6")   \
  COMMAND(fpic_modules, FPInCppCh7, "FPICCH7")   \
  COMMAND(fpic_modules, FPInCppCh9, "FPICCH9")   \
  COMMAND(fpic_modules, FPInCppCh10, "FPICCH10") \
  COMMAND(fpic_modules, FPInCppCh11, "FPICCH11")
