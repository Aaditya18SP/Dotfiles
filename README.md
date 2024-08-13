# How are dotfiles managed

## Utilities used
1. GNU Stow (need to install it)

## Command
cd to this directory(ie Dotfiles)  and then issue the command- `stow <name-of-folder> -R --dotfiles -t ~`
** COMMAND EXPLAINATION **
1. `-R` -> restows (removes and then stows again)
2. `--dotfiles` => use it to replace the word 'dot-'prefix from directories with a '.'(period). Eg: We want to stow it to the .config directory, then we would name it directories in the ***stow directory*** as `<package_name>/dot-config/`.
3. `-t` => is used to set the target directory to the home directory (`~`).


## NOTE 
1. The file `xorg.conf` is not stowed. Rather it is symlinked using `Ansible`. Find the YAML file for the same in the Ansible repo.
2. I need to solve the ssh issue where I cant push my encrypted ssh keys because git cant read those encrypted keys. It has become cyclic :(
***AND JUST LIKE I SETUP MY DOTFILES!!***  
