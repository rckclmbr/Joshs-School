/* Josh Braegger CS3550
 Triggers, functions, and stored procedures */


-- If an event status is changed to 'C'ancelled, all Bookings are changed
-- to cancelled as well.
CREATE TRIGGER tr_eventStatus
ON [Event]
AFTER UPDATE
AS


GO

-- In order to keep the hotel database and the extension in sync, this procedure
-- is required.
CREATE TRIGGER tr_hotelSync
ON [Event]
AFTER UPDATE, INSERT, DELETE
AS


GO

-- Purchases a ticket for a customer.  When someone purchases a ticket, the default
-- event ticket price is used, unless someone specifies a ticket price and 
-- overrides it.
CREATE PROC sp_purchaseTicket

GO

--  Books an event for a performer.  Performers can only be booked for an event once.
CREATE PROC sp_bookEvent


GO

-- Assigns a staff member to an event.  Only one staff member can be assigned to an 
-- event per day.
CREATE PROC sp_assignStaff


GO

-- Allows a staff member to clock in or out of an event.  After a staff member
-- is clocked out, his paycheck is automatically written.
CREATE PROC sp_staffClock

GO

-- When a viewer enters the event, their ticket is scanned, and they cannot re-enter.
-- This procedure is called when the viewer enters.  If the ticket was already
-- scanned, an error is raised.
CREATE PROC sp_scanTicket

GO

-- Creates an event.  If no default ticket price is specified, then the default is 
-- calculated as the number of staff required divided by two.
CREATE PROC sp_createEvent

GO