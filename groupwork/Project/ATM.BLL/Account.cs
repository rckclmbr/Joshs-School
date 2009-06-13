using System;
using System.Collections.Generic;
using System.Text;

namespace ATM.BLL
{
    public class Account : BaseObject
     {
        private int accountNumber;
        private decimal balance;

        public Account() { }

        public Account(int accountNumber, decimal balance)
        {
            this.accountNumber = accountNumber;
            this.balance = balance;
        }

        public Account(Account copy) 
            :base(copy)
        {
            this.accountNumber = copy.AccountNumber;
            this.balance = copy.Balance;
        }

        public decimal Balance          //Not sure on this one.
        {
            get { return this.balance; }
            set
            {
                dirty();
                this.balance = value;
            }
        }

        public int AccountNumber
        {
            get { return this.accountNumber; }
            set 
            {
                dirty();
                this.accountNumber = value; 
            }
		}
    }
}
