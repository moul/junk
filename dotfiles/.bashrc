## VARIABLES
BREW_PREFIX=$(brew --prefix)

## ALIASES
alias venv=". ~/venv/bin/activate"
alias emacs="emacs -nw"

## GIT ACHIEVEMENTS
if [ -d ~/Git/watch/icefox/git-achievements ]; then
    alias git="~/Git/watch/icefox/git-achievements/git-achievements"
fi


## LOAD DEPENDENCIES
for file in "$HOME/.bash_private" "$BREW_PREFIX/etc/bash_completion" "$BREW_PREFIX/etc/grc.bashrc"; do
    if [ -f $file ]; then
        . $file
    fi
done

## CLEAN
unset BREW_PREFIX
