/* Josh Braegger CS3550
 Hotel Events Database Creation Script */
 
USE Master
 
IF  EXISTS (
    SELECT name
        FROM sys.databases
        WHERE name = 'Braegger_HotelEvents')

DROP Database Braegger_HotelEvents
GO

CREATE DATABASE Braegger_HotelEvents
ON Primary
(NAME = 'Braegger_HotelEvents', -- Virtual Internal Name
 FILENAME = 'O:\SQLDB\Braegger_HotelEvents.mdf',
 SIZE = 2MB,
 MAXSIZE = 4MB, 
 FILEGROWTH = 500KB
)

LOG ON
(NAME = 'Braegger_HotelEvents_Log', -- Virtual Internal Name
 FILENAME = 'O:\SQLDB\Braegger_HotelEvents.ldf',
 SIZE = 2MB,
 MAXSIZE = 4MB, 
 FILEGROWTH = 500KB
)
GO

USE Braegger_HotelEvents

CREATE TABLE Performer
( PerformerID	smallint	IDENTITY(1,1) NOT NULL,
  PerformerName	varchar(64)	NOT NULL,
  PerformerWebsite varchar(128)
)

CREATE TABLE Booking
( BookingID	smallint	IDENTITY(1,1)	NOT NULL,
  PerformerID	smallint	NOT NULL,
  EventID	smallint	NOT NULL,
  StageID	smallint,
  BookingDate	smalldatetime	NOT NULL DEFAULT GetDate(),
  BookingComments   varchar(256)
)

CREATE TABLE Stage
( StageID	smallint	IDENTITY(1,1)	NOT NULL,
  StageName	varchar(32)	NOT NULL,
  StageLocation	varchar(64)
)

CREATE TABLE Event
( EventID	smallint	IDENTITY(1,1)	NOT NULL,
  EventName	varchar(64)	NOT NULL,
  EventDate	smalldatetime	NOT NULL,
  EventMaxTickets	smallint,
  EventNumStaffReq	smallint	NOT NULL,
  EventTicketPrice	smallmoney	NOT NULL,
)

CREATE TABLE StaffClock
( StaffClockID	smallint	IDENTITY(1,1)	NOT NULL,
  EventID	smallint	NOT NULL,
  EventStaffID	smallint	NOT NULL,
  SCClockinDate	smalldatetime,
  SCClockoutDate	smalldatetime
)

CREATE TABLE EventStaff
( EventStaffID	smallint	IDENTITY(1,1)	NOT NULL,
  StaffTypeID	smallint	NOT NULL,
  StaffLastName	varchar(64)	NOT NULL,
  StaffFirstName	varchar(64)	NOT NULL,
  StaffStartDate	smalldatetime
)

CREATE TABLE StaffType
( StaffTypeID	smallint	IDENTITY(1,1)	NOT NULL,
  StaffTypeDescription	varchar(64)	NOT NULL
)

CREATE TABLE Ticket
( TicketID	smallint	IDENTITY(1,1)	NOT NULL,
  EventID	smallint	NOT NULL,
  ViewerID	smallint	NOT NULL,
  TicketPrice	smallmoney	NOT NULL,
  TicketPurchaseDate    smalldatetime   NOT NULL,
  TicketScannedDate smalldatetime
)

CREATE TABLE Viewer
( ViewerID	smallint	IDENTITY(1,1)	NOT NULL,
  ViewerFirstName	varchar(64)	NOT NULL,
  ViewerLastName	varchar(64)	NOT NULL
)

-- PK Constraints
ALTER TABLE Performer
ADD CONSTRAINT PK_PerformerID
PRIMARY KEY (PerformerID) 

ALTER TABLE Booking
ADD CONSTRAINT PK_BookingID
PRIMARY KEY (BookingID) 

ALTER TABLE Stage
ADD CONSTRAINT PK_StageID
PRIMARY KEY (StageID) 

ALTER TABLE Event
ADD CONSTRAINT PK_EventID
PRIMARY KEY (EventID) 

ALTER TABLE StaffClock
ADD CONSTRAINT PK_StaffClockID
PRIMARY KEY (StaffClockID) 

ALTER TABLE Ticket
ADD CONSTRAINT PK_TicketID
PRIMARY KEY (TicketID) 

ALTER TABLE EventStaff
ADD CONSTRAINT PK_EventStaffID
PRIMARY KEY (EventStaffID)
 
ALTER TABLE Viewer
ADD CONSTRAINT PK_ViewerID
PRIMARY KEY (ViewerID) 

ALTER TABLE StaffType
ADD CONSTRAINT PK_StaffTypeID
PRIMARY KEY (StaffTypeID) 

-- FK Constraints
ALTER TABLE Booking
ADD CONSTRAINT FK_BookingMustHavePerformer
FOREIGN KEY (PerformerID) REFERENCES Performer(PerformerID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE Booking
ADD CONSTRAINT FK_BookingCanHaveStage
FOREIGN KEY (StageID) REFERENCES Stage(StageID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE Booking
ADD CONSTRAINT FK_BookingMustHaveEvent
FOREIGN KEY (EventID) REFERENCES Event(EventID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE StaffClock
ADD CONSTRAINT FK_StaffClockMustHaveEvent
FOREIGN KEY (EventID) REFERENCES Event(EventID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE StaffClock
ADD CONSTRAINT FK_StaffClockMustHaveStaff
FOREIGN KEY (EventStaffID) REFERENCES EventStaff(EventStaffID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketMustHaveEvent
FOREIGN KEY (EventID) REFERENCES Event(EventID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketMustHaveViewer
FOREIGN KEY (ViewerID) REFERENCES Viewer(ViewerID)
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE EventStaff
ADD CONSTRAINT FK_EventStaffMustHaveStaffType
FOREIGN KEY (StaffTypeID) REFERENCES StaffType(StaffTypeID)
ON UPDATE CASCADE
ON DELETE CASCADE