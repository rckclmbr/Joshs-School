/* Josh Braegger CS3550
 Triggers, functions, and stored procedures */


-- If an event status is changed to 'C'ancelled, all Bookings are changed
-- to cancelled as well.
CREATE TRIGGER tr_eventStatus
ON [Event]
AFTER UPDATE
AS
	IF UPDATE(EventStatus)
	BEGIN
		DECLARE @EventStatus char(1)
		DECLARE @EventID smallint

		SELECT
			@EventID = EventID
			@EventStatus = EventStatus
		FROM Inserted i

		IF @EventStatus = 'C'
			UPDATE Booking
			SET BookingStatus = 'C'
			WHERE EventID = @EventID
	END

GO

-- When a staff member clocks out, run sp_paycheck to automatically create the paycheck
CREATE TRIGGER tr_staffClockOut
ON StaffClock
AFTER UPDATE
AS
	IF UPDATE(SCClockoutDate)
	BEGIN
		DECLARE @HoursWorked decimal
		DECLARE @PaycheckAmount money
		DECLARE @EventStaffID smallint

		SELECT
			@EventStaffID   = i.EventStaffID,
			@PaycheckAmount = DATEDIFF('h', i.SCClockinDate, i.SCClockoutDate) * es.StaffHourlyRate,
			@HoursWorked    = DATEDIFF('h', i.SCClockinDate, i.SCClockoutDate)
		FROM Inserted i
			JOIN EventStaff es ON es.EventStaffID = i.EventStaffID

		INSERT INTO Paycheck (PaycheckAmount, PaycheckHoursWorked, EventStaffID)
		VALUES (@PaycheckAmount, @HoursWorked, @EventStaffID)
	END
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
-- Also, a ticket can only be scanned once
CREATE PROC sp_purchaseTicket

GO

--  Books an event for a performer.  Performers can only be booked for an event once.
CREATE PROC sp_bookEvent
@EventID smallint,
@PerformerID smallint,
@StageID smallint,
@BookingComments varchar(256) = NULL

AS

	-- Make sure they're not already booked
	IF (
		SELECT *
		FROM Booking
		WHERE PerformerID = @PerformerID
			AND EventID = @EventID
	) > 0
		RAISERROR('Cannot book event -- there is already a performer assigned to this event', 1, 10)

	INSERT INTO Booking (PerformerID, EventID, StageID, BookingComments)
	VALUES (@PerformerID, @EventID, @StageID, @bookingComments)

GO

-- Assigns a staff member to an event.  Only one staff member can be assigned to an 
-- event per day.
CREATE PROC sp_assignStaff
@EventID smallint,
@EventStaffID smallint

AS
	DECLARE @EventDay smalldatetime
	-- Find the date the event is
	SET @EventDay = ( SELECT EventDate FROM [Event] WHERE EventID = @EventID )

	IF (
		-- Check to see if the employee has any events for that day
		SELECT TOP 1 EventID
		FROM [Event] e
			JOIN StaffClock sc ON sc.EventID = e.EventID
		WHERE sc.EventStaffID = @EventStaffID
			AND e.EventDate = @EventDay
			-- TODO: Compare by day
	) > 0
		RAISERROR('A staff member cannot be assigned to more than 1 event per day', 1, 10)

	INSERT INTO StaffClock (EventID, EventStaffID)
	VALUES (@EventID, @EventStaffID)

GO

-- Allows a staff member to clock in or out of an event.
CREATE PROC sp_staffClock
@EventStaffID smallint,
@Clockin boolean = NULL,
@Clockout boolean = NULL

AS
	DECLARE @EventID smallint
	DECLARE @Today date
	-- Find the Event the EventStaffID has today

	SET @Today = GetDate()

	SELECT 
	FROM 
	WHERE 
		CONVERT(varchar, EventDate, 101) -- compare only date, not time

	IF @Clockin
	BEGIN

	END

	IF @Clockout
	BEGIN
		
	END

GO

--  Inserts a clock record into the paycheck table.
CREATE PROC sp_paycheck

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

