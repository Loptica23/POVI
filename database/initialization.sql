use vigor;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Administrator', 'Administrator', '5555', 'administrator', 'adm', true);
CREATE USER 'administrator'@'%'  IDENTIFIED BY '1234';
GRANT ALL PRIVILEGES ON *.* TO 'administrator'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Komercijalista', 'Komercijalista', '5555', 'komercijalista', 'kom', true);
CREATE USER 'komercijalista'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'komercijalista'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner', 'Dizajner', '5555', 'dizajner', 'diz', true);
CREATE USER 'dizajner'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'dizajner'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Magacioner', 'Magacioner', '5555', 'magacioner', 'mag', true);
CREATE USER 'magacioner'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'magacioner'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('SefProizvodnje', 'SefProizvodnje', '5555', 'sefproizvodnje', 'spr', true);
CREATE USER 'sefproizvodnje'@'%'  IDENTIFIED BY '5555';
GRANT ALL PRIVILEGES ON *.* TO 'sefproizvodnje'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;


insert into klijent (Ime) values ('Znam d.o.o');

insert into narudzbina (idKlijent, Cena, Opis, Naslov, Rok) values (1, 55.20, 'Ovo je opis!', 'Ovo je naslov!', '2013-08-05 18:19:03');

insert into nalog (idNarudzbina, idKlijent, BrojNaloga, Stanje) values (1, 1, 100, 'nov');

insert into TipoviZadatka (Naziv) values ('Dizajn'); 			#1
insert into TipoviZadatka (Naziv) values ('Magacin');			#2
insert into TipoviZadatka (Naziv) values ('Planiranje');		#3
insert into TipoviZadatka (Naziv) values ('Lastis');			#4
insert into TipoviZadatka (Naziv) values ('Stampa');			#5
insert into TipoviZadatka (Naziv) values ('Tkanje');			#6
insert into TipoviZadatka (Naziv) values ('Secenje');			#7
insert into TipoviZadatka (Naziv) values ('Savijanje');			#8
insert into TipoviZadatka (Naziv) values ('Peglanje');			#9
insert into TipoviZadatka (Naziv) values ('Lepljenje');			#10
insert into TipoviZadatka (Naziv) values ('Laser');				#11
insert into TipoviZadatka (Naziv) values ('Sivenje');			#12

insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za planiranje 1', 3);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za lastis 1', 4);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za stampu 1', 5);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za tkanje 1', 6);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za secenje 1', 7);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za savijanje 1', 8);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za peglanje 1', 9);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za lepljenje 1', 10);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za laser 1', 11);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za sivenje 1', 12);

insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za planiranje 2', 3);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za lastis 2', 4);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za stampu 2', 5);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za tkanje 2', 6);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za secenje 2', 7);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za savijanje 2', 8);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za peglanje 2', 9);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za lepljenje 2', 10);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za laser 2', 11);
insert into Masina (Naziv, TipoviZadatka_idTipoviZadatka) values ('Masina za sivenje 2', 12);