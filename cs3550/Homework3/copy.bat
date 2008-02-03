:: Josh Braegger
:: Populates the database with the csv files (It's required they're in a folder called 'data')

for %%i in (Discount Guest TaxRate CreditCard Hotel HotelRoomType Reservation ReservationDetail Revenue Room) do bcp BRAEGGER_HOTEL.dbo.%%i in data/%%i.csv -h "CHECK_CONSTRAINTS" -c -t, -r,\n -Stitan.cs.weber.edu,10433 -Ujbraegger -PC$3550 