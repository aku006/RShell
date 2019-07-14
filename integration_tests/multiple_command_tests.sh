#!/bin/sh

echo "echo hello && echo bye || mkdir dummy_folder ; ls -a ; exit" | ../rshell
