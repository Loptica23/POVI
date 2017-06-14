use vigor;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Administrator', 'Administrator', '5555', 'administrator', 'adm', true);
CREATE USER 'administrator'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'administrator'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Komercijalista', 'Komercijalista', '5555', 'komercijalista', 'kom', true);
CREATE USER 'komercijalista'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'komercijalista'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Lastis', 'Dizajner Lastis', '5555', 'dizajnerlastis', 'dil', true);
CREATE USER 'dizajnerlastis'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'dizajnerlastis'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Tkanje', 'Dizajner Tkanje', '5555', 'dizajnertkanje', 'dit', true);
CREATE USER 'dizajnertkanje'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'dizajnertkanje'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Stampa', 'Dizajner Stampa', '5555', 'dizajnerstampa', 'dis', true);
CREATE USER 'dizajnerstampa'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'dizajnerstampa'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Magacioner', 'Magacioner', '5555', 'magacioner', 'mag', true);
CREATE USER 'magacioner'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'magacioner'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('SefProizvodnje', 'SefProizvodnje', '5555', 'sefproizvodnje', 'spr', true);
CREATE USER 'sefproizvodnje'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'sefproizvodnje'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('SefSmene', 'SefSmene', '5555', 'sefsmene', 'ssm', true);
CREATE USER 'sefsmene'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'sefsmene'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje1', 'RadnikProizvodnje1', '0000', 'radnikproizvodnje1', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje2', 'RadnikProizvodnje2', '0000', 'radnikproizvodnje2', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje3', 'RadnikProizvodnje3', '0000', 'radnikproizvodnje3', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje4', 'RadnikProizvodnje4', '0000', 'radnikproizvodnje4', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje5', 'RadnikProizvodnje5', '0000', 'radnikproizvodnje5', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje6', 'RadnikProizvodnje6', '0000', 'radnikproizvodnje6', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje7', 'RadnikProizvodnje7', '0000', 'radnikproizvodnje7', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje8', 'RadnikProizvodnje8', '0000', 'radnikproizvodnje8', 'pro', true);
insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje9', 'RadnikProizvodnje9', '0000', 'radnikproizvodnje9', 'pro', true);

insert into klijent (Ime) values ('Znam d.o.o');

insert into narudzbina (idKlijent, Cena, Opis, Naslov, Rok) values (1, 55.20, 'Ovo je opis!', 'Ovo je naslov!', '2013-08-05 18:19:03');

insert into nalog (idNarudzbina, idKlijent, BrojNaloga, Stanje) values (1, 1, 100, 'nov');

insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Lastis', False); 			#1
insert into TipoviZadatka (Naziv, Faktura) values ('Snovanje', False);					#2
insert into TipoviZadatka (Naziv, Faktura) values ('Tkanje Lastis', True);				#3
insert into TipoviZadatka (Naziv, Faktura) values ('Peglanje Lastis', False);			#4
insert into TipoviZadatka (Naziv, Faktura) values ('Namotavanje', False);				#5
insert into TipoviZadatka (Naziv, Faktura) values ('Kontrola Pakovanje', False);		#6
insert into TipoviZadatka (Naziv, Faktura) values ('Faktura', False);					#7
insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Tkanje', False);				#8
insert into TipoviZadatka (Naziv, Faktura) values ('Magacin Zaduzivanje', False);		#9
insert into TipoviZadatka (Naziv, Faktura) values ('Tkacnica', False);					#10
insert into TipoviZadatka (Naziv, Faktura) values ('Magacuin Razduzivanje', True);		#11
insert into TipoviZadatka (Naziv, Faktura) values ('Peglanje Tkanje', False);			#12
insert into TipoviZadatka (Naziv, Faktura) values ('Secenje-Savijanje', False);			#13
insert into TipoviZadatka (Naziv, Faktura) values ('Lepljenje', True);					#14
insert into TipoviZadatka (Naziv, Faktura) values ('Laser', False);						#15
insert into TipoviZadatka (Naziv, Faktura) values ('Endlanje', False);					#16
insert into TipoviZadatka (Naziv, Faktura) values ('Sivenje', False);					#17
insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Stampa', False);				#18
insert into TipoviZadatka (Naziv, Faktura) values ('Stampa', True);						#19
insert into TipoviZadatka (Naziv, Faktura) values ('Transfer', False);					#20
insert into TipoviZadatka (Naziv, Faktura) values ('Blindruk', False);					#21

#1
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Dizajn Lastis', 1, True);
#2
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Snovanje', 2, True);
#3
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MBJ1', 3, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MBJ2', 3, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('NF', 3, False);
#4
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Peglanje Lastis', 4, True);
#5
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Namotavanje', 5, True);
#6
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Kontrola Pakovanje', 6, True);
#7
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Faktura', 7, True);
#8
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Dizajn Tkanje', 8, True);
#9
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Magacin Zaduzivanje', 9, True);
#10
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MVC BELI', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MVC CRNI', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MUGRIP1', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MUGRIP2', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MUGRIP3', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MUGRIP4', 10, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MUGRIP5', 10, False);
#11
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Magacin Razduzivanje', 11, True);
#12
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('SAR', 12, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MONTY', 12, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('WILLY', 12, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('V.PRESA', 12, False);
#13
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('WILLY1', 13, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('WILLY2; WILLY3; MULLER;', 13, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('WILLY3; MULLER;', 13, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MULLER;', 13, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Secenje-Savijanje', 13, True);
#14
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Lepljenje', 14, True);
#15
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Laser 1', 15, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Laser 2', 15, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Laser 3', 15, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Laser 4', 15, False);
#16
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Endlanje', 16, True);
#17
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Sivenje', 17, True);
#18
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Dizajn Stampa', 18, True);
#19
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('EPSON1', 19, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('EPSON2', 19, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('EPSON3', 19, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('CDS', 19, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('PAXAR', 19, False);
#20
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('MONTY', 20, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('SAR', 20, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('PRESA1', 20, False);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('PRESA2', 20, False);
#21
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka, Virtuelna) values ('Rucno Blindruk', 21, True);
