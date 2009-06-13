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
    public partial class Withdraw_UserControl : ATM.WIN.MainPanel_BaseUserControl
    {
        public Withdraw_UserControl()
        {
            InitializeComponent();
        }

        public Withdraw_UserControl(Main owner)
            : base(owner)
        {
            InitializeComponent();
        }

        protected override void Repaint(object sender, EventArgs e)
        {
            List<String> account_types = new List<string>();
            if (this.owner.CAccount != null) account_types.Add("Checking");
            if (this.owner.SAccount != null) account_types.Add("Savings");
            this.account_type_dropdown.DataSource = account_types;
        }

        private void withdraw_button_Click(object sender, EventArgs e)
        {
            decimal amount = 0;
            try
            {
                amount = decimal.Parse(this.amount_withdraw_box.Text);
            }
            catch (Exception err)
            { this.errorProvider1.SetError(this.amount_withdraw_box, "Invalid amount set"); return; }
            String type = this.account_type_dropdown.Text;
            Account a = new Account();
            if (type.Equals("Checking"))
                a = this.owner.CAccount;
            else if (type.Equals("Savings"))
                a = this.owner.SAccount;
            a.Balance -= amount;
            this.errorProvider1.Clear();
            this.owner.UpdateAccounts();

            MessageBox.Show("Withdrawal completed successfully!");
        }
    }
}

