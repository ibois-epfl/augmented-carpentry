#!/bin/bash

# Take a screenshot of the current screen and save it to the specified file
# Usage: ./ssh_take_screenshot.sh /path/to/screenshot.png

# Check if the file path is provided as an argument
if [ -z "$1" ]; then
    echo "Please provide the file path to save the screenshot"
    exit 1
fi

# Take a screenshot of the current screen and save it to the specified file
gnome-screenshot -f $1

# Check if the screenshot was successfully saved
if [ $? -eq 0 ]; then
    echo "Screenshot saved to $1"
else
    echo "Failed to save screenshot"
    exit 1
fi
