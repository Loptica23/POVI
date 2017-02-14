use vigor;

insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Milos', 'Pajkic', '1234', 'milos.pajkic', 'adm', true)

insert into klijent (Ime) values ('Znam d.o.o')

insert into narudzbina (idKlijent, Cena, Opis, Naslov, Stanje, Rok) values (1, 55.20, 'Ovo je opis!', 'Ovo je naslov!', 'nov', '2013-08-23 18:19:03')