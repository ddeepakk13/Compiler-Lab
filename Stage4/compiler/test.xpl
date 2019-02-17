begin
    decl
        int arr[3][3],i,j;
    enddecl
	i=0;
    while(i<3) do
        j=0;
        while(j<3) do
            read(arr[i][j]);
            j = j+1;
        endwhile;
        i=i+1;
    endwhile;

    i=0;
    while(i<3) do
        j=0;
        while(j<3) do
            write(arr[i][j]);
            j = j+1;
        endwhile;
        i=i+1;
    endwhile;
end