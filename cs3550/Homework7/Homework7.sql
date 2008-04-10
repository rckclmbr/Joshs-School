/*
	Josh Braegger
	CS3550
	Homework 7
*/

USE Braegger_Hotel

IF EXISTS (SELECT name FROM sysobjects WHERE name = 'sp_InsertGuest' AND type = 'P')
	DROP PROC sp_InsertGuest

-- 1.  In your script, add a linkedserver called 'TITAN-YOURLASTNAME' that points to the the Titan Server.

USE MASTER
GO
Exec sp_addlinkedserver
@server='TITAN-BRAEGGER',
@srvproduct='',
@provider='MSDASQL',
@provstr='DRIVER={SQL Server};SERVER=titan.cs.weber.edu,10433;UID=Test_User;PWD=test_password;Initial Catalog=Fry_Hotel'

GO

Exec sp_serveroption 'TITAN', 'data access', 'true'
Exec sp_serveroption 'TITAN', 'rpc', 'true'--enables from the REMOTE to LOCAL server
Exec sp_serveroption 'TITAN', 'rpc out', 'true' -- enables from the LOCAL to REMOTE server
Exec sp_serveroption 'TITAN', 'collation compatible', 'true'

-- 2.  Add a User called 'UK_User' and the password 'UK_Test' to the linked server.  Set Self = "True", because there is already a 
--     UK_User created in the UK_HOBS database.
PRINT '2.  Adding user ''UK_User'' with password ''UK_Test'''

Exec sp_addlinkedsrvlogin
@rmtsrvname='TITAN',
@useself='true',
@locallogin='jbraegger',
@rmtuser='UK_User', 
@rmtpassword='UK_Test'


-- 3.  Using the Linked Server, perform the following queries on the UK_HOBS, to determine the layout and contents of the tables.
PRINT '3.  Queries Linked Server to determine layout'

SELECT * FROM OPENQUERY ('TITAN-BRAEGGER', 'SELECT * FROM UK_Hobs.dbo.Hotels') as passthrough
SELECT * FROM OPENQUERY ('TITAN-BRAEGGER', 'SELECT * FROM UK_Hobs.dbo.Bookings') as passthrough
SELECT * FROM OPENQUERY ('TITAN-BRAEGGER', 'SELECT * FROM UK_Hobs.dbo.Guests') as passthrough
SELECT * FROM OPENQUERY ('TITAN-BRAEGGER', 'SELECT * FROM UK_Hobs.dbo.Rooms') as passthrough
SELECT * FROM OPENQUERY ('TITAN-BRAEGGER', 'SELECT * FROM UK_Hobs.dbo.Room_Type') as passthrough

-- 4.  Create a Modified version of the stored procedure (sp_InsertGuest) you created in HW 5A to INSERT INTO the UK_HOBS database 
--     instead of your own database (using Linked Server).   Demonstrate this stored procedure by executing it, and adding yourself 
--     as a guest to the UK_HOBS database.  Note:  You may need to set RPC IN/OUT on your linked server (I've already done it on 
--     UK_HOBS).

PRINT '4.  Creating modified version of sp_InsertGuest to INSERT INTO Other database instead of this.'
GO

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

INSERT OPENQUERY ('TITAN-BRAEGGER', 
	'SELECT GuestFirst, GuestLast, GuestAddress1, GuestAddress2, GuestCity, GuestState, GuestPostalCode, GuestCountry,
		GuestPhone, GuestEmail, GuestComments
	FROM Guest')
VALUES (@GuestFirst, @GuestLast, @GuestAddress1, @GuestAddress2, @GuestCity, @GuestState, @GuestPostalCode, @GuestCountry,
@GuestPhone, @GuestEmail, @GuestComments)

GO

PRINT '    ... Inserting myself'



-- 5.  Using OpenQuery, Write a statement that SELECTS information about Hotel Names and Cities, their Room Types, and Formatted 
--     Prices* (from both databases), and presents them together (UNION), sorted by Hotel Name and Room Types.



-- 6.  Using OpenRowSet, Write a query that SELECTS the Reservation Detail # (Booking # in the UK Database), Guest Last Name, 
--     Formatted Quoted Rate*, and Check-in Date from Both Databases, and presents all the details together, sorted by Guest Last 
--     Name.


-- XML

-- 7.  Apply OPENXML to this XML document, using Element-Centric mapping.  Show guestid, guestfirst, guestlast, and Check-in ONLY 
--     for each guest.  Save the document as openxml.sql.



-- 8.  Using the same raw XML above, use OPENXML to Insert GuestId, GuestFirst, and GuestLast (Plus fake data for these required 
--     fields: Address, City, Country, Postal Code, and Phone) into the HOTEL Guest Table (I will run the script against my 
--     database so, in this case don't specify "USE" in your script).  Note:  You may also need to SET IDENTITY_INSERT Guest ON, 
--     so you can turn off the auto IDENTITY, and manually insert new guest ids.  Save the document as insertguest_xml.sql.

--     *Note the Exchange Rate (2.075 dollars = 1 pound).  So, display the quoted rate (from HOBS_UK) in US Dollars based on exchange 
--      rate.