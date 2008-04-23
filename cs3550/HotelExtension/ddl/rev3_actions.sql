/* Josh Braegger CS3550
 Triggers, functions, and stored procedures */
USE Braegger_HotelEvents

-- Drop any existing procs/triggers/etc
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'tr_hotelSync')
	DROP TRIGGER tr_hotelSync
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'tr_eventStatus')
	DROP TRIGGER tr_eventStatus
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'tr_staffClockOut')
	DROP TRIGGER tr_staffClockOut
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_purchaseTicket' AND type = 'P')
	DROP PROC sp_purchaseTicket
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_bookEvent' AND type = 'P')
	DROP PROC sp_bookEvent
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_assignStaff' AND type = 'P')
	DROP PROC sp_assignStaff
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_staffClock' AND type = 'P')
	DROP PROC sp_staffClock
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_paycheck' AND type = 'P')
	DROP PROC sp_paycheck
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_scanTicket' AND type = 'P')
	DROP PROC sp_scanTicket
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_createEvent' AND type = 'P')
	DROP PROC sp_createEvent
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_addEventRevenue' AND type = 'P')
	DROP PROC sp_addEventRevenue

GO

-- Add the linked server (may give non-fatal error if it exists)
Exec sp_addlinkedserver
@server='TITAN_BRAEGGER',
@srvproduct='',
@provider='MSDASQL',
@provstr='DRIVER={SQL Server};SERVER=titan.cs.weber.edu,10433;UID=jbraegger;PWD=C$3550;Initial Catalog=Braegger_Hotel'

GO

-- Add linkedsrvlogin
Exec sp_addlinkedsrvlogin
@rmtsrvname='TITAN_BRAEGGER',
@useself='true',
@locallogin='THESHIZNIT\arnie',
@rmtuser='jbraegger', 
@rmtpassword='C$3550'

GO

-- Enable proper server options
Exec sp_serveroption 'TITAN_BRAEGGER', 'data access', 'true'
Exec sp_serveroption 'TITAN_BRAEGGER', 'rpc', 'true'--enables from the REMOTE to LOCAL server
Exec sp_serveroption 'TITAN_BRAEGGER', 'rpc out', 'true' -- enables from the LOCAL to REMOTE server
Exec sp_serveroption 'TITAN_BRAEGGER', 'collation compatible', 'true'

GO

-- Required for SQL Server 2005 (only need to run once)
-- sp_configure 'show advanced options', 1
-- reconfigure
-- GO
-- sp_configure 'Ad Hoc Distributed Queries', 1
-- reconfigure

GO

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
			@EventID = EventID,
			@EventStatus = EventStatus
		FROM Inserted i

		IF @EventStatus = 'C'
		BEGIN
			UPDATE Booking
			SET BookingStatus = 'C'
			WHERE EventID = @EventID
		END

		IF @EventStatus = 'O'
		BEGIN
			-- Insert stuff into Revenue table
			EXEC sp_addEventRevenue @EventID 
		END
	END

GO

-- When a staff member clocks out, run sp_paycheck to automatically create the paycheck
CREATE TRIGGER tr_staffClockOut
ON StaffClock
AFTER UPDATE
AS
	DECLARE @StaffClockID smallint

	IF UPDATE(SCClockoutDate)
	BEGIN
		SET @StaffClockID = (SELECT StaffClockID FROM Inserted i)

		EXEC sp_paycheck @StaffClockID
	END
GO

-- In order to keep the hotel database and the extension in sync, this procedure
-- is required.
CREATE TRIGGER tr_hotelSync
ON [Event]
FOR UPDATE, INSERT
AS
	-- There's no point to check if the HotelID was updated -- it's ok to check every time
	-- a row is inserted or updated.

	DECLARE @HotelID smallint

	SET @HotelID = (SELECT HotelID FROM Inserted i)

	-- So, we make sure the HotelID exists
	IF NOT EXISTS(
		SELECT HotelID 
		FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT HotelID FROM Braegger_Hotel.dbo.Hotel') 
				AS passthrough
		WHERE HotelID = @HotelID
	)
	BEGIN
		RAISERROR('Hotel doesn''t exist', 15, 1)
		ROLLBACK TRANSACTION
	END

	-- At this point, we can assume the HotelID exists, and carry on to let it update/insert

GO

-- Purchases a ticket for a customer.  When someone purchases a ticket, the default
-- event ticket price is used, unless someone specifies a ticket price and 
-- overrides it.
-- Also, a ticket can only be scanned once
CREATE PROC sp_purchaseTicket
@TicketPrice money = NULL,
@ViewerID smallint,
@EventID smallint
AS
	IF @TicketPrice IS NULL
		SET @TicketPrice = (
			SELECT EventTicketPrice
			FROM Events
			WHERE EventID = @EventID
		)

	INSERT INTO Ticket (EventID, ViewerID, TicketPrice)
	VALUES (@EventID, @ViewerID, @TicketPrice)

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
		SELECT COUNT(1) AS Booked
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

	IF EXISTS (
		-- Check to see if the employee has any events for that day
		SELECT TOP 1 e.EventID
		FROM [Event] e
			JOIN StaffClock sc ON sc.EventID = e.EventID
		WHERE sc.EventStaffID = @EventStaffID
			AND e.EventDate = @EventDay
			-- TODO: Compare by day
	)
		RAISERROR('A staff member cannot be assigned to more than 1 event per day', 1, 15)

	INSERT INTO StaffClock (EventID, EventStaffID)
	VALUES (@EventID, @EventStaffID)

GO

-- Allows a staff member to clock in or out of an event.
CREATE PROC sp_staffClock
@EventStaffID smallint,
@Clockin bit = 0,
@Clockout bit = 0

AS
	DECLARE @StaffClockID smallint
	DECLARE @Today datetime
	-- Find the Event the EventStaffID has today

	SET @Today = DATEADD(dd, DATEDIFF(dd,0,GetDate()), 0) -- Get Date only

	-- Get the Event the staff member is registered for
	SET @StaffClockID = (
		SELECT e.EventID
		FROM [Event] e
			JOIN StaffClock sc ON e.EventID = sc.EventID
		WHERE sc.EventStaffID = @EventStaffID
			AND DATEADD(dd, DATEDIFF(dd,0,e.EventDate), 0) = @Today -- compare only date, not time
	)

	IF (@Clockin = 1)
	BEGIN
		UPDATE StaffClock
		SET SCClockinDate = GetDate()
		WHERE StaffClockID = @StaffClockID
	END

	IF (@Clockout = 1)
	BEGIN
		UPDATE StaffClock
		SET SCClockoutDate = GetDate()
		WHERE StaffClockID = @StaffClockID		
	END

GO

--  Inserts a clock record into the paycheck table.
CREATE PROC sp_paycheck
@StaffClockID smallint
AS
	DECLARE @HoursWorked decimal
	DECLARE @PaycheckAmount money
	DECLARE @EventStaffID smallint

	-- Make sure sure the Clockin Date and Clockout Date are valid
	IF NOT EXISTS (
		SELECT StaffClockID
		FROM StaffClock
		WHERE StaffClockID = @StaffClockID
			AND SCClockinDate IS NOT NULL
			AND SCClockoutDate IS NOT NULL
			AND SCClockinDate < SCClockoutDate
			AND (
				 -- Make sure it's on the same date
				DATEADD(dd, DATEDIFF(dd,0,SCClockinDate), 0)
				=
				DATEADD(dd, DATEDIFF(dd,0,SCClockoutDate), 0) 
			)
	)
		RAISERROR('You have entered an invalid StaffClockID: %d', 1, 15, @StaffClockID)

	SELECT
		@EventStaffID   = sc.EventStaffID,
		@PaycheckAmount = DATEDIFF(hh, sc.SCClockinDate, sc.SCClockoutDate) * es.StaffHourlyRate,
		@HoursWorked    = DATEDIFF(hh, sc.SCClockinDate, sc.SCClockoutDate)
	FROM StaffClock sc
		JOIN EventStaff es ON es.EventStaffID = sc.EventStaffID
	WHERE sc.StaffClockID = @StaffClockID

	INSERT INTO Paycheck (PaycheckAmount, PaycheckHoursWorked, EventStaffID)
	VALUES (@PaycheckAmount, @HoursWorked, @EventStaffID)
GO

-- When a viewer enters the event, their ticket is scanned, and they cannot re-enter.
-- This procedure is called when the viewer enters.  If the ticket was already
-- scanned, an error is raised.
CREATE PROC sp_scanTicket
@TicketID smallint
AS
	-- Make sure the ticket hasn't been scanned
	IF EXISTS (
		SELECT TicketID
		FROM Ticket
		WHERE TicketID = @TicketID
			AND TicketScannedDate IS NOT NULL
	)
		RAISERROR('Ticket %d has already been scanned, and re-entry is not allowed', 1, 15, @TicketID)

	UPDATE Ticket
	SET TicketScannedDate = GetDate()
	WHERE TicketID = @TicketID

GO

-- Creates an event.  If no default ticket price is specified, then the default is 
-- calculated as the number of staff required divided by two.
CREATE PROC sp_createEvent
@EventName varchar(64),
@EventDate smalldatetime,
@EventMaxTickets smallint,
@EventNumStaffReq tinyint,
@EventTicketPrice smallmoney = NULL,
@HotelID smallint
AS
	IF @EventTicketPrice IS NULL
		SET @EventTicketPrice = @EventNumStaffReq / 2

	INSERT INTO [Event] (EventName, EventDate, EventMaxTickets, EventNumStaffReq, 
			EventTicketPrice, HotelID)
	VALUES (@EventName, @EventDate, @EventMaxTickets, @EventNumStaffReq, @EventTicketPrice,
			@HotelID)

GO

-- Adds all the revenue for an event into the Hotel's Revenue table.
-- Normally called from a trigger when an Event is changed to 'O'
CREATE PROC sp_addEventRevenue
@EventID smallint
AS
	DECLARE @HotelID smallint
	DECLARE @TotalRevenue smallmoney
	DECLARE @Revenue smallmoney

	SET @HotelID = (SELECT HotelID FROM [Event] WHERE EventID = @EventID)

	DECLARE revenue_cursor CURSOR
	FOR
		-- Get all Tickets sold
		SELECT TicketPrice
		FROM Ticket
		WHERE EventID = @EventID

	OPEN revenue_cursor

	FETCH NEXT FROM revenue_cursor
	INTO @Revenue

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @TotalRevenue = @TotalRevenue + @Revenue
		FETCH NEXT FROM revenue_cursor INTO @Revenue
	END

	CLOSE RevenueCursor
	DEALLOCATE RevenueCursor
	
	INSERT OPENQUERY (TITAN_BRAEGGER, 
		'SELECT RevenueAmount, RevenueComments, HotelID, RevenueCategoryID 
		 FROM Braegger_Hotel.dbo.Revenue') 
	VALUES (
		@TotalRevenue,
		'Ticket sales',
		@HotelID,
		6 -- 'Ticket Sales'
	)

GO

-- Not part of an SPROC, but add support for 'Ticket Sales'
IF NOT EXISTS (
	SELECT RevenueCategoryDescription 
	FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT RevenueCategoryDescription FROM Braegger_Hotel.dbo.RevenueCategory') 
			AS passthrough
	WHERE RevenueCategoryDescription = 'Ticket Sales'
)
	INSERT OPENQUERY (TITAN_BRAEGGER, 
			'SELECT RevenueCategoryDescription 
			 FROM Braegger_Hotel.dbo.RevenueCategory') 
	VALUES ('Ticket Sales')