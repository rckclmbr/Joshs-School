using System;
using System.Collections.Generic;
using System.Text;

namespace ATM.BLL
{
    public class CheckingAccount : Account
    {
        public CheckingAccount(){}
        public CheckingAccount(CheckingAccount copy) 
             :base(copy)
        {
        }

        public CheckingAccount(int acctNum, decimal bal)
            : base(acctNum, bal)
	    {
	    }

        
	    public override string ToString()
        {
            //return string.Format("{0} Checking - {1:c}", AccountNumber, Balance);
            return "Checking";
	    }
        

    }
}
