```tefcha
while !validarFecha(curso->fFin)
gotoXY(18,9)
printf(ANSI_COLOR_RED "\n\nIntroduzca una fecha correcta (dd/mm/aaaa).\n\n" ANSI_COLOR_RESET);
gotoXY(46,5);
obtenerDato(date,11);
insertarFecha(date,&curso->fFin);
     
```