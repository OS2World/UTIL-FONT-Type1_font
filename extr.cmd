/* Extract font info from all type 1 files...*/
'@echo off'

PARSE SOURCE dummy1 dummy2 commandline;
sourcepath = FILESPEC( "drive", commandline)FILESPEC( "path", commandline)

call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs

call SysFileTree '*.pf?', 'names', 'FO'

say names.0

do index = 1 to names.0
name = FILESPEC( "name", names.index )
doext = sourcepath"type1ext" name " <" names.index
doext
end

exit