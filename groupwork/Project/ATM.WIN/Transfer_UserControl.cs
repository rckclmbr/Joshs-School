using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ATM.BLL;
using ATM.DAL;

namespace ATM.WIN
{
    public partial class Transfer_UserControl : ATM.WIN.MainPanel_BaseUserControl
    {
        private CustomerDB customerDB = new CustomerDB();   // We need this because the parent doesn't
                                                            // know how to save the to account

        public Transfer_UserControl()
        {
            InitializeComponent();
        }

        public Transfer_UserControl(Main owner)
            : base(owner)
        {
            InitializeComponent();
        }

        protected override void Repaint(object sender, EventArgs e)
        {
            List<Account> account_types = new List<Account>();

            account_types.Add(this.owner.CAccount);
            account_types.Add(this.owner.SAccount);

            this.transfer_from_type_box.DataSource = account_types;

            this.transfer_to_account_box.DataSource = this.owner.Customer.AccountNumbers;
        }

        private void transfer_to_account_box_SelectedIndexChanged(object sender, EventArgs e)
        {
            // populate the account type box

            // Get what they changed it to
            String acctNum = this.transfer_to_account_box.Text;
            List<Account> acct_types = new List<Account>();

            foreach (Account i in this.owner.Customer.Accounts)
            {
                if (i.AccountNumber.ToString() == acctNum)
                   acct_types.Add(i);
            }
            this.transfer_to_type_box.DataSource = acct_types;
    
        }

        private void transfer_button_Click(object sender, EventArgs e)
        {
            // Do the transfer crap
            Account fromAcct = (Account)this.transfer_from_type_box.SelectedValue;
            Account toAcct = (Account)this.transfer_to_type_box.SelectedValue;

            decimal amount = 0;
            try
            {
                amount = decimal.Parse(this.transfer_amount_textbox.Text);
            }
            catch (Exception err)
            { this.errorProvider1.SetError(this.transfer_amount_textbox, "Invalid amount set"); return; }


            toAcct.Balance += amount;
            fromAcct.Balance -= amount;

            this.errorProvider1.Clear();
            this.owner.UpdateAccounts();    // Updates "From Account"
            customerDB.SaveAccount(toAcct); // Owner doesn't update this account


            MessageBox.Show("Transfer completed successfully!");
        }
    }
}

