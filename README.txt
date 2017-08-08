Ovo je moj test projekat;


Kopirao sam C:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.dll 
u C:\Qt\5.8\msvc2013_64\bin

-----------------------------------------------------------------
deployment 64bit win

Prebacivanje svih binarya u deploy direktorijum(to podrazumeva exe i dll fajlove)
izvrsavanje sledecih komandi
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe TimeSimulator.dll
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe DBConnection.dll
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe POVI.exe
i kopiranje gore pomenutog dll u isti folder