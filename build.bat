cl.exe download_exec.cpp /Febtassist.exe
rcedit /I btassist.exe bt.ico  

set VERSION="7.0.0.0 (1)"
set FILEDESCR=/s desc "Bluetooth Assistant"
set BUILDINFO=/s pb ""
set COMPINFO=/s company "TOSHIBA CORPORATION" /s (c) "Copyright (C) 2009 TOSHIBA CORPORATION, All rights reserved."
set PRODINFO=/s product "Bluetooth Assistant" /pv "7.0.0.0"

verpatch /va btassist.exe %VERSION% %FILEDESCR% %COMPINFO% %PRODINFO% %BUILDINFO%