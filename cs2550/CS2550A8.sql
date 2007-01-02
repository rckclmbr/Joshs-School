Joshua Braegger
CS2550 Assignment 8
October 19, 2006

INSERT INTO Client VALUES ('CR6', 'Aline', 'Stewart', '0141-848-1825', 'Flat', 350);
INSERT INTO Client VALUES ('CR6', 'Mary', 'Tregear', '01224-196720', 'Flat', 600);
INSERT INTO Client VALUES ('CR62', 'Mike', 'Ritchie', '01475-392178', 'House', 750);
INSERT INTO Client VALUES ('CR76', 'John', 'Kay', '0207-774-5632', 'Flat', 425);

INSERT INTO Branch  VALUES ('B002', '56 Clover Dr', 'London', 'NW10 6EU');
INSERT INTO Branch  VALUES ('B003', '163 Main St', 'Glasgow', 'G11 9QX');
INSERT INTO Branch  VALUES ('B004', '32 Manse Rd', 'Bristol', 'B599 1NZ');
INSERT INTO Branch  VALUES ('B005', '22 Deer Rd', 'London', 'SW1 4EH');
INSERT INTO Branch  VALUES ('B007', '16 Argyll St', 'Aberdeen', 'AB2 3SU');

INSERT INTO Staff  VALUES ('SA9', 'Mary', 'Howe', 'Assistant', 'F', '19700219', 9000, 'B007');
INSERT INTO Staff  VALUES ('SG14', 'David', 'Ford', 'Superviso', 'M', '19580324', 18000, 'B003');
INSERT INTO Staff  VALUES ('SG37', 'Ann', 'Beech', 'Assistant', 'F', '19601110',12000, 'B003');
INSERT INTO Staff  VALUES ('SG5', 'Susan', 'Brand', 'Manager', 'F', '19400603', 24000, 'B003');
INSERT INTO Staff  VALUES ('SL21', 'John', 'White', 'Manager', 'M', '19451001', 30000, 'B005');
INSERT INTO Staff  VALUES ('SL41', 'Julie', 'Lee', 'Assistant', 'F', '19650613',9000, 'B005');

INSERT INTO PropertyForRent  VALUES ('PA14', '16 Holhead', 'Aberdeen', 'AB7 5SU', 'House', 6, 650, 'CO46', 'SA9', 'B007');
INSERT INTO PropertyForRent  VALUES ('PG16', '5 Novar Dr', 'Glasgow', 'G12 9AX', 'Flat', 4, 450, 'CO93', 'SG14', 'B003');
INSERT INTO PropertyForRent  VALUES ('PG21', '18 Dale Rd', 'Glasgow', 'G12', 'House', 5, 600, 'CO87', 'SG37', 'B003');
INSERT INTO PropertyForRent  VALUES ('PG36', '2 Manor Rd', 'Glasgow', 'G32 4QX', 'Flat', 3, 375, 'CO93', 'SG37', 'B003');
INSERT INTO PropertyForRent  VALUES ('PG4', '6 Lawrence St', 'Glasgow', 'G11 9QX', 'Flat', 3, 350, 'CO40', '', 'B003');
INSERT INTO PropertyForRent  VALUES ('PL94', '6 Argyll St', 'London', 'NW2', 'Flat',  4, 400, 'CO87', 'SL41', 'B005');

INSERT INTO Viewing  values ('CR56', 'PA14', '20010524', 'too small');
INSERT INTO Viewing  values ('CR56', 'PG36', '20010428', '');
INSERT INTO Viewing  values ('CR56', 'PG4', '20010526', '');
INSERT INTO Viewing  values ('CR62', 'PA14', '20010514', 'no dining room');
INSERT INTO Viewing  values ('CR76', 'PG4', '20010420', 'too remote');

INSERT INTO Registration  values ('CR56', 'B003', 'SG37', '20000411');
INSERT INTO Registration  values ('CR62', 'B007', 'SA9', '20000307');
INSERT INTO Registration  values ('CR74', 'B003', 'SG37', '19991116');
INSERT INTO Registration  values ('CR76', 'B005', 'SL41', '20010102');