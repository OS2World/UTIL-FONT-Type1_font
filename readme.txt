
Font information from type 1 fonts
----------------------------------
This code is intended to help installing Type1 fonts in
OS/2 XFree86.

Command extr extracts font information from type 1 
font files into standard output.

Format of output can be redirected 
to fonts.dir and fonts.scale files located 
in font\xxx directories in XFree86 installations
After this you should review output, to correct
problems.

This implementation is in public domain.

Please note:
 - This code is partially based on type1inst code. 
   type1inst is better and more complete, 
   so use it, if you can.
 - I am not very good at helpping with problems,
   as I do not know engouht about X or type1 fonts.
   Short but good advices are given in GIMP manual.
   Guess why I wanted to add type1 fonts into XFree86?

This code is working for me, but ABSOLUTELY NO GUARANTY IS GIVEN.

Author:
 Lauri Paatero
 Lauri.Paatero@paatero.pp.fi
