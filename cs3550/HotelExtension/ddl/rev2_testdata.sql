/* Josh Braegger CS3550
 Hotel Events Test Data Script */

USE Braegger_HotelEvents

INSERT INTO Event(EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice) VALUES ('Three Kings Performing', '2008-03-03', 100, 10, 75.50);
INSERT INTO Event(EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice) VALUES ('Super Concert', '2008-08-03', 200, 24, 25.50);

INSERT INTO Stage(StageName, StageLocation) VALUES ('Stage 1', 'Outside');
INSERT INTO Stage(StageName, StageLocation) VALUES ('Back Stage', 'Near the kitchen');
INSERT INTO Stage(StageName, StageLocation) VALUES ('Front Stage', 'Near the entrance');

INSERT INTO Performer(PerformerName, PerformerWebsite) VALUES ('Three Kings Performers', 'http://3kingsperformers.com');
INSERT INTO Performer(PerformerName, PerformerWebsite) VALUES ('Travelling Yodelers', 'http://travelingyodelers.com');
INSERT INTO Performer(PerformerName, PerformerWebsite) VALUES ('Musak Singers', 'http://musaksingers.com');
INSERT INTO Performer(PerformerName, PerformerWebsite) VALUES ('The Nutcracker', 'http://nutcracker.com');

INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (1, 1, 1, 'May not be able to make it');
INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (2, 2, 1, NULL);
INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (3, 2, 2, 'Keep these guys near the back...');

INSERT INTO StaffType(StaffTypeDescription) VALUES ('Host');
INSERT INTO StaffType(StaffTypeDescription) VALUES ('Garbage Man');
INSERT INTO StaffType(StaffTypeDescription) VALUES ('Security');

INSERT INTO EventStaff(StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (1, 'George', 'Boy', '2007-06-06');
INSERT INTO EventStaff(StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (3, 'Bird', 'Lady', '2007-07-17');
INSERT INTO EventStaff(StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (3, 'Jackson', 'Michael', '2007-05-21');
INSERT INTO EventStaff(StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (2, 'Hilton', 'Paris', '2008-01-12');

INSERT INTO StaffClock(EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (1, 1, '2008-03-03', '2008-03-03');
INSERT INTO StaffClock(EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (1, 2, '2008-03-03', '2008-03-03');
INSERT INTO StaffClock(EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (2, 2, '2008-08-03', '2008-08-03');
INSERT INTO StaffClock(EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (2, 3, '2008-08-03', '2008-08-03');
INSERT INTO StaffClock(EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (2, 4, '2008-08-03', '2008-08-03');

INSERT INTO Viewer (ViewerFirstName, ViewerLastName) VALUES ('Bruce', 'Willis');
INSERT INTO Viewer (ViewerFirstName, ViewerLastName) VALUES ('Britney', 'Spears');
INSERT INTO Viewer (ViewerFirstName, ViewerLastName) VALUES ('Daniel', 'Radcliffe');
INSERT INTO Viewer (ViewerFirstName, ViewerLastName) VALUES ('Harry', 'Potter');

INSERT INTO Ticket(EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (1, 3, 75.50, '2007-05-15', NULL);
INSERT INTO Ticket(EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (1, 4, 75.50, '2007-05-08', '2007-06-08');
INSERT INTO Ticket(EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (1, 1, 60.50, '2007-09-09', NULL);
INSERT INTO Ticket(EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (2, 1, 25.50, '2007-09-09', NULL);

SELECT * FROM Booking
SELECT * FROM Event
SELECT * FROM EventStaff
SELECT * FROM Performer
SELECT * FROM StaffClock
SELECT * FROM StaffType
SELECT * FROM Stage
SELECT * FROM Ticket
SELECT * FROM Viewer