#!/bin/bash

HISTORY_FILE="$HOME/.clipboard_history"

if [ ! -f "$HISTORY_FILE" ]; then
   touch "$HISTORY_FILE" 
fi

get_clipboard_content(){
    xclip -o -selection clipboard
}

while true; do
    LATEST_CLIPBOARD_CONTENT=$(get_clipboard_content)

    if ! grep -Fxq "$LATEST_CLIPBOARD_CONTENT" "$HISTORY_FILE"; then
        echo "$LATEST_CLIPBOARD_CONTENT" >> "$HISTORY_FILE"     
        printf  "\n\n" >> "$HISTORY_FILE"
    fi
    sleep 1
done
