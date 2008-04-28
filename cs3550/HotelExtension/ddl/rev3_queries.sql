/* Josh Braegger CS3550
 Hotel Events Test Queries */

DECLARE @EventID smallint
DECLARE @PerformerID smallint
DECLARE @StageID smallint
DECLARE @EventStaffID smallint
DECLARE @TicketID smallint

BEGIN TRY

SET @PerformerID = 1
SET @StageID = 2
SET @EventStaffID = 3

PRINT 'Testing if an event status is changed to C, all relevent bookings are changed'

PRINT '----------------------------------------------------'
PRINT 'Testing Hotel ID Sync for events'

PRINT '  Testing INSERT with invalid HotelID (should give error)'

	BEGIN TRY
		INSERT INTO [Event] (EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice, HotelID)
		VALUES ('A Cool Event', GetDate(), 13, 14, 29.95, 1111)
	END TRY
	BEGIN CATCH
		PRINT '  Threw an error correctly: ' + ERROR_MESSAGE()
		PRINT ''
	END CATCH

PRINT '  Testing INSERT with valid HotelID (should work ok)'

	INSERT INTO [Event] (EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice, HotelID)
	VALUES ('A Cool Event', GetDate(), 13, 14, 29.95, 2300)

	SET @EventID = @@IDENTITY

PRINT '  Testing UPDATE with invalid HotelID (should give error)'

	BEGIN TRY
		UPDATE [Event] SET HotelID = 1222 WHERE EventID = @EventID
	END TRY
	BEGIN CATCH
		PRINT '  Threw an error correctly: ' + ERROR_MESSAGE()
		PRINT ''
	END CATCH

PRINT '  Testing UPDATE with valid HotelID'

	UPDATE [Event] SET HotelID = 2400 WHERE EventID = @EventID

PRINT '----------------------------------------------------'
PRINT 'Testing creation of an event with an SPROC'
PRINT '  Creating with a default ticket price'

	INSERT INTO [Event] (EventName, EventDate, EventMaxTickets, EventNumStaffReq, EventTicketPrice, HotelID)
	VALUES ('Test event sproc 1', '2008-12-03', 200, 30, 35.00, 2300)

PRINT '  Creating with no default price (should be EventNumStaffReq / 2)'

	INSERT INTO [Event] (EventName, EventDate, EventMaxTickets, EventNumStaffReq, HotelID)
	VALUES ('Test event sproc 2', '2008-12-25', 120, 90, 2300)

PRINT '  Showing Results:'

SELECT * FROM [Event]

PRINT '----------------------------------------------------'
PRINT 'Testing ticket creation'

PRINT '  Testing with supplying a ticket price'

	EXEC sp_purchaseTicket
	@EventID = @EventID,
	@ViewerID = 2,
	@TicketPrice = 19.99,
	@TicketID = @TicketID OUTPUT

PRINT '  Testing without supplying a ticket price'

	EXEC sp_purchaseTicket
	@EventID = @EventID,
	@ViewerID = 2

PRINT '  Showing Results:'

PRINT '    (First ticket price inserted should be 19.99, Second should be 29.95)'

	SELECT * FROM Ticket

PRINT '----------------------------------------------------'
PRINT 'Trying to book an event'

PRINT '   (Cleaning up any data from a previous run)'

	DELETE FROM Booking WHERE PerformerID = @PerformerID AND EventID = @EventID

PRINT '   Booking the Event'

	EXEC sp_bookEvent
	@EventID = @EventID,
	@PerformerID = @PerformerID,
	@StageID = @StageID

PRINT '  Trying to book the performer again for the same event -- should throw an error'

	BEGIN TRY
		EXEC sp_bookEvent
		@EventID = @EventID,
		@PerformerID = @PerformerID,
		@StageID = @StageID
	END TRY
	BEGIN CATCH
		PRINT '  Threw an error correctly: ' + ERROR_MESSAGE()
		PRINT ''
	END CATCH

PRINT '----------------------------------------------------'
PRINT 'Assigning a staff member to an event'

	EXEC sp_assignStaff
	@EventID = @EventID,
	@EventStaffID = @EventStaffID


PRINT '  Trying to assign him to another event for that day -- should throw an error'

	BEGIN TRY
		-- Just do it for the same event, technically it's the same
		EXEC sp_assignStaff
		@EventID = @EventID,
		@EventStaffID = @EventStaffID
	END TRY
	BEGIN CATCH
		PRINT '  Threw an error correctly: ' + ERROR_MESSAGE()
		PRINT ''
	END CATCH

PRINT '----------------------------------------------------'
PRINT 'Testing the staff clock functionality'

PRINT '  Clocking a staff member in for an event'

	EXEC sp_staffClock
	@EventStaffID = @EventStaffID,
	@Clockin = 1

PRINT '  Clocking a staff member out of an event (should trigger tr_staffClockOut which calls sp_paycheck)'

	EXEC sp_staffClock
	@EventStaffID = @EventStaffID,
	@Clockout = 1

PRINT '  Showing paycheck results'

	SELECT * FROM Paycheck

PRINT '----------------------------------------------------'
PRINT 'Scanning a ticket'

	EXEC sp_scanTicket
	@TicketID = @TicketID

PRINT '  Attempting to scan the ticket again (should give error)'

	BEGIN TRY
		EXEC sp_scanTicket
		@TicketID = @TicketID
	END TRY
	BEGIN CATCH
		PRINT '  Threw an error correctly: ' + ERROR_MESSAGE()
		PRINT ''
	END CATCH

PRINT '----------------------------------------------------'
PRINT 'Changing Event Status to O (should put revenue in the Hotel database for the sum of all tickets)'

	-- This doesn't work, I can't figure out why
	BEGIN TRY
		UPDATE [Event]
		SET EventStatus = 'O'
		WHERE EventID = @EventID
	END TRY
	BEGIN CATCH
		PRINT 'An unexpected error occurred (probably with the DTC): ' + ERROR_MESSAGE()
	END CATCH

PRINT '  Showing results from Hotel Database:'

	SELECT * 
	FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM Braegger_Hotel.dbo.Revenue') 
			AS passthrough

END TRY
BEGIN CATCH
	PRINT 'There was a big error with the script: ' + ERROR_MESSAGE()
END CATCH

PRINT '----------------------------------------------------'
PRINT 'Just Cleaning up some data'
DELETE FROM [Event] WHERE EventID > 3
DELETE FROM Paycheck WHERE PaycheckID > 2