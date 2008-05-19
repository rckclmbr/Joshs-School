/*
	Josh Braegger
	CS3550
	Homework 7
*/

USE Braegger_Hotel

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertGuest' AND type = 'P')
	DROP PROC sp_InsertGuest

-- 1.  In your script, add a linkedserver called 'TITAN-YOURLASTNAME' that points to the the Titan Server.
PRINT '1.  Creating linkedserver TITAN_BRAEGGER'

USE MASTER
GO

Exec sp_addlinkedserver
@server='TITAN_BRAEGGER',
@srvproduct='',
@provider='MSDASQL',
@provstr='DRIVER={SQL Server};SERVER=titan.cs.weber.edu,10433;UID=UK_User;PWD=UK_Test;Initial Catalog=Braegger_Hotel'

GO

Exec sp_serveroption 'TITAN_BRAEGGER', 'data access', 'true'
Exec sp_serveroption 'TITAN_BRAEGGER', 'rpc', 'true'--enables from the REMOTE to LOCAL server
Exec sp_serveroption 'TITAN_BRAEGGER', 'rpc out', 'true' -- enables from the LOCAL to REMOTE server
Exec sp_serveroption 'TITAN_BRAEGGER', 'collation compatible', 'true'

USE Braegger_Hotel

-- 2.  Add a User called 'UK_User' and the password 'UK_Test' to the linked server.  Set Self = "True", because there is already a 
--     UK_User created in the UK_HOBS database.
PRINT '2.  Adding user ''UK_User'' with password ''UK_Test'''

Exec sp_addlinkedsrvlogin
@rmtsrvname='TITAN_BRAEGGER',
@useself='true',
@locallogin='THESHIZNIT\arnie',
@rmtuser='UK_User', 
@rmtpassword='UK_Test'


-- 3.  Using the Linked Server, perform the following queries on the UK_HOBS, to determine the layout and contents of the tables.
PRINT '3.  Querying Linked Server to determine layout'

/* TODO: Uncomment
SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Hotels') as passthrough
SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Bookings') as passthrough
SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Guests') as passthrough
SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Rooms') as passthrough
SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Room_Type') as passthrough
*/

-- 4.  Create a Modified version of the stored procedure (sp_InsertGuest) you created in HW 5A to INSERT INTO the UK_HOBS database 
--     instead of your own database (using Linked Server).   Demonstrate this stored procedure by executing it, and adding yourself 
--     as a guest to the UK_HOBS database.  Note:  You may need to set RPC IN/OUT on your linked server (I've already done it on 
--     UK_HOBS).

PRINT '4.  Creating modified version of sp_InsertGuest to INSERT INTO Other database instead of this.'
GO

CREATE PROC sp_InsertGuest
@GuestID int,
@GuestFirst varchar(20),
@GuestLast varchar(20),
@GuestAddress varchar(30),
@GuestCity varchar(20),
@GuestPostalCode char(10),
@GuestCountry varchar(20)

AS

INSERT OPENQUERY (TITAN_BRAEGGER, 
	'SELECT GuestID, GuestFirst, GuestLast, GuestAddress, GuestCity, GuestPostalCode, GuestCountry
	FROM UK_Hobs.dbo.Guests')
VALUES (@GuestID, @GuestFirst, @GuestLast, @GuestAddress, @GuestCity, @GuestPostalCode, @GuestCountry)

GO

PRINT '    ... Inserting myself'

EXEC sp_InsertGuest
@GuestID = 3300,
@GuestFirst = 'Josh',
@GuestLast = 'Braegger',
@GuestAddress = '123 Hickory Street',
@GuestCity = 'Bountiful',
@GuestPostalCode = '84010',
@GuestCountry = 'USA'

PRINT '    ... Showing I inserted myself (should be GuestID 3300)'

SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 'SELECT * FROM UK_Hobs.dbo.Guests') as passthrough

-- 5.  Using OpenQuery, Write a statement that SELECTS information about Hotel Names and Cities, their Room Types, and Formatted 
--     Prices* (from both databases), and presents them together (UNION), sorted by Hotel Name and Room Types.
PRINT '5.  Getting Hotel information and prices from both databases'

SELECT HotelName, HotelCity, RoomType,
	'$' + CONVERT(varchar(20), CAST(RackRate AS money), 1 ) AS RackRate
FROM (
	SELECT h.HotelName, h.HotelCity, rt.RoomType,
			rt.RoomTypeRackRate AS RackRate
	FROM Hotel h
		JOIN HotelRoomType rt ON h.HotelID = rt.HotelID
	UNION
	SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 
		'SELECT h.HotelName, h.HotelCity, rt.RoomDescription AS RoomType,
			 r.RoomPrice / 2.075 AS RackRate
		 FROM UK_HOBS.dbo.Hotels h
			 JOIN UK_HOBS.dbo.Rooms r ON h.HotelNo = r.HotelNo
			 JOIN UK_HOBS.dbo.Room_Type rt ON r.RoomType = rt.RoomType')
	as passthrough
) tmp
ORDER BY HotelName

-- 6.  Using OpenRowSet, Write a query that SELECTS the Reservation Detail # (Booking # in the UK Database), Guest Last Name, 
--     Formatted Quoted Rate*, and Check-in Date from Both Databases, and presents all the details together, sorted by Guest Last 
--     Name.
PRINT '6.  Select Reservation information from both databases'

SELECT ReservationNum, GuestLast,
	'$' + CONVERT(varchar(20), CAST(QuotedRate AS money), 1 ) AS QuotedRate,
	CheckinDate
FROM (
	SELECT rd.ReservationDetailID AS ReservationNum,
		g.GuestLast,
		rd.QuotedRate,
		rd.CheckinDate
	FROM ReservationDetail rd
		JOIN Reservation r ON rd.ReservationID = r.ReservationID
		JOIN CreditCard cc ON r.CreditCardID = cc.CreditCardID
		JOIN Guest g ON g.GuestID = cc.GuestID
	UNION
	SELECT * FROM OPENQUERY (TITAN_BRAEGGER, 
		'SELECT b.BookingNo AS ReservationNum,
		g.GuestLast,
		b.BookingPrice / 2.075 AS QuotedRate,
		b.ArrivalDate AS CheckinDate
	FROM UK_HOBS.dbo.Bookings b
		JOIN UK_HOBS.dbo.Guests g ON g.GuestID = b.GuestNo')
	as passthrough
) tmp
ORDER BY GuestLast

-- XML

-- 7.  Apply OPENXML to this XML document, using Element-Centric mapping.  Show guestid, guestfirst, guestlast, and Check-in ONLY 
--     for each guest.  Save the document as openxml.sql.
PRINT '7.  (See openxml.sql)'


-- 8.  Using the same raw XML above, use OPENXML to Insert GuestId, GuestFirst, and GuestLast (Plus fake data for these required 
--     fields: Address, City, Country, Postal Code, and Phone) into the HOTEL Guest Table (I will run the script against my 
--     database so, in this case don't specify "USE" in your script).  Note:  You may also need to SET IDENTITY_INSERT Guest ON, 
--     so you can turn off the auto IDENTITY, and manually insert new guest ids.  Save the document as insertguest_xml.sql.
PRINT '8.  (See openxml.sql)'

--     *Note the Exchange Rate (2.075 dollars = 1 pound).  So, display the quoted rate (from HOBS_UK) in US Dollars based on exchange 
--      rate.