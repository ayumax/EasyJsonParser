cd /d %~dp0
Froola.exe plugin -n EasyJsonParser -p EasyJsonParserTest -v UE_5_6 -u git@github.com:ayumax/EasyJsonParser.git -b UE5.6 -t -c -o packages
Froola.exe plugin -n EasyJsonParser -p EasyJsonParserTest -v UE_5_5 -u git@github.com:ayumax/EasyJsonParser.git -b UE5.5 -t -c -o packages
Froola.exe plugin -n EasyJsonParser -p EasyJsonParserTest -v UE_5_4 -u git@github.com:ayumax/EasyJsonParser.git -b UE5.4 -t -c -o packages