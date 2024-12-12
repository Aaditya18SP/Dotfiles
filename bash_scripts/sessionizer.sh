#!/bin/bash
session=$(find ~ ~/Projects ~/Documents -mindepth 1 -maxdepth 1 -type d | fzf)
session_name=$(basename "$session"| tr . _)

if ! tmux -has-session -t "$session_name" 2> /dev/null; then 
	tmux new-session -c "$session" -d -s "$session_name"
fi

tmux switch-client -t "$session_name"