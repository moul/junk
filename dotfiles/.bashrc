## LOAD DEPENDENCIES
for file in $HOME/.bash_private; do
    if [ -f $file ]; then
        . $file
    fi
done
