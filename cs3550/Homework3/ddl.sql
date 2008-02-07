/* Josh Braegger CS3550
 Hotel Database Creation Script */
 
USE Master
 
IF  EXISTS (
    SELECT name
        FROM sys.databases
        WHERE name = 'Braegger_Hotel')

DROP Database Braegger_Hotel
GO

CREATE DATABASE Braegger_Hotel
ON Primary
(NAME = 'Braegger_Hotel', -- Virtual Internal Name
 FILENAME = 'O:\SQLDB\Braegger_Hotel.mdf',
 SIZE = 2MB,
 MAXSIZE = 4MB, 
 FILEGROWTH = 500KB
)

LOG ON
(NAME = 'Braegger_Hotel_Log', -- Virtual Internal Name
 FILENAME = 'O:\SQLDB\Braegger_Hotel.ldf',
 SIZE = 2MB,
 MAXSIZE = 4MB, 
 FILEGROWTH = 500KB
)
GO

USE Braegger_Hotel

CREATE TABLE CreditCard
( CreditCardID	smallint	IDENTITY(1,1) NOT NULL	PRIMARY KEY,
  GuestID	smallint NOT NULL,
  CCType	varchar(5)	NOT NULL,
  CCNumber	varchar(16)	NOT NULL,
  CCCompany	varchar(40),
  CCCardHolder	varchar(40)	NOT NULL,
  CCExpiration	smalldatetime	NOT NULL
)

CREATE TABLE Guest
( GuestID	smallint	IDENTITY(1500,1) NOT NULL	PRIMARY KEY,
  GuestFirst	varchar(20)	NOT NULL,
  GuestLast	varchar(20)	NOT NULL,
  GuestAddress1	varchar(30)	NOT NULL,
  GuestAddress2	varchar(10),
  GuestCity	varchar(20) NOT NULL,
  GuestState	char(2),
  GuestPostalCode	char(10),
  GuestCountry	varchar(20) NOT NULL,
  GuestPhone	varchar(20) NOT NULL,
  GuestEmail	varchar(30),
  GuestComments	varchar(200)
)

CREATE TABLE Reservation
( ReservationID	smallint IDENTITY(5000,1) NOT NULL	PRIMARY KEY,
  CreditCardID	smallint	NOT NULL,
  ReservationDate	smalldatetime	NOT NULL DEFAULT GetDate(),
  ReservationStatus	char(1)	NOT NULL
		DEFAULT 'A'
		CONSTRAINT DC_ReservationStatus CHECK (ReservationStatus IN ('A','B','C')) ,
  ReservationComments	varchar(200)
)

CREATE TABLE ReservationDetail
( ReservationDetailID	smallint	IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  RoomID	smallint	NOT NULL,
  ReservationID	smallint	NOT NULL,
  QuotedRate	smallmoney	NOT NULL,
  CheckinDate	smalldatetime	NOT NULL,
  Nights	tinyint	NOT NULL,
  [Status]	char(1)	NOT NULL
		DEFAULT 'A'
		CONSTRAINT DC_ReservationDetailStatus CHECK ([Status] IN ('A','B','C')),  
  Comments	varchar(200),
  DiscountID	smallint	NOT NULL
)

CREATE TABLE Room
( RoomID	smallint	IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  HotelRoomTypeID	smallint	NOT NULL,
  RoomNumber	varchar(5)	NOT NULL,
  RoomDescription	varchar(200)	NOT NULL,
  Smoking	bit	NOT NULL,
  BedConfiguration	varchar(30)	NOT NULL
)

CREATE TABLE HotelRoomType
( HotelRoomTypeID	smallint	IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  HotelID	smallint	NOT NULL,
  Roomtype	varchar(20)	NOT NULL,
  RackRoomRate	smallmoney	NOT NULL,
  RoomTypeDescription	varchar(200)
)

CREATE TABLE ReservationDetailBilling
( RevenueDetailsID	smallint	IDENTITY(1,1) NOT NULL	PRIMARY KEY,
  ReservationDetailID	smallint	NOT NULL,
  ItemCategory	varchar(15)	NOT NULL,
  ItemAmount	smallmoney	NOT NULL,
  ItemDate	smalldatetime	NOT NULL,
  ItemComments	varchar(200),
  RevenueID	smallint	NOT NULL,
)

CREATE TABLE Discount
( DiscountID	smallint	IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  Description	varchar(50)	NOT NULL,
  Expiration	smalldatetime	NOT NULL,
  Rules	varchar(100),
  Percentage	decimal(4,2),
  CouponAmount	smallmoney
)

CREATE TABLE Revenue
( RevenueID smallint IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  RevenueType varchar(15)	NOT NULL,
  RevenuePaymentDate	smalldatetime,
  RevenuePaymentType	varchar(10),
  Revenuecomments	varchar(200)
)

CREATE TABLE TaxRate
( TaxLocationID	smallint	IDENTITY(1,1)	NOT NULL	PRIMARY KEY,
  TaxDescription	varchar(30)	NOT NULL,
  TaxRate	decimal(6,4)	NOT NULL
)

CREATE TABLE Hotel
( HotelID	smallint	NOT NULL	PRIMARY KEY,
  HotelName	varchar(30)	NOT NULL,
  HotelAddress	varchar(30)	NOT NULL,
  HotelCity	varchar(20)	NOT NULL,
  HotelState	char(2),
  HotelCountry	varchar(20)	NOT NULL,
  HotelPostalCode	varchar(10)	NOT NULL,
  HotelStarRating	char(1),
  HotelPictureLink	varchar(100),
  TaxLocationID	smallint	NOT NULL
)

ALTER TABLE CreditCard
ADD CONSTRAINT FK_CreditCardMustHaveGuest
FOREIGN KEY (GuestID) REFERENCES Guest(GuestID)

ALTER TABLE Reservation
ADD CONSTRAINT FK_ReservationMustHaveCC
FOREIGN KEY (CreditCardID) REFERENCES CreditCard(CreditCardID)

ALTER TABLE ReservationDetail
ADD CONSTRAINT FK_ReservationDetailMustHaveRoom
FOREIGN KEY (RoomID) REFERENCES Room(RoomID)

ALTER TABLE ReservationDetail
ADD CONSTRAINT FK_ReservationDetailMustHaveReservation
FOREIGN KEY (ReservationID) REFERENCES Reservation(ReservationID)

ALTER TABLE ReservationDetail
ADD CONSTRAINT FK_ReservationDetailMustHaveDiscount
FOREIGN KEY (DiscountID) REFERENCES Discount(DiscountID)

ALTER TABLE ReservationDetailBilling
ADD CONSTRAINT FK_ReservationDetailBillingMustHaveRevenue
FOREIGN KEY (RevenueID) REFERENCES Revenue(RevenueID)

ALTER TABLE Room
ADD CONSTRAINT FK_RoomMustHaveRoomType
FOREIGN KEY (HotelRoomTypeID) REFERENCES HotelRoomType(HotelRoomTypeID)

ALTER TABLE HotelRoomType
ADD CONSTRAINT FK_HotelRoomTypeMustHaveHotel
FOREIGN KEY (HotelID) REFERENCES Hotel(HotelID)

ALTER TABLE Hotel
ADD CONSTRAINT FK_HotelMustHaveTaxRate
FOREIGN KEY (TaxLocationID) REFERENCES TaxRate(TaxLocationID)

ALTER TABLE ReservationDetailBilling
ADD CONSTRAINT FK_ReservationDetailBillingMustHaveReservationDetail
FOREIGN KEY (ReservationDetailID) REFERENCES ReservationDetail(ReservationDetailID)
