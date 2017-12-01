use Vigor;

insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Administrator', 'Administrator', '5555', 'administrator', 'adm', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Komercijalista', 'Komercijalista', '5555', 'komercijalista', 'kom', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Lastis', 'Dizajner Lastis', '5555', 'dizajnerlastis', 'dil', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Tkanje', 'Dizajner Tkanje', '5555', 'dizajnertkanje', 'dit', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Dizajner Stampa', 'Dizajner Stampa', '5555', 'dizajnerstampa', 'dis', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Magacioner', 'Magacioner', '5555', 'magacioner', 'mag', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('SefProizvodnje', 'SefProizvodnje', '5555', 'sefproizvodnje', 'spr', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('SefSmene', 'SefSmene', '5555', 'sefsmene', 'ssm', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Knjigovodjaf', 'Knjigovodjaf', '5555', 'knjigovodjaf', 'kfa', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('Narucilac', 'Narucilac', '5555', 'narucilac', 'nar', true);

insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje1', 'RadnikProizvodnje1', '0000', 'radnikproizvodnje1', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje2', 'RadnikProizvodnje2', '0000', 'radnikproizvodnje2', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje3', 'RadnikProizvodnje3', '0000', 'radnikproizvodnje3', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje4', 'RadnikProizvodnje4', '0000', 'radnikproizvodnje4', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje5', 'RadnikProizvodnje5', '0000', 'radnikproizvodnje5', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje6', 'RadnikProizvodnje6', '0000', 'radnikproizvodnje6', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje7', 'RadnikProizvodnje7', '0000', 'radnikproizvodnje7', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje8', 'RadnikProizvodnje8', '0000', 'radnikproizvodnje8', 'pro', true);
insert into Radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('RadnikProizvodnje9', 'RadnikProizvodnje9', '0000', 'radnikproizvodnje9', 'pro', true);

#Tipovi zadatka
insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Lastis', 			False); #1
insert into TipoviZadatka (Naziv, Faktura) values ('Snovanje', 					False);	#2
insert into TipoviZadatka (Naziv, Faktura) values ('Tkanje Lastis', 			True);	#3
insert into TipoviZadatka (Naziv, Faktura) values ('Peglanje Lastis', 			False);	#4
insert into TipoviZadatka (Naziv, Faktura) values ('Namotavanje', 				False);	#5
insert into TipoviZadatka (Naziv, Faktura) values ('Kontrola Pakovanje', 		False);	#6
insert into TipoviZadatka (Naziv, Faktura) values ('Faktura', 					False);	#7
insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Tkanje', 			False);	#8
insert into TipoviZadatka (Naziv, Faktura) values ('Magacin Zaduzivanje', 		False);	#9
insert into TipoviZadatka (Naziv, Faktura) values ('Tkacnica', 					False);	#10
insert into TipoviZadatka (Naziv, Faktura) values ('Magacin Razduzivanje', 		True);	#11
insert into TipoviZadatka (Naziv, Faktura) values ('Peglanje Tkanje', 			False);	#12
insert into TipoviZadatka (Naziv, Faktura) values ('Secenje-Savijanje', 		False);	#13
insert into TipoviZadatka (Naziv, Faktura) values ('Lepljenje', 				True);	#14
insert into TipoviZadatka (Naziv, Faktura) values ('Laser', 					False);	#15
insert into TipoviZadatka (Naziv, Faktura) values ('Endlanje', 					False);	#16
insert into TipoviZadatka (Naziv, Faktura) values ('Sivenje', 					False);	#17
insert into TipoviZadatka (Naziv, Faktura) values ('Dizajn Stampa', 			False);	#18
insert into TipoviZadatka (Naziv, Faktura) values ('Stampa', 					True);	#19
insert into TipoviZadatka (Naziv, Faktura) values ('Transfer', 					False);	#20
insert into TipoviZadatka (Naziv, Faktura) values ('Blindruk', 					False);	#21
insert into TipoviZadatka (Naziv, Faktura) values ('Narucivanje materijalia', 	False);	#22
insert into TipoviZadatka (Naziv, Faktura) values ('Motanje', 					False);	#23
insert into TipoviZadatka (Naziv, Faktura) values ('Navezivanje', 				False);	#24

#Masine
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Virtuelna', True,  '07:00:00', '15:00:00', 6);	#1
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MBJ1', 		False, '00:00:00', '00:00:00', 7);	#2
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MBJ2', 		False, '00:00:00', '00:00:00', 7);	#3
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('NF', 		False, '00:00:00', '00:00:00', 7);	#4
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MVC BELI',	False, '00:00:00', '00:00:00', 7); 	#5
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MVC CRNI', 	False, '00:00:00', '00:00:00', 7);	#6
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MUGRIP1', 	False, '00:00:00', '00:00:00', 7);	#7
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MUGRIP2', 	False, '00:00:00', '00:00:00', 7);	#8
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MUGRIP3', 	False, '00:00:00', '00:00:00', 7);	#9
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MUGRIP4', 	False, '00:00:00', '00:00:00', 7);	#10
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MUGRIP5', 	False, '00:00:00', '00:00:00', 7);	#11
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('SAR', 		False, '07:00:00', '15:00:00', 6);	#12
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MONTY', 	False, '07:00:00', '15:00:00', 6);	#13
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('WILLY', 	False, '07:00:00', '15:00:00', 6);	#14
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('V.PRESA', 	False, '07:00:00', '15:00:00', 6);	#15
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('WILLY1', 	False, '00:00:00', '00:00:00', 7);	#16
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('WILLY2', 	False, '00:00:00', '00:00:00', 7);	#17
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('WILLY3', 	False, '00:00:00', '00:00:00', 7);	#18
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('MULLER;', 	False, '00:00:00', '00:00:00', 7);	#19
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Laser 1', 	False, '07:00:00', '15:00:00', 6);	#20
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Laser 2', 	False, '07:00:00', '15:00:00', 6);	#21
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Laser 3', 	False, '07:00:00', '15:00:00', 6);	#22
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Laser 4', 	False, '07:00:00', '15:00:00', 6);	#23
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('EPSON1', 	False, '07:00:00', '15:00:00', 6);	#24
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('EPSON2', 	False, '07:00:00', '15:00:00', 6);	#25
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('EPSON3', 	False, '07:00:00', '15:00:00', 6);	#26
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('CDS', 		False, '07:00:00', '15:00:00', 6);	#27
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('PAXAR', 	False, '07:00:00', '15:00:00', 6);	#28
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('PRESA1', 	False, '07:00:00', '15:00:00', 6);	#29
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('PRESA2', 	False, '07:00:00', '15:00:00', 6);	#30
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Motalica', 	False, '07:00:00', '15:00:00', 6);	#31
insert into Masina (Naziv, Virtuelna, VremePocetka, VremeKraja, RadniDani) values ('Endlarica', False, '07:00:00', '15:00:00', 6);	#32

#Masina-TipoviZadataka
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 1 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 2 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (2 , 3 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (3 , 3 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (4 , 3 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 4 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 5 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 6 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 7 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 8 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 9 );
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (5 , 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (6 , 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (7 , 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (8 , 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (9 , 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (10, 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (11, 10);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 11);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (12, 11);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (13, 12);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (14, 12);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (15, 12);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (16, 13);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (17, 13);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (18, 13);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (19, 13);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 14);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (20, 15);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (21, 15);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (22, 15);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (23, 15);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (32, 16);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 17);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 18);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (24, 19);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (25, 19);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (26, 19);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (27, 19);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (28, 19);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (13, 20);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (12, 20);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (29, 20);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (30, 20);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 21);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (1 , 22);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (31, 23);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (2 , 24);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (3 , 24);
insert into MasinaTipoviZadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (4 , 24);