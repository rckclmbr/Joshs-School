using System;
using System.Collections.Generic;
using System.Text;

namespace ATM.BLL
{
    public class Customer : BaseObject
    {
        private int customerNumber;
        private List<Account> accounts = new List<Account>();
        private string firstName = string.Empty;
        private string lastName = string.Empty;

        public Customer()
        {

        }

        public Customer(int cust, string fname, string lname)
        {
            CustomerNumber = cust;
            FirstName = fname;
            LastName = lname;
        }

        public int CustomerNumber{
            get { return customerNumber; }
            set
            {
                dirty();
                customerNumber = value;
            }
        }
        public string FirstName
        {
            get
            {
                return firstName;
            }
            set
            {
                dirty();
                firstName = value;
            }
        }
        public string LastName
        {
            get
            {
                return lastName;
            }
            set
            {
                dirty();
                lastName = value;
            }
        }

        public List<Account> Accounts
        {
            get
            {
                return accounts;
            }
            set
            {
                accounts = value;
            }
        }

        public List<String> AccountNumbers
        {
            get
            {
                List<String> accountNums = new List<String>();
                // Only get distinct account numbers
                foreach(Account i in this.accounts) {
                       if(! accountNums.Contains(i.AccountNumber.ToString()))
                           accountNums.Add(i.AccountNumber.ToString());
                }
                return accountNums;
            }
        }
    
    }
}
