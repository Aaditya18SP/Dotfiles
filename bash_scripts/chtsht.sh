#!/bin/bash
languages=$(echo " c cpp java python scala r golang javascript"| tr " " "\n")
core_utils=$(echo "find xargs sed awk locate where"| tr " " "\n")
selected=$(echo -e "$languages\n$core_utils" |fzf)

read -p "GIVE ME YOUR QUERY. COME ON GIVE IT TO ME:" query
if echo "$languages" |grep -qs $selected; then 
	tmux split-window  -h bash -c "curl cht.sh/$selected/$(echo "$query"|tr " " "+")| less"
else
	curl cht.sh/$selected~$query
fi
