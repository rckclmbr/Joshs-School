use Braegger_Hotel

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'fn_GetTotalRoomCharge')
	DROP FUNCTION dbo.fn_GetTotalRoomCharge
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'fn_GetTotalTax')
	DROP FUNCTION dbo.fn_GetTotalTax
IF EXISTS (SELECT name, type FROM sysobjects WHERE name = 'fn_ProduceBill')
	DROP FUNCTION dbo.fn_ProduceBill
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'fn_AnticipatedRevenue')
	DROP FUNCTION dbo.fn_AnticipatedRevenue


-- In this project, you will start to develop data components for the Hotel On-time Booking System (HOBS). 
-- The purpose of the system is to help in planning vacancies, reservations, and revenue for SQL Hotels, Inc. 
-- Use your freshly created (since 5-A) database on TITAN: YOURLASTNAME_HOTEL to run your script against.

-- 1A. Write a user-defined function named dbo.ProduceBill that accepts only the input parameter 'ReservationDetailID' 
--     to generate a printed bill (nothing fancy - use SELECT statements) displaying the guest's information (Name, 
--     address, etc), reservation details (Hotel Name, Room #, Check-in Date, Check-Out Date, Total Room Charge, 
--     Total Tax). Note: This may require more than one user defined function...and/or the use of a cursor.
PRINT '1A. Creating dbo.ProduceBill'
GO

CREATE FUNCTION dbo.fn_GetTotalTax (@ReservationDetailID smallint)
RETURNS smallmoney
AS
BEGIN
	RETURN (
		SELECT 
			dbo.fn_GetTotalRoomCharge( rd.ReservationDetailID ) * (t.RoomTaxRate / 100) AS TotalTax
		FROM ReservationDetail rd
			JOIN Discount d ON rd.DiscountID = d.DiscountID
			JOIN Room r ON rd.RoomID = r.RoomID
			JOIN Hotel h ON r.HotelID = h.HotelID
			JOIN TaxRate t ON h.TaxLocationID = t.TaxLocationID
		WHERE rd.ReservationDetailID = @ReservationDetailID
	)
END

GO

CREATE FUNCTION dbo.fn_GetTotalRoomCharge(@ReservationDetailID smallint)
RETURNS smallmoney
AS
BEGIN
	RETURN (
		SELECT 
			(rd.QuotedRate * Nights) * ((100 - d.DiscountPercent) / 100) - d.DiscountAmount 
				AS TotalRoomCharge
		FROM ReservationDetail rd
			JOIN Discount d ON rd.DiscountID = d.DiscountID
			JOIN Room r ON rd.RoomID = r.RoomID
			JOIN Hotel h ON r.HotelID = h.HotelID
			JOIN TaxRate t ON h.TaxLocationID = t.TaxLocationID
		WHERE rd.ReservationDetailID = @ReservationDetailID
	)
END

GO

CREATE FUNCTION dbo.fn_ProduceBill (@ReservationDetailID smallint)
RETURNS @Report table (
	FirstName varchar(30),
	LastName varchar(30),
	Address varchar(64),
	City varchar(32),
	State char(2),
	PostalCode varchar(32),
	Country varchar(32),
	HotelName varchar(32),
	RoomNumber varchar(5),
	CheckinDate smalldatetime,
	CheckoutDate smalldatetime,
	TotalRoomCharge smallmoney,
	TotalTax smallmoney
)
AS
BEGIN
	INSERT INTO @Report

		SELECT 
			GuestFirst AS FirstName,
			GuestLast AS LastName,
			GuestAddress1 AS Address,
			GuestCity AS City,
			GuestState AS State,
			GuestPostalCode AS PostalCode,
			GuestCountry AS Country,
			h.HotelName AS HotelName,
			r.RoomNumber AS RoomNumber,
			rd.CheckinDate AS CheckinDate,
			rd.CheckinDate + Nights AS CheckoutDate,
			-- Calculate room charge
			dbo.fn_GetTotalRoomCharge( rd.ReservationDetailID ) AS TotalRoomCharge,
			dbo.fn_GetTotalTax( rd.ReservationDetailID ) AS TotalTax
		FROM ReservationDetail rd
			JOIN Reservation res ON rd.ReservationID = res.ReservationID
			JOIN CreditCard cc ON res.CreditCardID = cc.CreditCardID
			JOIN Guest g ON cc.GuestID = g.GuestID
			JOIN Room r ON rd.RoomID = r.RoomId
			JOIN Hotel h ON r.HotelID = h.HotelID
		WHERE ReservationDetailID = @ReservationDetailID
	
	RETURN
END
GO
-- 1B. Demonstrate this function with a query that contains a master reservation number (pick one starting with 5000). 
--     Then, starting with ReservationDetailID 1, Loop through calling dbo.ProduceBill and displaying (if count > 0) 
--     the bill for each Reservation Detail associated with that reservation number.
PRINT '1B.  Demonstrating the dbo.ProduceBill function'

DECLARE @ResDetailStopPoint smallint
DECLARE @ReservationID smallint
DECLARE @ReservationDetailIDPostion smallint

SET @ReservationID = 5010 --(The Reservation # you want the details for)
SET @ReservationDetailIDPostion = 1 --(Starting Res Detail # in the table)
 

-- Modified this from the sample so that only one row is returned (makes more sense to me)
SELECT TOP 1 @ResDetailStopPoint = ReservationDetailID
FROM ReservationDetail
WHERE ReservationID = @ReservationID
ORDER BY ReservationDetailID DESC

--Here is the loop
WHILE (@ReservationDetailIDPostion <= @ResDetailStopPoint)
BEGIN

	--As long as there's at least 1 row returned....
	IF (
		SELECT COUNT(*) 
		FROM ReservationDetail
		WHERE ReservationDetailID = @ReservationDetailIDPostion 
			AND ReservationID = @ReservationID
	) > 0
		SELECT *	
		FROM dbo.fn_ProduceBill( @ReservationDetailIDPostion )

		SET @ReservationDetailIDPostion = @ReservationDetailIDPostion +1
END

GO

-- 2A. Write a user-defined function named dbo.AnticipatedRevenue to calculate the total actual (Status="B") plus 
--     anticipated (Status = "A") revenue and taxes from the reservations details table, given a date range input 
--     parameter (Use Error Handling if first date > ending date)*. The function returns a table containing the total 
--     revenue and tax for each hotel number, for a given date range. Remember, Revenue is based off of Checkout, 
--     not Check-in date. *Note: Functions do not allow RAISERROR, like stored procedures, so at a minimum, you'll 
--     have to return the error through the function (in this case, as a table entry). HINT: you can query the 
--     returned table to find out if the error was written to it, delete the error entry, and notify the user. See 
--     Clues
PRINT '2A. Creating dbo.AnticipatedRevenue'
GO
CREATE FUNCTION dbo.fn_AnticipatedRevenue (@1stDate smalldatetime, @2ndDate smalldatetime)

RETURNS @Report Table (
	Revenue smallmoney,
	Taxes smallmoney,
	Error varchar(64)
)

AS

BEGIN
	DECLARE @ERROR varchar(64)

	IF (@1stDate > @2ndDate)
	BEGIN
		SET @ERROR = 'The 2nd Date is less than the first date'
		INSERT INTO @Report VALUES (NULL, NULL, @ERROR)
	END

	ELSE

	BEGIN
		DECLARE @Revenue numeric
		DECLARE @Taxes  numeric

		SELECT
			@Revenue = TotalRoomCharge,
			@Taxes = TotalRoomTax
		-- Break this out, for readability sake
		FROM (
			SELECT
				SUM( dbo.fn_GetTotalRoomCharge( rd.ReservationDetailID ) ) AS TotalRoomCharge,
				SUM( dbo.fn_GetTotalTax( rd.ReservationDetailID ) ) AS TotalRoomTax
			FROM ReservationDetail rd
				JOIN Room r ON rd.RoomID = r.RoomID
				JOIN Hotel h ON r.HotelID = h.HotelID
					JOIN TaxRate t ON h.TaxLocationID = t.TaxLocationID
			WHERE CheckinDate + Nights BETWEEN @1stDate AND @2ndDate
				AND rd.Status IN ('A','B')
		) a
		-- the real data with @Error = NULL
		INSERT INTO @Report VALUES (
			@Revenue, @Taxes, NULL
		)
	END

	RETURN
END

GO

-- 2B. After defining this function, pass in the dates 31 Mar - 1 Mar (yes that's right, so we can test the error),
PRINT '2B. Testing error with invalid dates'

SELECT * FROM dbo.fn_AnticipatedRevenue( '03-31-2008', '03-01-2008' )

-- 2C. Do it again with the correct date sequence of 1 Mar - 31 Mar to test it out.
PRINT '2C. Testing dates with correct sequence'

SELECT * FROM dbo.fn_AnticipatedRevenue( '03-01-2008', '03-31-2008' )