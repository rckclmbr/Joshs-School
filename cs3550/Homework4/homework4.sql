USE Braegger_Hotel

DECLARE @GUEST  smallint
DECLARE @CREDITCARD smallint
DECLARE @DISCOUNT smallint
DECLARE @RESERVATION smallint

PRINT 'Beginning #1 - I''m inserting myself as a new guest....' 

INSERT INTO Guest (
		GuestFirst, GuestLast, GuestAddress1, GuestCity, 
		GuestState, GuestPostalCode, GuestCountry, GuestPhone, GuestEmail
)
VALUES (
	'Josh', 'Braegger', '123 Hickory Street', 'Bountiful',
	'UT', '84010', 'USA', '801-555-5555', 'jbraegger@mail.weber.edu'
)

SET @GUEST = @@IDENTITY -- Save the GuestID for later

PRINT 'Here is the result of the Guest Table after I inserted myself...'
PRINT ''

SELECT * FROM Guest

PRINT 'Beginning #2 - Insert myself into CreditCard table'

-- Write a statement to add a new Credit Card for yourself (using @@IDENTITY to determine Guest ID Number).

INSERT INTO CreditCard(GuestID, CCType, CCNumber, CCCompany, CCCardHolder, CCExpiration)
VALUES (@GUEST, 'AMEX', '1234123412341234', 'Chase', 'Josh Braegger', '11-22-2009');

PRINT 'Inserted myself, here are the results'
PRINT ''

SELECT * FROM CreditCard

SET @CREDITCARD = @@IDENTITY -- Save the CreditCardID for later

PRINT 'Beginning #3 - Updating Room Rates'

-- Rich's B&B is expanding. They want to decrease their single room rates 5% (Rounding down 
-- to the nearest dollar) and increase their other room rates 5% (Rounding up to the nearest dollar) 
-- for all their rooms. They also want to introduce a new student coupon of $5 (expires 12/31/2008) 
-- for all WSU CS 3550 students. A student must currently be enrolled in CS 3550 to use this coupon. 
-- Write Statements to make these adjustments.

UPDATE HotelRoomType
SET 
	RoomTypeRackRate = CASE 
		WHEN RoomType LIKE '%Single%' -- Single rooms  
			THEN FLOOR(.95 * RoomTypeRackRate)
		ELSE
			CEILING(.95 * RoomTypeRackRate)
		END
WHERE HotelID = 2100 -- Rich's Bed and Breakfast

PRINT 'Updated Room Rates, Here are the results:'
PRINT ''

SELECT * FROM HotelRoomType

PRINT 'Introducing new student coupon'

INSERT INTO Discount (
	DiscountDescription, DiscountExpiration, DiscountRules, DiscountPercentage, 
	DiscountAmount
)
VALUES (
	'New student coupon - $5', '12/31/2008', 'For enrolled CS 3550 students only', 0.00, 
	5.00
)

SET @DISCOUNT = @@IDENTITY

PRINT 'Inserted new student coupon, here are the results'
PRINT ''

SELECT * FROM Discount

PRINT 'Beginning #4 - Making a reservation for myself'

-- Make a (multiple details) reservation for yourself at Rich's B&B, using a single reservation 
-- id for both details.

PRINT 'Inserting into Reservation'

INSERT INTO Reservation(CreditCardID) VALUES (@CREDITCARD)

PRINT 'Details from Reservation Insert'
PRINT ''

SELECT * FROM Reservation

SET @RESERVATION = @@IDENTITY

PRINT 'Inserting first ReservationDetail'

INSERT INTO ReservationDetail(RoomID, ReservationID, QuotedRate, CheckinDate, Nights, DiscountID)
(
	SELECT RoomID, @RESERVATION, 29.00, '02-26-2008', 3, @DISCOUNT
	FROM Hotel h
		JOIN Room r ON r.HotelID = h.HotelID
	WHERE r.RoomNumber = 302
		AND h.HotelName = 'Rich''s Bed and Breakfast'
)

PRINT 'Inserting second ReservationDetail'

INSERT INTO ReservationDetail(RoomID, ReservationID, QuotedRate, CheckinDate, Nights, DiscountID)
(
	SELECT RoomID, @RESERVATION, 29.00, '03-06-2008', 3, @DISCOUNT
	FROM Hotel h
		JOIN Room r ON r.HotelID = h.HotelID
	WHERE r.RoomNumber = 302
		AND h.HotelName = 'Rich''s Bed and Breakfast'
)

PRINT 'ReservationDetail results'
PRINT ''

SELECT * FROM ReservationDetail

PRINT 'Beginning #5 - UPDATE all Active Reservation Details...'

-- UPDATE all Active Reservation Details ('A' status) with a Checkout Date (Hint: Calculated) 
-- on or Before 1/31/08 to 'B' for billed.

UPDATE ReservationDetail
SET Status = 'B'
WHERE Status = 'A'
	AND (CheckinDate + Nights) <= '01/31/08'

PRINT 'Updated Active Reservations, here are the results:'
PRINT ''

SELECT * FROM ReservationDetail

PRINT 'Beginning #6 - Updating University Guest House to HotelID 3300 (Removed from assignment)'
PRINT ''

-- The University Guest House would like to UPDATE their Hotel ID to 3300. Make sure the HotelRoomType 
-- data automatically reflects this change, by changing the Hotel ID once in the Hotel Table only. 
-- Hint: This will require a CASCADE UPDATE to be turned on in your foreign key constraint, (ALTER TABLE) 
-- if you haven't already done so.

-- DONT NEED TO DO!

PRINT 'Beginning Number 7 - SQL Select Statements'

-- Write SQL SELECT statements to perform the following queries. Include all fields in the output that 
-- you think would be relevant. If a query is too complex for a single select statement, define one or 
-- more views, and then query the views.

PRINT 'Beginning 7a'
PRINT ''

-- List the hotel name, room number, room description, and rental price of all 
-- double and family rooms (all types) with a price at or below $199.00 per night, 
-- in ascending order by formatted price.

SELECT h.HotelName, r.RoomID, r.RoomDescription, 
	'$' + CONVERT(varchar(12), rt.RoomTypeRackRate,1 ) AS RackRate
FROM Hotel h
	JOIN HotelRoomType rt ON h.HotelID = rt.HotelID
	JOIN Room r ON r.HotelRoomTypeID = rt.HotelRoomTypeID
WHERE rt.RoomTypeRackRate <= 199.00
ORDER BY '$' + CONVERT(varchar(12), rt.RoomTypeRackRate,1)  ASC

PRINT 'Beginning 7b'
PRINT ''

-- For each hotel, list the (first word only of the) hotel name, count of rooms 
-- by floor, and formatted average room rental rate for all rooms at the property. 
-- Hint: Use Substring/Len/PatIndex Function(s).

SELECT h.HotelName, -- TODO: First word only
	SUBSTRING(r.RoomNumber, 1, 1) AS [Floor], 
	COUNT(r.RoomNumber) AS RoomsOnFloor, 
	'$' + CONVERT(varchar(12), 
		AVG(rt.RoomTypeRackRate), 1) AS AvgRoomRate
FROM Hotel h
	JOIN HotelRoomType rt ON h.HotelID = rt.HotelID
	JOIN Room r ON r.HotelRoomTypeID = rt.HotelRoomTypeID
GROUP BY h.HotelName, SUBSTRING(r.RoomNumber, 1, 1)

PRINT 'Beginning 7c'
PRINT ''

-- For check-ins during February, what was the total number of bookings, the average 
-- (decimal) length of stay for each hotel by hotel name?

SELECT h.HotelName, COUNT(*) AS Bookings,
	AVG( CAST(Nights AS decimal) ) AS AvgNights
FROM Hotel h
	JOIN Room r ON h.HotelID = r.HotelID
	JOIN ReservationDetail rd ON rd.RoomID = r.RoomID
WHERE DatePart("M", rd.CheckinDate) = 2 -- Only in February
GROUP BY h.HotelName

PRINT 'Beginning 7d'
PRINT ''

-- For check-ins during January & February, what is the most commonly booked room type 
-- (ignoring length of stay) for each hotel name?

SELECT h.HotelName, MAX(rt.RoomType) AS MostCommonRoomType
FROM Hotel h
	JOIN HotelRoomType rt ON rt.HotelID = h.HotelID
	JOIN Room r ON rt.HotelRoomTypeID = r.HotelRoomTypeID
	JOIN ReservationDetail rd ON rd.RoomID = r.RoomID
WHERE DatePart("M", rd.CheckinDate) IN (1,2) -- January and February
GROUP BY h.HotelName

PRINT 'Beginning 7e'
PRINT ''

-- For each hotel, List the hotel name, and how many different (unique) guests lodged 
-- at the hotel in Jan and Feb (group by Month).

SELECT h.HotelName, DatePart(M, rd.CheckinDate) AS CheckinMonth, COUNT(DISTINCT cc.GuestID) AS NumGuests
FROM Hotel h
	JOIN HotelRoomType rt ON rt.HotelID = h.HotelID
	JOIN Room r ON rt.HotelRoomTypeID = r.HotelRoomTypeID
	JOIN ReservationDetail rd ON rd.RoomID = r.RoomID
	JOIN Reservation res ON res.ReservationID = rd.ReservationID
	JOIN CreditCard cc ON cc.CreditCardID = res.CreditCardID
WHERE DatePart("M", rd.CheckinDate) IN (1,2)
GROUP BY h.HotelName,
	DatePart(M, rd.CheckinDate)

PRINT 'Beginning 7f'
PRINT ''

-- List the guest name (formatted last comma first. Example: Fry, Richard), hotel name, 
-- room number, arrival date, and departure date for all bookings in which the arrival 
-- date is a Monday-Thursday. The date format should be like FEB 29 2008. Hint: Use 
-- DatePart Function.

SELECT g.GuestLast + ', ' + g.GuestFirst, h.HotelName, r.RoomNumber, 
	UPPER(
		SUBSTRING( CONVERT(varchar, rd.CheckinDate, 9), 1, 11)
	) AS ArrivalDate, 
	UPPER( 
		SUBSTRING( CONVERT(varchar, (rd.CheckinDate + nights), 9), 1, 11)
	) AS DepartureDate
FROM Hotel h
	JOIN Room r ON h.HotelID = r.HotelID
	JOIN ReservationDetail rd ON rd.RoomID = r.RoomID
	JOIN Reservation res ON res.ReservationID = rd.ReservationID
	JOIN CreditCard cc ON cc.CreditCardID = res.CreditCardID
	JOIN Guest g ON g.GuestID = cc.GuestID
WHERE DatePart(dw, rd.CheckinDate) IN (2,3,4,5) -- Mon-Thurs

PRINT 'Beginning 8'
PRINT ''

-- Assume, it is March 6th, and you just called to cancel your reservation for tonight 
-- (the one made above in #4). You will need to cancel your reservation detail 
-- (Status change to 'C'), but the hotel will still need to collect 1 night room and tax 
-- (see business rules) since it's less than 48 hours. Since you have no 'A' Active 
-- reservation details anymore, go ahead and also UPDATE the Status of the master 
-- Reservation Table to 'C', Cancelled, as well. Then, add the reservationdetailbilling 
-- and revenue entries as well.

PRINT 'Beginning 8a - Updating all "A" statuses to "C" statuses in ReservationDetail'
PRINT ''

-- Change the "A" status in the Reservations Details Table to a "C" status for cancelled

UPDATE ReservationDetail
SET Status = 'A'
WHERE Status = 'C'

PRINT 'Updated, here are the results:'
PRINT ''

SELECT * FROM ReservationDetail

PRINT 'Beginning 8b - Updating all "A" statuses to "C" statuses in Reservation'
PRINT ''

-- Change the "A" status in the Reservations Table to a "C" status for cancelled, as well.

UPDATE Reservation
SET ReservationStatus = 'A'
WHERE ReservationStatus = 'C'

PRINT 'Updated, here are the results:'
PRINT ''

SELECT * FROM Reservation

PRINT 'Beginning 8c'
PRINT ''

-- Insert two line items into the ReservationDetailBilling Table, with the calculated 
-- room revenue (1 night less any discounts) and calculated tax revenue (room revenue * 
-- tax rate) with appropriate comments.

PRINT 'Beginning 8d'
PRINT ''

-- Insert the master Revenue entry for these two items. Specifying the Revenue Type 
-- as "Cancellation", Today's Date, and "AMEX" as the payment type.

PRINT 'Beginning 9'
PRINT ''

-- Generate a report showing anticipated room revenue (and tax) for each hotel, for the 
-- month of February. Hint: Anticipated revenue is determined by calculating any discounts 
-- times quoted rate times length of stay (with a Checkout date in February). The 
-- formatted result should be displayed as money. Again, if the query is too complex for 
-- a single select statement, define one or more views, and then query the views.

SELECT h.HotelName,
	'$' + CONVERT(varchar(24), 
		CAST(
			SUM(
				CASE 
					WHEN d.DiscountID IS NOT NULL
						THEN( (100 - d.DiscountPercentage) / 100 * rd.QuotedRate)
					ELSE  -- Looks like this doesn't happen, but *shrug*
						rd.QuotedRate
				END * Nights
			)
		AS smallmoney)
	, 1) AS AnticipatedRevenue
FROM Hotel h
	JOIN Room r ON h.HotelID = r.HotelID
	JOIN ReservationDetail rd ON rd.RoomID = r.RoomID
	LEFT JOIN Discount d ON rd.DiscountID = d.DiscountID
WHERE DatePart(M, rd.CheckinDate + rd.nights) = 2 -- February only
GROUP BY h.HotelName

PRINT 'Beginning 10'
PRINT ''

-- Add at least 4 non-clustered indexes, and one clustered index to your columns/tables 
-- of your choice. Your non-clustered indexes should make sense from a performance 
-- point of view. However, your clustered index is probably not realistic in this scenario -
-- only to make sure you know how to do it.

-- #1-  2  Points
-- #2 - 2  Points
-- #3 - 2  Points
-- #4 - 2  Points
-- #5 - 2  Points
-- #6 - 3  Points
-- #7 - 18 Points (6 each)
-- #8 - 3  Points
-- #9 - 3  Points
-- #10- 3 Points

-- Total 40 Points