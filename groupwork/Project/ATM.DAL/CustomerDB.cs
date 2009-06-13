using System;
using System.Collections.Generic;
using System.Text;
using ATM.BLL;
using ATM.DAL.ATMTableAdapters;

namespace ATM.DAL
{
    #region Class CustomerDB
    public class CustomerDB
    {
        #region Declarations
        private CustomerTableAdapter _customerAdapter = null;
        private AccountTableAdapter _accountAdapter = null;
        #endregion Declarations

        #region Properties
        protected CustomerTableAdapter CustomerAdapter
        {
            get
            {
                if (_customerAdapter == null)
                    _customerAdapter = new CustomerTableAdapter();

                return _customerAdapter;
            }
        }

        protected AccountTableAdapter AccountAdapter
        {
            get
            {
                if (_accountAdapter == null)
                    _accountAdapter = new AccountTableAdapter();

                return _accountAdapter;
            }
        }       

        #endregion Properties

        #region Methods
        public Customer GetCustomerObject(string userId, short pin)
        {
            ATM.CustomerDataTable customerTable = CustomerAdapter.GetCustomerBySecureInfo(userId, pin);
            if (customerTable.Count == 0)
            {
                return new Customer();
            }
            Customer customer = new Customer(customerTable[0].CustomerNumber, customerTable[0].FirstName, customerTable[0].LastName);
            customer.Status = ObjectStatus.Clean;
            return customer;
        }

        public Customer GetCustomer(string userId, short pin)
        {
            Customer customer = new Customer();
            ATM.CustomerDataTable customerTable = CustomerAdapter.GetCustomerBySecureInfo(userId, pin);

            if (customerTable.Count == 0)
            {
                return customer;
            }
            return createCustomer(customerTable[0]);
        }

        public void SaveAccount(Account account)
        {
            if (account != null)
            {
                ATM.AccountDataTable accountDataTable = AccountAdapter.GetAccountByAccountNumber(account.AccountNumber);
                ATM.AccountRow accountRow = (ATM.AccountRow)accountDataTable.Rows[0];
                if (account is SavingsAccount)
                {
                    accountRow.SavingsBalance = account.Balance;
                }
                else if (account is CheckingAccount)
                {
                    accountRow.Checking_Balance = account.Balance;
                }
                AccountAdapter.Update(accountDataTable);
            }
        }

        public List<Account> GetAccounts(int customerNumber)
        {
            List<Account> accounts = new List<Account>();

            ATM.AccountDataTable accountTable = AccountAdapter.GetAccountsByCustomerNumber(customerNumber);
            foreach (ATM.AccountRow row in accountTable)
            {
                accounts.AddRange(createAccount(row));
            }
            return accounts;
        }

        protected Customer createCustomer(ATM.CustomerRow customerRow)
        {
            Customer customer = new Customer(customerRow.CustomerNumber, customerRow.FirstName, customerRow.LastName);
            customer.Status = ObjectStatus.Clean;

            ATM.AccountDataTable accountTable = AccountAdapter.GetAccountsByCustomerNumber(customer.CustomerNumber);
            foreach (ATM.AccountRow row in accountTable)
            {
                customer.Accounts.AddRange(createAccount(row));
            }
            return customer;
        }

        /// <summary>
        /// Creates the account.
        /// </summary>
        /// <param name="accountRow">The account row.</param>
        /// <returns></returns>
        protected List<Account> createAccount(ATM.AccountRow accountRow)
        {
            List<Account> accounts = new List<Account>();

            if (accountRow.AccountType == (short)AccountType.Both || accountRow.AccountType == (short)AccountType.Checking)
            {
                CheckingAccount checking = new CheckingAccount(accountRow.AccountNumber, accountRow.Checking_Balance);
                checking.Status = ObjectStatus.Clean;
                accounts.Add(checking);
            }
            if (accountRow.AccountType == (short)AccountType.Both || accountRow.AccountType == (short)AccountType.Savings)
            {
                SavingsAccount savings = new SavingsAccount(accountRow.AccountNumber, accountRow.SavingsBalance);
                savings.Status = ObjectStatus.Clean;
                accounts.Add(savings);
            }
            return accounts;
        }

        #endregion Methods
    }
    #endregion Class CustomerDB
}
