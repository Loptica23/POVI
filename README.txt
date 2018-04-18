Ovo je moj test projekat;

------------------------------------------------------------------
Bildanje na win64

Kopirao sam C:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.dll 
u C:\Qt\5.8\msvc2013_64\bin

-----------------------------------------------------------------
Bildanje ubuntu 64

1. Potrebno je instalirati lgl.. Komanda: sudo apt-get install libgl1-mesa-dev
- sada se aplikacija bilda ali nece da se nakaci na bazu.... izbacuje gresku driver not loaded! Ako radi onda je sve ok..
2. radis ldd qsqlmysql.so 
- ldd izbaci koje biblioteke mu fale.. Meni fali libmysqlclient18 pa sam ga stavio u repozitorijum
3. sudo dpkg -i libmysqlclient18_5.6.25-0ubuntu1_amd64.deb - sa ovom komandom se instalira so koji fali iz tacke 2.

-----------------------------------------------------------------
deployment 64bit win

Prebacivanje svih binarya u deploy direktorijum(to podrazumeva exe i dll fajlove)
izvrsavanje sledecih komandi
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe TimeSimulator.dll
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe DBConnection.dll
C:\Qt\5.8\msvc2015_64\bin\windeployqt.exe POVI.exe
i kopiranje gore pomenutog dll u isti folder
-----------------------------------------------------------------
Deployment ubuntu64

Prebacis sve binary fajlove u jedan dir. Tu stavis i linuxdeployqt fajl, koji skines sa gita.
Startujes linuxqtdeploy i kao parametar prosledis samo exe (glavni binary) i sacekas da on prikupi sve zavisnosti.
Sada sve svoje .so fajlove prebacis u lib direktorijum i mozes da startujes aplikaciju.

--mala izmena (new_feature); 

-- jos jedna izmena
