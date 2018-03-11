CREATE TABLE IF NOT EXISTS stations_type (
  name varchar(25) PRIMARY KEY NOT NULL
);

CREATE TABLE IF NOT EXISTS stations_state (
  name varchar(25) PRIMARY KEY NOT NULL
);

REPLACE INTO stations_type values ('BIKE'), ('BIKE-ELECTRIC');

CREATE TABLE IF NOT EXISTS stations (
  id int(11) NOT NULL DEFAULT '0',
  latitude float DEFAULT NULL,
  longitude float DEFAULT NULL,
  streetName char(250) DEFAULT NULL,
  streetNumber int(11) DEFAULT NULL,
  altitude int(11) DEFAULT NULL,
  type varchar(25) NOT NULL DEFAULT ('BIKE') REFERENCES stations_type(name),
  PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS station_status (
  id_station int(11) NOT NULL DEFAULT '-1',
  bikes int(11) DEFAULT NULL,
  slots int(11) DEFAULT NULL,
  state varchar(25) NOT NULL DEFAULT ('OPN') REFERENCES stations_state(name),
  updateDT datetime NOT NULL,
  PRIMARY KEY (id_station,updateDT),
  CONSTRAINT FK_station_status_stations FOREIGN KEY (id_station) REFERENCES stations (id)
);

REPLACE INTO stations (id, latitude, longitude, streetName, streetNumber, altitude, type) VALUES
        (1, 41.398, 2.18004, 'Gran Via Corts Catalanes', 760, 21, 'BIKE'),
        (2, 41.3955, 2.17706, 'Roger de Flor/ Gran Vía', 126, 21, 'BIKE'),
        (3, 41.3937, 2.18114, 'Ali Bei', 44, 21, 'BIKE'),
        (4, 41.3935, 2.18149, 'Ribes', 13, 21, 'BIKE'),
        (5, 41.3911, 2.18022, 'Pg Lluís Companys', 11, 16, 'BIKE'),
        (6, 41.3913, 2.18061, 'Pg Lluís Companys', 18, 16, 'BIKE'),
        (7, 41.3889, 2.18325, 'Pg Lluís Companys', 1, 16, 'BIKE'),
        (8, 41.3891, 2.18357, 'Pg Lluís Companys', 2, 11, 'BIKE'),
        (9, 41.385, 2.18525, 'Marquès de l''Argentera', 17, 11, 'BIKE'),
        (10, 41.385, 2.18417, 'Carrer Comerç', 27, 11, 'BIKE'),
        (11, 41.3817, 2.19391, 'Trelawny', 2, 1, 'BIKE'),
        (12, 41.3845, 2.19568, 'Pg Marítim Barceloneta', 23, 0, 'BIKE'),
        (13, 41.3869, 2.19576, 'Avinguda Litoral', 16, 1, 'BIKE'),
        (14, 41.3848, 2.18507, 'Avinguda del Marques Argentera', 19, 11, 'BIKE'),
        (15, 41.3952, 2.17076, 'Girona', 74, 42, 'BIKE'),
        (16, 41.3983, 2.18671, 'Av. Meridiana', 47, 18, 'BIKE'),
        (17, 41.3982, 2.18671, 'Av. Meridiana', 47, 18, 'BIKE'),
        (18, 41.4059, 2.17414, 'Rosselló', 412, 49, 'BIKE'),
        (19, 41.4033, 2.17073, 'Rosselló', 354, 49, 'BIKE'),
        (20, 41.4102, 2.17576, 'Cartagena', 308, 59, 'BIKE'),
        (21, 41.4109, 2.17402, 'Sant Antoni Maria Claret', 214, 59, 'BIKE'),
        (22, 41.4021, 2.17521, 'Sardenya', 296, 28, 'BIKE'),
        (23, 41.3925, 2.17181, 'Bruc', 45, 42, 'BIKE'),
        (24, 41.4, 2.18032, 'Marina', 185, 21, 'BIKE'),
        (25, 41.3952, 2.16829, 'Bruc', 102, 42, 'BIKE'),
        (26, 41.407, 2.18198, 'Dos Maig', 230, 28, 'BIKE'),
        (27, 41.3969, 2.16441, 'Provença', 322, 49, 'BIKE'),
        (28, 41.4073, 2.17087, 'Marina', 311, 49, 'BIKE'),
        (29, 41.4011, 2.17008, 'Provença', 388, 50, 'BIKE'),
        (30, 41.402, 2.18229, 'Diagonal', 231, 28, 'BIKE'),
        (31, 41.3748, 2.18895, 'Plaça del Mar', 72, 1, 'BIKE'),
        (32, 41.3737, 2.18893, 'Plaça del Mar', 1, 1, 'BIKE'),
        (33, 41.3769, 2.19077, 'Baluart', 58, 1, 'BIKE'),
        (34, 41.3871, 2.17525, 'Sant Pere Més Alt', 4, 16, 'BIKE'),
        (35, 41.4136, 2.22115, 'Sant Ramon de Penyafort', 1, 1, 'BIKE'),
        (36, 41.3852, 2.1768, 'Catedral', 6, 16, 'BIKE'),
        (37, 41.3812, 2.18189, 'Pl. Antonio López', 0, 5, 'BIKE'),
        (38, 41.3811, 2.1864, 'Pl. Pau Vila', 0, 1, 'BIKE'),
        (39, 41.381, 2.18658, 'Pl. Pau Vila', 0, 1, 'BIKE'),
        (40, 41.3822, 2.18628, 'Doctor Aiguader', 2, 1, 'BIKE'),
        (41, 41.3793, 2.18991, 'Pl. Poeta Boscà/Atlàntida', 0, 1, 'BIKE'),
        (42, 41.4045, 2.18988, 'Ciutat de Granada', 168, 18, 'BIKE'),
        (43, 41.4054, 2.18712, 'Av Meridiana', 80, 18, 'BIKE'),
        (44, 41.4022, 2.18714, 'Av Meridiana', 66, 18, 'BIKE'),
        (45, 41.392, 2.19043, 'Marina', 65, 18, 'BIKE'),
        (46, 41.3884, 2.193, 'Ramon trias Fargas', 19, 1, 'BIKE'),
        (47, 41.3891, 2.1921, 'Ramon Trias Fargas', 0, 1, 'BIKE'),
        (48, 41.3953, 2.18708, 'Meridiana', 40, 18, 'BIKE'),
        (49, 41.3911, 2.19646, 'Rosa Sensat en front', 20, 1, 'BIKE'),
        (50, 41.375, 2.17035, 'Av. Paral.lel', 54, 1, 'BIKE'),
        (51, 41.3841, 2.16902, 'Pl. Vicenç Martorell', 0, 32, 'BIKE'),
        (53, 41.3852, 2.17388, 'Pl. Carles Pi i Sunyer', 0, 32, 'BIKE'),
        (54, 41.3776, 2.17059, 'Sant Oleguer', 2, 24, 'BIKE'),
        (55, 41.3812, 2.1735, 'La Rambla', 80, 24, 'BIKE'),
        (56, 41.377, 2.17583, 'Portal de Santa Madrona', 2, 5, 'BIKE'),
        (57, 41.3768, 2.17709, 'La Rambla', 2, 5, 'BIKE'),
        (58, 41.3828, 2.16715, 'Plaça dels Àngels', 1, 24, 'BIKE'),
        (59, 41.3828, 2.1672, 'Plaça dels Àngels', 2, 24, 'BIKE'),
        (60, 41.3903, 2.16424, 'Rambla Catalunya', 47, 41, 'BIKE'),
        (61, 41.3901, 2.16495, 'Rambla Catalunya', 42, 41, 'BIKE'),
        (62, 41.3871, 2.16886, 'Pl. Catalunya', 5, 32, 'BIKE'),
        (63, 41.3864, 2.16942, 'Pl. Catalunya', 7, 32, 'BIKE'),
        (64, 41.3875, 2.16905, 'Pl. Catalunya', 0, 32, 'BIKE'),
        (65, 41.3877, 2.16959, 'Pl. Catalunya', 0, 32, 'BIKE'),
        (66, 41.3891, 2.16793, 'Gran Via', 609, 32, 'BIKE'),
        (67, 41.385, 2.14584, 'Rocafort', 214, 51, 'BIKE'),
        (68, 41.3954, 2.15736, 'Rambla Catalunya', 133, 59, 'BIKE'),
        (69, 41.3868, 2.19569, 'Avda. Litoral', 0, 1, 'BIKE'),
        (70, 41.3813, 2.16179, 'Villarroel', 2, 35, 'BIKE'),
        (71, 41.3819, 2.16297, 'Floridablanca', 145, 35, 'BIKE'),
        (72, 41.3927, 2.15881, 'Provença', 215, 55, 'BIKE'),
        (73, 41.3928, 2.15579, 'Enric Granados', 99, 59, 'BIKE'),
        (74, 41.3894, 2.1431, 'Josep Tarradellas', 129, 51, 'BIKE'),
        (75, 41.3851, 2.14287, 'Josep Tarradellas', 58, 51, 'BIKE'),
        (76, 41.3918, 2.15312, 'Còrsega', 216, 45, 'BIKE'),
        (78, 41.3856, 2.16338, 'Pl. Universitat', 0, 41, 'BIKE'),
        (79, 41.3855, 2.16333, 'Pl. Universitat', 0, 41, 'BIKE'),
        (80, 41.3897, 2.16, 'Enric Granados', 35, 41, 'BIKE'),
        (81, 41.3789, 2.14917, 'Vilamarí davant', 61, 44, 'BIKE'),
        (82, 41.379, 2.1538, 'Rocafort', 72, 40, 'BIKE'),
        (83, 41.3841, 2.15365, 'Comte Borrell', 177, 45, 'BIKE'),
        (84, 41.3834, 2.15758, 'Diputació', 152, 35, 'BIKE'),
        (85, 41.3751, 2.15905, 'Paral·lel', 146, 35, 'BIKE'),
        (86, 41.3754, 2.163, 'Viladomat', 2, 35, 'BIKE'),
        (87, 41.3832, 2.14851, 'Mallorca', 41, 44, 'BIKE'),
        (88, 41.3935, 2.15076, 'Londres', 101, 59, 'BIKE'),
        (89, 41.388, 2.15017, 'Rosselló', 101, 45, 'BIKE'),
        (90, 41.3883, 2.15083, 'Rosselló', 108, 45, 'BIKE'),
        (91, 41.3805, 2.1584, 'Comte Borrell', 119, 35, 'BIKE'),
        (92, 41.3939, 2.16024, 'Provença', 241, 50, 'BIKE'),
        (93, 41.3755, 2.14979, 'Gran Via', 375, 40, 'BIKE'),
        (94, 41.3756, 2.14989, 'Gran Via', 375, 40, 'BIKE'),
        (95, 41.3764, 2.14773, 'Tarragona', 103, 44, 'BIKE'),
        (96, 41.3742, 2.14815, 'Gran Via', 361, 61, 'BIKE'),
        (97, 41.3781, 2.14539, 'Tarragona', 141, 44, 'BIKE'),
        (98, 41.3807, 2.1417, 'Viriat', 45, 44, 'BIKE'),
        (99, 41.3806, 2.14155, 'Viriat', 53, 44, 'BIKE'),
        (100, 41.3791, 2.14409, 'Tarragona', 159, 44, 'BIKE'),
        (101, 41.3924, 2.14321, 'Av. Diagonal', 602, 69, 'BIKE'),
        (102, 41.3922, 2.14213, 'Av. Diagonal', 612, 69, 'BIKE'),
        (103, 41.4099, 2.18822, 'Aragó', 629, 17, 'BIKE'),
        (104, 41.4108, 2.18736, 'C/València', 621, 17, 'BIKE'),
        (105, 41.3891, 2.17342, 'PL. Urquinaona', 9, 32, 'BIKE'),
        (106, 41.4056, 2.16232, 'Pl. Joanic', 0, 59, 'BIKE'),
        (107, 41.3983, 2.15313, 'Travessera de Gracia', 92, 59, 'BIKE'),
        (108, 41.4023, 2.16496, 'Indústria', 10, 59, 'BIKE'),
        (109, 41.391, 2.14737, 'C/ Londres', 53, 51, 'BIKE'),
        (110, 41.3856, 2.15481, 'Avda. Roma', 117, 45, 'BIKE'),
        (111, 41.3812, 2.15308, 'Calabria', 134, 40, 'BIKE'),
        (112, 41.3776, 2.15725, 'Floridablanca', 49, 40, 'BIKE'),
        (113, 41.3788, 2.1608, 'Comte Borrell', 60, 35, 'BIKE'),
        (114, 41.3768, 2.17304, 'Pl. Jean Genet', 1, 24, 'BIKE'),
        (115, 41.3838, 2.18424, 'Marqués d''Argentera', 3, 1, 'BIKE'),
        (116, 41.3837, 2.19141, 'Salvat Papasseit', 72, 11, 'BIKE'),
        (117, 41.3907, 2.19702, 'Rosa Sensat', 12, 1, 'BIKE'),
        (118, 41.3924, 2.18776, 'Sardenya', 59, 18, 'BIKE'),
        (119, 41.3966, 2.1828, 'Ausiàs March', 122, 21, 'BIKE'),
        (120, 41.4047, 2.17652, 'Lepant', 278, 28, 'BIKE'),
        (121, 41.4063, 2.17869, 'Castillejos', 258, 28, 'BIKE'),
        (122, 41.4054, 2.16624, 'Nàpols', 344, 59, 'BIKE'),
        (123, 41.3974, 2.1678, 'Girona', 126, 42, 'BIKE'),
        (124, 41.3703, 2.18781, 'Passeig Joan de Borbó', 0, 5, 'BIKE'),
        (125, 41.3844, 2.19559, 'Passeig Maritim', 31, 1, 'BIKE'),
        (126, 41.3806, 2.18224, 'Passeig de Colom', 0, 5, 'BIKE'),
        (127, 41.4123, 2.19142, 'Aragó', 661, 17, 'BIKE'),
        (128, 41.4156, 2.19581, 'Rambla Guipúscoa', 43, 13, 'BIKE'),
        (129, 41.3771, 2.16124, 'Manso', 46, 35, 'BIKE'),
        (130, 41.4199, 2.20157, 'Rambla Guipúscoa', 103, 9, 'BIKE'),
        (131, 41.4228, 2.20604, 'Rambla Guipúscoa', 158, 9, 'BIKE'),
        (132, 41.4084, 2.19217, 'Pl. Valentí Amirall', 0, 13, 'BIKE'),
        (133, 41.4074, 2.19282, 'Gran Vía', 902, 16, 'BIKE'),
        (134, 41.4113, 2.19813, 'Gran Via', 990, 13, 'BIKE'),
        (135, 41.4119, 2.19794, 'Gran Vía', 981, 13, 'BIKE'),
        (136, 41.4142, 2.20173, 'Gran Vía', 1062, 9, 'BIKE'),
        (137, 41.4148, 2.20154, 'Gran Vía, 1041/ Selva de Mar', 1041, 9, 'BIKE'),
        (138, 41.417, 2.2054, 'Gran Vía', 1118, 9, 'BIKE'),
        (139, 41.418, 2.20602, 'Gran Vía', 1131, 9, 'BIKE'),
        (140, 41.3806, 2.15614, 'Viladomat', 122, 41, 'BIKE'),
        (141, 41.409, 2.1949, 'Gran Via', 940, 13, 'BIKE'),
        (142, 41.4005, 2.19251, 'Sancho de Ávila', 104, 16, 'BIKE'),
        (143, 41.4032, 2.19606, 'Sancho de Ávila', 170, 16, 'BIKE'),
        (144, 41.4056, 2.19764, 'Castella', 28, 16, 'BIKE'),
        (145, 41.4098, 2.2029, 'Pere IV', 301, 9, 'BIKE'),
        (146, 41.4125, 2.20484, 'Pere IV', 383, 9, 'BIKE'),
        (147, 41.416, 2.21266, 'Rambla Prim', 79, 5, 'BIKE'),
        (148, 41.3784, 2.16332, 'Ronda Sant Pau', 79, 79, 'BIKE'),
        (149, 41.3959, 2.19296, 'Pujades', 0, 11, 'BIKE'),
        (150, 41.4065, 2.20311, 'Espronceda', 124, 10, 'BIKE'),
        (151, 41.4006, 2.19719, 'Pallars', 462, 6, 'BIKE'),
        (152, 41.3993, 2.19742, 'Pujades', 121, 11, 'BIKE'),
        (153, 41.4018, 2.20077, 'Pujades', 173, 10, 'BIKE'),
        (154, 41.4025, 2.20166, 'Pujades', 191, 10, 'BIKE'),
        (155, 41.407, 2.2076, 'Pujades', 311, 10, 'BIKE'),
        (156, 41.4089, 2.20855, 'Diagonal', 82, 5, 'BIKE'),
        (157, 41.4116, 2.21634, 'C/Llull', 396, 5, 'BIKE'),
        (158, 41.4117, 2.21855, 'Rambla de Prim', 19, 1, 'BIKE'),
        (159, 41.4109, 2.21638, 'Avda. Diagonal', 26, 5, 'BIKE'),
        (160, 41.411, 2.21938, 'Avda. d''Eduard Maristany', 1, 1, 'BIKE'),
        (161, 41.395, 2.19631, 'Ramon Turro', 91, 11, 'BIKE'),
        (162, 41.4039, 2.20844, 'Ramon Turro', 292, 0, 'BIKE'),
        (163, 41.3942, 2.20077, 'Avda. Icaria', 202, 11, 'BIKE'),
        (164, 41.4119, 2.17804, 'Independència', 379, 33, 'BIKE'),
        (165, 41.3992, 2.20425, 'Carrer del Doctor Trueta', 221, 0, 'BIKE'),
        (166, 41.401, 2.20788, 'Passeig de Taulat', 116, 10, 'BIKE'),
        (167, 41.4034, 2.21117, 'Passeig de Taulat', 188, 0, 'BIKE'),
        (168, 41.4052, 2.21352, 'Passeig de Taulat', 238, 0, 'BIKE'),
        (169, 41.3899, 2.20005, 'Avda. Litoral', 40, 0, 'BIKE'),
        (170, 41.3897, 2.19993, 'Avda. Litoral', 40, 1, 'BIKE'),
        (171, 41.392, 2.2037, 'Passeig Marítim de la Nova Icària', 83, 0, 'BIKE'),
        (172, 41.3918, 2.20344, 'Passeig Marítim de la Nova Icària', 83, 0, 'BIKE'),
        (173, 41.398, 2.20898, 'Avda. Litoral', 84, 0, 'BIKE'),
        (174, 41.4006, 2.21046, 'Passeig de Garcia Fària', 21, 0, 'BIKE'),
        (175, 41.4067, 2.20956, 'Llull / Provençals', 309, 10, 'BIKE'),
        (176, 41.4025, 2.21264, 'Passeig de Garcia Fària', 37, 0, 'BIKE'),
        (177, 41.4111, 2.18112, 'Rosselló', 557, 0, 'BIKE'),
        (178, 41.4054, 2.21621, 'Passeig de Garcia Fària', 85, 0, 'BIKE'),
        (179, 41.3635, 2.13677, 'Pg. Zona Franca', 244, 48, 'BIKE'),
        (180, 41.3678, 2.13926, 'Gran Via', 181, 50, 'BIKE'),
        (181, 41.3677, 2.13911, 'Gran Via', 180, 50, 'BIKE'),
        (182, 41.3715, 2.14388, 'Gran Via', 273, 61, 'BIKE'),
        (183, 41.3723, 2.14188, 'Gavà', 1, 61, 'BIKE'),
        (184, 41.3675, 2.13409, 'Quetzal', 22, 50, 'BIKE'),
        (185, 41.3705, 2.13899, 'Gavà', 81, 50, 'BIKE'),
        (186, 41.3756, 2.14381, 'Consell de Cent', 6, 44, 'BIKE'),
        (187, 41.3769, 2.16981, 'Carrer de Sant Pau', 89, 24, 'BIKE'),
        (188, 41.3755, 2.13554, 'Pl. Sants (Ps. S. Antoni)', 0, 45, 'BIKE'),
        (189, 41.3969, 2.16616, 'Bruc', 130, 50, 'BIKE'),
        (190, 41.3961, 2.2078, 'Avinguda Litoral', 72, 0, 'BIKE'),
        (191, 41.3826, 2.14909, 'Rocafort', 167, 44, 'BIKE'),
        (192, 41.3798, 2.1328, 'Joan Güell', 85, 46, 'BIKE'),
        (193, 41.3813, 2.12891, 'Figols', 1, 46, 'BIKE'),
        (194, 41.3823, 2.13165, 'Joan Güell', 139, 46, 'BIKE'),
        (195, 41.3823, 2.13619, 'Comtes de Bell-lloc', 148, 45, 'BIKE'),
        (196, 41.3845, 2.1347, 'Comte Bell-lloch', 216, 57, 'BIKE'),
        (197, 41.387, 2.14096, 'Entença', 227, 57, 'BIKE'),
        (198, 41.3851, 2.13328, 'Vallespir', 198, 60, 'BIKE'),
        (199, 41.3818, 2.12693, 'Mejía Lequerica', 2, 46, 'BIKE'),
        (200, 41.3838, 2.13127, 'Can bruixa', 1, 60, 'BIKE'),
        (201, 41.3885, 2.13583, 'Déu i Mata', 56, 57, 'BIKE'),
        (202, 41.3853, 2.12874, 'Carrer de les Corts', 20, 60, 'BIKE'),
        (203, 41.3887, 2.1285, 'Avda. Diagonal', 664, 60, 'BIKE'),
        (204, 41.388, 2.12559, 'Avda. Diagonal', 668, 60, 'BIKE'),
        (205, 41.3875, 2.13084, 'Europa', 25, 60, 'BIKE'),
        (206, 41.3898, 2.13284, 'Avda. Diagonal', 650, 60, 'BIKE'),
        (207, 41.3908, 2.13666, 'Avda. Diagonal', 634, 57, 'BIKE'),
        (208, 41.3915, 2.13912, 'Avda. Diagonal', 630, 57, 'BIKE'),
        (209, 41.3858, 2.161, 'Diputació', 200, 41, 'BIKE'),
        (210, 41.3745, 2.14236, 'Vilardell', 18, 50, 'BIKE'),
        (211, 41.3988, 2.19029, 'Sancho de Ávila', 60, 18, 'BIKE'),
        (212, 41.3922, 2.13032, 'Numancia', 212, 82, 'BIKE'),
        (213, 41.3925, 2.13559, 'Doctor Fleming', 9, 79, 'BIKE'),
        (214, 41.394, 2.13496, 'Doctor Fleming', 19, 79, 'BIKE'),
        (215, 41.3945, 2.13864, 'Carrer de Francesc Pérez Cabrero', 6, 79, 'BIKE'),
        (216, 41.3968, 2.14453, 'Madrazo', 131, 69, 'BIKE'),
        (217, 41.3985, 2.14392, 'Rector Ubach', 24, 69, 'BIKE'),
        (218, 41.4041, 2.1832, 'Consell de Cent', 566, 28, 'BIKE'),
        (219, 41.3978, 2.14758, 'Carre Laforja', 74, 69, 'BIKE'),
        (220, 41.3962, 2.15148, 'Tuset', 19, 59, 'BIKE'),
        (221, 41.4025, 2.15252, 'Gran de Gràcia', 155, 71, 'BIKE'),
        (222, 41.4012, 2.15748, 'Carrer del Canó', 1, 71, 'BIKE'),
        (223, 41.3983, 2.15986, 'Carrer de Bonavista', 14, 50, 'BIKE'),
        (224, 41.4001, 2.16644, 'Bailèn', 158, 50, 'BIKE'),
        (225, 41.3848, 2.15057, 'Mallorca', 84, 44, 'BIKE'),
        (226, 41.4035, 2.1611, 'Montmany', 1, 59, 'BIKE'),
        (227, 41.4078, 2.15868, 'Torrent de Les Flors', 102, 59, 'BIKE'),
        (228, 41.4069, 2.15579, 'Pl. Del Nord', 5, 71, 'BIKE'),
        (229, 41.4051, 2.15687, 'Carrer de la Santacreu', 2, 71, 'BIKE'),
        (230, 41.406, 2.15163, 'C. De Nil Fabra', 16, 71, 'BIKE'),
        (231, 41.4091, 2.16327, 'C. Del Secretari Coloma', 59, 87, 'BIKE'),
        (232, 41.3735, 2.171, 'Vilà i Vilà', 45, 1, 'BIKE'),
        (233, 41.372, 2.16687, 'Nou de la Rambla', 164, 1, 'BIKE'),
        (234, 41.3715, 2.16217, 'Passeig de l''Exposició', 30, 44, 'BIKE'),
        (235, 41.3738, 2.16163, 'Elkano', 64, 44, 'BIKE'),
        (236, 41.3722, 2.15655, 'Carrer de la França Xica', 42, 67, 'BIKE'),
        (237, 41.3729, 2.15447, 'Rius i Taulet', 4, 67, 'BIKE'),
        (238, 41.4157, 2.19099, 'Espronceda', 298, 17, 'BIKE'),
        (239, 41.4173, 2.18471, 'Indústria', 344, 18, 'BIKE'),
        (240, 41.4178, 2.18756, 'Josep Estivill', 32, 18, 'BIKE'),
        (241, 41.4199, 2.18123, 'Pl. Maragall', 22, 37, 'BIKE'),
        (242, 41.4245, 2.17728, 'Ramon Albó', 1, 37, 'BIKE'),
        (243, 41.4239, 2.1813, 'Alenxadre Galí', 1, 37, 'BIKE'),
        (244, 41.4269, 2.17851, 'Felip II', 214, 47, 'BIKE'),
        (246, 41.4226, 2.18573, 'Juan de Garay', 116, 18, 'BIKE'),
        (247, 41.4228, 2.18517, 'Olesa', 43, 18, 'BIKE'),
        (248, 41.4182, 2.19037, 'Palència', 31, 18, 'BIKE'),
        (249, 41.4252, 2.189, 'Açores', 1, 18, 'BIKE'),
        (250, 41.4262, 2.19013, 'Portugal', 12, 27, 'BIKE'),
        (251, 41.4254, 2.18523, 'Cardenal Tedeschini', 13, 27, 'BIKE'),
        (252, 41.4282, 2.1934, 'Carrer del Pare Manyanet', 23, 18, 'BIKE'),
        (253, 41.43, 2.19182, 'Onze de Setembre', 37, 18, 'BIKE'),
        (254, 41.4303, 2.18958, 'Gran de Sant Andreu', 93, 27, 'BIKE'),
        (255, 41.4312, 2.18585, 'Irlanda', 11, 27, 'BIKE'),
        (256, 41.436, 2.18952, 'Malats', 28, 25, 'BIKE'),
        (257, 41.4339, 2.18961, 'Sant Adrià', 2, 25, 'BIKE'),
        (258, 41.442, 2.1891, 'Carrer de Palomar', 6, 24, 'BIKE'),
        (259, 41.4391, 2.18582, 'Carrer de Bartrina', 14, 25, 'BIKE'),
        (260, 41.4362, 2.19295, 'Plaça de l''Estació', 6, 19, 'BIKE'),
        (261, 41.3822, 2.16064, 'Villarroel', 39, 35, 'BIKE'),
        (262, 41.3798, 2.1525, 'Rocafort', 103, 40, 'BIKE'),
        (263, 41.4377, 2.19139, 'C/Joan Torras', 28, 25, 'BIKE'),
        (264, 41.4399, 2.19703, 'República Dominicana', 25, 19, 'BIKE'),
        (265, 41.3857, 2.15837, 'Casanovas, 71', 82, 41, 'BIKE'),
        (266, 41.4268, 2.18424, 'Concepció Arenal', 176, 37, 'BIKE'),
        (267, 41.4434, 2.19062, 'Passeig Torras i Bages', 129, 24, 'BIKE'),
        (268, 41.4457, 2.19289, 'Fernando Pessoa', 72, 23, 'BIKE'),
        (269, 41.4481, 2.19283, 'Via Barcino', 121, 23, 'BIKE'),
        (270, 41.4499, 2.19098, 'Pl. de la Trinitat, 5-7 / amb Mare de Déu de Lorda', 5, 24, 'BIKE'),
        (271, 41.4509, 2.19267, 'Via Barcino', 71, 18, 'BIKE'),
        (272, 41.4326, 2.18429, 'Concepció Arenal', 281, 27, 'BIKE'),
        (273, 41.4304, 2.18338, 'Avda. Meridiana', 404, 27, 'BIKE'),
        (274, 41.4301, 2.18473, 'Rambla Fabra i Puig', 67, 27, 'BIKE'),
        (275, 41.4307, 2.18222, 'Rio de Janeiro', 3, 27, 'BIKE'),
        (276, 41.4122, 2.16527, 'Plaça Alfons X el Savi / Ronda del Guinardó', 0, 87, 'BIKE'),
        (277, 41.4083, 2.16905, 'Travessera de Gràcia', 328, 59, 'BIKE'),
        (278, 41.4115, 2.17207, 'Rosalia de Castro', 41, 59, 'BIKE'),
        (279, 41.417, 2.17468, 'Ronda Guinardo', 143, 74, 'BIKE'),
        (280, 41.4128, 2.17853, 'Industria', 241, 33, 'BIKE'),
        (281, 41.4194, 2.17652, 'Ronda Guinardo', 179, 37, 'BIKE'),
        (282, 41.4276, 2.16602, 'Font d''en Fargas', 1, 88, 'BIKE'),
        (283, 41.4297, 2.16157, 'Carrer Fulton', 1, 88, 'BIKE'),
        (284, 41.3895, 2.13145, 'Ada. Diagonal', 652, 60, 'BIKE'),
        (285, 41.4367, 2.18606, 'Malats', 98, 25, 'BIKE'),
        (286, 41.4031, 2.19143, 'Bolívia', 76, 18, 'BIKE'),
        (287, 41.3892, 2.16811, 'Gran Via', 632, 32, 'BIKE'),
        (288, 41.4296, 2.17449, 'Pl. Virrei Amat', 0, 63, 'BIKE'),
        (289, 41.4168, 2.19102, 'Múrcia', 64, 18, 'BIKE'),
        (290, 41.4371, 2.17405, 'Plaça dels Jardins d''Alfàbia', 1, 61, 'BIKE'),
        (291, 41.427, 2.1746, 'Subirats', 5, 63, 'BIKE'),
        (292, 41.43, 2.17197, 'Amilcar', 1, 63, 'BIKE'),
        (293, 41.4287, 2.16456, 'Petrarca', 44, 88, 'BIKE'),
        (294, 41.4364, 2.17068, 'Seu del Districte (Nou Barris)', 0, 61, 'BIKE'),
        (295, 41.4335, 2.1715, 'Sant Iscle', 60, 61, 'BIKE'),
        (296, 41.4365, 2.18388, 'Carrer de Rosselló i Porcel', 1, 25, 'BIKE'),
        (297, 41.4389, 2.17682, 'Carrer Turó Blau', 1, 45, 'BIKE'),
        (298, 41.4346, 2.18175, 'Andreu Nin', 22, 45, 'BIKE'),
        (299, 41.434, 2.1752, 'Carrer de l''Escultor Ordóñez', 55, 45, 'BIKE'),
        (300, 41.4316, 2.17691, 'Carrer de Maladeta', 1, 47, 'BIKE'),
        (301, 41.4371, 2.16964, 'Marie Curie', 8, 61, 'BIKE'),
        (302, 41.3907, 2.11162, 'Cavallers', 41, 73, 'BIKE'),
        (303, 41.3933, 2.11508, 'Cavallers', 67, 101, 'BIKE'),
        (304, 41.3902, 2.12103, 'Manuel Girona', 7, 63, 'BIKE'),
        (305, 41.3875, 2.12364, 'Diagonal', 680, 63, 'BIKE'),
        (306, 41.3855, 2.12291, 'Doctor Salvador Cardenal', 7, 63, 'BIKE'),
        (307, 41.3791, 2.1135, 'Pintor Ribalta', 0, 50, 'BIKE'),
        (308, 41.3768, 2.11386, 'Cardenal Reig', 11, 50, 'BIKE'),
        (309, 41.3767, 2.11697, 'Sant Ramón Nonat', 26, 47, 'BIKE'),
        (310, 41.3812, 2.11908, 'Josep Samitier', 0, 47, 'BIKE'),
        (311, 41.3782, 2.12183, 'Travessera de les Corts', 58, 47, 'BIKE'),
        (312, 41.3798, 2.12659, 'Felipe de Paz', 2, 46, 'BIKE'),
        (313, 41.3745, 2.13098, 'Rambla Badal', 184, 39, 'BIKE'),
        (314, 41.3784, 2.12974, 'Rambla del Brasil', 44, 46, 'BIKE'),
        (315, 41.4156, 2.18197, 'Guinardó', 32, 33, 'BIKE'),
        (316, 41.4222, 2.19832, 'Cantàbria', 55, 13, 'BIKE'),
        (317, 41.4256, 2.20069, 'Rambla Prim', 256, 12, 'BIKE'),
        (318, 41.4141, 2.17084, 'Ronda Guinardo', 83, 59, 'BIKE'),
        (319, 41.3947, 2.14516, 'Amigó', 23, 69, 'BIKE'),
        (320, 41.4034, 2.14588, 'Francolí', 21, 86, 'BIKE'),
        (321, 41.404, 2.14365, 'Carrer de Pádua', 98, 86, 'BIKE'),
        (322, 41.401, 2.13907, 'Santaló', 165, 106, 'BIKE'),
        (323, 41.398, 2.13872, 'Vallmajor', 13, 79, 'BIKE'),
        (324, 41.3969, 2.13626, 'Reina Victoria', 31, 79, 'BIKE'),
        (325, 41.3949, 2.13033, 'Alt de Gironella', 13, 82, 'BIKE'),
        (326, 41.407, 2.13774, 'Castanyer', 16, 106, 'BIKE'),
        (327, 41.405, 2.13453, 'Reus', 23, 106, 'BIKE'),
        (328, 41.4029, 2.13427, 'Artesa de Segre', 2, 106, 'BIKE'),
        (329, 41.4029, 2.12854, 'Carrer de les Escoles Pies', 99, 130, 'BIKE'),
        (330, 41.4006, 2.13066, 'Doctor Carulla', 44, 130, 'BIKE'),
        (331, 41.3971, 2.12801, 'Castellnou', 65, 82, 'BIKE'),
        (332, 41.3998, 2.12809, 'Doctor Roux', 86, 82, 'BIKE'),
        (333, 41.3956, 2.12511, 'Passatge de Senillosa', 3, 82, 'BIKE'),
        (334, 41.4007, 2.12327, 'Via Augusta', 348, 138, 'BIKE'),
        (335, 41.3936, 2.12322, 'Santa Amèlia', 2, 96, 'BIKE'),
        (336, 41.3953, 2.12097, 'Caponata', 10, 96, 'BIKE'),
        (337, 41.3987, 2.12042, 'Carme Karr', 12, 96, 'BIKE'),
        (338, 41.3976, 2.11951, 'Avinguda de J.Foix', 63, 96, 'BIKE'),
        (339, 41.4026, 2.2037, 'Bilbao', 51, 10, 'BIKE'),
        (340, 41.4361, 2.20463, 'Sant Adrià', 113, 28, 'BIKE'),
        (341, 41.4342, 2.20589, 'Passeig Enric Sanchís', 33, 28, 'BIKE'),
        (342, 41.4035, 2.1937, 'Roc Boronat', 134, 18, 'BIKE'),
        (343, 41.4389, 2.1996, 'Campana de la Maquinista', 0, 19, 'BIKE'),
        (344, 41.4431, 2.19954, 'Ciutat d''Asunción', 73, 23, 'BIKE'),
        (345, 41.3631, 2.13977, 'Pl. Teresa de Claramunt', 0, 48, 'BIKE'),
        (346, 41.3607, 2.13913, 'Carrer de la Foneria', 33, 48, 'BIKE'),
        (347, 41.3583, 2.1434, 'Mare de Déu dels Ports', 235, 34, 'BIKE'),
        (348, 41.3571, 2.14156, 'Jardins de Can Ferrero', 0, 13, 'BIKE'),
        (349, 41.3573, 2.13717, 'Carrer de l''Energia', 2, 13, 'BIKE'),
        (350, 41.3918, 2.14812, 'Villarroel', 208, 69, 'BIKE'),
        (351, 41.3621, 2.13564, 'Jane Addams', 26, 48, 'BIKE'),
        (352, 41.3633, 2.13414, 'Radi', 10, 48, 'BIKE'),
        (353, 41.3754, 2.12319, 'Munné', 6, 47, 'BIKE'),
        (354, 41.3759, 2.13008, 'Rambla del Brasil', 5, 46, 'BIKE'),
        (355, 41.3721, 2.12859, 'Carreras i Candi', 89, 39, 'BIKE'),
        (356, 41.4111, 2.16107, 'Balcells', 48, 87, 'BIKE'),
        (357, 41.4105, 2.1581, 'Cardener', 82, 104, 'BIKE'),
        (358, 41.3872, 2.17927, 'Gombau', 24, 16, 'BIKE'),
        (359, 41.39, 2.17757, 'Méndez Núñez', 16, 16, 'BIKE'),
        (360, 41.3952, 2.17298, 'Bailén', 62, 42, 'BIKE'),
        (361, 41.3763, 2.17855, 'Passeig de Colom', 0, 5, 'BIKE'),
        (362, 41.397, 2.17057, 'Bailén', 100, 42, 'BIKE'),
        (363, 41.3908, 2.1744, 'Bruc', 20, 32, 'BIKE'),
        (364, 41.3932, 2.16343, 'Passeig de Gràcia', 61, 50, 'BIKE'),
        (365, 41.3875, 2.14702, 'Viladomat', 244, 51, 'BIKE'),
        (366, 41.393, 2.14358, 'Pau Casals', 1, 69, 'BIKE'),
        (367, 41.3851, 2.13733, 'Sentmenat', 39, 57, 'BIKE'),
        (368, 41.3968, 2.17571, 'Diputació', 350, 21, 'BIKE'),
        (369, 41.4008, 2.1786, 'Consell de Cent', 513, 28, 'BIKE'),
        (370, 41.4037, 2.17299, 'Sardenya', 234, 49, 'BIKE'),
        (371, 41.404, 2.18126, 'Carrer dels Enamorats', 49, 28, 'BIKE'),
        (372, 41.4, 2.18451, 'Padilla', 159, 18, 'BIKE'),
        (373, 41.3751, 2.16131, 'Av. Paral.lel', 132, 35, 'BIKE'),
        (374, 41.395, 2.16123, 'Passeig de Gràcia', 89, 50, 'BIKE'),
        (375, 41.3722, 2.1807, 'World Trade Center', 0, 1, 'BIKE'),
        (376, 41.3717, 2.1803, 'World Trade Center', 0, 1, 'BIKE'),
        (377, 41.3775, 2.18374, 'Pl. Ictíneo', 0, 1, 'BIKE'),
        (378, 41.3785, 2.17672, 'Pl.Joaquim Xira i Palau', 1, 5, 'BIKE'),
        (379, 41.3817, 2.17731, 'Pl. Sant Miquel', 4, 5, 'BIKE'),
        (380, 41.3855, 2.17425, 'Duran i Bas', 2, 32, 'BIKE'),
        (381, 41.3816, 2.16767, 'Agustí Duran i Sanpere', 10, 24, 'BIKE'),
        (382, 41.4039, 2.20419, 'Lope de Vega', 79, 10, 'BIKE'),
        (384, 41.3807, 2.14679, 'Vilamarí', 85, 44, 'BIKE'),
        (385, 41.388, 2.15527, 'Casanova', 119, 45, 'BIKE'),
        (386, 41.3751, 2.15685, 'Av.Paral.lel', 164, 40, 'BIKE'),
        (387, 41.3958, 2.17878, 'Nàpols', 125, 21, 'BIKE'),
        (388, 41.3806, 2.16742, 'Riera Alta', 6, 24, 'BIKE'),
        (389, 41.3874, 2.1875, 'Recinte Parc de la Ciutadella', 0, 11, 'BIKE'),
        (390, 41.387, 2.18195, 'Comerç', 36, 16, 'BIKE'),
        (391, 41.4229, 2.1912, 'Sagrera', 74, 18, 'BIKE'),
        (392, 41.3907, 2.19054, 'Ramon Turró', 5, 11, 'BIKE'),
        (393, 41.4022, 2.19765, 'Llacuna', 86, 16, 'BIKE'),
        (394, 41.3873, 2.16305, 'Diputació', 226, 41, 'BIKE'),
        (395, 41.386, 2.17021, 'Pl. Catalunya', 22, 32, 'BIKE'),
        (396, 41.389, 2.19684, 'Joan Miró', 2, 1, 'BIKE'),
        (397, 41.3889, 2.19933, 'Av. Del Litoral', 24, 1, 'BIKE'),
        (398, 41.381, 2.1935, 'Passeig Marítim de la Barceloneta', 0, 0, 'BIKE'),
        (400, 41.3696, 2.18802, 'Moll Oriental', 0, 5, 'BIKE'),
        (401, 41.3812, 2.18184, 'Pl. Antonio López (Via Laietana) annexa a la 37', 0, 5, 'BIKE'),
        (402, 41.3806, 2.18212, 'Passeig de Colom', 0, 5, 'BIKE'),
        (404, 41.3654, 2.13309, 'Juan Gris', 28, 16, 'BIKE'),
        (405, 41.3855, 2.152, 'Comte Borrell', 198, 45, 'BIKE'),
        (406, 41.3865, 2.1646, 'Gran Via de Les Corts Catalanes', 592, 41, 'BIKE'),
        (407, 41.3885, 2.19284, 'Ramon Trias Fargas', 19, 1, 'BIKE'),
        (408, 41.3886, 2.19231, 'Villena, 11', 11, 1, 'BIKE'),
        (409, 41.3924, 2.19242, 'Joan d''Àustria', 50, 11, 'BIKE'),
        (410, 41.3764, 2.17871, 'Passeig de Colom, s/n', 0, 5, 'BIKE'),
        (412, 41.389, 2.17267, 'Pl. Urquinaona', 3, 32, 'BIKE'),
        (413, 41.3935, 2.17072, 'Bruc', 66, 42, 'BIKE'),
        (414, 41.3937, 2.17645, 'Casp', 67, 21, 'BIKE'),
        (415, 41.3794, 2.16892, 'Rambla del Raval', 13, 24, 'BIKE'),
        (416, 41.3781, 2.16965, 'Rambla del Raval', 20, 24, 'BIKE'),
        (418, 41.3909, 2.18025, 'Passeig de Lluís Companys', 0, 16, 'BIKE'),
        (419, 41.3913, 2.18083, 'Passeig de Lluís Companys', 0, 16, 'BIKE'),
        (420, 41.3742, 2.14808, 'Gran Via', 361, 61, 'BIKE'),
        (421, 41.3778, 2.13923, 'Plaça de Joan Peiró', 0, 45, 'BIKE'),
        (423, 41.4202, 2.18953, 'Carrer d''Hondures', 32, 18, 'BIKE'),
        (424, 41.3796, 2.19266, 'Passeig Marítim de la Barceloneta, devant del 5-7', 5, 0, 'BIKE'),
        (425, 41.3765, 2.1749, 'Carrer de Cervelló', 5, 24, 'BIKE'),
        (426, 41.3983, 2.18302, 'Carrer de Ribes', 59, 21, 'BIKE'),
        (427, 41.3753, 2.16801, 'Carrer de Sant Pau', 119, 24, 'BIKE'),
        (428, 41.3984, 2.19626, 'Carrer Pujades', 103, 11, 'BIKE'),
        (451, 41.3745, 2.15967, '(PK) C/ JAUME FABRA', 12, 35, 'BIKE-ELECTRIC'),
        (452, 41.3987, 2.18629, '(PK) C/ PADILLA', 159, 18, 'BIKE-ELECTRIC'),
        (453, 41.3796, 2.16204, '(PK) C/ URGELL', 14, 35, 'BIKE-ELECTRIC'),
        (454, 41.4024, 2.20413, '(PK) C/ BILBAO', 24, 18, 'BIKE-ELECTRIC'),
        (455, 41.389, 2.19917, '(PK) AV. DEL LITORAL', 34, 1, 'BIKE-ELECTRIC'),
        (456, 41.3899, 2.12858, '(PK) C/ DE FLOS I CALCAT', 2, 60, 'BIKE-ELECTRIC'),
        (457, 41.4015, 2.13423, '(PK) C/ DE JOSEP BALARÍ', 2, 106, 'BIKE-ELECTRIC'),
        (458, 41.3843, 2.12209, '(PK) AV. JOAN XXIII', 0, 60, 'BIKE-ELECTRIC'),
        (459, 41.3939, 2.18144, '(PK) C/ D''ALÍ BEI', 54, 21, 'BIKE-ELECTRIC'),
        (460, 41.3857, 2.17732, '(PK) AV. FRANCESC CAMBÓ', 10, 16, 'BIKE-ELECTRIC'),
        (461, 41.3841, 2.14274, '(PK) AV. JOSEP TARRADELLAS', 46, 51, 'BIKE-ELECTRIC'),
        (462, 41.3901, 2.14322, '(PK) AV. JOSEP TARRADELLAS', 139, 51, 'BIKE-ELECTRIC'),
        (463, 41.3752, 2.1698, '(PK) C/ DE L´ABAT SAFONT', 2, 1, 'BIKE-ELECTRIC'),
        (464, 41.4277, 2.1772, '(PK) C/ DE RAMON ALBÓ, 77s', 77, 42, 'BIKE-ELECTRIC'),
        (465, 41.4054, 2.14246, '(PK) RDA. DEL GENERAL MITRE', 203, 76, 'BIKE-ELECTRIC'),
        (466, 41.4157, 2.18068, '(PK) PG. MARAGALL', 54, 33, 'BIKE-ELECTRIC'),
        (467, 41.3858, 2.19414, '(PK) C/ DEL DR. AIGUADER', 0, 1, 'BIKE-ELECTRIC'),
        (468, 41.4302, 2.18797, '(PK) C/ DE LES MONGES', 2, 27, 'BIKE-ELECTRIC'),
        (469, 41.4044, 2.19713, '(PK) RAMBLA DEL POBLENOU', 130, 32, 'BIKE-ELECTRIC'),
        (470, 41.3979, 2.12541, '(PK) C/ CARDENAL DE SENTMENAT', 8, 82, 'BIKE-ELECTRIC'),
        (471, 41.3942, 2.11497, '(PK) C/ MARQUÈS DE MULHACÉN', 51, 101, 'BIKE-ELECTRIC'),
        (472, 41.4074, 2.15134, '(PK) C/ DEL TORRENT DE L´OLLA', 221, 72, 'BIKE-ELECTRIC'),
        (473, 41.4045, 2.21498, '(PK) PG. DE GARCIA FÀRIA', 71, 1, 'BIKE-ELECTRIC'),
        (474, 41.3989, 2.15367, '(PK) PL. GAL·LA PLACÍDIA', 2, 59, 'BIKE-ELECTRIC'),
        (475, 41.4085, 2.16939, '(PK) C/ DE LA MARINA', 345, 59, 'BIKE-ELECTRIC'),
        (476, 41.4025, 2.19042, '(PK) C/ DE BADAJOZ', 168, 18, 'BIKE-ELECTRIC'),
        (477, 41.3766, 2.17875, '(PK) PG. DE COLOM', 1, 1, 'BIKE-ELECTRIC'),
        (478, 41.3798, 2.1891, '(PK) C/ DEL BALUARD', 27, 1, 'BIKE-ELECTRIC'),
        (479, 41.3873, 2.19659, '(PK) C/ DE LA MARINA', 0, 1, 'BIKE-ELECTRIC'),
        (480, 41.3815, 2.17024, '(PK) C/ DELS FLORISTES DE LA RAMBLA', 8, 24, 'BIKE-ELECTRIC'),
        (481, 41.383, 2.15034, '(PK) C/ DE VALÈNCIA', 77, 44, 'BIKE-ELECTRIC'),
        (482, 41.4131, 2.22123, '(PK) PL. D''ERNEST LLUCH I MARTIN', 0, 1, 'BIKE-ELECTRIC'),
        (483, 41.4018, 2.16075, '(PK) C/ DE SIRACUSA', 0, 58, 'BIKE-ELECTRIC'),
        (484, 41.3881, 2.167, '(PK) RAMBLA CATALUNYA - RDA. UNIVERSITAT', 0, 40, 'BIKE-ELECTRIC'),
        (485, 41.3899, 2.17324, '(PK) PLAÇA URQUINAONA', 0, 32, 'BIKE-ELECTRIC'),
        (486, 41.3969, 2.15944, '(PK) PG. DE GRÀCIA - DIAGONAL', 0, 50, 'BIKE-ELECTRIC'),
        (487, 41.3892, 2.154, '(PK) PL. DE FERRER I CAJIGAL', 0, 45, 'BIKE-ELECTRIC'),
        (488, 41.424, 2.18439, '(PK) C/ DE CIENFUEGOS', 13, 18, 'BIKE-ELECTRIC'),
        (489, 41.4095, 2.18828, '(PK) PLAÇA CANONGE RODÓ', 0, 40, 'BIKE-ELECTRIC'),
        (490, 41.397, 2.19772, '(PK) C/ DE BADAJOZ, 58', 58, 11, 'BIKE-ELECTRIC'),
        (491, 41.3725, 2.12898, '(PK) C/ DE CARRERAS I CANDI', 65, 61, 'BIKE-ELECTRIC'),
        (492, 41.3942, 2.17528, 'PL. DE TETUAN', 0, 21, 'BIKE-ELECTRIC'),
        (493, 41.3819, 2.17709, 'PL. SANT MIQUEL', 4, 8, 'BIKE-ELECTRIC'),
        (494, 41.3895, 2.16536, 'RAMBLA CATALUNYA', 31, 41, 'BIKE-ELECTRIC'),
        (495, 41.3772, 2.14928, 'C/ DIPUTACIÓ - TARRAGONA', 0, 45, 'BIKE-ELECTRIC'),
        (496, 41.4049, 2.17514, 'C/ DE PROVENÇA', 445, 21, 'BIKE-ELECTRIC');
