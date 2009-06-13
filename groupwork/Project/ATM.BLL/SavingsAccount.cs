using System;
using System.Collections.Generic;
using System.Text;

namespace ATM.BLL
{
    public class SavingsAccount : Account
    {
        public SavingsAccount(){}
        public SavingsAccount(SavingsAccount copy) 
             :base(copy)
        {
        }
        
        public SavingsAccount (int acctNum, decimal bal):base(acctNum, bal)
	    {
	    }
        
	    public override string ToString()
        {
            //return string.Format("{0} Savings - {1:c}", AccountNumber, Balance);
            return "Savings";
	    }
        

    }
}
