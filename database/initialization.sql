use vigor;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Milos', 'Pajkic', '1234', 'milos.pajkic', 'adm', true);

insert into klijent (Ime) values ('Znam d.o.o');

insert into narudzbina (idKlijent, Cena, Opis, Naslov, Stanje, Rok) values (1, 55.20, 'Ovo je opis!', 'Ovo je naslov!', 'nov', '2013-08-05 18:19:03');

insert into nalog (idNarudzbina, idKlijent, BrojNaloga) values (1, 1, 100);

insert into TipoviZadatka (Naziv) values ('Dizajn');
insert into TipoviZadatka (Naziv) values ('Magacin');
insert into TipoviZadatka (Naziv) values ('Lastis');
insert into TipoviZadatka (Naziv) values ('Stampa');
insert into TipoviZadatka (Naziv) values ('Tkanje');
insert into TipoviZadatka (Naziv) values ('Secenje');
insert into TipoviZadatka (Naziv) values ('Savijanje');
insert into TipoviZadatka (Naziv) values ('Peglanje');
insert into TipoviZadatka (Naziv) values ('Lepljenje');
insert into TipoviZadatka (Naziv) values ('Laser');
insert into TipoviZadatka (Naziv) values ('Sivenje');