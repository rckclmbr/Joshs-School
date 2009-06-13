using System;
using System.Collections.Generic;
using System.Text;

namespace ATM.BLL
{
    public abstract class Transaction : BaseObject
    {
        private int _id = 0;
        private double _amount = 0.0;
        private DateTime _transactionDate = DateTime.Now;

        public Transaction()
        {

        }

        public Transaction(Transaction copy)
            : base(copy)
        {
            _id = copy.ID;
            _amount = copy.Amount;
            _transactionDate = copy.TransactionDate;
        }

        public Transaction(int id, double amount, DateTime transactionDate)
            : base(ObjectStatus.New)
        {
            _id = id;
            _amount = amount;
            _transactionDate = transactionDate;
        }

        public DateTime TransactionDate
        {
            get { return _transactionDate; }
            set
            {
                if (!_transactionDate.Equals(value))
                {
                    _transactionDate = value;
                    dirty();
                }
            }
        }
	
        public double Amount
        {
            get { return _amount; }
            set
            {
                if (!_amount.Equals(value))
                {
                    _amount = value;
                    dirty();
                }
            }
        }
	
        public int ID
        {
            get { return _id; }
        }
	
    }
}
