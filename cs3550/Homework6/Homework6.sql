use Braegger_Hotel;

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'tr_UpdateReservation')
	DROP TRIGGER tr_UpdateReservation

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'tr_InsertRevenue')
	DROP TRIGGER tr_InsertRevenue

-- 1. Write a trigger named tr_UpdateReservation (column update) that will be invoked when a 
--    ReservationDetails table 'status' field is changed.

GO

CREATE TRIGGER tr_UpdateReservation
ON ReservationDetail
FOR UPDATE 
AS
	DECLARE @ReservationDetailID smallint
	DECLARE @InsertedCheckinDate smalldatetime
	DECLARE @InsertedNights tinyint
	DECLARE @Status char(1)
	
	SELECT
		@ReservationDetailID = i.ReservationDetailID,
		@InsertedNights = i.Nights,
		@InsertedCheckinDate = i.CheckinDate,
		@Status = i.Status
	FROM Inserted i
	
--   * If ReservationDetail status is updated to 'C' for cancelled, and it's less than 48 hours 
--     (as of 6PM), run the appropriate statements to INSERT a Room and a Tax entry in the 
--     ReservationDetailsBilling table, for one night. For demonstration purposes, just hard code 
--     and use any existing reservationdetailID.
	IF @Status = 'C'
			AND DATEDIFF (HOUR, GetDate(), @InsertedCheckinDate) <= 48
		SET @InsertedNights = 1


--   * If Reservation Status changes to 'B' for Billed, run the appropriate statements to INSERT a Room 
--     and a Tax entry in the ReservationDetailsBilling Table (factoring in the late checkout surcharge 
--     policy*). 
--     *Checkout time is Noon. Guest is given a one hour grace period. After 1PM, 50% of one night's 
--     room charge is added (plus tax). After 4PM, a full night's room and tax is added.

	IF @Status = 'B' -- If Status == 'b'
		IF DATEDIFF (HOUR, @InsertedCheckinDate + @InsertedNights, GetDate()) >= 16
			SET @InsertedNights = @InsertedNights + 1
		ELSE IF DATEDIFF (HOUR, @InsertedCheckinDate + @InsertedNights, GetDate()) >= 13
			SET @InsertedNights = @InsertedNights + .5

	PRINT 'Updating nights based on rules'
	-- Update the reservation nights based on rules
	UPDATE ReservationDetail
	SET
		Nights = @InsertedNights
	WHERE ReservationDetailID = @ReservationDetailID 

	PRINT 'Inserting Tax Entry'
	-- Insert Tax Entry
	INSERT INTO ReservationDetailBilling (ReservationDetailID, BillingCategoryID,	
		BillingDescription, BillingAmount, BillingItemQty, BillingItemDate)
	VALUES (
		@ReservationDetailID,
		2, -- Lodging Tax
		'Tax',
		dbo.fn_getTotalTax( @ReservationDetailID ),
		1,
		GetDate()
	)

	PRINT 'Inserting Room Entry'
	-- Insert Room Entry
	INSERT INTO ReservationDetailBilling (ReservationDetailID, BillingCategoryID,	
		BillingDescription, BillingAmount, BillingItemQty, BillingItemDate)
	VALUES (
		@ReservationDetailID,
		1, -- Lodging
		'Room',
		dbo.fn_getTotalRoomCharge( @ReservationDetailID ),
		1,
		GetDate()
	)

-- 2. Write a trigger named tr_InsertRevenue that will be invoked when a entry is inserted into the table 
--    ReservationDetailsBilling . If Revenue Type is 'Room', then call dbo.ProduceBill  (from HW 5B), getting 
--    the ReservationID by joining the ReservationDetailsID from the inserted table to the ReservationDetails 
--    table then joining the ReservationDetails table to the Reservation table.
GO

CREATE TRIGGER tr_InsertRevenue
ON ReservationDetailBilling
AFTER INSERT 
AS
	DECLARE @ReservationDetailID smallint
	DECLARE @BillingCategoryID smallint

	SELECT 
		@ReservationDetailID = i.ReservationDetailID,
		@BillingCategoryID = i.BillingCategoryID
	FROM Inserted i
		
	IF @BillingCategoryID = 1 -- BillingCategory is 'Lodging' (room)
		SELECT * FROM dbo.fn_ProduceBill( @ReservationDetailID )

GO
-- 3. Assume today is (15 April 2008 at 2PM)*. *Change system date/time on computer, if necessary. Ian Stuart 
--    is due to check out today from the University Guesthouse. Run sp_UpdateResDetail (from HW 5A) to change 
--    the status of his reservation to 'B'. Note: This should automatically invoke Trigger 1 (factoring in the 
--    late charge), which automatically invokes 2, and calls dbo.ProduceBill, and produces a bill.

sp_UpdateResDetail
@ReservationDetailID = 4, -- Ian's reservation
@Status = 'B'

SELECT r.*, rd.*, h.*, g.*
FROM Reservation r
	JOIN ReservationDetail rd ON r.ReservationID = rd.ReservationID
	JOIN CreditCard cc ON r.CreditCardID = cc.CreditCardID
	JOIN Guest g ON cc.GuestID = g.GuestID
	JOIN Room rm ON rd.RoomId = rm.RoomID
	JOIN Hotel h ON h.HotelID = rm.HotelID

-- 4. Again, Assume today is (15 April 2008 at 2PM). Swen Swenson wants to cancel his April 24th Reservation 
--    at Rich's B&B. Run sp_UpdateResDetail to change the status of his reservation to 'C'. This shouldn't 
--    invoke a trigger because you're still within 48 hours of the cancellation policy.

sp_UpdateResDetail
@ReservationDetailID = 4, -- Ian's reservation
@Status = 'B'

-- 5. Run a SELECT statement on the ReservationDetailsBilling Table showing your Triggers worked.

PRINT 'Showing results:'
PRINT ''

SELECT * FROM ReservationDetailBilling

-- 6. Write a trigger called tr_InsertReservationDetail that will automatically insert the Default Room Rack 
--    Rate (from the Room Types Table) into the Quoted Rate field (in lieu of the user's input), when a 
--    reservation detail entry is inserted into the table.

-- 6B. Demonstrate this trigger by entering a reservation detail for an existing reservation of your choice. 
--     Go ahead and supply quoted rate (any rate). The INSTEAD OF trigger should overwrite your entry with 
--     the correct Rack Rate.

-- Set your SYSTEM CLOCK BACK TO THE CORRECT TIME!
