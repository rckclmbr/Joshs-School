using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ATM.BLL;

namespace ATM.WIN
{
    public partial class Deposit_UserControl : ATM.WIN.MainPanel_BaseUserControl
    {
        #region constructors
        public Deposit_UserControl()
        {
            InitializeComponent();
        }

        public Deposit_UserControl(Main owner)
            : base(owner)
        {
            InitializeComponent();
        }
        #endregion constructors

        protected override void Repaint(object sender, EventArgs e)
        {
            List<Account> account_types = new List<Account>();
            account_types.Add(this.owner.CAccount);
            account_types.Add(this.owner.SAccount);
            this.account_type_dropdown.DataSource = account_types;
        }

        private void deposit_button_Click(object sender, EventArgs e)
        {
            decimal amount = 0;
            try
            {
                amount = decimal.Parse(this.amount_deposit_box.Text);
            }
            catch (Exception err)
            { this.errorProvider1.SetError(this.amount_deposit_box, "Invalid amount set"); return; }
            Account a = (Account)this.account_type_dropdown.SelectedItem;
            a.Balance += amount;
            this.errorProvider1.Clear();
            this.owner.UpdateAccounts();

            MessageBox.Show("Deposit completed successfully!");

           
        }
    }
}

