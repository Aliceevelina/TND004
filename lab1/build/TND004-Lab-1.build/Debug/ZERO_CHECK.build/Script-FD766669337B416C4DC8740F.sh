#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/build"
  make -f /Users/Alice/Desktop/SKOLA/TND004\ -\ Datastrukturer/lab1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/build"
  make -f /Users/Alice/Desktop/SKOLA/TND004\ -\ Datastrukturer/lab1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/build"
  make -f /Users/Alice/Desktop/SKOLA/TND004\ -\ Datastrukturer/lab1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/build"
  make -f /Users/Alice/Desktop/SKOLA/TND004\ -\ Datastrukturer/lab1/build/CMakeScripts/ReRunCMake.make
fi

