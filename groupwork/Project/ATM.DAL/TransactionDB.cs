using System;
using System.Collections.Generic;
using System.Text;
using ATM.BLL;
using ATM.DAL.ATMTableAdapters;

namespace ATM.DAL
{
    #region Class TransactionDB
    public class TransactionDB
    {
        #region Declarations
        private TransactionTableAdapter _transactionAdapter = null;
        #endregion Declarations

        #region Properties
        protected TransactionTableAdapter TranactionAdapter
        {
            get
            {
                if (_transactionAdapter == null)
                {
                    _transactionAdapter = new TransactionTableAdapter();
                }
                return _transactionAdapter;
            }
        }
        #endregion Properties

        #region Methods
        public void SaveTranaction(decimal amount, Account account)
        {
            AccountType accountType = AccountType.None;
            TransactionType transactionType = TransactionType.None;

            if (account is CheckingAccount)
            {
                accountType = AccountType.Checking;
            }
            else if (account is SavingsAccount)
            {
                accountType = AccountType.Savings;
            }

            if (amount > 0)
            {
                transactionType = TransactionType.Credit;
            }
            else if (amount < 0)
            {
                transactionType = TransactionType.Debit;
                amount *= -1;
            }
            
            if ((amount != 0) && (account != null))
            {
                TranactionAdapter.Insert(
                            account.AccountNumber,
                            (short)accountType,
                            DateTime.Now,
                            amount,
                            (short)transactionType);
            }
        }
        #endregion Methods
    }
    #endregion Class TransactionDB
}
