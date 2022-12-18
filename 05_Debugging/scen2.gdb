set $a=0
b 40 if $a < 9
    command 1
    printf "@@@%d %d %d %d %d\n", M, N, S, i, $a
    set $a=$a+1
    c
end
ignore 1 27
r