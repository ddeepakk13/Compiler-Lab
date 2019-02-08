begin
    read(a);
    read(b);
    read(c);
    if(a>b) then
        if(a>c) then
            write(a);
        endif;
    else
        if(b>c) then
            write(b);
        else
            write(c);
        endif;
    endif;
end