use Braegger_Hotel;

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertGuest' AND type = 'P')
	DROP PROC sp_InsertGuest
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertRooms' AND type = 'P')
	DROP PROC sp_InsertRooms
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertReservationDetail' AND type = 'P')
	DROP PROC sp_InsertReservationDetail
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_UpdatePrices' AND type = 'P')
	DROP PROC sp_UpdatePrices
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_UpdateResDetail' AND type = 'P')
	DROP PROC sp_UpdateResDetail
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertReservation' AND type = 'P')
	DROP PROC sp_InsertReservation

-- 1.  Write a stored procedure named sp_InsertGuest that can be used to insert a row of data into the GuestTable. 
PRINT '1. Creating sp_InsertGuest stored procedure'

GO
CREATE PROC sp_InsertGuest
@GuestFirst varchar(20),
@GuestLast varchar(20),
@GuestAddress1 varchar(30),
@GuestAddress2 varchar(10) = NULL,
@GuestCity varchar(20),
@GuestState char(2),
@GuestPostalCode char(10),
@GuestCountry varchar(20),
@GuestPhone varchar(20),
@GuestEmail varchar(30) = NULL,
@GuestComments varchar(200) = NULL

AS

INSERT INTO Guest (GuestFirst, GuestLast, GuestAddress1, GuestAddress2, GuestCity, GuestState, GuestPostalCode, GuestCountry,
GuestPhone, GuestEmail, GuestComments) VALUES
(@GuestFirst, @GuestLast, @GuestAddress1, @GuestAddress2, @GuestCity, @GuestState, @GuestPostalCode, @GuestCountry,
@GuestPhone, @GuestEmail, @GuestComments)

GO

--    1A.  Demonstrate this procedure by adding yourself as a new guest, using sp_InsertGuest.
PRINT '1A.  Inserting myself as a new guest using sp_InsertGuest'
EXEC sp_InsertGuest
@GuestFirst = 'Josh',
@GuestLast = 'Braegger',
@GuestAddress1 = '123 Hickory Street',
@GuestCity = 'Bountiful',
@GuestState = 'UT',
@GuestPostalCode = '84010',
@GuestCountry = 'USA',
@GuestPhone = '801-555-5555'

GO
--    1B.  Select * From Guests to show the results.
PRINT 'Showing results: '
SELECT * FROM Guest

--2.  Write a stored procedure named sp_InsertRooms that can be used to insert a row of data into the HotelRoomTypes AND 
--    Room Tables. 
PRINT '2.  Creating sp_InsertRooms'
GO

CREATE PROC sp_InsertRooms
@HotelID smallint,
@RoomType varchar(20),
@RoomTypeRackRate smallmoney,
@RoomTypeDescription varchar(200),
@RoomNumber varchar(5),
@RoomDescription varchar(200),
@RoomSmoking bit,
@RoomBedConfiguration varchar(30)

AS

DECLARE @RoomTypeID smallint

IF NOT EXISTS (
	SELECT HotelRoomTypeID
	FROM HotelRoomType
	WHERE HotelID = @HotelID
		AND RoomType = @RoomType
)
BEGIN
	INSERT INTO HotelRoomType (HotelID, RoomType, RoomTypeRackRate, RoomTypeDescription) VALUES
	( @HotelID, @RoomType, @RoomTypeRackRate, @RoomTypeDescription )

	SELECT @RoomTypeID = @@IDENTITY
END

ELSE
	SELECT @RoomTypeID = (SELECT HotelRoomTypeID FROM HotelRoomType WHERE HotelID = @HotelID AND RoomType = @RoomType)

INSERT INTO Room (HotelRoomTypeID, RoomNumber, RoomDescription, RoomSmoking, RoomBedConfiguration, HotelID) VALUES 
(@RoomTypeID, @RoomNumber, @RoomDescription, @RoomSmoking, @RoomBedConfiguration, @HotelID)

GO

--    2A.  Demonstrate:  The Weber Towers and Suites is expanding.  Using sp_InsertRooms, Insert a New Room Type called 
--         'Suite' and add Room 351, a Suite, with a rate of $199 / night and room description:  'A new suite overlooking 
--         the Great Salt Lake'.

EXEC sp_insertRooms
@HotelID = 2300, -- Weber Towers and Sweets
@RoomType = 'Suite',
@RoomTypeRackRate = 199.00,
@RoomTypeDescription = 'A nice suite',
@RoomNumber = 351,
@RoomDescription = 'A new suite overlooking the Great Salt Lake',
@RoomSmoking = 0,
@RoomBedConfiguration = 'Double'

GO 

--    2B.  Select * From Rooms to show the results.
PRINT '2B. Showing results'
SELECT * FROM Room

--3.  Write a stored procedure named sp_UpdatePrices that can be used to update prices on the HotelRoomTypes Table.  
--    The procedure will require a Hotel Number (ID) and percentage increase (or decrease) parameter to be passed.  
--    It will set the new rate of the room - rounding down to the nearest dollar for price decreases, or rounding up to 
--    the nearest dollar for price increases.
GO
PRINT '3. Creating sp_UpdatePrices'
GO
CREATE PROC sp_UpdatePrices
@HotelID smallint,
@PercentInc decimal

AS

	UPDATE HotelRoomType
	SET 
		RoomTypeRackRate = CASE 
			WHEN @PercentInc < 0 -- Round down for price decreases  
				THEN FLOOR(@PercentInc / 100 * RoomTypeRackRate)
			ELSE -- Round up for price increases
				CEILING(@PercentInc / 100 * RoomTypeRackRate)
			END
	WHERE HotelID = @HotelID

GO 

--    3A.  Demonstrate:  It's springtime in Park City, and Rich's B&B wants to decrease rates 6.5% (Rounding down to the 
--         nearest dollar) for all their rooms.   Call sp_UpdatePrices to make this happen.  
PRINT '3A. Demonstrating sp_UpdatePrices'
GO
EXEC sp_UpdatePrices
@HotelID = 2100,    -- Rich's B&B
@PercentInc = -6.5 -- Decreasing the price, so negative

--    3B.  Select * From HotelRoomType to show the results.
PRINT '3B. Showing results: '
SELECT * FROM HotelRoomType

--    3C.  Demonstrate:  Calling the exact same sp_UpdatePrices (only supplying a different Hotel # and %), increase the 
--         price of all Rooms at Weber Towers and Suites 5% (rounding up to the nearest dollar). 
PRINT '3C.  Calling sp_UpdatePrices (again, with different params)'
GO
EXEC sp_UpdatePrices
@HotelID = 2300, -- Weber Towers and Suites
@PercentInc = 5

--    3D.  Select * From HotelRoomType to show the results.
PRINT '3D. Showing results: '
SELECT * FROM HotelRoomType

--4.  Write a stored procedure named  sp_UpdateResDetail (for the ReservationsDetail Table in your DB)  that can be used 
--    to update a reservation (and any combination of check-in date, number of nights, and/or status).  If any of the 3 
--    values are not supplied when the procedure is executed, then then these parameters should retain their original 
--    value.  This stored procedure should include appropriate error handling to give the user a friendly message.  For 
--    example:  Show a friendly message like "Sorry, but 'A' is not a valid value for the number of nights.  Record not 
--    updated."  You only need to do one error handling routine - you don't need to account for every possible error.
PRINT '4. Creating sp_UpdateResDetail'
GO

PRINT '   (Creating custom error)'

IF NOT EXISTS (SELECT * FROM sys.messages WHERE message_id = 76224)
	EXEC sp_addmessage
    @msgnum = 76224, -- Message Number
    @severity = 15,  -- Severity
    @msgtext = 'Sorry the ReservationID %s was not found.' -- Custom message

PRINT '   (Creating SPROC)'
GO

CREATE PROC sp_UpdateResDetail
@ReservationDetailID smallint,
@CheckinDate smalldatetime = NULL,
@NumberOfNights int = NULL,
@Status char(1) = NULL

AS

-- Exception check: They have to enter a valid ReservationDetailID
IF NOT EXISTS (
	SELECT *
	FROM ReservationDetail
	WHERE ReservationDetailID = @ReservationDetailID
)
	RAISERROR (
		76224, -- Error Number
		15,    -- Severity
		1,     -- State
		@ReservationDetailID -- Parameters
	)


IF @CheckinDate IS NOT NULL
	UPDATE ReservationDetail 
	SET CheckinDate = @CheckinDate 
	WHERE ReservationDetailID = @ReservationDetailID
IF @NumberOfNights IS NOT NULL
	UPDATE ReservationDetail 
	SET Nights = @NumberOfNights 
	WHERE ReservationDetailID = @ReservationDetailID
IF @Status IS NOT NULL
	UPDATE ReservationDetail
	SET Status = @Status
	WHERE ReservationDetailID = @ReservationDetailID

GO
--    4A.  Demonstrate by providing any combination of nights, status, and/or check-in date changes.
PRINT '4A. Demonstrating sp_UpdateResDetail'
GO
EXEC sp_UpdateResDetail
@ReservationDetailID = 1,
@NumberOfNights = 2

GO

--    4B.  Do it one more time with different combinations.
PRINT '4B. Demonstrating sp_UpdateResDetail (again...)'
GO
EXEC sp_UpdateResDetail
@ReservationDetailID = 9,
@CheckinDate = '6/9/2008',
@Status = 'A'

--    4C.  Do it a third time so it triggers your error.
PRINT '4C. Demonstrating sp_UpdateResDetail so it triggers my error'
GO
EXEC sp_UpdateResDetail
@ReservationDetailID = 2222, -- Invalid ReservationDetailID
@CheckinDate = '6/9/2008',
@Status = 'A'

--5.  Write a stored procedure named sp_InsertReservation that can be used to insert reservation data into the 
--    Reservations Table AND ReservationDetails Table.  You will need to retrieve the value of @@IDENTITY from the 
--    reservationID, then populate the First Reservation Detail using that ID.  Note: Break this down into 2 stored 
--    procedures (1 for Reservation and one for reservation details).  By keeping a separate reservation detail sproc, 
--    we would be able to run the detail part as many times as needed to accommodate multiple reservation details.
PRINT '5.  Creating sp_InsertReservation'
GO
CREATE PROC sp_InsertReservation
@CreditCardID smallint,
@ReservationDate smalldatetime,
@ReservationStatus char(1) = 'A',
@ReservationComments varchar(200) = NULL

AS
	DECLARE @ReservationID smallint
	DECLARE @SuiteID smallint

	INSERT INTO Reservation (CreditCardID, ReservationDate, ReservationStatus, ReservationComments) VALUES
	(@CreditCardID, @ReservationDate, @ReservationStatus, @ReservationComments)

	SELECT @ReservationID = @@IDENTITY

	-- Get the RoomID for the Suite
	SELECT @SuiteID = RoomID
	FROM Room
	WHERE RoomNumber = 351
	AND HotelID = 2300

	EXEC sp_InsertReservationDetail
	@RoomID = @SuiteID,
	@ReservationID = @ReservationID,
	@CheckinDate = 'April 21, 2008',
	@Nights = 2,
	@QuotedRate = 500.99

	EXEC sp_InsertReservationDetail
	@RoomID = 3, -- Rich's bed and breakfast, Double Room, non-smoking
	@ReservationID = @ReservationID,
	@CheckinDate = 'April 28, 2008',
	@Nights = 2,
	@QuotedRate = 250.99

	EXEC sp_InsertReservationDetail
	@RoomID = 3, -- Rich's bed and breakfast, Double Room, non-smoking
	@ReservationID = @ReservationID,
	@CheckinDate = 'May 28, 2008',
	@Nights = 2,
	@QuotedRate = 299.99

GO
PRINT '5. (cont) Creating sp_InsertReservationDetail'
GO
CREATE PROC sp_InsertReservationDetail
@RoomID smallint,
@ReservationID smallint,
@QuotedRate smallmoney,
@CheckinDate smalldatetime,
@Nights tinyint,
@Comments varchar(200) = NULL,
@DiscountID smallint = 1,
@Status char(1) = 'A'

AS
	INSERT INTO ReservationDetail (RoomID, ReservationID, QuotedRate, CheckinDate, Nights, Status, Comments, DiscountID)
	VALUES
	(@RoomID, @ReservationID, @QuotedRate, @CheckinDate, @Nights, @Status, @Comments, @DiscountID)

GO

--    5A.  Demonstrate:  Using sp_InsertReservations, make a single reservation, with 3 details*, for yourself at the 
--         Weber Towers and Suites on April 21st for 2 nights (the suite), a reservation for the Rich's B&B on April 28th 
--         for 2 nights, (double room), non-smoking, and a reservation for the Rich's B&B on May 28th for 2 nights, 
--         (double room), non-smoking.  
--         *You'll run the second part of the stored procedure (in #5) three times, with different data.
PRINT '5A. Creating reservation using sp_InsertReservations'

EXEC sp_InsertReservation
@CreditCardID = 7, -- Just a credit card
@ReservationDate = 'March 24, 2008'

GO
--    5B.  Select * From Reservations and ReservationDetails to show the results. 
PRINT '5B.  Showing results'

SELECT * FROM Reservation
SELECT * FROM ReservationDetail