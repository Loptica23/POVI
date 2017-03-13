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

insert into TipoviZadatka (Naziv) values ('Dizajn');
insert into TipoviZadatka (Naziv) values ('Magacin');
insert into TipoviZadatka (Naziv) values ('Planiranje');
insert into TipoviZadatka (Naziv) values ('Lastis');
insert into TipoviZadatka (Naziv) values ('Stampa');
insert into TipoviZadatka (Naziv) values ('Tkanje');
insert into TipoviZadatka (Naziv) values ('Secenje');
insert into TipoviZadatka (Naziv) values ('Savijanje');
insert into TipoviZadatka (Naziv) values ('Peglanje');
insert into TipoviZadatka (Naziv) values ('Lepljenje');
insert into TipoviZadatka (Naziv) values ('Laser');
insert into TipoviZadatka (Naziv) values ('Sivenje');