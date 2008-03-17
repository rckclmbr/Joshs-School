/* Josh Braegger CS3550
 Hotel Events Drop Tables Script */

USE Braegger_HotelEvents

ALTER TABLE Booking 
DROP CONSTRAINT FK_BookingMustHavePerformer

ALTER TABLE Booking
DROP CONSTRAINT FK_BookingCanHaveStage

ALTER TABLE Booking
DROP CONSTRAINT FK_BookingMustHaveEvent

ALTER TABLE StaffClock
DROP CONSTRAINT FK_StaffClockMustHaveEvent

ALTER TABLE StaffClock
DROP CONSTRAINT FK_StaffClockMustHaveStaff

ALTER TABLE Ticket
DROP CONSTRAINT FK_TicketMustHaveEvent

ALTER TABLE Ticket
DROP CONSTRAINT FK_TicketMustHaveViewer

ALTER TABLE EventStaff
DROP CONSTRAINT FK_EventStaffMustHaveStaffType

ALTER TABLE Paycheck
DROP CONSTRAINT FK_PaycheckMustHaveEventStaff

DROP TABLE Booking
DROP TABLE [Event]
DROP TABLE EventStaff
DROP TABLE Performer
DROP TABLE StaffClock
DROP TABLE StaffType
DROP TABLE Stage
DROP TABLE Ticket
DROP TABLE Viewer
DROP TABLE Paycheck