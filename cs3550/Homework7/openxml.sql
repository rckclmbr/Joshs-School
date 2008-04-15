-- Josh Braegger

-- 7.  Apply OPENXML to this XML document, using Element-Centric mapping.  Show guestid, guestfirst, guestlast, and Check-in ONLY 
--     for each guest.  Save the document as openxml.sql.

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

SELECT * FROM OPENXML (@idoc, '/ROOT/guests', 0)
WITH(
	GuestID varchar(4) 'guestid',
	GuestFirst varchar(64) 'guestfirst',
	GuestLast varchar(64) 'guestlast',
	CheckinDate smalldatetime 'bookings/CheckinDate'
)