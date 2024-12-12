#!/bin/bash
HISTORY_FILE="$HOME/.clipboard_history"
SELECTED_OPTION= $( tac "$HISTORY_FILE" | awk 'BEGIN { RS="\n\n"; ORS="\n\n" } { if (NR <= 10) print }' "$HOME/.clipboard_history"|tac |fzf )
if [ ! -z "$SELECTED_OPTION" ]; then
    echo "$SELECTED_OPTION" | xclip -i -selection clipboard
fi

