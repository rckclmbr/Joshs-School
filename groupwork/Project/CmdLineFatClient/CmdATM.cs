using System;
using System.Collections.Generic;
using System.Text;
using ATM.BLL;
using ATM.DAL;

namespace CmdLineFatClient
{
    class CmdATM
    {
        private static CustomerDB customerDB = new CustomerDB();
        private static Customer customer = null;

        static void Main(string[] args)
        {
            while (1 == 1)
            {
                short menuItem = 0;
                System.Console.WriteLine("***** ATM System *****");
                System.Console.WriteLine();
                customer = Login();
                while (customer.CustomerNumber < 1)
                {
                    customer = Login();
                }
                System.Console.WriteLine();
                while (menuItem != -1)
                {
                    menuItem = MainMenu();
                    switch (menuItem)
                    {
                        case 1:
                            Balances();
                            break;

                        case 2:
                            Withdraw();
                            break;

                        case 3:
                            Deposit();
                            break;

                        case 4:
                            Transfer();
                            break;

                        case 5:
                            menuItem = -1;
                            break;

                        default:
                            System.Console.WriteLine();
                            System.Console.WriteLine("***** Invalid Entry *****");
                            System.Console.WriteLine();
                            break;
                    }
                }
            }
        }

        private static Customer Login()
        {
            string userId = string.Empty;
            string pin = string.Empty;
            short nPin = 0;

            System.Console.WriteLine("Please log in");
            System.Console.WriteLine("User ID: ");
            userId = System.Console.ReadLine();
            System.Console.WriteLine("Password: ");
            pin = System.Console.ReadLine();
            if (Int16.TryParse(pin, out nPin) == false)
            {
                return null;
            }

            Customer customer = customerDB.GetCustomer(userId, nPin);
            if (customer.CustomerNumber > 0 && customer.Status == ObjectStatus.Clean)
            {
                return customer;
            }
            else
            {
                System.Console.WriteLine("***** Login Error *****");
                return customer;
            }
        }

        private static short MainMenu()
        {
            string selection = string.Empty;
            short nSelection = 0;
            while (nSelection == 0)
            {
                System.Console.WriteLine("1. Balances");
                System.Console.WriteLine("2. Withdraw");
                System.Console.WriteLine("3. Deposit");
                System.Console.WriteLine("4. Transfer");
                System.Console.WriteLine("5. Log out");
                System.Console.WriteLine();
                System.Console.WriteLine("Make a selection:");
                selection = System.Console.ReadLine();

                if (Int16.TryParse(selection, out nSelection) == false || nSelection < 1 || nSelection > 5)
                {
                    nSelection = 0;
                }
            }
            return nSelection;
        }
        private static void Transfer()
        {
            throw new Exception("The Transfer method is not implemented.");
        }

        private static void Deposit()
        {
            throw new Exception("The Deposit method is not implemented.");
        }

        private static void Withdraw()
        {
            throw new Exception("The Withdraw method is not implemented.");
        }

        private static void Balances()
        {
            System.Console.WriteLine();
            foreach (Account account in customer.Accounts)
            {
                System.Console.WriteLine(account.ToString());
            }
            System.Console.WriteLine();
            System.Console.WriteLine();
        }

    }
}
