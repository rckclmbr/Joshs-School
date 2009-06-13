using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ATM.WIN
{
    public partial class Balance_UserControl : ATM.WIN.MainPanel_BaseUserControl
    {
        public Balance_UserControl()
        {
            InitializeComponent();
        }
        public Balance_UserControl(Main owner) : base(owner)
        {
            InitializeComponent();
        }

        protected override void Repaint(object sender, EventArgs e)
        {
            if (this.owner.SAccount != null)
            {
                this.savings_balance_box.Show();
                this.savings_balance_label.Show();
                this.savings_balance_box.Text = this.owner.SAccount.Balance.ToString("C");
            }
            else
            {
                this.savings_balance_box.Hide();
                this.savings_balance_label.Hide();
            }
            if (this.owner.CAccount != null)
            {
                this.checking_balance_label.Show();
                this.checking_balance_box.Show();
                this.checking_balance_box.Text = this.owner.CAccount.Balance.ToString("C");
            }
            else
            {
                this.checking_balance_label.Hide();
                this.checking_balance_box.Hide();
            }
        }

    }
}

