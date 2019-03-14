decl 
  int a;
enddecl


int main()
{
  begin
    a = 0;
    while(NOT(a==10)) do
      if(NOT((a%3 == 0) OR (a%5 == 0))) then
        write(a);
      endif;
      a = a+1;
    endwhile;
    return 0;
  end
}