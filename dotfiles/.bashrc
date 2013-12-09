## VARIABLES
BREW_PREFIX=$(brew --prefix)


## ENVIRONMENT
export PYTHONDONTWRITEBYTECODE=1
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
export EDITOR=emacs


## ALIASES
alias venv=". ~/venv/bin/activate"
alias emacs="emacs -nw"
alias brew="brew growl"


## GIT ACHIEVEMENTS
if [ -d ~/Git/watch/icefox/git-achievements ]; then
    alias git="~/Git/watch/icefox/git-achievements/git-achievements"
fi


## PROMPT
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac
force_color_prompt=yes
if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	color_prompt=yes
    else
	color_prompt=
    fi
fi
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;35m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac
unset color_prompt force_color_prompt


## BASH COMPLETION
if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
    . /etc/bash_completion
fi
for dir in /usr/local/etc/bash_completion.d; do
    #echo $dir
    if [ -d $dir ]; then
        for file in $dir/*; do
            if [ -x $file ]; then
                #echo "[+] $file"
                . $file
            else
                #echo "[-] $file"
                source $file 2>/dev/null
            fi
        done
    fi
done


## LOAD DEPENDENCIES
for file in \
    "$BREW_PREFIX/etc/bash_completion" \
    "$BREW_PREFIX/etc/grc.bashrc" \
    "$HOME/.bash_private" \
    ; do
    if [ -f $file ]; then
        . $file
    fi
done


## CLEAN
unset BREW_PREFIX
