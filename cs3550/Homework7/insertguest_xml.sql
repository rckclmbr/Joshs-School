-- Josh Braegger

-- USE Braegger_Hotel (Not needed in assignment submission)

-- 8.  Using the same raw XML above, use OPENXML to Insert GuestId, GuestFirst, and GuestLast (Plus fake data for these required 
--     fields: Address, City, Country, Postal Code, and Phone) into the HOTEL Guest Table (I will run the script against my 
--     database so, in this case don't specify "USE" in your script).  Note:  You may also need to SET IDENTITY_INSERT Guest ON, 
--     so you can turn off the auto IDENTITY, and manually insert new guest ids.  Save the document as insertguest_xml.sql.

DECLARE @idoc int
DECLARE @xmldoc nvarchar(4000)

SET @xmldoc ='<ROOT><guests>
<guestid>2318</guestid>
<guestfirst>Ben</guestfirst>
<guestlast>Sala</guestlast>
<bookings><CheckinDate>2008-04-28</CheckinDate>
<Nights>4</Nights>
</bookings>
</guests>
<guests>
<guestid>2331</guestid>
<guestfirst>Chris</guestfirst>
<guestlast>Walls</guestlast>
<bookings><CheckinDate>2008-05-02</CheckinDate>
<Nights>2</Nights>
</bookings>
</guests>
<guests>
<guestid>2263</guestid>
<guestfirst>Tim</guestfirst>
<guestlast>Daley</guestlast>
<bookings><CheckinDate>2008-04-15</CheckinDate>
<Nights>2</Nights>
</bookings>
</guests>
<guests>
<guestid>2280</guestid>
<guestfirst>Danny</guestfirst>
<guestlast>Massimini</guestlast>
<bookings><CheckinDate>2008-05-11</CheckinDate>
<Nights>3</Nights>
</bookings>
</guests></ROOT>'

EXEC sp_xml_preparedocument @idoc OUTPUT, @xmldoc

SET IDENTITY_INSERT Guest ON

INSERT INTO Guest (GuestID, GuestFirst, GuestLast, GuestAddress1, GuestCity, GuestCountry, GuestPostalCode, GuestPhone)
SELECT GuestID, GuestFirst, GuestLast, 'address1', 'Somewhere', 'Canada', 'N0B 1C0', '801-555-5555'
FROM OPENXML (@idoc, '/ROOT/guests', 0)
	WITH(
		GuestID varchar(4) 'guestid',
		GuestFirst varchar(64) 'guestfirst',
		GuestLast varchar(64) 'guestlast'
	)