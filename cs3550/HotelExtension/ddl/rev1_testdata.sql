USE Braegger_HotelEvents

INSERT INTO Event(EventID, EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice) VALUES (1, 'Three Kings Performing', '2008-03-03', 100, 10, 75.50);
INSERT INTO Event(EventID, EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice) VALUES (2, 'Super Concert', '2008-08-03', 200, 24, 25.50);

INSERT INTO Stage(StageID, StageName, StageLocation) VALUES (1, 'Stage 1', 'Outside');
INSERT INTO Stage(StageID, StageName, StageLocation) VALUES (2, 'Back Stage', 'Near the kitchen');
INSERT INTO Stage(StageID, StageName, StageLocation) VALUES (3, 'Front Stage', 'Near the entrance');

INSERT INTO Performer(PerformerID, PerformerName, PerformerWebsite) VALUES (1, 'Three Kings Performers', 'http://3kingsperformers.com');
INSERT INTO Performer(PerformerID, PerformerName, PerformerWebsite) VALUES (2, 'Travelling Yodelers', 'http://travelingyodelers.com');
INSERT INTO Performer(PerformerID, PerformerName, PerformerWebsite) VALUES (3, 'Musak Singers', 'http://musaksingers.com');
INSERT INTO Performer(PerformerID, PerformerName, PerformerWebsite) VALUES (4, 'The Nutcracker', 'http://nutcracker.com');

INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (1, 1, 1, 'May not be able to make it');
INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (2, 2, 1, NULL);
INSERT INTO Booking(PerformerID, EventID, StageID, BookingComments) VALUES (3, 2, 2, 'Keep these guys near the back...');

INSERT INTO StaffType(StaffTypeID, StaffTypeDescription) VALUES (1, 'Host');
INSERT INTO StaffType(StaffTypeID, StaffTypeDescription) VALUES (2, 'Garbage Man');
INSERT INTO StaffType(StaffTypeID, StaffTypeDescription) VALUES (3, 'Security');

INSERT INTO EventStaff(EventStaffID, StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (1, 1, 'George', 'Boy', '2007-06-06');
INSERT INTO EventStaff(EventStaffID, StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (2, 3, 'Bird', 'Lady', '2007-07-17');
INSERT INTO EventStaff(EventStaffID, StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (3, 3, 'Jackson', 'Michael', '2007-05-21');
INSERT INTO EventStaff(EventStaffID, StaffTypeID, StaffLastName, StaffFirstName, StaffStartDate) VALUES (4, 2, 'Hilton', 'Paris', '2008-01-12');

INSERT INTO StaffClock(StaffClockID, EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (1, 1, 1, '2008-03-03', '2008-03-03');
INSERT INTO StaffClock(StaffClockID, EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (2, 1, 2, '2008-03-03', '2008-03-03');
INSERT INTO StaffClock(StaffClockID, EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (3, 2, 2, '2008-08-03', '2008-08-03');
INSERT INTO StaffClock(StaffClockID, EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (4, 2, 3, '2008-08-03', '2008-08-03');
INSERT INTO StaffClock(StaffClockID, EventID, EventStaffID, SCClockinDate, SCClockoutDate) VALUES (5, 2, 4, '2008-08-03', '2008-08-03');

INSERT INTO Viewer (ViewerID, ViewerFirstName, ViewerLastName) VALUES (1, 'Bruce', 'Willis');
INSERT INTO Viewer (ViewerID, ViewerFirstName, ViewerLastName) VALUES (2, 'Britney', 'Spears');
INSERT INTO Viewer (ViewerID, ViewerFirstName, ViewerLastName) VALUES (3, 'Daniel', 'Radcliffe');
INSERT INTO Viewer (ViewerID, ViewerFirstName, ViewerLastName) VALUES (4, 'Harry', 'Potter');

INSERT INTO Ticket(TicketID, EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (1, 1, 3, 75.50, '2007-05-15', NULL);
INSERT INTO Ticket(TicketID, EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (2, 1, 4, 75.50, '2007-05-08', '2007-06-08');
INSERT INTO Ticket(TicketID, EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (3, 1, 1, 60.50, '2007-09-09', NULL);
INSERT INTO Ticket(TicketID, EventID, ViewerID, TicketPrice, TicketPurchaseDate, TicketScannedDate) VALUES (3, 2, 1, 25.50, '2007-09-09', NULL);
