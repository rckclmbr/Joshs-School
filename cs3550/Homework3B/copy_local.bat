:: Josh Braegger
:: Populates the database with the csv files (It's required they're in a folder called 'data')

for %%i in (Discount Guest TaxRate CreditCard Hotel HotelRoomType Room BillingCategory Reservation ReservationDetail ReservationDetailBilling RevenueCategory Revenue) do bcp.exe BRAEGGER_HOTEL.dbo.%%i in data/%%i.csv -h "CHECK_CONSTRAINTS" -c -t, -r\n -T -S .\SQLEXPRESS
