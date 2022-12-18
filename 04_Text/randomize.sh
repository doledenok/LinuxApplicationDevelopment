#! /bin/sh

SLEEP=0
if [ $# != 0 ]
then
    SLEEP=$1
fi

parse_lines ()
{
    y=0
    while IFS= read -r line
    do
        x=0
        for j in $(echo "$line" | od -v -t x1 -A n);
        do
            if [ $j = 20 ]
            then
                x=$(($x+1))
                continue
            fi
            echo "$y $x $j";
            x=$(($x+1))
        done
        y=$(($y+1))
    done
}

output_picture ()
{
    while IFS=' ' read -r x y hex_char
    do
        tput cup $x $y
        #echo "$x $y"
        echo "$hex_char" | xxd -r -p -
        sleep $SLEEP
    done
}

clear
parse_lines | shuf | output_picture
tput cup $(tput lines) 0